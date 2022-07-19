//sub file to ArduinoAdapter.hpp
//This file is used to when running on actual Arduino Uno/Nano

#include <stdint.h>
#include <Arduino.h>

unsigned long __get_millis(){
    unsigned long m = millis();
    return m;
}

bool __get_digitalRead(int pin){
    return digitalRead(pin);
}

void __set_pinMode(int pin, int state){
    pinMode(pin, state);
}

void __set_pin_init(int pin, uint16_t val){
    //analogWrite(pin, val);
}

int16_t __get_analogRead(int pin){
    return analogRead(pin);
}