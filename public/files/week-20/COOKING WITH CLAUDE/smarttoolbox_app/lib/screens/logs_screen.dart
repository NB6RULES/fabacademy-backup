import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/tool_event.dart';
import '../providers/providers.dart';
import '../theme.dart';
import '../util/time.dart';

class LogsScreen extends ConsumerWidget {
  const LogsScreen({super.key});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final eventsAsync = ref.watch(latestEventsProvider);
    return Scaffold(
      appBar: AppBar(title: const Text('Latest Logs')),
      body: eventsAsync.when(
        data: (events) => events.isEmpty
            ? const Center(child: Text('No activity yet'))
            : RefreshIndicator(
                onRefresh: () async => ref.invalidate(latestEventsProvider),
                child: ListView.separated(
                  itemCount: events.length,
                  separatorBuilder: (_, _) => const Divider(height: 1),
                  itemBuilder: (c, i) => _row(events[i]),
                ),
              ),
        loading: () => const Center(child: CircularProgressIndicator()),
        error: (e, _) => Center(child: Text('Error: $e')),
      ),
    );
  }

  Widget _row(ToolEvent e) {
    final c = _colorFor(e.type);
    return ListTile(
      leading: CircleAvatar(
        backgroundColor: c.withValues(alpha: 0.18),
        child: Icon(_iconFor(e.type), color: c, size: 20),
      ),
      title: Text('${e.who} ${e.actionLabel}'
          '${e.target.isNotEmpty ? ' ${e.target}' : ''}'),
      subtitle: Text(fullTime(e.ts)),
      trailing: Text(timeAgo(e.ts),
          style: const TextStyle(color: AppColors.textSecondary)),
    );
  }

  Color _colorFor(EventType t) {
    switch (t) {
      case EventType.returned:
      case EventType.unlock:
        return AppColors.present;
      case EventType.taken:
        return const Color(0xFFF59E0B); // amber
      case EventType.denied:
        return AppColors.missing;
      default:
        return AppColors.textSecondary;
    }
  }

  IconData _iconFor(EventType t) {
    switch (t) {
      case EventType.taken:
        return Icons.north_east;
      case EventType.returned:
        return Icons.south_west;
      case EventType.unlock:
        return Icons.lock_open;
      case EventType.denied:
        return Icons.block;
      case EventType.drawerOpen:
      case EventType.drawerClose:
        return Icons.inbox;
      case EventType.unknown:
        return Icons.bolt;
    }
  }
}
