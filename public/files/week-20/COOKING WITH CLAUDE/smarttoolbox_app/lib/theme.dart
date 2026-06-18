import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';

/// Design tokens from the Claude Design bundle — LIGHT theme, TEAL accent.
class C {
  static const bg = Color(0xFFEEF1F5);
  static const bg2 = Color(0xFFFFFFFF);
  static const surface = Color(0xFFFFFFFF);
  static const surface2 = Color(0xFFF1F4F8);
  static const surface3 = Color(0xFFE0E6EE);
  static const border = Color(0x1A10161E); // rgba(16,22,30,.10)
  static const text = Color(0xFF0F141A);
  static const textDim = Color(0xFF586273);
  static const textFaint = Color(0xFF98A2AF);
  static const green = Color(0xFF16A34A);
  static const red = Color(0xFFDC2626);
  static const amber = Color(0xFFD97706);
  static const accent = Color(0xFF2DD4BF);
  static const accentInk = Color(0xFF08120F);

  // gradient flourish (logo / hairline)
  static const grad1 = Color(0xFF2DD4BF);
  static const grad2 = Color(0xFF38BDF8);
  static const grad3 = Color(0xFF8B5CF6);
}

/// Spacing / density — COMFORTABLE.
class S {
  static const pad = 16.0;
  static const gap = 12.0;
  static const cardPad = 14.0;
  static const toolH = 116.0;
  static const r = 14.0;
  static const rSm = 10.0;
}

TextStyle mono({
  double size = 12,
  Color color = C.textFaint,
  FontWeight weight = FontWeight.w500,
  double spacing = 0.3,
}) =>
    GoogleFonts.jetBrainsMono(
        fontSize: size, color: color, fontWeight: weight, letterSpacing: spacing);

ThemeData buildTheme() {
  final scheme = ColorScheme.fromSeed(
    seedColor: C.accent,
    brightness: Brightness.light,
  ).copyWith(
    primary: C.accent,
    surface: C.surface,
    error: C.red,
    onSurface: C.text,
  );

  final base = ThemeData(
    useMaterial3: true,
    brightness: Brightness.light,
    scaffoldBackgroundColor: C.bg,
    colorScheme: scheme,
    splashFactory: InkSparkle.splashFactory,
  );

  return base.copyWith(
    textTheme: GoogleFonts.plusJakartaSansTextTheme(base.textTheme)
        .apply(bodyColor: C.text, displayColor: C.text),
    appBarTheme: const AppBarTheme(
      backgroundColor: C.bg,
      surfaceTintColor: Colors.transparent,
      elevation: 0,
    ),
  );
}

/// Initials from a name, e.g. "Nadec Biju" -> "NB".
String initialsOf(String name) {
  final parts = name.trim().split(RegExp(r'\s+'));
  final a = parts.isNotEmpty && parts[0].isNotEmpty ? parts[0][0] : '';
  final b = parts.length > 1 && parts[1].isNotEmpty ? parts[1][0] : '';
  return (a + b).toUpperCase();
}

/// Mask a UID to its last two octets: AA:13:7F:02:5C -> ··:02:5C
String maskUid(String uid) {
  final octets = uid.split(':');
  if (octets.length < 2) return uid;
  return '··:${octets.sublist(octets.length - 2).join(':')}';
}

/// Stable avatar color from a name (design uses per-user colors).
Color colorFromName(String name) {
  const palette = [
    C.accent,
    Color(0xFF8B5CF6),
    Color(0xFFF59E0B),
    Color(0xFF38BDF8),
    Color(0xFFF472B6),
    Color(0xFF16A34A),
  ];
  var h = 0;
  for (final c in name.codeUnits) {
    h = (h * 31 + c) & 0x7fffffff;
  }
  return palette[h % palette.length];
}
