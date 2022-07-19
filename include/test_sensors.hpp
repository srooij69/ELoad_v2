#ifndef TEST_SENSORS_HPP
#define TEST_SENSORS_HPP

#include <stdio.h>
#include <unity.h>

#include "config.hpp"

#include "ArduinoAdapter.hpp"
#include "sensors.hpp"

namespace test_sensors
{
    void setup_test()
    {
        sensors::buttons[BUTTON_MODE] = sensors::None;
    }

    void teardown_test()
    {
    }

    void _test_pin_to_Action(int btn, int cnt, unsigned long mills[], bool pinVal[], sensors::eAction result)
    {
        ArduinoAdapter::pinState_init(btn, mills, pinVal);

        for (int i = 0; i < cnt; i++)
        {
            sensors::read();
        }
        TEST_ASSERT_EQUAL(result, sensors::buttons[btn]);
    }

    void sensors_read_buttons()
    {
        setup_test();

        unsigned long mills[] = {0, 1, 3, 30, 56, 128};
        bool pinValues[] = {HIGH, HIGH, LOW, LOW, HIGH, HIGH};
        _test_pin_to_Action(BUTTON_MODE, 4, mills, pinValues, sensors::None);
        _test_pin_to_Action(BUTTON_MODE, 5, mills, pinValues, sensors::Short);
        _test_pin_to_Action(BUTTON_MODE, 6, mills, pinValues, sensors::None);

        unsigned long mills2[] = {0, 1, 100, 500, 503, 128};
        bool pinValues2[] = {HIGH, LOW, LOW, LOW, HIGH, HIGH};
        _test_pin_to_Action(BUTTON_RUN, 3, mills2, pinValues2, sensors::None);
        _test_pin_to_Action(BUTTON_RUN, 4, mills2, pinValues2, sensors::LongDown);
        _test_pin_to_Action(BUTTON_RUN, 5, mills2, pinValues2, sensors::Long);
        _test_pin_to_Action(BUTTON_RUN, 6, mills2, pinValues2, sensors::None);

        unsigned long mills3[] = {0, 10, 20, 30, 40, 50};
        bool pinValues3[] = {HIGH, LOW, HIGH, LOW, HIGH, LOW};
        _test_pin_to_Action(BUTTON_MODE, 0, mills3, pinValues3, sensors::None);
        _test_pin_to_Action(BUTTON_MODE, 1, mills3, pinValues3, sensors::None);
        _test_pin_to_Action(BUTTON_MODE, 2, mills3, pinValues3, sensors::None);
        _test_pin_to_Action(BUTTON_MODE, 3, mills3, pinValues3, sensors::None);
        _test_pin_to_Action(BUTTON_MODE, 4, mills3, pinValues3, sensors::None);
        _test_pin_to_Action(BUTTON_MODE, 5, mills3, pinValues3, sensors::None);

        teardown_test();
    }

    void sensors_read_sensors()
    {
        setup_test();

        int set = 213;
        int exp = 213000;
        int act;

        ArduinoAdapter::pinState_init(sensors::sensor_pins[SENSOR_TEMP], set);

        sensors::read();
        act = sensors::sensors[SENSOR_TEMP];

        TEST_ASSERT_EQUAL(exp, act);

        teardown_test();
    }

    void Run()
    {
        RUN_TEST(sensors_read_buttons);
        RUN_TEST(sensors_read_sensors);
    }

}

#endif