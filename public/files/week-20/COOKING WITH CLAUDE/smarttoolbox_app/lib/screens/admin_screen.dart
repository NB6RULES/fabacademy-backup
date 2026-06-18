import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/app_user.dart';
import '../models/device_status.dart';
import '../providers/providers.dart';
import '../theme.dart';
import '../util/time.dart';

class AdminScreen extends ConsumerWidget {
  const AdminScreen({super.key});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final usersAsync = ref.watch(usersProvider);
    final deviceAsync = ref.watch(deviceProvider);
    return Scaffold(
      appBar: AppBar(
        title: const Text('Admin'),
        actions: [
          IconButton(
            tooltip: 'Sign out',
            onPressed: () => ref.read(authServiceProvider).signOut(),
            icon: const Icon(Icons.logout),
          ),
        ],
      ),
      floatingActionButton: FloatingActionButton.extended(
        onPressed: () => _openUserDialog(context, null),
        icon: const Icon(Icons.person_add),
        label: const Text('Add user'),
      ),
      body: ListView(
        children: [
          _deviceCard(deviceAsync),
          const Padding(
            padding: EdgeInsets.fromLTRB(16, 16, 16, 4),
            child: Text('Users', style: TextStyle(fontWeight: FontWeight.bold)),
          ),
          ...usersAsync.when(
            data: (users) => users.isEmpty
                ? [const ListTile(title: Text('No users yet'))]
                : users.map((u) => _userTile(context, ref, u)).toList(),
            loading: () => [
              const Padding(
                  padding: EdgeInsets.all(24),
                  child: Center(child: CircularProgressIndicator()))
            ],
            error: (e, _) =>
                [Padding(padding: const EdgeInsets.all(16), child: Text('Error: $e'))],
          ),
          const SizedBox(height: 80),
        ],
      ),
    );
  }

  Widget _deviceCard(AsyncValue<DeviceStatus?> deviceAsync) {
    return Card(
      child: deviceAsync.when(
        data: (d) {
          final online = d?.online ?? false;
          return ListTile(
            leading: Icon(Icons.developer_board,
                color: online ? AppColors.present : AppColors.textSecondary),
            title: Text(d?.name ?? 'Device'),
            subtitle: Text(d == null
                ? 'Not registered yet'
                : '${online ? 'Online' : 'Offline'} · fw ${d.fwVersion ?? '?'} · '
                    'seen ${timeAgo(d.lastSeen)}'),
            trailing: Icon(Icons.circle,
                size: 12,
                color: online ? AppColors.present : AppColors.missing),
          );
        },
        loading: () => const ListTile(title: Text('Loading device…')),
        error: (e, _) => ListTile(title: Text('Device error: $e')),
      ),
    );
  }

  Widget _userTile(BuildContext context, WidgetRef ref, AppUser u) {
    return Card(
      child: ListTile(
        title: Text(u.name.isEmpty ? '(no name)' : u.name),
        subtitle: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Text(u.rfidUid.isEmpty ? 'no tag' : u.rfidUid,
                style: const TextStyle(
                    fontFamily: 'monospace', color: AppColors.textSecondary)),
            const SizedBox(height: 4),
            Wrap(
              spacing: 4,
              children: [
                for (final dwr in [1, 2, 3])
                  _drawerChip(dwr, u.allowedDrawers.contains(dwr)),
              ],
            ),
          ],
        ),
        trailing: Switch(
          value: u.active,
          onChanged: (v) =>
              ref.read(firestoreServiceProvider).setUserActive(u.id, v),
        ),
        onTap: () => _openUserDialog(context, u),
        isThreeLine: true,
      ),
    );
  }

  Widget _drawerChip(int n, bool on) => Container(
        padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 2),
        decoration: BoxDecoration(
          color: on ? AppColors.accent.withValues(alpha: 0.2) : null,
          border: Border.all(
              color: on ? AppColors.accent : AppColors.textSecondary),
          borderRadius: BorderRadius.circular(8),
        ),
        child: Text('D$n',
            style: TextStyle(
                fontSize: 12,
                color: on ? AppColors.accent : AppColors.textSecondary)),
      );

  void _openUserDialog(BuildContext context, AppUser? existing) {
    showDialog(
      context: context,
      builder: (_) => _UserDialog(existing: existing),
    );
  }
}

class _UserDialog extends ConsumerStatefulWidget {
  final AppUser? existing;
  const _UserDialog({this.existing});

  @override
  ConsumerState<_UserDialog> createState() => _UserDialogState();
}

class _UserDialogState extends ConsumerState<_UserDialog> {
  late final TextEditingController _name;
  late final TextEditingController _uid;
  final Set<int> _drawers = {};
  bool _active = true;
  bool _busy = false;

  @override
  void initState() {
    super.initState();
    final e = widget.existing;
    _name = TextEditingController(text: e?.name ?? '');
    _uid = TextEditingController(text: e?.rfidUid ?? '');
    _active = e?.active ?? true;
    if (e != null) _drawers.addAll(e.allowedDrawers);
  }

  @override
  void dispose() {
    _name.dispose();
    _uid.dispose();
    super.dispose();
  }

  Future<void> _save() async {
    setState(() => _busy = true);
    final user = AppUser(
      id: widget.existing?.id ?? '',
      rfidUid: _uid.text.trim().toUpperCase(),
      name: _name.text.trim(),
      allowedDrawers: _drawers.toList()..sort(),
      active: _active,
    );
    try {
      final svc = ref.read(firestoreServiceProvider);
      if (widget.existing == null) {
        await svc.addUser(user);
      } else {
        await svc.updateUser(user);
      }
      if (mounted) Navigator.of(context).pop();
    } catch (e) {
      if (mounted) {
        setState(() => _busy = false);
        ScaffoldMessenger.of(context)
            .showSnackBar(SnackBar(content: Text('Error: $e')));
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    return AlertDialog(
      title: Text(widget.existing == null ? 'Add user' : 'Edit user'),
      content: SingleChildScrollView(
        child: Column(
          mainAxisSize: MainAxisSize.min,
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            TextField(
              controller: _name,
              decoration: const InputDecoration(labelText: 'Name'),
            ),
            TextField(
              controller: _uid,
              decoration: const InputDecoration(
                  labelText: 'RFID UID',
                  hintText: 'DE:AD:BE:EF (tap a tag to read it)'),
            ),
            const SizedBox(height: 16),
            const Text('Allowed drawers'),
            Wrap(
              spacing: 8,
              children: [
                for (final n in [1, 2, 3])
                  FilterChip(
                    label: Text('Drawer $n'),
                    selected: _drawers.contains(n),
                    onSelected: (v) => setState(
                        () => v ? _drawers.add(n) : _drawers.remove(n)),
                  ),
              ],
            ),
            SwitchListTile(
              contentPadding: EdgeInsets.zero,
              title: const Text('Active'),
              value: _active,
              onChanged: (v) => setState(() => _active = v),
            ),
          ],
        ),
      ),
      actions: [
        TextButton(
            onPressed: _busy ? null : () => Navigator.of(context).pop(),
            child: const Text('Cancel')),
        FilledButton(
          onPressed: _busy ? null : _save,
          child: _busy
              ? const SizedBox(
                  height: 18,
                  width: 18,
                  child: CircularProgressIndicator(strokeWidth: 2))
              : const Text('Save'),
        ),
      ],
    );
  }
}
