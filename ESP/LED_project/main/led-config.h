#ifndef LED_CONFIG
#define LED_CONFIG

#define PIN_LED_RED 2     //LD5
#define PIN_LED_GREEN 15  //LD6

#include "Arduino.h"

// extern "C"
// {
    class Led
    {
    public:
        byte pin;
        byte ltime;
        byte OnTime;
        bool cstate;
        byte OffTime;
        bool invert;
        String inname;
        Led(byte pin, bool invert);                       // Constructor
        void init();                                      // method
        void on();                                        // method
        void off();                                       // method
        void Blink(byte ontime, byte offtime, byte cont); // method
        void BlinkLoop();                                 // method
    };
// }

extern Led RED;      //led class object
extern Led GREEN;  //led class object

#endif