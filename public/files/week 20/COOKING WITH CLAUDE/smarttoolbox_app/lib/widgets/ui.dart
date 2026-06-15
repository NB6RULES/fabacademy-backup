import 'package:flutter/material.dart';
import '../theme.dart';

/// ── status dot with soft glow ──────────────────────────────
class StatusDot extends StatelessWidget {
  final Color color;
  final double size;
  const StatusDot({super.key, this.color = C.green, this.size = 10});

  static Color kindColor(String kind) => kind == 'present'
      ? C.green
      : kind == 'accent'
          ? C.accent
          : C.red;

  @override
  Widget build(BuildContext context) {
    return Container(
      width: size,
      height: size,
      decoration: BoxDecoration(
        shape: BoxShape.circle,
        color: color,
        boxShadow: [
          BoxShadow(color: color.withValues(alpha: 0.22), spreadRadius: 3),
          BoxShadow(color: color.withValues(alpha: 0.65), blurRadius: 10),
        ],
      ),
    );
  }
}

/// ── pill / chip ────────────────────────────────────────────
enum ChipTone { neutral, green, red, amber, accent }

class AppChip extends StatelessWidget {
  final String label;
  final ChipTone tone;
  final bool small;
  final bool solid;
  final IconData? icon;
  const AppChip(this.label,
      {super.key,
      this.tone = ChipTone.neutral,
      this.small = false,
      this.solid = false,
      this.icon});

  @override
  Widget build(BuildContext context) {
    final (fg, bg, bd) = switch (tone) {
      ChipTone.green => (C.green, C.green.withValues(alpha: 0.14), C.green.withValues(alpha: 0.30)),
      ChipTone.red => (C.red, C.red.withValues(alpha: 0.14), C.red.withValues(alpha: 0.30)),
      ChipTone.amber => (C.amber, C.amber.withValues(alpha: 0.16), C.amber.withValues(alpha: 0.32)),
      ChipTone.accent => (C.accent, C.accent.withValues(alpha: 0.15), C.accent.withValues(alpha: 0.32)),
      ChipTone.neutral => (C.textDim, C.surface2, C.border),
    };
    return Container(
      padding: EdgeInsets.symmetric(horizontal: small ? 7 : 10, vertical: small ? 2 : 4),
      decoration: BoxDecoration(
        color: solid ? C.accent : bg,
        borderRadius: BorderRadius.circular(999),
        border: Border.all(color: solid ? Colors.transparent : bd),
      ),
      child: Row(
        mainAxisSize: MainAxisSize.min,
        children: [
          if (icon != null) ...[
            Icon(icon, size: small ? 12 : 13, color: solid ? C.accentInk : fg),
            const SizedBox(width: 5),
          ],
          Text(label,
              style: TextStyle(
                  fontSize: small ? 11 : 12,
                  fontWeight: FontWeight.w600,
                  color: solid ? C.accentInk : fg)),
        ],
      ),
    );
  }
}

/// ── avatar (initials, gradient) ────────────────────────────
class Avatar extends StatelessWidget {
  final String name;
  final Color? color;
  final double size;
  const Avatar({super.key, required this.name, this.color, this.size = 36});

  @override
  Widget build(BuildContext context) {
    final c = color ?? colorFromName(name);
    return Container(
      width: size,
      height: size,
      alignment: Alignment.center,
      decoration: BoxDecoration(
        shape: BoxShape.circle,
        gradient: LinearGradient(
          begin: Alignment.topLeft,
          end: Alignment.bottomRight,
          colors: [c, Color.lerp(c, Colors.black, 0.4)!],
        ),
        boxShadow: [BoxShadow(color: c.withValues(alpha: 0.4), spreadRadius: 0.5)],
      ),
      child: Text(initialsOf(name),
          style: TextStyle(
              color: Colors.white,
              fontWeight: FontWeight.w700,
              fontSize: size * 0.38)),
    );
  }
}

