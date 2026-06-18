import 'package:flutter_test/flutter_test.dart';
import 'package:smarttoolbox_app/models/tool_event.dart';
import 'package:smarttoolbox_app/util/time.dart';

void main() {
  group('eventTypeFrom', () {
    test('maps known strings', () {
      expect(eventTypeFrom('taken'), EventType.taken);
      expect(eventTypeFrom('returned'), EventType.returned);
      expect(eventTypeFrom('drawer_open'), EventType.drawerOpen);
      expect(eventTypeFrom('denied'), EventType.denied);
    });
    test('falls back to unknown', () {
      expect(eventTypeFrom('nonsense'), EventType.unknown);
      expect(eventTypeFrom(null), EventType.unknown);
    });
  });

  group('timeAgo', () {
    test('null is empty', () => expect(timeAgo(null), ''));
    test('seconds', () {
      final dt = DateTime.now().subtract(const Duration(seconds: 5));
      expect(timeAgo(dt), endsWith('s ago'));
    });
    test('hours', () {
      final dt = DateTime.now().subtract(const Duration(hours: 3));
      expect(timeAgo(dt), '3h ago');
    });
  });
}
