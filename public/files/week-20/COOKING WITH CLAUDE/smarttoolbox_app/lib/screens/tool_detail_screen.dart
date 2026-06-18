import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/tool.dart';
import '../models/tool_event.dart';
import '../providers/providers.dart';
import '../theme.dart';
import '../util/time.dart';

class ToolDetailScreen extends ConsumerWidget {
  final Tool tool;
  const ToolDetailScreen({super.key, required this.tool});

  @override
  Widget build(BuildContext context, WidgetRef ref) {
    final history = ref.watch(toolHistoryProvider(tool.id));
    return Scaffold(
      appBar: AppBar(title: Text(tool.name.isEmpty ? 'Tool' : tool.name)),
      body: Column(
        children: [
          _header(),
          const Divider(height: 1),
          Expanded(
            child: history.when(
              data: (events) => events.isEmpty
                  ? const Center(child: Text('No history yet'))
                  : ListView.separated(
                      itemCount: events.length,
                      separatorBuilder: (_, _) => const Divider(height: 1),
                      itemBuilder: (c, i) => _eventTile(events[i]),
                    ),
              loading: () => const Center(child: CircularProgressIndicator()),
              error: (e, _) => Center(child: Text('Error: $e')),
            ),
          ),
        ],
      ),
    );
  }

  Widget _header() {
    final color = tool.present ? AppColors.present : AppColors.missing;
    return Padding(
      padding: const EdgeInsets.all(16),
      child: Row(
        children: [
          Icon(Icons.circle, size: 18, color: color),
          const SizedBox(width: 10),
          Expanded(
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(tool.present ? 'Present' : 'Taken',
                    style: TextStyle(
                        fontSize: 18,
                        fontWeight: FontWeight.bold,
                        color: color)),
                Text('Drawer ${tool.drawer} · node ${tool.nodeId}',
                    style: const TextStyle(color: AppColors.textSecondary)),
                if (!tool.present && tool.holderName != null)
                  Text('Held by ${tool.holderName}',
                      style: const TextStyle(color: AppColors.textSecondary)),
              ],
            ),
          ),
        ],
      ),
    );
  }

  Widget _eventTile(ToolEvent e) {
    final returned = e.type == EventType.returned;
    return ListTile(
      leading: Icon(returned ? Icons.south_west : Icons.north_east,
          color: returned ? AppColors.present : AppColors.missing),
      title: Text('${e.who} ${e.actionLabel}'),
      subtitle: Text(fullTime(e.ts)),
      trailing: Text(timeAgo(e.ts),
          style: const TextStyle(color: AppColors.textSecondary)),
    );
  }
}
