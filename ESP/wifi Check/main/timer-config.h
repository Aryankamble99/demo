#ifndef TIMER_CONFIG 
#define TIMER_CONFIG

#include "Arduino.h"

extern hw_timer_t *timer;

extern const char *ntpServer;
extern const long gmtOffset_sec;
extern const int daylightOffset_sec;

extern char timeStringBuff[50]; 
extern volatile int T_MCount;
extern volatile bool F_OneSec;
extern volatile bool F_OneMin;
extern volatile word T_OneSec;
extern volatile word T_OneMin;

// extern "C" {
void onTime(void);
void printLocalTime(void);
// }

#endif 