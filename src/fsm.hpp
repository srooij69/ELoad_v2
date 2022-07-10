#ifndef ELOAD_FSM_HPP
#define ELOAD_FSM_HPP

#include "config.hpp"
#include "presenter.hpp"
#include "sensors.hpp"

namespace fsm {
  unsigned long __now = 0;

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

void handle_state(){  
  config::eRunMode newState = state.runMode;

  switch( state.runMode){
    case config::Init : {  
      if(  state.IsInStateFor(config::Period_Show_Flash_millis) ) newState = config::SelectCC;
      break; }
    case config::SelectCC : {  
      if( presenter::buttons[BUTTON_MODE] == presenter::Short) newState = config::SelectCV;
      if( presenter::buttons[BUTTON_RUN ] == presenter::Short) newState = config::RunCC;
      break; }
    case config::SelectCV : {
      if( presenter::buttons[BUTTON_MODE] == presenter::Short) newState = config::SelectCP;
      if( presenter::buttons[BUTTON_RUN ] == presenter::Short) newState = config::RunCV;
      break; }
    case config::SelectCP : {
      if( presenter::buttons[BUTTON_MODE] == presenter::Short) newState = config::SelectCR;
      if( presenter::buttons[BUTTON_RUN ] == presenter::Short) newState = config::RunCP;
      break; }
    case config::SelectCR : {
      if( presenter::buttons[BUTTON_MODE] == presenter::Short) newState = config::SelectCC;
      if( presenter::buttons[BUTTON_RUN ] == presenter::Short) newState = config::RunCR;
      break; }

    case config::RunCC : {  
      if( presenter::buttons[BUTTON_RUN ] == presenter::Short) newState = config::SelectCC;
      break; }
    case config::RunCV : {
      if( presenter::buttons[BUTTON_RUN ] == presenter::Short) newState = config::SelectCV;
      break; }
    case config::RunCP : {
      if( presenter::buttons[BUTTON_RUN ] == presenter::Short) newState = config::SelectCP;
      break; }
    case config::RunCR : {
      if( presenter::buttons[BUTTON_RUN ] == presenter::Short) newState = config::SelectCR;
      break; }

    case config::Error :{
      break; }
    case config::Dummy :{
      break; }
  }

  state.set(newState);
}

void tick(){  
  __now = presenter::tick();
  handle_state();
  presenter::DisplayRunMode(state.runMode);
}

}

#endif