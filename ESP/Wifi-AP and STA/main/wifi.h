#ifndef WIFI_H
#define WIFI_H

#include<stdio.h>
#include<stdbool.h>

#define AP_SSID "ESP32_AP"
#define AP_PASS "12345678"
#define STA_SSID "Redmi Note 9"
#define STA_PASS "18888888"


void wifi_connect_sta();
void wifi_start_ap();
bool wifi_is_connected();
const char* wifi_get_ip_address();

#endif