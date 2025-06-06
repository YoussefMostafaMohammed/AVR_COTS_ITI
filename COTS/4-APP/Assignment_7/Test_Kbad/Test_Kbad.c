#include "HCLCD_CFG.h"
#include "HCLCD.h"
#include "HKPAD_CFG.h"
#include "HKPAD.h"
#include <util/delay.h>

int main(){
    HKBAD_enuInit();
    HCLCD_enuInit();
    uint8_t PressedKey=0xFF,row=0,column=0;
    while(1){
        HKBAD_enuGetPressedKey(&PressedKey,KPAD_ONE);
        if(PressedKey=='C'){
            HCLCD_enuWriteCommand(CLEAR_DISPLAY,LCD_ONE);
        }else if(PressedKey=='r' ){
            if(column==15)column=0;
            else column+=1;
        }else if (PressedKey=='l'){
            if(column==0)column=15;
            else column-=1;
        }else if(PressedKey=='u'){
            row^=1;
        }else if(PressedKey=='d'){
            row^=1;
        }else if(PressedKey!=0xFF){
            HCLCD_enuWriteString("Youssef",LCD_ONE);
        }
        HCLCD_enuGotoRowColumn(row,column,LCD_ONE);
    }
    return 0;
}
