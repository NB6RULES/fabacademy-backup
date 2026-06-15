import 'package:flutter/material.dart';

import 'admin_screen.dart';
import 'device_screen.dart';
import 'logs_screen.dart';
import 'status_screen.dart';

class HomeShell extends StatefulWidget {
  const HomeShell({super.key});

  @override
  State<HomeShell> createState() => _HomeShellState();
}

class _HomeShellState extends State<HomeShell> {
  int _index = 0;

  static const _pages = [
    StatusScreen(),
    LogsScreen(),
    AdminScreen(),
    DeviceScreen(),
  ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: IndexedStack(index: _index, children: _pages),
      bottomNavigationBar: NavigationBar(
        selectedIndex: _index,
        onDestinationSelected: (v) => setState(() => _index = v),
        destinations: const [
          NavigationDestination(icon: Icon(Icons.grid_view), label: 'Status'),
          NavigationDestination(
              icon: Icon(Icons.receipt_long), label: 'Logs'),
          NavigationDestination(
              icon: Icon(Icons.admin_panel_settings), label: 'Admin'),
          NavigationDestination(icon: Icon(Icons.wifi), label: 'Device'),
        ],
      ),
    );
  }
}
