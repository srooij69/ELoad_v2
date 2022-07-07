#ifndef TEST_FSM_HPP
#define TEST_FSM_HPP

#include <unity.h>
#include "ArduinoAdapter.hpp"

#include "config.hpp"

#include "fsm.hpp"
#include "display.hpp"

namespace test_fsm {


void setup_test(){
    ArduinoAdapter::setup();  
    fsm::setup();
    display::clear();

    presenter::buttons[BUTTON_MODE] = presenter::None;
    presenter::buttons[BUTTON_RUN] = presenter::None;
    presenter::buttons[BUTTON_ENCODER] = presenter::None;
}

void teardown_test(){

}

void _test_buttonAction(config::eRunMode start, int button, presenter::eAction action, config::eRunMode expect){
      setup_test();

    fsm::state.set(start);
    presenter::buttons[button] = action;

    fsm::tick();

    TEST_ASSERT_EQUAL(expect,  fsm::state.runMode);

    teardown_test();
}


void fsm_initial_state(void)
{
    setup_test();

    fsm::tick();
    
    TEST_ASSERT_EQUAL(config::Init,  fsm::state.runMode);
 
    teardown_test();
}

void fsm_init_to_selectCC_state_after_500(void)
{
    setup_test();

    unsigned long turns[] {0, 10, 520};
    ArduinoAdapter::millis_initTurn(turns);

    fsm::tick();
    fsm::tick();

    TEST_ASSERT_EQUAL(config::Init,  fsm::state.runMode);

    fsm::tick();

    TEST_ASSERT_EQUAL(config::SelectCC,  fsm::state.runMode);

    teardown_test();
}

void fsm_SelectCC(void){
    _test_buttonAction(config::SelectCC, BUTTON_MODE, presenter::Short, config::SelectCV );
    _test_buttonAction(config::SelectCC, BUTTON_RUN, presenter::Short, config::RunCC );
}

void fsm_SelectCV(void){
    _test_buttonAction(config::SelectCV, BUTTON_MODE, presenter::Short, config::SelectCP );
    _test_buttonAction(config::SelectCV, BUTTON_RUN, presenter::Short, config::RunCV );
}

void fsm_SelectCP(void){
    _test_buttonAction(config::SelectCP, BUTTON_MODE, presenter::Short, config::SelectCR );
    _test_buttonAction(config::SelectCP, BUTTON_RUN , presenter::Short, config::RunCP );
}

void fsm_SelectCR(void){
    _test_buttonAction(config::SelectCR, BUTTON_MODE, presenter::Short, config::SelectCC );
    _test_buttonAction(config::SelectCR, BUTTON_RUN , presenter::Short, config::RunCR );
}

void fsm_RunCC(void){
    _test_buttonAction(config::RunCC, BUTTON_MODE, presenter::Short, config::RunCC );
    _test_buttonAction(config::RunCC, BUTTON_RUN , presenter::Short, config::SelectCC );
}

void fsm_RunCV(void){
    _test_buttonAction(config::RunCV, BUTTON_MODE, presenter::Short, config::RunCV );
    _test_buttonAction(config::RunCV, BUTTON_RUN , presenter::Short, config::SelectCV );
}

void fsm_RunCP(void){
    _test_buttonAction(config::RunCP, BUTTON_MODE, presenter::Short, config::RunCP );
    _test_buttonAction(config::RunCP, BUTTON_RUN , presenter::Short, config::SelectCP );
}

void fsm_RunCR(void){
    _test_buttonAction(config::RunCR, BUTTON_MODE, presenter::Short, config::RunCR );
    _test_buttonAction(config::RunCR, BUTTON_RUN , presenter::Short, config::SelectCR );
}


void Run(){
    RUN_TEST(fsm_initial_state);
    RUN_TEST(fsm_init_to_selectCC_state_after_500);

    RUN_TEST( fsm_SelectCC );
    RUN_TEST( fsm_SelectCV );
    RUN_TEST( fsm_SelectCP );
    RUN_TEST( fsm_SelectCR );
    RUN_TEST( fsm_RunCC );
    RUN_TEST( fsm_RunCV );
    RUN_TEST( fsm_RunCP );
    RUN_TEST( fsm_RunCR );
}

}

#endif