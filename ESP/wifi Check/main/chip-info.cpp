#include <stdio.h>
#include "Arduino.h"
#include "chip-info.h"
#include "esp_log.h"
#include <inttypes.h>
#include "WiFi.h"
#include "ver-mgmt.h"

const char VerDate[20] = __DATE__;
const char VerTime[20] = __TIME__;

String sVerDate = "";
String sVerTime = "";

static const char *TAG = "CHIP-INFO";

char C_ChipStr[20] = {};
uint16_t C_Chip = NULL;

void getChipInfo(void)
{
    // esp_log_level_set(TAG, ESP_LOG_INFO);
    uint64_t C_ChipID;
    C_ChipID = ESP.getEfuseMac(); // The chip ID is essentially its MAC address(length: 6 bytes).
    C_Chip = (uint16_t)(C_ChipID >> 32);
    snprintf(C_ChipStr, 20, "IES-%04X%08" PRIX32, C_Chip, (uint32_t)C_ChipID);
    LOGI(TAG, "CHIP = %s", C_ChipStr);
    LOGI(TAG, "Version %s | Model %s |  Date %s | Time %s \n", Version, Model, VerDate, VerTime);
    int i;
    for (i = 0; i < 20; i++)
    {
        if (String(VerDate[i]) == " ") sVerDate += "-";
        else sVerDate += String(VerDate[i]);
        sVerTime += String(VerTime[i]);
    }
}
