#ifndef ARDUINOADAPTER_HPP
#define ARDUINOADAPTER_HPP

#include <stdint.h>

#ifdef INPUT_PULLUP //ARDUINO_MAIN 
    #include "ArduinoAdapter_embedded.hpp"
#else
    #include "ArduinoAdapter_eload.hpp"
#endif

namespace ArduinoAdapter {
    unsigned long _millis_start = 0;
    unsigned long * _millis_list;
    int _millis_list_index = -1;

    bool * _value_list;
    int _pin;
    int _value_list_index = -1;
    
    void _millis_initTime(){
        _millis_start = __get_millis();
        _millis_list_index = -1;
    }

    void setup(){
        _millis_initTime();
        _value_list_index = -1;
    }

    void millis_initTurn(unsigned long list[]){
        _millis_list_index = 0;
        _millis_list =  list;
    }

    void pinState_init(int pin, unsigned long listMSec[], bool listVal[]){
        millis_initTurn(listMSec);
        _value_list_index = 0;
        _value_list = listVal;
        _pin = pin;
    }

    unsigned long get_millis(){
        unsigned long ulMillis = 0;
        if( _millis_list_index <0) {
            ulMillis = __get_millis();
            ulMillis -= _millis_start;
        } else {
            ulMillis = _millis_list[_millis_list_index];
            _millis_list_index++;
        }
        return ulMillis; 
    }

    void set_pinMode(int pin, int state){
        __set_pinMode(pin, state);
    }

    bool get_digitalRead(int pin){
        bool bVal = LOW;
        if( _value_list_index <0) {
            bVal = __get_digitalRead(pin);
        } else {
            if( pin == _pin) {
                bVal = _value_list[_value_list_index];
                _value_list_index++;
            }
        }
        return bVal;
    }

}

#endif