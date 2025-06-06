#include "HSEVENSEG_CFG.h"
#include "HSEVENSEG.h"
#include <util/delay.h>


int main(void){

    HSEVENSEG_enuvInit();
    while(1){
        for(uint8_t value =0; value<1000; value++){
            HSEVENSEG_enuSetMultiDigitValue(value);   
            _delay_ms(10);
        }
    }
    return 0;
}