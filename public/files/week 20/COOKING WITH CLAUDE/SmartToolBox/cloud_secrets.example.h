// =====================================================================================
//  cloud_secrets.example.h  —  TEMPLATE. Safe to commit.
//
//  Copy this file to  cloud_secrets.h  (which is git-ignored) and fill in your own
//  Firebase project values. The firmware includes cloud_secrets.h, never this template.
// =====================================================================================
#pragma once

#define FB_API_KEY          "YOUR_WEB_API_KEY"        // Project settings -> General -> Web API Key
#define FB_PROJECT_ID       "your-project-id"

// Device account (NOT your admin login). Make it in Console -> Authentication -> Add user.
#define FB_DEVICE_EMAIL     "device@example.local"
#define FB_DEVICE_PASSWORD  "change-me"

#define FB_DEVICE_ID        "main-box"
#define FB_FW_VERSION       "1.0.0"
