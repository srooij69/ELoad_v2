#ifndef TEST_PRESENTER_HPP
#define TEST_PRESENTER_HPP

#include <stdio.h>
#include <unity.h>

#include "config.hpp"

#include "display.hpp"

#include "ArduinoAdapter.hpp"
#include "presenter.hpp"

namespace test_presenter
{

    void setup_test()
    {
    }

    void teardown_test()
    {
    }

    void _test_title_led(config::eRunMode runMode, char const *exp, unsigned long rgb)
    {
        setup_test();

        presenter::display_runMode(runMode);

        uint8_t exp_red = (rgb >> 16) & 0x0000FF;
        uint8_t exp_green = (rgb >> 8) & 0x0000FF;
        uint8_t exp_blue = (rgb >> 0) & 0x0000FF;
        bool exp_blink = (rgb & 0xFF000000) > 0;

        TEST_ASSERT_EQUAL_CHAR_ARRAY(exp, display::lines[0], 15);
        TEST_ASSERT_EQUAL(exp_red, display::leds[LED_RED]);
        TEST_ASSERT_EQUAL(exp_green, display::leds[LED_GREEN]);
        TEST_ASSERT_EQUAL(exp_blue, display::leds[LED_BLUE]);
        TEST_ASSERT_EQUAL(exp_blink, presenter::__blink_led);

        teardown_test();
    }

    void presenter_read_ledblink()
    {
        unsigned long now;

        setup_test();

        uint8_t red = _RED >> 16;
        uint8_t off = _OFF;

        unsigned long mills[]{0, 195, 205, 295, 405, 605, 805};
        uint8_t exp_led_color[]{red, red, off, off, red, off, red};

        presenter::display_runMode(config::Error);

        ArduinoAdapter::millis_initTurn(mills);

        TEST_ASSERT_EQUAL(true, presenter::__blink_led);

        for (int j = 0; j < 7; j++)
        {
            now = sensors::read();
            presenter::blink_led(now);
            TEST_ASSERT_EQUAL(exp_led_color[j], display::leds[LED_RED]);
        }

        teardown_test();
    }

    void presenter_display_splash(void)
    {
        char exp[4][21] = {"                    ", "   ELoad v2.1       ", " by Steven de Rooij ", "                    "};

        setup_test();

        presenter::display_runMode(config::Init);
        TEST_ASSERT_EQUAL_CHAR_ARRAY(exp[0], display::lines[0], 84);

        teardown_test();
    }

    void presenter_display_SensorData(void)
    { 
        //...............xxxC
        //..x,xxxV..x,xxxW..
        //..x,xxxA..x,xxxR..
        
    }

    void presenter_display_ErrorDetails(void)
    { //Limit to lines 1, 2
        char exp[2][21] = { " Temp. over limit   ", " 123.0 C > 100.0 C  "};
        int32_t mock_pin_value = 123;
        int32_t exp_value = 123000;
        uint8_t pin = sensors::sensor_pins[SENSOR_TEMP];

        setup_test();

        ArduinoAdapter::pinState_init(pin, mock_pin_value);

        sensors::read();
        presenter::display_Error(config::MaxTemp, SENSOR_TEMP);
        TEST_ASSERT_EQUAL(exp_value, sensors::sensors[SENSOR_TEMP]);        
        TEST_ASSERT_EQUAL_CHAR_ARRAY(exp[0], display::lines[1], 42);        

        teardown_test();
    }

    void presenter_display_RunModes(void)
    { //Test line 0
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

    void Run()
    {
        RUN_TEST(presenter_read_ledblink);
        RUN_TEST(presenter_display_splash);
        RUN_TEST(presenter_display_RunModes);
        RUN_TEST(presenter_display_ErrorDetails);

        //RUN_TEST(presenter_display_SensorData);
    }

}

#endif