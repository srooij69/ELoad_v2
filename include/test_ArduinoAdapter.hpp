#ifndef TEST_ARDUINOADAPTER_HPP
#define TEST_ARDUINOADAPTER_HPP

#include <unity.h>
#include "ArduinoAdapter.hpp"

namespace test_ArduinoAdapter {

void setup_test(){
    ArduinoAdapter::setup();
}

void teardown_test(){

}


void aa_millis_timeBased(void)
{
    setup_test();
    unsigned long now = ArduinoAdapter::get_millis();
    unsigned long next = now+100;
    
    while( next > now ){
        now = ArduinoAdapter::get_millis();
    }

    TEST_ASSERT_GREATER_OR_EQUAL( next, now);

    teardown_test();
}

void aa_millis_turnBased(void)
{
    setup_test();
    unsigned long list[] = {12, 5004, 12345};

    ArduinoAdapter::millis_initTurn( list );

    TEST_ASSERT_GREATER_OR_EQUAL( 12, ArduinoAdapter::get_millis());
    TEST_ASSERT_GREATER_OR_EQUAL( 5004, ArduinoAdapter::get_millis());
    TEST_ASSERT_GREATER_OR_EQUAL( 12345, ArduinoAdapter::get_millis());

    teardown_test();
}

void aa_pinState(){
    setup_test();

    unsigned long list[] = {1, 2, 30, 56};
    bool pinState[] = { LOW, HIGH, HIGH, LOW };

    ArduinoAdapter::pinState_init( 11, list, pinState );

    TEST_ASSERT_GREATER_OR_EQUAL( LOW, ArduinoAdapter::get_digitalRead(11));
    TEST_ASSERT_GREATER_OR_EQUAL( 1, ArduinoAdapter::get_millis());
    
    TEST_ASSERT_GREATER_OR_EQUAL( 2, ArduinoAdapter::get_millis());
    TEST_ASSERT_GREATER_OR_EQUAL( HIGH, ArduinoAdapter::get_digitalRead(11));

    TEST_ASSERT_GREATER_OR_EQUAL( HIGH, ArduinoAdapter::get_digitalRead(11));
    TEST_ASSERT_GREATER_OR_EQUAL( 30, ArduinoAdapter::get_millis());

    TEST_ASSERT_GREATER_OR_EQUAL( LOW, ArduinoAdapter::get_digitalRead(11));
    TEST_ASSERT_GREATER_OR_EQUAL( 56, ArduinoAdapter::get_millis());

    teardown_test();
}

void Run(){
    RUN_TEST(aa_millis_turnBased);
    RUN_TEST(aa_millis_timeBased);
    RUN_TEST(aa_pinState);
}

}


#endif