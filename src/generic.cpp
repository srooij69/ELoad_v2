#ifndef GENERIC_CPP
#define GENERIC_CPP

#include "ArduinoAdapter.hpp"

#include "presenter.hpp"
#include "sensors.hpp"
#include "fsm.hpp"

void main_setup(){
  ArduinoAdapter::setup();
  presenter::setup();
  sensors::setup();
}

void main_loop(){
  unsigned long __now;
  config::eRunMode __runMode;

  __now = sensors::read();
  __runMode = fsm::handle_state(__now);
  presenter::display_runMode(__runMode);
  presenter::display_sensorData(__runMode);
  presenter::blink_led(__now);
}

#endif