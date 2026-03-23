from __future__ import annotations

from pathlib import Path

import numpy as np
from PIL import Image, ImageDraw, ImageFilter, ImageFont


ROOT = Path(__file__).resolve().parents[1]
STATIC_DIR = ROOT / "static"


def _load_font(px: int) -> ImageFont.FreeTypeFont:
    # Prefer a local Windows font for a crisp iOS-ish monogram.
    candidates = [
        Path(r"C:\Windows\Fonts\segoeuib.ttf"),
        Path(r"C:\Windows\Fonts\SegUIVar.ttf"),
        Path(r"C:\Windows\Fonts\segoeui.ttf"),
    ]
    for p in candidates:
        if p.exists():
            return ImageFont.truetype(str(p), px)
    return ImageFont.load_default()


def make_base(size: int = 1024) -> Image.Image:
    x = np.linspace(0.0, 1.0, size, dtype=np.float32)
    y = np.linspace(0.0, 1.0, size, dtype=np.float32)
    xx, yy = np.meshgrid(x, y)

    # Diagonal blue->purple blend + warm accent blob.
    t = (xx * 0.55 + yy * 0.45).clip(0.0, 1.0)
    c1 = np.array([10.0, 132.0, 255.0], dtype=np.float32)  # iOS blue
    c2 = np.array([191.0, 90.0, 242.0], dtype=np.float32)  # iOS purple
    base = (c1 * (1.0 - t[..., None]) + c2 * (t[..., None])).astype(np.float32)

    # Warm highlight near bottom (subtle).
    blob = np.exp(-(((xx - 0.55) ** 2) / (2 * 0.18**2) + ((yy - 1.05) ** 2) / (2 * 0.22**2))).astype(np.float32)
    warm = np.array([255.0, 159.0, 10.0], dtype=np.float32)
    base = base + (warm - base) * (blob[..., None] * 0.22)

    # Tiny noise to avoid flat gradients.
    rng = np.random.default_rng(20260205)
    noise = rng.normal(0.0, 1.0, size=(size, size, 1)).astype(np.float32)
    base = (base + noise * 3.0).clip(0.0, 255.0)

    img = Image.fromarray(base.astype(np.uint8), mode="RGB").convert("RGBA")

    # Soft specular highlight.
    overlay = Image.new("RGBA", (size, size), (255, 255, 255, 0))
    d = ImageDraw.Draw(overlay)
    d.ellipse(
        (-size * 0.25, -size * 0.35, size * 1.1, size * 0.55),
        fill=(255, 255, 255, 55),
    )
    overlay = overlay.filter(ImageFilter.GaussianBlur(radius=size * 0.06))
    img = Image.alpha_composite(img, overlay)

    return img


def add_monogram(img: Image.Image, text: str = "NB") -> Image.Image:
    size = img.size[0]
    font = _load_font(int(size * 0.42))
    draw = ImageDraw.Draw(img)

    bbox = draw.textbbox((0, 0), text, font=font)
    w, h = bbox[2] - bbox[0], bbox[3] - bbox[1]
    x = (size - w) // 2
    y = int(size * 0.52 - h / 2)

    # Shadow
    shadow = Image.new("RGBA", img.size, (0, 0, 0, 0))
    sd = ImageDraw.Draw(shadow)
    sd.text((x, y + int(size * 0.015)), text, font=font, fill=(0, 0, 0, 110))
    shadow = shadow.filter(ImageFilter.GaussianBlur(radius=size * 0.02))
    img = Image.alpha_composite(img, shadow)

    # Text
    draw = ImageDraw.Draw(img)
    draw.text((x, y), text, font=font, fill=(255, 255, 255, 235))
    return img


def export_all(base: Image.Image) -> None:
    STATIC_DIR.mkdir(parents=True, exist_ok=True)

    def save_png(name: str, px: int) -> None:
        out = base.resize((px, px), resample=Image.Resampling.LANCZOS)
        out.save(STATIC_DIR / name, format="PNG", optimize=True)

    # Full-size PNG (nice for PWA and modern browsers)
    save_png("favicon.png", 512)
    save_png("apple-touch-icon.png", 180)
    save_png("favicon-32x32.png", 32)
    save_png("favicon-16x16.png", 16)

    # Classic ICO
    ico = base.resize((256, 256), resample=Image.Resampling.LANCZOS)
    ico.save(
        STATIC_DIR / "favicon.ico",
        sizes=[(16, 16), (32, 32), (48, 48), (64, 64), (128, 128), (256, 256)],
        format="ICO",
    )


def main() -> None:
    base = make_base(1024)
    base = add_monogram(base, "NB")
    export_all(base)
    print("Wrote favicon assets to:", STATIC_DIR)


if __name__ == "__main__":
    main()

