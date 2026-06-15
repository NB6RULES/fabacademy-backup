import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/app_user.dart';
import '../models/device_status.dart';
import '../models/tool.dart';
import '../models/tool_event.dart';
import '../services/auth_service.dart';
import '../services/firestore_service.dart';
import '../services/provisioning_service.dart';

final firebaseAuthProvider =
    Provider<FirebaseAuth>((ref) => FirebaseAuth.instance);
final firestoreProvider =
    Provider<FirebaseFirestore>((ref) => FirebaseFirestore.instance);

final authServiceProvider =
    Provider<AuthService>((ref) => AuthService(ref.watch(firebaseAuthProvider)));
final firestoreServiceProvider = Provider<FirestoreService>(
    (ref) => FirestoreService(ref.watch(firestoreProvider)));
final provisioningServiceProvider =
    Provider<ProvisioningService>((ref) => ProvisioningService());

final authStateProvider =
    StreamProvider<User?>((ref) => ref.watch(authServiceProvider).authState());

final toolsProvider = StreamProvider<List<Tool>>(
    (ref) => ref.watch(firestoreServiceProvider).tools());
final latestEventsProvider = StreamProvider<List<ToolEvent>>(
    (ref) => ref.watch(firestoreServiceProvider).latestEvents());
final usersProvider = StreamProvider<List<AppUser>>(
    (ref) => ref.watch(firestoreServiceProvider).users());
final deviceProvider = StreamProvider<DeviceStatus?>(
    (ref) => ref.watch(firestoreServiceProvider).device());
final toolHistoryProvider = StreamProvider.family<List<ToolEvent>, String>(
    (ref, toolId) => ref.watch(firestoreServiceProvider).toolHistory(toolId));
