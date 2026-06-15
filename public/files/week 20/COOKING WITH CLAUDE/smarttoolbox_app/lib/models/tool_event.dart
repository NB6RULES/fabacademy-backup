import 'package:cloud_firestore/cloud_firestore.dart';

enum EventType { taken, returned, unlock, denied, drawerOpen, drawerClose, unknown }

EventType eventTypeFrom(String? s) {
  switch (s) {
    case 'taken':
      return EventType.taken;
    case 'returned':
      return EventType.returned;
    case 'unlock':
      return EventType.unlock;
    case 'denied':
      return EventType.denied;
    case 'drawer_open':
      return EventType.drawerOpen;
    case 'drawer_close':
      return EventType.drawerClose;
    default:
      return EventType.unknown;
  }
}

/// One append-only event from the cabinet.
class ToolEvent {
  final String id;
  final EventType type;
  final String? toolId;
  final int? nodeId;
  final int? drawer;
  final String? uid;
  final String? userName;
  final String? rfidUid;
  final DateTime? ts;

  ToolEvent({
    required this.id,
    required this.type,
    this.toolId,
    this.nodeId,
    this.drawer,
    this.uid,
    this.userName,
    this.rfidUid,
    this.ts,
  });

  factory ToolEvent.fromDoc(DocumentSnapshot<Map<String, dynamic>> doc) {
    final d = doc.data() ?? <String, dynamic>{};
    return ToolEvent(
      id: doc.id,
      type: eventTypeFrom(d['type'] as String?),
      toolId: d['toolId'] as String?,
      nodeId: (d['nodeId'] as num?)?.toInt(),
      drawer: (d['drawer'] as num?)?.toInt(),
      uid: d['uid'] as String?,
      userName: d['userName'] as String?,
      rfidUid: d['rfidUid'] as String?,
      ts: (d['ts'] as Timestamp?)?.toDate(),
    );
  }

  /// Verb phrase for the logs feed, e.g. "Nadec took 6mm Allen Key".
  String get actionLabel {
    switch (type) {
      case EventType.taken:
        return 'took';
      case EventType.returned:
        return 'returned';
      case EventType.unlock:
        return 'unlocked the box';
      case EventType.denied:
        return 'was denied';
      case EventType.drawerOpen:
        return 'opened a drawer';
      case EventType.drawerClose:
        return 'closed a drawer';
      case EventType.unknown:
        return 'event';
    }
  }

  String get who => (userName != null && userName!.isNotEmpty)
      ? userName!
      : (rfidUid ?? 'Unknown tag');

  String get target => toolId ?? (drawer != null ? 'Drawer $drawer' : '');
}
