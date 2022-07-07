#include <unity.h>

#include "test_fsm.hpp"
#include "test_ArduinoAdapter.hpp"
#include "test_presenter.hpp"

void setUp(void)
{
  
}

void tearDown(void)
{
}

int main( int argc, char **argv){
  UNITY_BEGIN(); // IMPORTANT LINE!

  ArduinoAdapter::setup();
  presenter::setup();

  test_fsm::Run();
  test_ArduinoAdapter::Run();
  test_presenter::Run();

  UNITY_END(); // stop unit testing
}
