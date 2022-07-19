//sub file to ArduinoAdapter.hpp
//This file is used to mimic Arduino when running on laptop 

#include <stdint.h>

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

//When running on Laptop
#include <time.h>

int16_t __pin[21];

unsigned long __get_millis(){
    time_t now = time(nullptr);
    return now * 1000;
}

bool __get_digitalRead(int pin){
    return __pin[pin] > 0;
}

void __set_pinMode(int pin, int state){
}

void __set_pin_init(int pin, uint16_t val){
    __pin[pin] = val;
}

int16_t __get_analogRead(int pin){
    return __pin[pin];
}
