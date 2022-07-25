#ifndef ELOAD_SENSORS_HPP
#define ELOAD_SENSORS_HPP

#include "ArduinoAdapter.hpp"
#include "config.hpp"

#define SENSOR_TEMP    0
#define SENSOR_CURRENT 1
#define SENSOR_VOLT    2
#define NR_SENSORS     3

#define BUTTON_MODE    0
#define BUTTON_RUN     1
#define BUTTON_ENCODER 2
#define NR_BUTTONS     3

namespace sensors {
    enum eAction { None, Short, LongDown, Long, Left, Right};

    unsigned long __now = 0;  

    eAction buttons[NR_BUTTONS];
    long __buttons_start_down[NR_BUTTONS];
    int8_t button_pins[NR_BUTTONS];

    int32_t sensors[NR_SENSORS];
    int8_t sensor_pins[NR_SENSORS];

    char sensorUnits[] {'C', 'A'};

    void setup(){
        for(int i=0; i< NR_BUTTONS; i++) buttons[i]=None;
        for(int i=0; i< NR_SENSORS; i++) sensors[i]=0;

        button_pins[BUTTON_MODE]    = 10;
        button_pins[BUTTON_RUN]     = 11;
        button_pins[BUTTON_ENCODER] = 12;
        

        sensor_pins[SENSOR_TEMP] = 7;
        sensor_pins[SENSOR_CURRENT] = 8;
        sensor_pins[SENSOR_VOLT] = 9;
    }

    eAction _downIntervalToEnum(long interval){
        eAction btnAction = eAction::None;

        if( interval < -config::Button_Interval_Long)  
            btnAction = eAction::LongDown;  //Still down
        else {
            if( interval > config::Button_Interval_Short ) btnAction = eAction::Short; //up after min 30 down
            if( interval > config::Button_Interval_Long)   btnAction = eAction::Long;  //up after min 400 down
        }    
        return btnAction;
    }

    void _read_buttonpress(unsigned long now){
        bool btnDown;
        long interval = 0 ;

        for(int btn=0; btn<NR_BUTTONS; btn++){
            interval =0;
            btnDown = ! ArduinoAdapter::get_digitalRead(button_pins[btn]);

            if( btnDown & (__buttons_start_down[btn]==0))  __buttons_start_down[btn] = now; //Mark first down
            if( __buttons_start_down[btn] > 0) interval = now - __buttons_start_down[btn]; //Only calc interval for when marked down
            if( ! btnDown )  __buttons_start_down[btn] = 0; //Clear when up 

            if( btnDown )    interval = - interval;  //use negative interval when button still down 

            buttons[btn] = _downIntervalToEnum( interval);  
        }
    }

    void _read_sensors(unsigned long now){
        sensors[SENSOR_TEMP] = 1000 * ArduinoAdapter::get_analogRead(sensor_pins[SENSOR_TEMP]);
        sensors[SENSOR_CURRENT] = 1 * ArduinoAdapter::get_analogRead(sensor_pins[SENSOR_CURRENT]);
    }

    unsigned long read(){
        __now = ArduinoAdapter::get_millis();
        _read_buttonpress(__now);
        _read_sensors(__now);
        return __now;
    }

    bool isShort(uint8_t button){
        return ( sensors::buttons[button] == sensors::Short);
    }
}

#endif