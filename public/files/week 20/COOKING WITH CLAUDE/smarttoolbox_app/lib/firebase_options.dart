// PLACEHOLDER — regenerate with `flutterfire configure` (see cloud/FIREBASE_SETUP.md).
//
// This stub lets the project compile before Firebase is connected. Running
// `flutterfire configure` overwrites this file with your real project values.
import 'package:firebase_core/firebase_core.dart' show FirebaseOptions;
import 'package:flutter/foundation.dart'
    show defaultTargetPlatform, kIsWeb, TargetPlatform;

class DefaultFirebaseOptions {
  static FirebaseOptions get currentPlatform {
    if (kIsWeb) {
      throw UnsupportedError('Web not configured — run flutterfire configure.');
    }
    switch (defaultTargetPlatform) {
      case TargetPlatform.android:
        return android;
      case TargetPlatform.iOS:
        return ios;
      default:
        throw UnsupportedError(
            'Platform not configured — run flutterfire configure.');
    }
  }

  static const FirebaseOptions android = FirebaseOptions(
    apiKey: 'AIzaSyCdN1BhDgK-DT9vfQpqAQoDJpNU1QR44b0',
    appId: '1:22185564193:android:ae2d062cac66d7cd47ab60',
    messagingSenderId: '22185564193',
    projectId: 'smart-tool-box-2efc9',
    storageBucket: 'smart-tool-box-2efc9.firebasestorage.app',
  );
  static const FirebaseOptions ios = FirebaseOptions(
    apiKey: 'AIzaSyCP2dltbJdyqoS2I9ARmBXpIM7aTG_L_eQ',
    appId: '1:22185564193:ios:5d28b5a53132933947ab60',
    messagingSenderId: '22185564193',
    projectId: 'smart-tool-box-2efc9',
    storageBucket: 'smart-tool-box-2efc9.firebasestorage.app',
    iosBundleId: 'com.nadecbiju.smarttoolboxApp',
  );
}
