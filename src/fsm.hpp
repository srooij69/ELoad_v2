#ifndef ELOAD_FSM_HPP
#define ELOAD_FSM_HPP

#include "config.hpp"
#include "presenter.hpp"
#include "sensors.hpp"

#include "ArduinoAdapter.hpp"


namespace fsm {
  unsigned long __now = 0;
  uint32_t __breached_limit=0;
  int __breached_sensor=0;

struct State{
  config::eRunMode runMode = config::eRunMode::Init;
  unsigned long prev_state_switch = 0;

  void set(config::eRunMode new_runMode){
    if( runMode == new_runMode) return;
    runMode = new_runMode;
    prev_state_switch = __now;
  }

  bool IsInStateFor(unsigned long milliseconds){
    unsigned long now = __now;
    return now-prev_state_switch > milliseconds;
  }

};

State state;

void setup(){
  __now = 0;
  state.runMode = config::Init;
  state.prev_state_switch = 0;
}

bool breachesLimit(int sensor, uint32_t limit){
  __breached_limit = limit;
  __breached_sensor = sensor;

  return (sensors::sensors[sensor] > config::configValue[limit]);
}

config::eRunMode handle_state(unsigned long now){
  config::eRunMode newState = state.runMode;
  __now = now;  

  switch( state.runMode){
    case config::Init : {  
      if(  state.IsInStateFor(config::Period_Show_Flash_millis) ) newState = config::SelectCC;
      break; }
    case config::SelectCC : {  
      if( sensors::buttons[BUTTON_MODE] == sensors::Short) newState = config::SelectCV;
      if( sensors::buttons[BUTTON_RUN ] == sensors::Short) newState = config::RunCC;
      break; }
    case config::SelectCV : {
      if( sensors::buttons[BUTTON_MODE] == sensors::Short) newState = config::SelectCP;
      if( sensors::buttons[BUTTON_RUN ] == sensors::Short) newState = config::RunCV;
      break; }
    case config::SelectCP : {
      if( sensors::buttons[BUTTON_MODE] == sensors::Short) newState = config::SelectCR;
      if( sensors::buttons[BUTTON_RUN ] == sensors::Short) newState = config::RunCP;
      break; }
    case config::SelectCR : {
      if( sensors::buttons[BUTTON_MODE] == sensors::Short) newState = config::SelectCC;
      if( sensors::buttons[BUTTON_RUN ] == sensors::Short) newState = config::RunCR;
      break; }

    case config::RunCC : {  
      if( sensors::buttons[BUTTON_RUN ] == sensors::Short) newState = config::SelectCC;
      break; }
    case config::RunCV : {
      if( sensors::buttons[BUTTON_RUN ] == sensors::Short) newState = config::SelectCV;
      break; }
    case config::RunCP : {
      if( sensors::buttons[BUTTON_RUN ] == sensors::Short) newState = config::SelectCP;
      break; }
    case config::RunCR : {
      if( sensors::buttons[BUTTON_RUN ] == sensors::Short) newState = config::SelectCR;
      break; }

    case config::Error :{
      break; }
    case config::Dummy :{
      break; }
  }

  if( breachesLimit(SENSOR_TEMP, config::MaxTemp) ) newState = config::Error;

  state.set(newState);

  return state.runMode;
}

}

#endif