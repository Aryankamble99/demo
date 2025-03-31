#include <stdio.h>
#include "timer-config.h"
#include "input-config.h"
#include "esp_log.h"
#include "led-config.h"
#include "ver-mgmt.h"

static const char *TAG = "TIMER";

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800;
const int daylightOffset_sec = 0;

volatile int T_MCount;  // Trigger

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// Code with critical section

volatile bool F_OneSec = 0;
volatile bool F_OneMin = 0;
volatile word T_OneSec = 0;
volatile word T_100msSec;
volatile word T_OneMin;
volatile word T_CommTimeOut;


void IRAM_ATTR onTime() {
  // Interrupt. It will come every 100msec.
  portENTER_CRITICAL_ISR(&timerMux);
  T_MCount++;
  T_100msSec++;
  //T_CommTimeOut++;
  if (!(T_MCount % 10))  //for one sec
  {
    F_OneSec = 1;
    T_OneSec++;
  }
  if (!(T_MCount % 600))  //for 1 min
  {
    F_OneMin = 1;
    T_OneMin++;
  }

  portEXIT_CRITICAL_ISR(&timerMux);
  
  GREEN.BlinkLoop();
  RED.BlinkLoop();
  IN_Config.Poll();
  for (int inp = 0; inp < MAX_INPUT; inp++){
    IN_Pin[inp].Poll();
    IN_Pin_Analog[inp].Poll();
  }
}  //End of Timer handler loop

char timeStringBuff[50];  //50 chars should be enough
void printLocalTime() {
  LOGI(TAG, "Polling NTP server");
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    LOGE(TAG, "Failed to obtain time from NTP server");
    char timeStringBuff[50] = "FailedToGetTime";
    return;
  }
  strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%d %H:%M:%S", &timeinfo);
  LOGI(TAG, "%s", timeStringBuff);
}