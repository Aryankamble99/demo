#include <stdio.h>
#include "Arduino.h"
#include "esp_log.h"
#include "EEPROM.h"
#include "network-config.h"
#include "input-config.h"
#include "esp_timer.h"
#include "WiFi.h"
#include "config.h"
#include "esp_log.h"
#include "ver-mgmt.h"
static const char *TAG = "WiFi_SETUP";

void setup() {
  esp_log_level_set("*", ESP_LOG_INFO);  // Set log level
  LOGI(TAG, "Initializing WiFi...");

  if (!enableConfigHotspot()) {
    LOGI(TAG, "Config hotspot not enabled, setting up WiFi...");

  //   if (MyConf.E_DHCP == 0) {
  //     SetupStaticIP_AP_STA();
  //   } else {
  //     SetupWiFi_AP_STA();
  //   }
  // } else {
  //   LOGI(TAG, "Hotspot mode enabled.");
  // }

  ShowWiFiStatus(NetworkMode);
}
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    LOGI(TAG, "Reconnecting to WiFi...");
    PollWiFi_STA();
  }

  if (NetworkMode & NW_AP) {
    int connectedClients = WiFi.softAPgetStationNum();
    if (connectedClients == 0) {
      LOGI(TAG, "No clients connected, disabling Hotspot...");
      WiFi.mode(WIFI_OFF);
      WiFi.mode(WIFI_MODE_STA);
      NetworkMode = NW_STA;

      // if (MyConf.E_DHCP == 0) {
      //   SetupStaticIP_AP_STA();
      // } else {
      //   SetupWiFi_AP_STA();
      // }
    }
  }

  ShowWiFiStatus(NetworkMode);
  delay(5000);  // Polling every 5 seconds for better stability
}
/*✅ Step 1: Properly Detect Disconnection

Instead of WiFi.status(), check the actual ping response or IP address validity.

📌 Modify PollWiFi_STA()
void PollWiFi_STA(void) {
  if (WiFi.status() != WL_CONNECTED || WiFi.localIP().toString() == "0.0.0.0") {
    LOGE(TAG, "WiFi Disconnected! Attempting to reconnect...");

    WiFi.disconnect(); // Ensure we start fresh
    delay(100);
    WiFi.begin(MyConf.E_SSID, MyConf.E_WPSWD);

    int retries = 10;
    while (WiFi.status() != WL_CONNECTED && retries-- > 0) {
      delay(500);
      LOGI(TAG, "Reconnecting... [%d tries left]", retries);
    }

    if (WiFi.status() == WL_CONNECTED) {
      LOGI(TAG, "Reconnected! IP: %s", WiFi.localIP().toString().c_str());
    } else {
      LOGE(TAG, "Reconnection failed.");
    }
  }
}

🛠 Fixes:

    Checks both WiFi.status() and WiFi.localIP().

    Forces WiFi.disconnect() before reconnecting.

    Retries 10 times before giving up.
//----------------------------------------------------

✅ Step 2: Force Auto Reconnect

📌 Enable Auto Reconnect in setup()

WiFi.setAutoReconnect(true);
WiFi.persistent(true);
  
//----------------------------------------------------

✅ Step 3: Add a Watchdog Timer (Optional)

If WiFi disconnects for too long, restart ESP32.

static unsigned long lastConnectionCheck = millis();

if (WiFi.status() != WL_CONNECTED) {
  if (millis() - lastConnectionCheck > 60000) {  // 1 min timeout
    LOGE(TAG, "Restarting ESP32 due to WiFi failure...");
    ESP.restart();
  }
} else {
  lastConnectionCheck = millis(); // Reset timer if connected
}


*///------------------------------------------------------


