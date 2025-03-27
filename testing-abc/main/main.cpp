#include "Arduino.h"
#include "abc-config/abc-config.h"

extern "C" void app_main()
{
    initArduino();
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
    print_sum(5, 10);
    digitalWrite(2, LOW);

    // Do your own thing
}