#include <Arduino.h>
#include <unity.h>

#include "test_arduino_hardware.hpp"
#include "test_fsm.hpp"
#include "test_presenter.hpp"

#include "test_ArduinoAdapter.hpp"

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void setup()
{
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay(2000);

  UNITY_BEGIN(); // IMPORTANT LINE!
}

void loop()
{
    test_ArduinoHardware::Run();
    test_fsm::Run();
    test_presenter::Run();

    test_ArduinoAdapter::Run();

  UNITY_END(); // stop unit testing
}