/// ── card ───────────────────────────────────────────────────
class AppCard extends StatelessWidget {
  final Widget child;
  final VoidCallback? onTap;
  final EdgeInsetsGeometry? padding;
  const AppCard({super.key, required this.child, this.onTap, this.padding});

  @override
  Widget build(BuildContext context) {
    final content = Container(
      padding: padding ?? const EdgeInsets.all(S.cardPad),
      decoration: BoxDecoration(
        color: C.surface,
        borderRadius: BorderRadius.circular(S.r),
        border: Border.all(color: C.border),
      ),
      child: child,
    );
    if (onTap == null) return content;
    return Material(
      color: Colors.transparent,
      borderRadius: BorderRadius.circular(S.r),
      child: InkWell(
        onTap: onTap,
        borderRadius: BorderRadius.circular(S.r),
        child: content,
      ),
    );
  }
}

/// ── segmented control ──────────────────────────────────────
class Segmented<T> extends StatelessWidget {
  final List<(T, String)> options;
  final T value;
  final ValueChanged<T> onChange;
  const Segmented(
      {super.key, required this.options, required this.value, required this.onChange});

  @override
  Widget build(BuildContext context) {
    return Container(
      padding: const EdgeInsets.all(3),
      decoration: BoxDecoration(
        color: C.surface2,
        borderRadius: BorderRadius.circular(999),
        border: Border.all(color: C.border),
      ),
      child: Row(
        children: [
          for (final (val, label) in options)
            Expanded(
              child: GestureDetector(
                onTap: () => onChange(val),
                child: AnimatedContainer(
                  duration: const Duration(milliseconds: 150),
                  padding: const EdgeInsets.symmetric(vertical: 7),
                  alignment: Alignment.center,
                  decoration: BoxDecoration(
                    color: val == value ? C.accent : Colors.transparent,
                    borderRadius: BorderRadius.circular(999),
                  ),
                  child: Text(label,
                      style: TextStyle(
                          fontSize: 12.5,
                          fontWeight: FontWeight.w600,
                          color: val == value ? C.accentInk : C.textDim)),
                ),
              ),
            ),
        ],
      ),
    );
  }
}

/// ── filter chips (scroll row) ──────────────────────────────
class FilterChipsRow<T> extends StatelessWidget {
  final List<(T, String)> options;
  final T value;
  final ValueChanged<T> onChange;
  const FilterChipsRow(
      {super.key, required this.options, required this.value, required this.onChange});

  @override
  Widget build(BuildContext context) {
    return SingleChildScrollView(
      scrollDirection: Axis.horizontal,
      child: Row(
        children: [
          for (final (val, label) in options) ...[
            GestureDetector(
              onTap: () => onChange(val),
              child: Container(
                padding: const EdgeInsets.symmetric(horizontal: 13, vertical: 7),
                decoration: BoxDecoration(
                  color: val == value ? C.accent : C.surface,
                  borderRadius: BorderRadius.circular(999),
                  border: Border.all(color: val == value ? Colors.transparent : C.border),
                ),
                child: Text(label,
                    style: TextStyle(
                        fontSize: 12.5,
                        fontWeight: FontWeight.w600,
                        color: val == value ? C.accentInk : C.textDim)),
              ),
            ),
            const SizedBox(width: 8),
          ],
        ],
      ),
    );
  }
}

/// ── button ─────────────────────────────────────────────────
enum BtnVariant { primary, secondary, ghost, danger }

class AppButton extends StatelessWidget {
  final String label;
  final VoidCallback? onTap;
  final BtnVariant variant;
  final bool full;
  final bool large;
  final IconData? icon;
  const AppButton(this.label,
      {super.key,
      this.onTap,
      this.variant = BtnVariant.primary,
      this.full = false,
      this.large = false,
      this.icon});

