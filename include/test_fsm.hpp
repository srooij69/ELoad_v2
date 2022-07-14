#ifndef TEST_FSM_HPP
#define TEST_FSM_HPP

#include <unity.h>
#include "ArduinoAdapter.hpp"

#include "config.hpp"

#include "fsm.hpp"
#include "sensors.hpp"

namespace test_fsm {


void setup_test(){
    ArduinoAdapter::setup();  
    sensors::setup();
    fsm::setup();

    sensors::buttons[BUTTON_MODE] = sensors::None;
    sensors::buttons[BUTTON_RUN] = sensors::None;
    sensors::buttons[BUTTON_ENCODER] = sensors::None;
}

void teardown_test(){

}

void _test_buttonAction(config::eRunMode start, int button, sensors::eAction action, config::eRunMode expect){
    setup_test();

    fsm::state.set(start);
    unsigned long now = sensors::read();
    sensors::buttons[button] = action;

    fsm::handle_state(now);
    TEST_ASSERT_EQUAL(expect,  fsm::state.runMode);

    teardown_test();
}

void fsm_initial_state(void)
{
    setup_test();

    fsm::handle_state(0);
    
    TEST_ASSERT_EQUAL(config::Init,  fsm::state.runMode);
 
    teardown_test();
}

void fsm_init_to_selectCC_state_after_500(void)
{
    setup_test();

    unsigned long turns[] {0, 10, 520};
    ArduinoAdapter::millis_initTurn(turns);

    unsigned long now = 0;
    now = sensors::read();
    fsm::handle_state(now);

    TEST_ASSERT_EQUAL(config::Init,  fsm::state.runMode);

    now = sensors::read();
    fsm::handle_state(now);
    now = sensors::read();
    fsm::handle_state(now);

    TEST_ASSERT_EQUAL(config::SelectCC,  fsm::state.runMode);

    teardown_test();
}

void fsm_handlestate_SelectCC(void){
    _test_buttonAction(config::SelectCC, BUTTON_MODE, sensors::Short, config::SelectCV );
    _test_buttonAction(config::SelectCC, BUTTON_RUN, sensors::Short, config::RunCC );
}

void fsm_handlestate_SelectCV(void){
    _test_buttonAction(config::SelectCV, BUTTON_MODE, sensors::Short, config::SelectCP );
    _test_buttonAction(config::SelectCV, BUTTON_RUN, sensors::Short, config::RunCV );
}

void fsm_handlestate_SelectCP(void){
    _test_buttonAction(config::SelectCP, BUTTON_MODE, sensors::Short, config::SelectCR );
    _test_buttonAction(config::SelectCP, BUTTON_RUN , sensors::Short, config::RunCP );
}

void fsm_handlestate_SelectCR(void){
    _test_buttonAction(config::SelectCR, BUTTON_MODE, sensors::Short, config::SelectCC );
    _test_buttonAction(config::SelectCR, BUTTON_RUN , sensors::Short, config::RunCR );
}

void fsm_handlestate_RunCC(void){
    _test_buttonAction(config::RunCC, BUTTON_MODE, sensors::Short, config::RunCC );
    _test_buttonAction(config::RunCC, BUTTON_RUN , sensors::Short, config::SelectCC );
}

void fsm_handlestate_RunCV(void){
    _test_buttonAction(config::RunCV, BUTTON_MODE, sensors::Short, config::RunCV );
    _test_buttonAction(config::RunCV, BUTTON_RUN , sensors::Short, config::SelectCV );
}

void fsm_handlestate_RunCP(void){
    _test_buttonAction(config::RunCP, BUTTON_MODE, sensors::Short, config::RunCP );
    _test_buttonAction(config::RunCP, BUTTON_RUN , sensors::Short, config::SelectCP );
}

void fsm_handlestate_RunCR(void){
    _test_buttonAction(config::RunCR, BUTTON_MODE, sensors::Short, config::RunCR );
    _test_buttonAction(config::RunCR, BUTTON_RUN , sensors::Short, config::SelectCR );
}

/* 
void fsm_sensor_read(void){
    setup_test();

    fsm::state.set(config::RunCC);
    sensors::sensors[SENSOR_TEMP] = 34000;

    fsm::tick();

    TEST_ASSERT_EQUAL(34,  presenter::sensorData[SENSOR_TEMP]);

    teardown_test();
} */

void Run(){
 //   RUN_TEST(fsm_initial_state);
 //   RUN_TEST(fsm_init_to_selectCC_state_after_500);

    RUN_TEST( fsm_handlestate_SelectCC );
    RUN_TEST( fsm_handlestate_SelectCV );
    RUN_TEST( fsm_handlestate_SelectCP );
    RUN_TEST( fsm_handlestate_SelectCR );
    RUN_TEST( fsm_handlestate_RunCC );
    RUN_TEST( fsm_handlestate_RunCV );
    RUN_TEST( fsm_handlestate_RunCP );
    RUN_TEST( fsm_handlestate_RunCR );
  
    //RUN_TEST(fsm_sensor_read);
}

}

#endif