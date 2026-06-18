import 'package:cloud_firestore/cloud_firestore.dart';

/// Heartbeat + allow-list version for the cabinet.
class DeviceStatus {
  final String id;
  final String name;
  final bool online;
  final DateTime? lastSeen;
  final String? fwVersion;
  final int allowlistVersion;

  DeviceStatus({
    required this.id,
    required this.name,
    required this.online,
    this.lastSeen,
    this.fwVersion,
    required this.allowlistVersion,
  });

  factory DeviceStatus.fromDoc(DocumentSnapshot<Map<String, dynamic>> doc) {
    final d = doc.data() ?? <String, dynamic>{};
    return DeviceStatus(
      id: doc.id,
      name: (d['name'] ?? doc.id) as String,
      online: (d['online'] ?? false) as bool,
      lastSeen: (d['lastSeen'] as Timestamp?)?.toDate(),
      fwVersion: d['fwVersion'] as String?,
      allowlistVersion: (d['allowlistVersion'] as num?)?.toInt() ?? 0,
    );
  }
}
