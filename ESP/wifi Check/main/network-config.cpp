#include <stdio.h>
#include "network-config.h"
#include "esp_log.h"
#include "WiFi.h"
#include "eeprom-conf.h"
#include "input-config.h"
#include "led-config.h"
#include "timer-config.h"
#include "ver-mgmt.h"

static const char *TAG = "NETWORK";

byte C_WiFi_STAOn = 0;      //byte -> similar to 8 bit unsigned integer(similar uint8_t) ; 0 means wifi station mode is OFF
byte C_WiFi_APOn = 0;       //byte -> similar to 8 bit unsigned integer(similar uint8_t) ; 0 means wifi Access mode is OFF

byte NetworkMode;

int wifiSTAStatus;
int No_Of_Channel;

byte C_MAC[6];
String C_MACStr;

// const char *MyConf.E_SSID="Redmi note 9";
// const char *MyConf.E_WPSWD="18888888";
void PollWiFi_STA(void) {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(MyConf.E_SSID, MyConf.E_WPSWD);
    LOGI(TAG, "Connecting to %s", MyConf.E_SSID);

    if (WiFi.isConnected()) {

      C_WiFi_STAOn = 1;
      // If connection successful show IP address in serial monitor
      LOGI(TAG, "Connected to %s", MyConf.E_SSID);

      LOGI(TAG, "IP Address: %s", ((WiFi.localIP()).toString()).c_str());
    } else {
      C_WiFi_STAOn = 0;
      LOGE(TAG, "Failed to connect to WiFi: %s", MyConf.E_SSID);
    }
  }
}  // End of PollWiFi_STA loop

void ShowWiFiStatus(int i) {
  LOGD(TAG, "NetworkMode = %d", NetworkMode);
  LOGD(TAG, "C_WiFi_APOn %d ", C_WiFi_APOn);
  LOGD(TAG, "C_WiFi_STA %d", C_WiFi_STAOn);
  switch (i) {
    case 1:

      No_Of_Channel = WiFi.softAPgetStationNum();

      LOGD(TAG, "AP IP: %s", ((WiFi.softAPIP()).toString()).c_str());
      LOGD(TAG, "%d Device Connected", No_Of_Channel);
      break;

    case 2:
      wifiSTAStatus = WiFi.status();
      LOGD(TAG, "WiFi STA Status: %d", wifiSTAStatus);
      if (WiFi.status() == WL_CONNECTED)  // returning 3
      {
        LOGD(TAG, "WiFi is Connected");
        GREEN.Blink(50, 50, 1);  // 5sec on 5sec off
      } else if (WiFi.status() == WL_IDLE_STATUS) {
        LOGD(TAG, "WiFi is in Idle State");
        GREEN.Blink(100, 10, 1);  // 10sec on 1sec off
      } else {
        LOGD(TAG, "WiFi is not connected");
        GREEN.Blink(10, 10, 1);  // 1sec on 1 sec off

        LOGD(TAG, "IP Address: %s", ((WiFi.localIP()).toString()).c_str());
      }
      break;
    default:
      No_Of_Channel = WiFi.softAPgetStationNum();

      LOGD(TAG, "AP IP: %s", ((WiFi.softAPIP()).toString()).c_str());
      LOGD(TAG, "%d Device Connected", No_Of_Channel);
      wifiSTAStatus = WiFi.status();
      LOGD(TAG, "WiFi STA Status: %d", wifiSTAStatus);
      if (WiFi.status() == WL_CONNECTED)  // returning 3
      {
        LOGD(TAG, "WiFi is Connected");

        LOGD(TAG, "IP Address: %s", ((WiFi.localIP()).toString()).c_str());
        GREEN.Blink(50, 50, 1);  // 5sec on 5sec off
      } else if (WiFi.status() == WL_IDLE_STATUS) {
        LOGD(TAG, "WiFi is in Idle State");
        GREEN.Blink(100, 10, 1);  // 10sec on 1sec off
      } else {
        LOGD(TAG, "WiFi is not connected");
        GREEN.Blink(10, 10, 1);  // 1sec on 1 sec off
      }
      break;

  }  // End of ShowWiFiStatus loop
}
const char *dns21 = "8.8.8.8";

