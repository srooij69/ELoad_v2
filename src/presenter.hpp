#ifndef ELOAD_PRESENTER_HPP
#define ELOAD_PRESENTER_HPP

#include "config.hpp"
#include "display.hpp"
#include "sensors.hpp"

#include "ArduinoAdapter.hpp"

namespace presenter {
    unsigned long __now = 0;  

    uint32_t _led_color=0;
    bool __blink_led = false;
    unsigned long __blink_next = 0;

    void setup(){
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

    void display_runMode(config::eRunMode runMode){
        static config::eRunMode prevMode = config::Dummy;
        char const * title;
        
        bool isFirst = (prevMode != runMode);

        _led_color = config::runmode_colors[(int)runMode];
        title = config::runmode_titles[(int)runMode];

        if( isFirst) { 
            display::clear();
            display::writeText(0,0, title);
            __blink_led = ((_led_color & 0xFF000000)>0);
            __blink_next = 0;
            _set_led_color(_led_color);
            if( runMode == config::Init) _ShowSplash(); 
        } 
        prevMode = runMode;
    }

    void blink_led(unsigned long now){
        static uint8_t blink_on = 0; 
        if( __blink_next < 1) {
            blink_on = 0;
            __blink_next = now;
        }
        if( now >= __blink_next) {
            blink_on = 1 - blink_on;
            __blink_next += config::Led_Blink_millis;
        }

        _set_led_color(_led_color * blink_on);
    }

}

#endif