/*
Issues in Your Code

    WiFi.status() != WL_CONNECTED does not always detect disconnection.

    WiFi.isConnected() may return old status instead of real-time data.

    ESP32 may think it's connected even after router shutdown.

    No forced reconnection mechanism after WiFi drop.



Fix 1: Improved PollWiFi_STA()

🔹 Ensure WiFi.disconnect() before reconnecting.
🔹 Check actual IP address & ping a server to confirm connection.

void PollWiFi_STA(void) {
  if (WiFi.status() != WL_CONNECTED || WiFi.localIP().toString() == "0.0.0.0") {
    LOGE(TAG, "WiFi Disconnected! Attempting to reconnect...");
    
    WiFi.disconnect();  // Force disconnect
    delay(100);
    WiFi.begin(MyConf.E_SSID, MyConf.E_WPSWD);

    int retries = 10;
    while (WiFi.status() != WL_CONNECTED && retries-- > 0) {
      delay(500);
      LOGI(TAG, "Reconnecting... [%d tries left]", retries);
    }

    if (WiFi.status() == WL_CONNECTED) {
      C_WiFi_STAOn = 1;
      LOGI(TAG, "Reconnected! IP: %s", WiFi.localIP().toString().c_str());
    } else {
      C_WiFi_STAOn = 0;
      LOGE(TAG, "Reconnection failed.");
    }
  }
}
//--WiFi.localIP() returns the ESP32’s current local IP address.

.toString() converts it into a string.

If the IP is "0.0.0.0", it means the ESP32 is not actually connected to the network, even if WiFi.status() still returns WL_CONNECTED.
--//

✅ Fix 2: Verify WiFi with a Ping Check

🔹 Sometimes WiFi.status() still returns WL_CONNECTED falsely.
🔹 Let's actually ping Google's DNS to verify connectivity.

 Updated ShowWiFiStatus()

#include <HTTPClient.h>

bool checkInternet() {
  HTTPClient http;
  http.begin("http://clients3.google.com/generate_204");
  int httpCode = http.GET();
  http.end();
  return (httpCode == 204);
}

void ShowWiFiStatus(int i) {
  LOGD(TAG, "NetworkMode = %d", NetworkMode);
  LOGD(TAG, "C_WiFi_APOn %d ", C_WiFi_APOn);
  LOGD(TAG, "C_WiFi_STA %d", C_WiFi_STAOn);
  
  wifiSTAStatus = WiFi.status();
  LOGD(TAG, "WiFi STA Status: %d", wifiSTAStatus);

  if (WiFi.status() == WL_CONNECTED) {
    if (checkInternet()) {
      LOGD(TAG, "WiFi is Connected & Internet is available.");
      GREEN.Blink(50, 50, 1);
    } else {
      LOGD(TAG, "WiFi is Connected but No Internet!");
      GREEN.Blink(100, 10, 1);
    }
  } else {
    LOGD(TAG, "WiFi is NOT connected.");
    GREEN.Blink(10, 10, 1);
  }
}

✔ This will check for real connectivity, not just WiFi status.


✅ Fix 3: Add Auto-Reconnect

Add this to setup() to enable ESP32's internal auto-reconnect:

WiFi.setAutoReconnect(true);
WiFi.persistent(true);

✔ ESP32 will automatically try to reconnect if disconnected.
*/

//---------------------------------------------------------------------

/*
OUR PollWiFi_STA() Issues

void PollWiFi_STA(void) {
  if (WiFi.status() != WL_CONNECTED) {                                  // ❌ Only checks WiFi.status(), not real connection
    WiFi.begin(MyConf.E_SSID, MyConf.E_WPSWD);
    LOGI(TAG, "Connecting to %s", MyConf.E_SSID);

    if (WiFi.isConnected()) {                                          // ❌ `WiFi.isConnected()` may return an old status
      C_WiFi_STAOn = 1;
      LOGI(TAG, "Connected to %s", MyConf.E_SSID);
      LOGI(TAG, "IP Address: %s", ((WiFi.localIP()).toString()).c_str());
    } else {
      C_WiFi_STAOn = 0;
      LOGE(TAG, "Failed to connect to WiFi: %s", MyConf.E_SSID);
    }
  }
}

❌ Problems in your version:

   1. Doesn't force disconnection before reconnecting → Can cause "stuck" connections.

   2. Only checks WiFi.status() != WL_CONNECTED → Doesn't verify real connectivity.

   3. No retry mechanism → If WiFi fails to connect, it won't retry.

   4. No check for invalid IP (0.0.0.0) → Sometimes ESP32 thinks it's connected but has no IP.




//--------------------------------------------------------------------------

✅ Improved PollWiFi_STA()

void PollWiFi_STA(void) {
  if (WiFi.status() != WL_CONNECTED || WiFi.localIP().toString() == "0.0.0.0") {
    LOGE(TAG, "WiFi Disconnected! Attempting to reconnect...");
    
    WiFi.disconnect();                                                           // ✅ Force disconnect first
    delay(100);
    WiFi.begin(MyConf.E_SSID, MyConf.E_WPSWD);

    int retries = 10;                                                            // ✅ Retries up to 10 times
    while (WiFi.status() != WL_CONNECTED && retries-- > 0) {
      delay(500);
      LOGI(TAG, "Reconnecting... [%d tries left]", retries);
    }

    if (WiFi.status() == WL_CONNECTED) {
      C_WiFi_STAOn = 1;
      LOGI(TAG, "Reconnected! IP: %s", WiFi.localIP().toString().c_str());
    } else {
      C_WiFi_STAOn = 0;
      LOGE(TAG, "Reconnection failed.");
    }
  }
}

✔ Fixes & Improvements:

   1. Forces a disconnect (WiFi.disconnect()) before reconnecting.

   2. Checks if IP is 0.0.0.0, meaning no valid network connection.

   3. Retries up to 10 times before giving up.

   4. Better logs to track reconnection attempts.
*/