void SetupStaticIP_AP_STA() {
  LOGI(TAG, "Setting Up Static WiFi");
  byte lp = 0;

  // AP Mode setting
  WiFi.setHostname(MyConf.E_HOSTNAME);  // define hostname
  WiFi.persistent(false);               //disable pesistent storage of wifi credentials in flash memory

  if (IN_Config.readraw() == 0)
  // if (digitalRead(CONFIG_PIN) == 0)
  {
    NetworkMode = NW_AP;
    LOGD(TAG, "CONFIG PIN reads 0");
    WiFi.mode(WIFI_MODE_AP);
  } else {
    NetworkMode = NW_STA;
    LOGD(TAG, "CONFIG PIN reads 1");
    WiFi.mode(WIFI_MODE_STA);
   }

  // AP Mode Setting
  if (NetworkMode & NW_AP) {
    LOGD(TAG, "Static NW_AP");
    LOGI(TAG, "Setting up WiFI Access Point");
    WiFi.softAP(MyConf.E_MYSSID, MyConf.E_MYPSWD);

    LOGI(TAG, "AP IP: %s", ((WiFi.softAPIP()).toString()).c_str());
    C_WiFi_APOn = 1;
    delay(500);
  }

  // STA Mode setting
  if (NetworkMode & NW_STA) {
    bool validConfig = true;
    LOGD(TAG, "Static NW_STA");

    IPAddress apip_, apgw, apsub, apdns1, apdns2;

    if (apip_.fromString(MyConf.E_MYIP)) {
      // try to parse into the IPAddress
      LOGI(TAG, "Setting IP: %s", (apip_.toString()).c_str());
    } else {
      LOGE(TAG, "Received Unparsable IP");
      validConfig = false;
    }

    if (apgw.fromString(MyConf.E_GW)) {
      // try to parse into the IPAddress
      LOGI(TAG, "Setting Gateway IP: %s", (apgw.toString()).c_str());
    } else {
      LOGE(TAG, "Received Unparsable Gateway IP");
      validConfig = false;
    }

    if (apsub.fromString(MyConf.E_NM)) {
      // try to parse into the IPAddress
      LOGI(TAG, "Setting SUbnet: %s", (apsub.toString()).c_str());
    } else {
      LOGE(TAG, "Received Unparsable Subnet");
      validConfig = false;
    }

    if (apdns1.fromString(MyConf.E_DNS)) {
      // try to parse into the IPAddress
      LOGI(TAG, "Setting DNS1: %s", (apdns1.toString()).c_str());
    } else {
      LOGE(TAG, "Received Unparsable DNS1");
      validConfig = false;
    }
    if (apdns2.fromString(dns21)) {
      // try to parse into the IPAddress
      LOGI(TAG, "Setting DNS2: %s", (apdns2.toString()).c_str());
    } else {
      LOGE(TAG, "Received Unparsable DNS2");
      validConfig = false;
    }

    if (validConfig) {

      WiFi.config(apip_, apgw, apsub, apdns1, apdns2);
      LOGI(TAG, "Network Details configured.");
    } else {
      LOGE(TAG, "Network Details are not configured correctly.");
      LOGI(TAG, "Connecting to %s on DHCP", MyConf.E_SSID);
    }
    WiFi.begin(MyConf.E_SSID, MyConf.E_WPSWD);
    delay(500);

    // Wait for WiFi to connect
    while (!WiFi.isConnected()) {
      LOGI(TAG, "-|-");
      delay(500);
      lp++;
      if (lp > 5)
        break;
    }
    if (WiFi.isConnected()) {
      C_WiFi_STAOn = 1;
      // If connection successful show IP address in serial monitor
      LOGI(TAG, "Connected to %s", MyConf.E_SSID);
      delay(100);
      LOGI(TAG, "IP Address: %s", ((WiFi.localIP()).toString()).c_str());
    } else {
      C_WiFi_STAOn = 0;
      LOGE(TAG, "Failed to connect to WiFi: %s", MyConf.E_SSID);
    }
  }
  // WiFi.macAddress(C_MAC);
  // C_MACStr = String(C_MAC[0], HEX) + String(C_MAC[1], HEX) + String(C_MAC[2], HEX) + String(C_MAC[3], HEX) + String(C_MAC[4], HEX) + String(C_MAC[5], HEX);
  // LOGI(TAG, "MAC = %s", C_MACStr.c_str());
}  // End of SetupWifi_AP_STA loop

