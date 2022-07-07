#ifndef TEST_ARDUINO_HARDWARE_HPP
#define TEST_ARDUINO_HARDWARE_HPP

#include <unity.h>
#include <Arduino.h>

#include "ArduinoAdapter.hpp"

namespace test_ArduinoHardware {

void setup_test(){
    pinMode(LED_BUILTIN, OUTPUT);
}

void teardown_test(){

}

void test_led_state_high(void)
{
  setup_test();

  digitalWrite(LED_BUILTIN, HIGH);
  TEST_ASSERT_EQUAL(HIGH, digitalRead(LED_BUILTIN));

  teardown_test();
}

void test_led_state_low(void)
{
  setup_test();

  digitalWrite(LED_BUILTIN, LOW);
  TEST_ASSERT_EQUAL(LOW, digitalRead(LED_BUILTIN));

  teardown_test();
}

void Run(){
  RUN_TEST(test_led_state_high);
  delay(500);
  RUN_TEST(test_led_state_low);
  delay(500);
}

}

#endif