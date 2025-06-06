#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MDIO.h"
#include "MPORT.h"
#include "MDIO_CFG.h"
#include <util/delay.h>

int main(void){
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTA,MDIO_ENU_PIN0,MPORT_ENU_PIN_INPUT_PULLUP);
    //MPORT_enuSetPinConfigration(MDIO_ENU_PORTA,MDIO_ENU_PIN1,MPORT_ENU_PIN_INPUT_PULLUP);
 
    MPORT_enuSetPinDirection(MPORT_enuPIN_A1,MPORT_ENU_PORT_PIN_INPUT);
    MPORT_enuSetPinMode(MPORT_enuPIN_A1,MPORT_ENU_PIN_MODE_INPUT_PULLUP);
 
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTC,MDIO_ENU_PIN0,MPORT_ENU_PIN_OUTPUT);
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTC,MDIO_ENU_PIN1,MPORT_ENU_PIN_OUTPUT);
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTC,MDIO_ENU_PIN2,MPORT_ENU_PIN_OUTPUT);
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTC,MDIO_ENU_PIN3,MPORT_ENU_PIN_OUTPUT);
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTC,MDIO_ENU_PIN4,MPORT_ENU_PIN_OUTPUT);
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTC,MDIO_ENU_PIN5,MPORT_ENU_PIN_OUTPUT);
    MPORT_enuSetPinConfigration(MDIO_ENU_PORTC,MDIO_ENU_PIN6,MPORT_ENU_PIN_OUTPUT);
    //MPORT_enuSetPinConfigration(MDIO_ENU_PORTC,MDIO_ENU_PIN7,MPORT_ENU_PIN_OUTPUT);
    MPORT_enuSetPinDirection(MPORT_enuPIN_C7,MPORT_ENU_PIN_OUTPUT);
   while(1){
        uint8_t pressedValue1=-1, pressedValue2=-1;
        // turn on odd leds (1-3-5-7)
        
        if(MDIO_enuGetPinValue(MDIO_ENU_PORTA,MDIO_ENU_PIN0,&pressedValue1)==MDIO_ENU_OK && (pressedValue1==0)){ 
            while((MDIO_enuGetPinValue(MDIO_ENU_PORTA,MDIO_ENU_PIN0,&pressedValue1)==MDIO_ENU_OK) && (pressedValue1==0));
            MDIO_enuSetPortValue(MDIO_ENU_PORTC,MDIO_ENU_PORT_LOW);
            MDIO_enuSetPortCustomValue(MDIO_ENU_PORTC,170);
        // turn on even leds (0-2-4-6)
        }else if(MDIO_enuGetPinValue(MDIO_ENU_PORTA,MDIO_ENU_PIN1,&pressedValue2)==MDIO_ENU_OK && (pressedValue2==0)){
		    while((MDIO_enuGetPinValue(MDIO_ENU_PORTA,MDIO_ENU_PIN1,&pressedValue2)==MDIO_ENU_OK) && (pressedValue2==0));
            MDIO_enuSetPortValue(MDIO_ENU_PORTC,MDIO_ENU_PORT_LOW);
            MDIO_enuSetPortCustomValue(MDIO_ENU_PORTC,85);
        }    
        }

    return 0;  
}