void SetupWiFi_AP_STA() {
  LOGI(TAG, "Setting Up WiFi on DHCP");
  byte lp = 0;

  // AP Mode setting
  WiFi.setHostname(MyConf.E_HOSTNAME);  // define hostname
  WiFi.persistent(false);
  if (IN_Config.readraw() == 0)
  // if (digitalRead(CONFIG_PIN) == 0)
  {
    NetworkMode = NW_AP;
    LOGD(TAG, "CONFIG PIN reads 0");
    WiFi.mode(WIFI_MODE_AP);
  } else {
    NetworkMode = NW_STA;
    LOGD(TAG, "CONFIG PIN reads 1");
    WiFi.mode(WIFI_MODE_STA);
  }

  if (NetworkMode & NW_AP) {
    LOGD(TAG, "NW_AP");
    LOGI(TAG, "Setting up WiFI Access Point");
    WiFi.softAP(MyConf.E_MYSSID, MyConf.E_MYPSWD);
    LOGI(TAG, "AP IP: %s", ((WiFi.softAPIP()).toString()).c_str());
    C_WiFi_APOn = 1;
    delay(500);
  }
  // STA Mode setting
  if (NetworkMode & NW_STA) {
    LOGD(TAG, "NW_STA");
    LOGI(TAG, "Connecting to %s", MyConf.E_SSID);
    WiFi.begin(MyConf.E_SSID, MyConf.E_WPSWD);
    // delay(500);
    // Wait for WiFi to connect
    while (!WiFi.isConnected()) {
      LOGI(TAG, "-|-");
      delay(500);
      lp++;
      if (lp > 5)
        break;
    }
    if (WiFi.isConnected()) {
      C_WiFi_STAOn = 1;

      // If connection successful show IP address in serial monitor
      LOGI(TAG, "Connected to %s", MyConf.E_SSID);
      delay(1000);

      LOGI(TAG, "IP Address: %s", ((WiFi.localIP()).toString()).c_str());
    } else {
      C_WiFi_STAOn = 0;
      LOGE(TAG, "Failed to connect to WiFi: %s", MyConf.E_SSID);
    }
  }

  // WiFi.macAddress(C_MAC);
  // C_MACStr = String(C_MAC[0], HEX) + String(C_MAC[1], HEX) + String(C_MAC[2], HEX) + String(C_MAC[3], HEX) + String(C_MAC[4], HEX) + String(C_MAC[5], HEX);
  // LOGI(TAG, "MAC = %s", C_MACStr.c_str());
}  // End of SetupWifi_AP_STA loop

bool enableConfigHotspot() {
  LOGI(TAG, "Setting up AP Mode for Configuration");
  NetworkMode = NW_AP;
  WiFi.softAP(MyConf.E_MYSSID, MyConf.E_MYPSWD);
  LOGI(TAG, "AP IP: %s", ((WiFi.softAPIP()).toString()).c_str());
  C_WiFi_APOn = 1;
  WiFi.macAddress(C_MAC);
  C_MACStr = String(C_MAC[0], HEX) + String(C_MAC[1], HEX) + String(C_MAC[2], HEX) + String(C_MAC[3], HEX) + String(C_MAC[4], HEX) + String(C_MAC[5], HEX);
  LOGI(TAG, "MAC = %s", C_MACStr.c_str());
  uint8_t clients;
  F_OneMin = 0;
  LOGI(TAG, "Waiting for client to connect...");
  while (1) {
    clients = WiFi.softAPgetStationNum();
    if (clients == 0) {
      if (F_OneMin == 1) {
        F_OneMin = 0;

        LOGI(TAG, "No Client has connected; Disabling Config Hotspot");
        WiFi.mode(WIFI_OFF);
        return false;
      } else {
        if (F_OneSec) {
          LOGD(TAG, "Waiting for client to connect...");
          F_OneSec = 0;
        }
      }
    } else {
      {
        LOGI(TAG, "Client has connected");
        return true;
      }
    }
  }
}


