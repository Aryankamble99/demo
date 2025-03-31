#include <stdio.h>
#include "wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main() {  
    printf("Connecting to WiFi...\n");
    wifi_connect_sta();

    if (wifi_is_connected()) {
        printf("Connected! IP: %s\n", wifi_get_ip_address());
    } else {
        printf("Failed to connect.\nStarting AP mode...\n");
        wifi_start_ap();
        printf("AP Started. Connect to SSID: %s\n", AP_SSID);
    }

    while (1) {
        if (wifi_is_connected()) {
            printf("Connected! IP: %s\n", wifi_get_ip_address());
        } else {
            printf("WiFi Disconnected.\n");
        }
        vTaskDelay(pdMS_TO_TICKS(1000));  
    }
}
