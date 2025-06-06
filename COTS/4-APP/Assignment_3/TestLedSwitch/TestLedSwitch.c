#include "HLED_CFG.h"
#include "HSWITCH_CFG.h"
#include "HSWITCH.h"
#include "HLED.h"
#include <util/delay.h>

int main(void){
    HLED_enuInit();
    HSWITCH_enuInit();
    while(1){
        uint8_t pressedValue1=-1, pressedValue2=-1,pressedValue3=-1;
        if((HSWITCH_enuGetSwitchState(SWITCH_START,&pressedValue1)==HSWITCH_ENU_OK) && (pressedValue1==0)){ 
            while((HSWITCH_enuGetSwitchState(SWITCH_START,&pressedValue1)==HSWITCH_ENU_OK) && (pressedValue1==0));
            HLED_enuSetLedState(LED_START,HLED_ENU_HIGH);
            HLED_enuSetLedState(LED_STOP,HLED_ENU_LOW);
            HLED_enuSetLedState(LED_ALERT,HLED_ENU_LOW);
        }else if((HSWITCH_enuGetSwitchState(SWITCH_STOP,&pressedValue2)==HSWITCH_ENU_OK) && (pressedValue2==0)){
		    while((HSWITCH_enuGetSwitchState(SWITCH_STOP,&pressedValue2)==HSWITCH_ENU_OK) && (pressedValue2==0));
            HLED_enuSetLedState(LED_START,HLED_ENU_LOW);
            HLED_enuSetLedState(LED_STOP,HLED_ENU_HIGH);
            HLED_enuSetLedState(LED_ALERT,HLED_ENU_LOW);
        }else if((HSWITCH_enuGetSwitchState(SWITCH_ALERT,&pressedValue3)==HSWITCH_ENU_OK) && (pressedValue3==0)){
		    while((HSWITCH_enuGetSwitchState(SWITCH_ALERT,&pressedValue3)==HSWITCH_ENU_OK) && (pressedValue3==0));
            HLED_enuSetLedState(LED_START,HLED_ENU_LOW);
            HLED_enuSetLedState(LED_STOP,HLED_ENU_LOW);
            HLED_enuSetLedState(LED_ALERT,HLED_ENU_HIGH);
        }
    }
    return 0;
}