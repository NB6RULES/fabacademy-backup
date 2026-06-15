# Firestore Schema — Smart Tool Box

Four collections. `ts`/`*At` fields use Firestore **server timestamps** (source of truth).

## `users/{uid}`
One per RFID tag. `{uid}` is the Firestore doc id (auto); the tag is `rfidUid`.
```jsonc
{
  "rfidUid": "DE:AD:BE:EF",      // the RC522 UID, colon-hex, UPPERCASE
  "name": "Nadec",
  "allowedDrawers": [1, 3],       // which drawers this tag may unlock (1..3)
  "active": true,                 // false = disabled without deleting
  "createdAt": <serverTimestamp>
}
```

## `tools/{toolId}`
One per tracked tool slot. `nodeId` ties it to the daisy-chain node (1..19, minus the
Hall nodes 10/18/19). `present` + `holder` are the live state the ESP patches.
```jsonc
{
  "name": "6mm Allen Key",
  "drawer": 1,
  "nodeId": 4,                    // chain node that senses this slot
  "present": true,                // true = sitting in slot, false = taken
  "holder": null,                 // uid of current holder, or null
  "updatedAt": <serverTimestamp>
}
```

## `events/{autoId}`
Append-only log. Drives the app's Tool History and Latest Logs.
```jsonc
{
  "type": "taken",               // taken | returned | unlock | denied | drawer_open | drawer_close
  "toolId": "tool_04",           // present for taken/returned
  "nodeId": 4,
  "drawer": 1,
  "uid": "<users doc id>",       // who; null for anonymous denied taps
  "userName": "Nadec",           // denormalized for easy display
  "rfidUid": "DE:AD:BE:EF",      // raw tag for denied taps
  "ts": <serverTimestamp>
}
```
Common queries:
- **Latest Logs:** `events` orderBy `ts` desc, limit 50
- **Tool History:** `events` where `toolId == x` orderBy `ts` desc

## `devices/{deviceId}`
Device heartbeat + a counter the ESP watches to know when to re-sync the allow-list.
```jsonc
{
  "name": "main-box",
  "online": true,
  "lastSeen": <serverTimestamp>,
  "fwVersion": "1.0.0",
  "allowlistVersion": 7           // admin bumps on user changes → ESP re-syncs users
}
```

## Notes
- `allowlistVersion`: the Admin Panel increments this whenever a user is added/edited so the
  ESP knows to re-fetch `users` instead of polling the whole collection constantly.
- `holder`/`uid` reference `users` doc ids; `userName`/`rfidUid` are denormalized so the log
  feed renders without extra lookups.
- No Cloud Functions required — all writes are done directly by the device + admin under the
  rules above (Spark-plan friendly).
