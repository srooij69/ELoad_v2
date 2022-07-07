#ifndef ELOAD_CONFIG_HPP
#define ELOAD_CONFIG_HPP

namespace config {
    enum eRunMode {
          Init
        , SelectCC, SelectCV, SelectCP, SelectCR
        , RunCC, RunCV, RunCP, RunCR
        , Dummy };

    const uint16_t Period_Show_Flash_millis = 500;

    const uint16_t Button_Interval_Short =  30;
    const uint16_t Button_Interval_Long  = 400;

    const uint32_t runmode_colors[] = { 
          0x000000
        , 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF
        , 0x00F400, 0x00F400, 0x00F400, 0x00F400
        , 0x000000 };     

    const char * splash_text[] = {"   ELoad v2.1       "," by Steven de Rooij "};

    const char * runmode_titles[] = {
          "               "
        , "C.Curr   Select","C.Volt   Select", "C.Power  Select" , "C.Resist Select"
        , "C.Curr   Run   "      , "C.Volt   Run   "      , "C.Power  Run   "      , "C.Resist Run   "
        , "               " };
}

#endif