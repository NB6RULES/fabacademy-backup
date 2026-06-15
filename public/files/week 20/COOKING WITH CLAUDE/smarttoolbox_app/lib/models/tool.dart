import 'package:cloud_firestore/cloud_firestore.dart';

/// Live state of one tracked tool slot.
class Tool {
  final String id;
  final String name;
  final int drawer;
  final int nodeId;
  final bool present;
  final String? holder; // uid of current holder
  final String? holderName; // denormalized for display
  final DateTime? updatedAt;

  Tool({
    required this.id,
    required this.name,
    required this.drawer,
    required this.nodeId,
    required this.present,
    this.holder,
    this.holderName,
    this.updatedAt,
  });

  factory Tool.fromDoc(DocumentSnapshot<Map<String, dynamic>> doc) {
    final d = doc.data() ?? <String, dynamic>{};
    return Tool(
      id: doc.id,
      name: (d['name'] ?? '') as String,
      drawer: (d['drawer'] as num?)?.toInt() ?? 0,
      nodeId: (d['nodeId'] as num?)?.toInt() ?? 0,
      present: (d['present'] ?? true) as bool,
      holder: d['holder'] as String?,
      holderName: d['holderName'] as String?,
      updatedAt: (d['updatedAt'] as Timestamp?)?.toDate(),
    );
  }
}
