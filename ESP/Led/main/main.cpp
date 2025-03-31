#include "Arduino.h"

extern "C" void app_main()
{
    initArduino();
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
   
}