  @override
  Widget build(BuildContext context) {
    final (bg, fg, bd) = switch (variant) {
      BtnVariant.primary => (C.accent, C.accentInk, Colors.transparent),
      BtnVariant.secondary => (C.surface2, C.text, C.border),
      BtnVariant.ghost => (Colors.transparent, C.accent, Colors.transparent),
      BtnVariant.danger => (C.red.withValues(alpha: 0.14), C.red, C.red.withValues(alpha: 0.30)),
    };
    final child = Row(
      mainAxisSize: full ? MainAxisSize.max : MainAxisSize.min,
      mainAxisAlignment: MainAxisAlignment.center,
      children: [
        if (icon != null) ...[
          Icon(icon, size: large ? 19 : 18, color: fg),
          const SizedBox(width: 8),
        ],
        Text(label,
            style: TextStyle(
                fontSize: large ? 16 : 14.5, fontWeight: FontWeight.w700, color: fg)),
      ],
    );
    return Material(
      color: bg,
      borderRadius: BorderRadius.circular(12),
      child: InkWell(
        onTap: onTap,
        borderRadius: BorderRadius.circular(12),
        child: Container(
          padding: EdgeInsets.symmetric(horizontal: large ? 20 : 16, vertical: large ? 15 : 11),
          decoration: BoxDecoration(
            borderRadius: BorderRadius.circular(12),
            border: Border.all(color: bd),
            boxShadow: variant == BtnVariant.primary
                ? [BoxShadow(color: C.accent.withValues(alpha: 0.35), blurRadius: 20, offset: const Offset(0, 6))]
                : null,
          ),
          child: child,
        ),
      ),
    );
  }
}

/// ── text field ─────────────────────────────────────────────
class AppField extends StatefulWidget {
  final String? label;
  final TextEditingController controller;
  final String? placeholder;
  final bool obscure;
  final bool mono;
  final IconData? icon;
  final Widget? trailing;
  final Widget? hint;
  final TextInputType? keyboardType;
  const AppField({
    super.key,
    this.label,
    required this.controller,
    this.placeholder,
    this.obscure = false,
    this.mono = false,
    this.icon,
    this.trailing,
    this.hint,
    this.keyboardType,
  });

  @override
  State<AppField> createState() => _AppFieldState();
}

class _AppFieldState extends State<AppField> {
  final _focus = FocusNode();

  @override
  void initState() {
    super.initState();
    _focus.addListener(() => setState(() {}));
  }

  @override
  void dispose() {
    _focus.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    final focused = _focus.hasFocus;
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        if (widget.label != null)
          Padding(
            padding: const EdgeInsets.only(bottom: 7),
            child: Text(widget.label!,
                style: const TextStyle(
                    fontSize: 12.5, fontWeight: FontWeight.w600, color: C.textDim)),
          ),
        Container(
          height: 50,
          padding: const EdgeInsets.symmetric(horizontal: 13),
          decoration: BoxDecoration(
            color: C.surface2,
            borderRadius: BorderRadius.circular(12),
            border: Border.all(color: focused ? C.accent : C.border),
            boxShadow: focused
                ? [BoxShadow(color: C.accent.withValues(alpha: 0.22), blurRadius: 0, spreadRadius: 3)]
                : null,
          ),
          child: Row(
            children: [
              if (widget.icon != null) ...[
                Icon(widget.icon, size: 18, color: C.textFaint),
                const SizedBox(width: 10),
              ],
              Expanded(
                child: TextField(
                  controller: widget.controller,
                  focusNode: _focus,
                  obscureText: widget.obscure,
                  keyboardType: widget.keyboardType,
                  style: widget.mono
                      ? mono(size: 15, color: C.text, weight: FontWeight.w500, spacing: 0.5)
                      : const TextStyle(fontSize: 15, color: C.text),
                  decoration: InputDecoration(
                    isCollapsed: true,
                    border: InputBorder.none,
                    hintText: widget.placeholder,
                    hintStyle: const TextStyle(color: C.textFaint, fontSize: 15),
                  ),
                ),
              ),
              if (widget.trailing != null) widget.trailing!,
            ],
          ),
        ),
        if (widget.hint != null)
          Padding(
            padding: const EdgeInsets.only(top: 6),
            child: DefaultTextStyle(
              style: const TextStyle(fontSize: 11.5, color: C.textFaint),
              child: widget.hint!,
            ),
          ),
      ],
    );
  }
}

