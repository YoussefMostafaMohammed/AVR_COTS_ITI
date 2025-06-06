#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MDIO.h"
#include "MPORT.h"
#include "MDIO_CFG.h"
#include <util/delay.h>

int main(void){
    
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTA,MDIO_ENU_PIN0,MPORT_ENU_PIN_INPUT_PULLUP);
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTA,MDIO_ENU_PIN1,MPORT_ENU_PIN_INPUT_PULLUP);
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTC,MDIO_ENU_PIN0,MPORT_ENU_PIN_OUTPUT);
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTC,MDIO_ENU_PIN1,MPORT_ENU_PIN_OUTPUT);
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTC,MDIO_ENU_PIN2,MPORT_ENU_PIN_OUTPUT);
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTC,MDIO_ENU_PIN3,MPORT_ENU_PIN_OUTPUT);
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTC,MDIO_ENU_PIN4,MPORT_ENU_PIN_OUTPUT);
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTC,MDIO_ENU_PIN5,MPORT_ENU_PIN_OUTPUT);
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTC,MDIO_ENU_PIN6,MPORT_ENU_PIN_OUTPUT);
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTC,MDIO_ENU_PIN7,MPORT_ENU_PIN_OUTPUT);
    
    uint8_t cnt=0;
    while(1){
        uint8_t pressedValue1=-1, pressedValue2=-1;
        if(MDIO_enuGetPinValue(MDIO_ENU_PORTA,MDIO_ENU_PIN0,&pressedValue1)==MDIO_ENU_OK && (pressedValue1==0)){ 
            while((MDIO_enuGetPinValue(MDIO_ENU_PORTA,MDIO_ENU_PIN0,&pressedValue1)==MDIO_ENU_OK) && (pressedValue1==0));
            cnt+=1;
            MDIO_enuSetPortCustomValue(MDIO_ENU_PORTC,cnt);
        }else if(MDIO_enuGetPinValue(MDIO_ENU_PORTA,MDIO_ENU_PIN1,&pressedValue2)==MDIO_ENU_OK && (pressedValue2==0)){
		    while((MDIO_enuGetPinValue(MDIO_ENU_PORTA,MDIO_ENU_PIN1,&pressedValue2)==MDIO_ENU_OK) && (pressedValue2==0));
            cnt-=1;
            MDIO_enuSetPortCustomValue(MDIO_ENU_PORTC,cnt);
        }
        if(cnt <0 )cnt=0;
    }

    return 0;  
}