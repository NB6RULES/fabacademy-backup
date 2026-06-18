import 'package:cloud_firestore/cloud_firestore.dart';

/// A user = one RFID tag with a set of drawers they may unlock.
class AppUser {
  final String id;
  final String rfidUid;
  final String name;
  final List<int> allowedDrawers;
  final bool active;
  final DateTime? createdAt;

  AppUser({
    required this.id,
    required this.rfidUid,
    required this.name,
    required this.allowedDrawers,
    required this.active,
    this.createdAt,
  });

  factory AppUser.fromDoc(DocumentSnapshot<Map<String, dynamic>> doc) {
    final d = doc.data() ?? <String, dynamic>{};
    return AppUser(
      id: doc.id,
      rfidUid: (d['rfidUid'] ?? '') as String,
      name: (d['name'] ?? '') as String,
      allowedDrawers:
          List<int>.from((d['allowedDrawers'] ?? const <int>[]) as List),
      active: (d['active'] ?? true) as bool,
      createdAt: (d['createdAt'] as Timestamp?)?.toDate(),
    );
  }

  Map<String, dynamic> toCreateMap() => {
        'rfidUid': rfidUid,
        'name': name,
        'allowedDrawers': allowedDrawers,
        'active': active,
        'createdAt': FieldValue.serverTimestamp(),
      };

  Map<String, dynamic> toUpdateMap() => {
        'rfidUid': rfidUid,
        'name': name,
        'allowedDrawers': allowedDrawers,
        'active': active,
      };
}
