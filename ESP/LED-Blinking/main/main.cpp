#include "Arduino.h"

extern "C" void app_main()
{
    initArduino();
    pinMode(2, OUTPUT);
    while(1)
    {
    digitalWrite(2, HIGH);
    delay(200);
    digitalWrite(2, LOW);
    delay(200);
    
    }
}