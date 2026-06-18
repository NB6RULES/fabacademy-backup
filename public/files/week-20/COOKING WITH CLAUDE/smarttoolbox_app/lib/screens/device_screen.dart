import 'package:flutter/material.dart';
import 'package:flutter_riverpod/flutter_riverpod.dart';

import '../providers/providers.dart';
import '../services/provisioning_service.dart';
import '../theme.dart';

/// Phase 6 WiFi provisioning: talks to the ESP's AP at 192.168.4.1.
/// Join the "SmartToolBox-XXXX" network first, then use this screen.
class DeviceScreen extends ConsumerStatefulWidget {
  const DeviceScreen({super.key});

  @override
  ConsumerState<DeviceScreen> createState() => _DeviceScreenState();
}

class _DeviceScreenState extends ConsumerState<DeviceScreen> {
  final _ssid = TextEditingController();
  final _pass = TextEditingController();
  List<WifiNetwork> _networks = [];
  List<String> _saved = [];
  bool _busy = false;
  String? _msg;

  @override
  void dispose() {
    _ssid.dispose();
    _pass.dispose();
    super.dispose();
  }

  ProvisioningService get _svc => ref.read(provisioningServiceProvider);

  Future<void> _run(Future<void> Function() action, {String? ok}) async {
    setState(() {
      _busy = true;
      _msg = null;
    });
    try {
      await action();
      if (mounted && ok != null) setState(() => _msg = ok);
    } catch (e) {
      if (mounted) {
        setState(() =>
            _msg = 'Could not reach the box. Join the SmartToolBox-XXXX WiFi first.');
      }
    } finally {
      if (mounted) setState(() => _busy = false);
    }
  }

  Future<void> _refresh() => _run(() async {
        final nets = await _svc.scan();
        final saved = await _svc.saved();
        if (mounted) {
          setState(() {
            _networks = nets;
            _saved = saved;
          });
        }
      });

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Device · WiFi'),
        actions: [
          IconButton(
              onPressed: _busy ? null : _refresh,
              icon: const Icon(Icons.refresh)),
        ],
      ),
      body: ListView(
        padding: const EdgeInsets.all(12),
        children: [
          const Card(
            child: Padding(
              padding: EdgeInsets.all(12),
              child: Text(
                '1. Join the "SmartToolBox-XXXX" WiFi network.\n'
                '2. Tap refresh to scan, pick a network, set the password, then '
                'Save & Connect.',
              ),
            ),
          ),
          if (_msg != null)
            Padding(
              padding: const EdgeInsets.symmetric(vertical: 8),
              child: Text(_msg!, style: const TextStyle(color: AppColors.accent)),
            ),
          const _SectionTitle('Available networks'),
          if (_networks.isEmpty)
            const Padding(
              padding: EdgeInsets.all(8),
              child: Text('Tap refresh to scan',
                  style: TextStyle(color: AppColors.textSecondary)),
            ),
          ..._networks.map((n) => ListTile(
                leading: Icon(
                    n.secure ? Icons.wifi_lock : Icons.wifi,
                    color: _signalColor(n.rssi)),
                title: Text(n.ssid),
                subtitle: Text('${n.rssi} dBm'),
                onTap: () {
                  setState(() {
                    _ssid.text = n.ssid;
                    _pass.clear();
                  });
                },
              )),
          const Divider(),
          const _SectionTitle('Add / update password'),
          TextField(
              controller: _ssid,
              decoration: const InputDecoration(labelText: 'SSID')),
          TextField(
              controller: _pass,
              obscureText: true,
              decoration: const InputDecoration(labelText: 'Password')),
          const SizedBox(height: 8),
          Row(
            children: [
              FilledButton.tonal(
                onPressed: _busy
                    ? null
                    : () => _run(
                          () => _svc.save(_ssid.text.trim(), _pass.text),
                          ok: 'Saved.',
                        ).then((_) => _refresh()),
                child: const Text('Save'),
              ),
              const SizedBox(width: 8),
              FilledButton(
                onPressed: _busy
                    ? null
                    : () async {
                        if (_ssid.text.trim().isNotEmpty) {
                          await _run(() =>
                              _svc.save(_ssid.text.trim(), _pass.text));
                        }
                        await _run(() => _svc.connect(),
                            ok: 'Box is rebooting to connect…');
                      },
                child: const Text('Save & Connect'),
              ),
            ],
          ),
          const Divider(),
          const _SectionTitle('Saved networks'),
          if (_saved.isEmpty)
            const Padding(
              padding: EdgeInsets.all(8),
              child: Text('none',
                  style: TextStyle(color: AppColors.textSecondary)),
            ),
          ..._saved.map((s) => ListTile(
                leading: const Icon(Icons.save),
                title: Text(s),
                trailing: Row(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    TextButton(
                      onPressed: _busy
                          ? null
                          : () => setState(() {
                                _ssid.text = s;
                                _pass.clear();
                              }),
                      child: const Text('edit'),
                    ),
                    TextButton(
                      onPressed: _busy
                          ? null
                          : () => _run(() => _svc.forget(s))
                              .then((_) => _refresh()),
                      child: const Text('forget'),
                    ),
                  ],
                ),
              )),
        ],
      ),
    );
  }

  Color _signalColor(int rssi) {
    if (rssi >= -60) return AppColors.present;
    if (rssi >= -75) return const Color(0xFFF59E0B);
    return AppColors.missing;
  }
}

class _SectionTitle extends StatelessWidget {
  final String text;
  const _SectionTitle(this.text);
  @override
  Widget build(BuildContext context) => Padding(
        padding: const EdgeInsets.fromLTRB(4, 12, 4, 4),
        child: Text(text, style: const TextStyle(fontWeight: FontWeight.bold)),
      );
}
