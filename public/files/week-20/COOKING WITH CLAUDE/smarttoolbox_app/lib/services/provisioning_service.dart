import 'dart:convert';
import 'package:http/http.dart' as http;

class WifiNetwork {
  final String ssid;
  final int rssi;
  final bool secure;
  WifiNetwork(this.ssid, this.rssi, this.secure);
}

/// Talks to the ESP's WiFi-manager HTTP API (default AP address 192.168.4.1).
/// Mirrors wifi_manager.cpp endpoints.
class ProvisioningService {
  final String base;
  ProvisioningService({this.base = 'http://192.168.4.1'});

  Future<List<WifiNetwork>> scan() async {
    final r = await http.get(Uri.parse('$base/scan'));
    final data = jsonDecode(r.body) as Map<String, dynamic>;
    final nets = (data['networks'] as List?) ?? const [];
    return nets
        .map((n) => WifiNetwork(
              (n['ssid'] ?? '') as String,
              (n['rssi'] as num?)?.toInt() ?? 0,
              (n['secure'] ?? false) as bool,
            ))
        .toList();
  }

  Future<List<String>> saved() async {
    final r = await http.get(Uri.parse('$base/saved'));
    final data = jsonDecode(r.body) as Map<String, dynamic>;
    return List<String>.from((data['saved'] as List?) ?? const []);
  }

  Future<void> save(String ssid, String pass) =>
      http.post(Uri.parse('$base/wifi'), body: {'ssid': ssid, 'pass': pass});

  Future<void> forget(String ssid) =>
      http.post(Uri.parse('$base/forget'), body: {'ssid': ssid});

  Future<void> connect() =>
      http.post(Uri.parse('$base/connect'), body: {'go': '1'});
}
