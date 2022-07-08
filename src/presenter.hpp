#ifndef ELOAD_PRESENTER_HPP
#define ELOAD_PRESENTER_HPP

#include "config.hpp"
#include "display.hpp"

#include "ArduinoAdapter.hpp"

#define BUTTON_MODE    0
#define BUTTON_RUN     1
#define BUTTON_ENCODER 2
#define NR_BUTTONS     3

namespace presenter {
    enum eAction { None, Short, LongDown, Long, Left, Right};

    unsigned long __now = 0;  

    uint32_t _led_color=0;
    bool __blink_led = false;
    unsigned long __blink_last = 0;

    eAction buttons[NR_BUTTONS];
    long __buttons_start_down[NR_BUTTONS];

    void setup(){
        for(int i=0; i< NR_BUTTONS; i++) buttons[i]=None;
        display::clear();
    }

    void _ShowSplash(){
        display::clear();
        display::writeText(1,0, config::splash_text[0] );
        display::writeText(2,0, config::splash_text[1]);
    }

    void _set_led_color(uint32_t led_color){
        display::leds[LED_RED]   = (led_color >> 16) & 0x00FF;
        display::leds[LED_GREEN] = (led_color >>  8) & 0x00FF;
        display::leds[LED_BLUE]  = (led_color >>  0) & 0x00FF;
    }

    void DisplayRunMode(config::eRunMode runMode){
        static config::eRunMode prevMode = config::Dummy;
        char const * title;
        
        bool isFirst = (prevMode != runMode);

        _led_color = config::runmode_colors[(int)runMode];
        title = config::runmode_titles[(int)runMode];

        if( isFirst) { 
            display::clear();
            display::writeText(0,0, title);
            __blink_led = ((_led_color & 0xFF000000)>0);
            _set_led_color(_led_color);
            if( runMode == config::Init) _ShowSplash(); 
        }
        prevMode = runMode;
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

    void handle_buttonpress(){
        bool btnDown;
        long interval = 0 ;
        
        for(int btn=0; btn<NR_BUTTONS; btn++){
            interval =0;
            btnDown = ! ArduinoAdapter::get_digitalRead(btn);

            if( btnDown & (__buttons_start_down[btn]==0))  __buttons_start_down[btn] = __now; //Mark first down
            if( __buttons_start_down[btn] > 0) interval = __now - __buttons_start_down[btn]; //Only calc interval for when marked down
            if( ! btnDown )  __buttons_start_down[btn] = 0; //Clear when up 

            if( btnDown )    interval = - interval;  //use negative interval when button still down 

            buttons[btn] = _downIntervalToEnum( interval);  
        }
    }

    void Tick(){
        __now = ArduinoAdapter::get_millis();
        handle_buttonpress();
    }

}

#endif