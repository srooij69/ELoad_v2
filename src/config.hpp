#ifndef ELOAD_CONFIG_HPP
#define ELOAD_CONFIG_HPP

#define _OFF   0x0000000
#define _RED   0x0FF0000
#define _GREEN 0x000F400
#define _BLUE  0x00000FF
#define _BLINK 0x8000000

namespace config {
    enum eRunMode {
          Init
        , SelectCC, SelectCV, SelectCP, SelectCR
        , RunCC, RunCV, RunCP, RunCR
        , Error, Dummy };

    enum eConfigValue {
      MaxTemp
    };

    const uint32_t configValue [] = {100000};

    const uint16_t Period_Show_Flash_millis = 500;
    const uint16_t Led_Blink_millis         = 200;

    const uint16_t Button_Interval_Short =  30;
    const uint16_t Button_Interval_Long  = 400;

    const uint32_t runmode_colors[] = { 
          _OFF
        , _BLUE , _BLUE , _BLUE , _BLUE
        , _GREEN, _GREEN, _GREEN, _GREEN
        , _RED+_BLINK   , _OFF };     

    const char * splash_text[] = {"   ELoad v2.1       "," by Steven de Rooij "};

    const char * runmode_titles[] = {
          "               "
        , "C.Curr   Select", "C.Volt   Select", "C.Power  Select", "C.Resist Select"
        , "C.Curr   Run   ", "C.Volt   Run   ", "C.Power  Run   ", "C.Resist Run   "
        , "        ERROR  ", "               " };
}

#endif