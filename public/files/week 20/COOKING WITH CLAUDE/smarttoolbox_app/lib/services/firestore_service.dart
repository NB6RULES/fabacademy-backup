import 'package:cloud_firestore/cloud_firestore.dart';

import '../models/app_user.dart';
import '../models/device_status.dart';
import '../models/tool.dart';
import '../models/tool_event.dart';

class FirestoreService {
  final FirebaseFirestore _db;
  FirestoreService(this._db);

  static const deviceId = 'main-box';

  CollectionReference<Map<String, dynamic>> get _users =>
      _db.collection('users');
  CollectionReference<Map<String, dynamic>> get _tools =>
      _db.collection('tools');
  CollectionReference<Map<String, dynamic>> get _events =>
      _db.collection('events');

  // ---- live reads ----
  Stream<List<Tool>> tools() => _tools.orderBy('drawer').snapshots().map(
      (s) => s.docs.map((d) => Tool.fromDoc(d)).toList());

  Stream<List<ToolEvent>> latestEvents({int limit = 50}) => _events
      .orderBy('ts', descending: true)
      .limit(limit)
      .snapshots()
      .map((s) => s.docs.map((d) => ToolEvent.fromDoc(d)).toList());

  Stream<List<ToolEvent>> toolHistory(String toolId) => _events
      .where('toolId', isEqualTo: toolId)
      .orderBy('ts', descending: true)
      .snapshots()
      .map((s) => s.docs.map((d) => ToolEvent.fromDoc(d)).toList());

  Stream<List<AppUser>> users() => _users.orderBy('name').snapshots().map(
      (s) => s.docs.map((d) => AppUser.fromDoc(d)).toList());

  Stream<DeviceStatus?> device() => _db
      .collection('devices')
      .doc(deviceId)
      .snapshots()
      .map((d) => d.exists ? DeviceStatus.fromDoc(d) : null);

  // ---- admin writes ----
  Future<void> addUser(AppUser u) async {
    await _users.add(u.toCreateMap());
    await _bumpAllowlist();
  }

  Future<void> updateUser(AppUser u) async {
    await _users.doc(u.id).update(u.toUpdateMap());
    await _bumpAllowlist();
  }

  Future<void> setUserActive(String id, bool active) async {
    await _users.doc(id).update({'active': active});
    await _bumpAllowlist();
  }

  /// Tell the device its allow-list changed so it re-syncs.
  Future<void> _bumpAllowlist() => _db
      .collection('devices')
      .doc(deviceId)
      .set({'allowlistVersion': FieldValue.increment(1)},
          SetOptions(merge: true));
}
