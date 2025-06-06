#include "HCLCD_CFG.h"
#include "HCLCD.h"
#include <util/delay.h>
uint8_t Hamada1[8] = {0b01110, 0b01110, 0b00100, 0b10101, 0b01110, 0b00100, 0b01010, 0b10001};

int main(void){
    HCLCD_enuInit();
    HCLCD_enuStoreSpecialChar(Hamada1,0,LCD_ONE);
    while(1){
        HCLCD_enuDisplaySpecialChar(0,0,0,LCD_ONE);
        _delay_ms(1000);
        HCLCD_enuWriteCommand(CLEAR_DISPLAY,LCD_ONE);  
        _delay_ms(1000);
    }
    return 0;
}