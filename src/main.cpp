#include <Arduino.h>
#include <driver/can.h>
#include <driver/gpio.h>
#include "lecturaYComunicacion.h"
//Serial.begin(115200);


void setup() {
 
Serial.begin(115200);
setup_can_driver();  
}


void loop() {
  readCanFrame();
}