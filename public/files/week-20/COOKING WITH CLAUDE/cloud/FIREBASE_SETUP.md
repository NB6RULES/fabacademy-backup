# Firebase Setup — Smart Tool Box

Do these once. They create the cloud backend the ESP and the app both talk to.
Everything here fits the free **Spark** plan.

## 1. Create the project
1. Go to <https://console.firebase.google.com> → **Add project** → name it `smart-tool-box`.
2. Disable Google Analytics (not needed) → **Create project**.

## 2. Add a Web app (gives you the config keys)
1. Project Overview → the **`</>` (Web)** icon → nickname `smarttoolbox-web` → **Register app**.
2. Copy the `firebaseConfig` block it shows you. You need:
   - `apiKey`   → used by the **ESP** (Web API key) **and** the app
   - `projectId`
   These go into `SmartToolBox/secrets.h` on the device (see firmware) — **never commit them**.

## 3. Enable Firestore
1. Build → **Firestore Database** → **Create database**.
2. Start in **production mode** → pick the closest location → **Enable**.
3. We'll lock it down with `firestore.rules` in step 6.

## 4. Enable Authentication (Email/Password)
1. Build → **Authentication** → **Get started**.
2. **Sign-in method** tab → enable **Email/Password** → Save.

## 5. Create the two accounts
In Authentication → **Users** → **Add user**:
- **Admin** (you log into the app with this): your email + a password.
- **Device** (the ESP signs in with this): e.g. `device@smarttoolbox.local` + a strong password.
  Write these down — they go into `secrets.h` on the ESP.

> The rules in step 6 reference these two emails. If you change them, update the rules too.

## 6. Deploy the security rules
With the Firebase CLI (already installed):
```
cd "cloud"
firebase login
firebase use --add            # pick the smart-tool-box project, alias it "default"
# edit firestore.rules: replace ADMIN_EMAIL and DEVICE_EMAIL with the two emails from step 5
firebase deploy --only firestore:rules
```
(Or paste `firestore.rules` into Console → Firestore → **Rules** → Publish.)

## 7. Connect the Flutter app
From the app folder, once it exists:
```
dart pub global activate flutterfire_cli
cd smarttoolbox_app
flutterfire configure          # select the smart-tool-box project
```
This generates `lib/firebase_options.dart` (gitignored) — the app's link to your project.

## 8. Hand me these values
Drop these into `SmartToolBox/secrets.h` (template provided, gitignored):
- `FB_API_KEY`     (Web API key from step 2)
- `FB_PROJECT_ID`
- `DEVICE_EMAIL`, `DEVICE_PASSWORD` (from step 5)

That's the whole backend. Next: WiFi creds get added on-device via the app, not here.
