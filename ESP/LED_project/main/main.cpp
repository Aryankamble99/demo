#include <iostream>
#include "led-config.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main() {
    std::cout << "ESP32 LED Control" << std::endl;

    // Initialize LEDs (already done in constructor)
    while(1){
    RED.on();
    std::cout << "RED LED is ON" << std::endl;
    delay(1000);
    RED.off();

    std::cout << "RED LED is OFF" << std::endl;
   delay(1000);

    //GREEN.Blink(2, 3, 1);
    //std::cout << "GREEN LED is Blinking" << std::endl;
    

    //RED.Blink(2,3,1);
    //std::cout << "RED LED is Blinking" << std::endl;
    /*while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000));  
    }*/
}
}