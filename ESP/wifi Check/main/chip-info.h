
#ifndef CHIP_INFO
#define CHIP_INFO

#include "Arduino.h"

extern char C_ChipStr[20];
extern uint16_t C_Chip;

extern String sVerDate;
extern String sVerTime;

// extern "C" {
    void getChipInfo(void);
// }
#endif