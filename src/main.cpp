
#include "ArduinoAdapter.hpp"

#include "presenter.hpp"
#include "sensors.hpp"
#include "fsm.hpp"

void main_setup(){
  sensors::setup();
}

void main_loop(){
  unsigned long __now;
  config::eRunMode __runMode;

  __now = sensors::read();
  __runMode = fsm::handle_state(__now);
  presenter::display_sensorData(__runMode);
  presenter::display_runMode(__runMode);
  presenter::blink_led(__now);
}


void main(){

}
void setup() {
  // put your setup code here, to run once:
 
 
}

void loop() {
  // put your main code here, to run repeatedly:


}

