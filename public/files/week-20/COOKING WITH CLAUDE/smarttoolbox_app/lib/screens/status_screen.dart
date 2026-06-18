import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../models/tool.dart';
import '../providers/providers.dart';
import '../theme.dart';
import 'tool_detail_screen.dart';

class StatusScreen extends ConsumerStatefulWidget {
  const StatusScreen({super.key});

  @override
  ConsumerState<StatusScreen> createState() => _StatusScreenState();
}

class _StatusScreenState extends ConsumerState<StatusScreen> {
  int _drawer = 0; // 0 = all

  @override
  Widget build(BuildContext context) {
    final toolsAsync = ref.watch(toolsProvider);
    return Scaffold(
      appBar: AppBar(title: const Text('Tool Status')),
      body: Column(
        children: [
          _filterBar(),
          Expanded(
            child: toolsAsync.when(
              data: (tools) {
                final list = _drawer == 0
                    ? tools
                    : tools.where((t) => t.drawer == _drawer).toList();
                final out = tools.where((t) => !t.present).length;
                return Column(
                  children: [
                    Padding(
                      padding: const EdgeInsets.all(8),
                      child: Align(
                        alignment: Alignment.centerLeft,
                        child: Text('${tools.length} tools · $out out',
                            style: const TextStyle(
                                color: AppColors.textSecondary)),
                      ),
                    ),
                    Expanded(
                      child: list.isEmpty
                          ? const Center(child: Text('No tools yet'))
                          : ListView.builder(
                              itemCount: list.length,
                              itemBuilder: (c, i) => _tile(list[i]),
                            ),
                    ),
                  ],
                );
              },
              loading: () => const Center(child: CircularProgressIndicator()),
              error: (e, _) => Center(child: Text('Error: $e')),
            ),
          ),
        ],
      ),
    );
  }

  Widget _filterBar() {
    const labels = ['All', 'Drawer 1', 'Drawer 2', 'Drawer 3'];
    return SingleChildScrollView(
      scrollDirection: Axis.horizontal,
      padding: const EdgeInsets.all(8),
      child: Row(
        children: [
          for (int i = 0; i < labels.length; i++)
            Padding(
              padding: const EdgeInsets.symmetric(horizontal: 4),
              child: ChoiceChip(
                label: Text(labels[i]),
                selected: _drawer == i,
                onSelected: (_) => setState(() => _drawer = i),
              ),
            ),
        ],
      ),
    );
  }

  Widget _tile(Tool t) {
    final subtitle = t.present
        ? 'Drawer ${t.drawer} · present'
        : 'Drawer ${t.drawer} · taken'
            '${t.holderName != null ? ' by ${t.holderName}' : ''}';
    return Card(
      child: ListTile(
        leading: Icon(Icons.circle,
            size: 14, color: t.present ? AppColors.present : AppColors.missing),
        title: Text(t.name.isEmpty ? '(unnamed tool)' : t.name),
        subtitle: Text(subtitle),
        trailing: const Icon(Icons.chevron_right),
        onTap: () => Navigator.of(context).push(
            MaterialPageRoute(builder: (_) => ToolDetailScreen(tool: t))),
      ),
    );
  }
}
