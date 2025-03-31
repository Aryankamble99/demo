#include <stdio.h>
#include "led-config.h"
#include "ver-mgmt.h"
  
Led RED(PIN_LED_RED, 0);
Led GREEN(PIN_LED_GREEN, 0);


Led::Led(byte pin, bool invert) {
  ltime = 0;
  cstate = 0;
  this->invert = invert;
  this->pin = pin;
  init();
}
void Led::init() {
  pinMode(pin, OUTPUT);
  off();
}
void Led::on() {
  cstate = 1;
  if (invert)
    digitalWrite(pin, LOW);
  else
    digitalWrite(pin, HIGH);
}

void Led::off() {
  cstate = 0;
  if (invert)
    digitalWrite(pin, HIGH);
  else
    digitalWrite(pin, LOW);
}

void Led::Blink(byte ontime, byte offtime, byte cont) {
  if ((ontime == 0) && (offtime == 0)) {
    ltime = 0;
  } else {
    if (cont == 0) {
      on();
      ltime = 0;
      OnTime = ontime;
      OffTime = offtime;
    } else {
      OnTime = ontime;
      OffTime = offtime;
    }
  }
}

void Led::BlinkLoop() {
  if ((OnTime == 0) && (OffTime == 0)) {
    ltime = 0;
  } else {
    ltime++;
    if ((ltime >= OnTime) && (cstate == 1)) {
      ltime = 0;
      off();
    } else if ((ltime >= OffTime) && (cstate == 0)) {
      ltime = 0;
      on();
    }
  }
}

