#include "wifi.h"
#include "WiFi.h"  

void wifi_connect_sta() {
    WiFi.mode(WIFI_STA);  
    WiFi.begin(STA_SSID, STA_PASS);

    int retry = 0;
    while (WiFi.status() != WL_CONNECTED && retry < 20) {
        delay(500);
        retry++;
    }
}

void wifi_start_ap() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASS);
}

bool wifi_is_connected() {
    return WiFi.status() == WL_CONNECTED;
}

const char* wifi_get_ip_address() {
    if (wifi_is_connected()) {
        return WiFi.localIP().toString().c_str();
    }
    return "0.0.0.0";
}
