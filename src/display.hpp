#ifndef ELOAD_DISPLAY_HPP
#define ELOAD_DISPLAY_HPP

#define LED_RED   0
#define LED_GREEN 1
#define LED_BLUE  2
#define NR_LEDS   3

namespace display {
    char lines[4][21];
    uint8_t leds[NR_LEDS];

    void clear(){
        for(int i=0;i<4; i++){
            for(int j=0;j<20; j++) lines[i][j]=' ';
            lines[i][20]='\0';
        }
        for(int i=0;i<NR_LEDS; i++){
            leds[i]=0;
        }
    }

    void writeText(int row, int col, const char * txt){
        int i=0;
        while( txt[i] != '\0'){
            lines[row][col+i] = txt[i];
            i++;
        } 
    }
}


#endif