/// ── toggle switch ──────────────────────────────────────────
class AppToggle extends StatelessWidget {
  final bool on;
  final ValueChanged<bool> onChanged;
  const AppToggle({super.key, required this.on, required this.onChanged});

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: () => onChanged(!on),
      child: AnimatedContainer(
        duration: const Duration(milliseconds: 180),
        width: 46,
        height: 28,
        padding: const EdgeInsets.all(3),
        alignment: on ? Alignment.centerRight : Alignment.centerLeft,
        decoration: BoxDecoration(
          color: on ? C.green : C.surface3,
          borderRadius: BorderRadius.circular(999),
        ),
        child: Container(
          width: 22,
          height: 22,
          decoration: BoxDecoration(
            color: Colors.white,
            shape: BoxShape.circle,
            boxShadow: [BoxShadow(color: Colors.black.withValues(alpha: 0.3), blurRadius: 3, offset: const Offset(0, 1))],
          ),
        ),
      ),
    );
  }
}

/// ── section label ──────────────────────────────────────────
class SectionLabel extends StatelessWidget {
  final String text;
  final Widget? right;
  const SectionLabel(this.text, {super.key, this.right});

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.fromLTRB(2, 4, 2, 10),
      child: Row(
        mainAxisAlignment: MainAxisAlignment.spaceBetween,
        children: [
          Text(text.toUpperCase(),
              style: const TextStyle(
                  fontSize: 12,
                  fontWeight: FontWeight.w700,
                  letterSpacing: 0.6,
                  color: C.textFaint)),
          if (right != null) right!,
        ],
      ),
    );
  }
}

/// ── log action meta + colored disc ─────────────────────────
class ActionMeta {
  final IconData icon;
  final Color color;
  final String verb;
  const ActionMeta(this.icon, this.color, this.verb);
}

ActionMeta actionMeta(String action) => switch (action) {
      'returned' => const ActionMeta(Icons.check, C.green, 'returned'),
      'denied' => const ActionMeta(Icons.warning_amber_rounded, C.red, 'was denied'),
      'unlock' => const ActionMeta(Icons.lock_open, C.green, 'unlocked'),
      _ => const ActionMeta(Icons.south, C.amber, 'took'),
    };

class ActionDisc extends StatelessWidget {
  final String action;
  final double size;
  const ActionDisc(this.action, {super.key, this.size = 38});

  @override
  Widget build(BuildContext context) {
    final m = actionMeta(action);
    return Container(
      width: size,
      height: size,
      alignment: Alignment.center,
      decoration: BoxDecoration(
        color: m.color.withValues(alpha: 0.15),
        borderRadius: BorderRadius.circular(11),
        border: Border.all(color: m.color.withValues(alpha: 0.26)),
      ),
      child: Icon(m.icon, size: 18, color: m.color),
    );
  }
}

/// ── signal bars ────────────────────────────────────────────
class SignalBars extends StatelessWidget {
  final int level; // 0..3
  const SignalBars({super.key, this.level = 3});

  @override
  Widget build(BuildContext context) {
    const heights = [6.0, 10.0, 14.0];
    return Row(
      mainAxisSize: MainAxisSize.min,
      crossAxisAlignment: CrossAxisAlignment.end,
      children: [
        for (int i = 0; i < 3; i++) ...[
          Container(
            width: 3.5,
            height: heights[i],
            decoration: BoxDecoration(
              color: i < level ? C.text : C.surface3,
              borderRadius: BorderRadius.circular(1),
            ),
          ),
          if (i < 2) const SizedBox(width: 2),
        ],
      ],
    );
  }
}
