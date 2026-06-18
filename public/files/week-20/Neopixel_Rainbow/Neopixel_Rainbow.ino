// Travelling rainbow on a WS2812 / NeoPixel strip
// Board:    Seeed XIAO ESP32-C6
// Data pin: D0  (GPIO0)
//
// Wiring:
//   strip DIN  -> XIAO D0          (a 330-470 ohm series resistor in line is safer
//                                   but optional for short jumper leads)
//   strip GND  -> XIAO GND  AND  external supply GND  (common ground is mandatory)
//   strip 5V   -> external 5 V supply if the strip has more than ~8 LEDs.
//                 If you only have a handful of pixels you can power the strip from
//                 the XIAO's 5V pin temporarily, but a real strip needs its own PSU.
//
// Behaviour: hue sweeps across all pixels and animates forward forever.

#include <Adafruit_NeoPixel.h>

#define LED_PIN     D0          // XIAO silkscreen D0 -> GPIO0
#define NUM_LEDS    117         // <-- change this if your strip is a different length
#define BRIGHTNESS  128         // 0-255. Strip is on a 12V/5A supply + buck converter,
                                // so we can push it. Capped at 128 because all-white
                                // at full brightness on 117 LEDs would draw ~7A and the
                                // supply is rated 5A.

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

uint16_t hueOffset = 0;         // animation phase, advances every frame

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();                 // start with all pixels off
  delay(300);
  Serial.println();
  Serial.print("NeoPixel rainbow running on D0 (GPIO0), ");
  Serial.print(NUM_LEDS);
  Serial.println(" pixels.");
}

void loop() {
  // Spread one full colour wheel (65536 in 16-bit hue) across the strip,
  // then shift the starting hue every frame so the rainbow appears to crawl.
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    uint16_t pixelHue = hueOffset + (i * 65536UL / NUM_LEDS);
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
  }
  strip.show();
  hueOffset += 256;             // step size = animation speed. Bigger = faster.
  delay(20);                    // frame delay in ms.   Smaller = faster + smoother.
}
