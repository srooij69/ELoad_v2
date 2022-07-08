#ifndef TEST_PRESENTER_HPP
#define TEST_PRESENTER_HPP

#include <unity.h>
#include <stdio.h>

#include "config.hpp"

#include "ArduinoAdapter.hpp"
#include "presenter.hpp"
#include "fsm.hpp"

namespace test_presenter {
    
void setup_test(){
  presenter::buttons[BUTTON_MODE] = presenter::None;
}

void teardown_test(){

}

void _test_pin_to_Action(int btn, int cnt, unsigned long mills[], bool pinVal[], presenter::eAction result){
    ArduinoAdapter::pinState_init( btn, mills, pinVal );

    for(int i=0; i< cnt; i++){
      presenter::Tick();
    }
    TEST_ASSERT_EQUAL(result, presenter::buttons[btn]);
}

void _test_title_led(config::eRunMode runMode, char const * exp, unsigned long rgb ){
    setup_test();

    fsm::state.set( runMode );
    fsm::display_state();

    uint8_t exp_red   = (rgb >> 16) & 0x0000FF;
    uint8_t exp_green = (rgb >>  8) & 0x0000FF;
    uint8_t exp_blue  = (rgb >>  0) & 0x0000FF;
    bool exp_blink = (rgb  & 0xFF000000)>0;

    TEST_ASSERT_EQUAL_CHAR_ARRAY(exp, display::lines[0], 15);
    TEST_ASSERT_EQUAL(exp_red, display::leds[LED_RED]);
    TEST_ASSERT_EQUAL(exp_green, display::leds[LED_GREEN]);
    TEST_ASSERT_EQUAL(exp_blue, display::leds[LED_BLUE]);
    TEST_ASSERT_EQUAL(exp_blink, presenter::__blink_led);

    teardown_test();
}

void presenter_read_buttons(){
      setup_test();

      unsigned long mills[] = {0, 1, 2, 30, 56, 128};
      bool pinValues[] = { HIGH , HIGH, LOW, LOW, HIGH, HIGH };
      _test_pin_to_Action( BUTTON_MODE, 4, mills, pinValues, presenter::None);
      _test_pin_to_Action( BUTTON_MODE, 5, mills, pinValues, presenter::Short);
      _test_pin_to_Action( BUTTON_MODE, 6, mills, pinValues, presenter::None);
      
      unsigned long mills2[] = {0,     1,   100, 500, 503,  128};
      bool pinValues2[] =      { HIGH, LOW, LOW, LOW, HIGH, HIGH };
      _test_pin_to_Action( BUTTON_RUN, 3, mills2, pinValues2, presenter::None);
      _test_pin_to_Action( BUTTON_RUN, 4, mills2, pinValues2, presenter::LongDown);
      _test_pin_to_Action( BUTTON_RUN, 5, mills2, pinValues2, presenter::Long);
      _test_pin_to_Action( BUTTON_RUN, 6, mills2, pinValues2, presenter::None);

      unsigned long mills3[] = {0, 10, 20, 30, 40, 50};
      bool pinValues3[] = { HIGH , LOW, HIGH, LOW, HIGH, LOW };
      _test_pin_to_Action( BUTTON_MODE, 0, mills3, pinValues3, presenter::None);
      _test_pin_to_Action( BUTTON_MODE, 1, mills3, pinValues3, presenter::None);
      _test_pin_to_Action( BUTTON_MODE, 2, mills3, pinValues3, presenter::None);
      _test_pin_to_Action( BUTTON_MODE, 3, mills3, pinValues3, presenter::None);
      _test_pin_to_Action( BUTTON_MODE, 4, mills3, pinValues3, presenter::None);
      _test_pin_to_Action( BUTTON_MODE, 5, mills3, pinValues3, presenter::None);

      teardown_test();
}

void presenter_display_splash(void)
{
    char exp[4][21] = {"                    ", "   ELoad v2.1       ", " by Steven de Rooij ", "                    "};

    setup_test();

    fsm::state.set( config::Init);
    fsm::display_state();

    TEST_ASSERT_EQUAL_CHAR_ARRAY(exp[0], display::lines[0], 84);

    teardown_test();
}

void presenter_display_RunModes(void)
{
    _test_title_led(config::SelectCC, "C.Curr   Select", 0x0000FF);
    _test_title_led(config::SelectCV, "C.Volt   Select", 0x0000FF);
    _test_title_led(config::SelectCP, "C.Power  Select", 0x0000FF);
    _test_title_led(config::SelectCR, "C.Resist Select", 0x0000FF);

    _test_title_led(config::RunCC, "C.Curr   Run   ", 0x00F400);
    _test_title_led(config::RunCV, "C.Volt   Run   ", 0x00F400);
    _test_title_led(config::RunCP, "C.Power  Run   ", 0x00F400);
    _test_title_led(config::RunCR, "C.Resist Run   ", 0x00F400); 

    _test_title_led(config::Error, "        ERROR  ", 0x08FF0000); 
}

void Run(){
    RUN_TEST(presenter_read_buttons);
    RUN_TEST(presenter_display_splash);
    RUN_TEST(presenter_display_RunModes);
}


}

#endif