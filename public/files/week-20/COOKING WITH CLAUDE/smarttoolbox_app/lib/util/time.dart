import 'package:intl/intl.dart';

String fullTime(DateTime? dt) =>
    dt == null ? '—' : DateFormat('MMM d, h:mm a').format(dt.toLocal());

String timeAgo(DateTime? dt) {
  if (dt == null) return '';
  final d = DateTime.now().difference(dt);
  if (d.inSeconds < 60) return '${d.inSeconds}s ago';
  if (d.inMinutes < 60) return '${d.inMinutes}m ago';
  if (d.inHours < 24) return '${d.inHours}h ago';
  return '${d.inDays}d ago';
}
