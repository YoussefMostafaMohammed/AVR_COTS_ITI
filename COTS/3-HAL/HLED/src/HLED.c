#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MPORT.h"
#include "MDIO.h"
#include "HLED_CFG.h"
#include "HLED.h"

extern HLED_structConfigrations_t HLED_enuArrLedConfig[NUMBER_OF_LEDS];

HLED_enuErrorStatus_t HLED_enuInit(void){
    HLED_enuErrorStatus_t Ret_enuErrorStatus = HLED_ENU_OK;
    MDIO_enuPortNum_t Local_enuCurrentPort;
    MDIO_enuPinNum_t Local_enuCurrentPin;
    HLED_ConnectioOpt_t Local_enuCurrentConnection;
    for(uint8_t itr=0; (itr<NUMBER_OF_LEDS); itr++){
        Local_enuCurrentPort=HLED_enuArrLedConfig[itr].HLED_PORT;
        Local_enuCurrentPin=HLED_enuArrLedConfig[itr].HLED_Pin;
        Local_enuCurrentConnection=HLED_enuArrLedConfig[itr].HLED_Connection;
        MPORT_enuPinPortNum_t Local_enuCurrentPinPort=((Local_enuCurrentPort << 4U) | Local_enuCurrentPin) ;
        
        if(Local_enuCurrentPort>3 || Local_enuCurrentPort < 0){
            Ret_enuErrorStatus= MDIO_ENU_INVALID_PORT_NUM;
        }
        else if(Local_enuCurrentPin <0 ||  Local_enuCurrentPin >7 ){
            Ret_enuErrorStatus= MDIO_ENU_INVALID_PIN_NUM;
        }
        else{
           /* Shhhhhhhhhhhhhh */
        }
         /* Set the Led to High */
        Ret_enuErrorStatus=MPORT_enuSetPinDirection(Local_enuCurrentPinPort,MPORT_ENU_PORT_PIN_OUTPUT);
            /*Set the Led to low*/
        if(Local_enuCurrentConnection==HLED_Forward){
            Ret_enuErrorStatus=MDIO_enuSetPinValue(Local_enuCurrentPort,Local_enuCurrentPin,MDIO_ENU_PIN_LOW);
        }else if(Local_enuCurrentConnection==HLED_Reverse){
            Ret_enuErrorStatus=MDIO_enuSetPinValue(Local_enuCurrentPort,Local_enuCurrentPin,MDIO_ENU_PIN_HIGH);
        }else{
            /* Shhhhhhhhhhhhhhhhhhhhh */
        }
    }
    return Ret_enuErrorStatus;
}

HLED_enuErrorStatus_t HLED_enuSetLedState(uint8_t Copy_u8LedName, HLED_enuPinState_t Copy_u8State){
    HLED_enuErrorStatus_t Ret_enuErrorStatus = HLED_ENU_OK;
    
    MDIO_enuPortNum_t Local_enuCurrentPort=HLED_enuArrLedConfig[Copy_u8LedName].HLED_PORT;
    MDIO_enuPinNum_t Local_enuCurrentPin=HLED_enuArrLedConfig[Copy_u8LedName].HLED_Pin;
    HLED_ConnectioOpt_t Local_enuCurrentConnection=HLED_enuArrLedConfig[Copy_u8LedName].HLED_Connection;
    
    if(Local_enuCurrentPort>3 || Local_enuCurrentPort < 0){
        Ret_enuErrorStatus= HLED_ENU_INVALID_PORT_NUM;
    }else if(Local_enuCurrentPin <0 ||  Local_enuCurrentPin >7 ){
        Ret_enuErrorStatus= HLED_ENU_INVALID_PIN_NUM;
    }else if((Local_enuCurrentConnection!=HLED_Reverse) && (Local_enuCurrentConnection != HLED_Forward)){
        Ret_enuErrorStatus= HLED_ENU_INVALID_LED_CONNECTION;
    }else if((Copy_u8State!=HLED_ENU_HIGH) && (Copy_u8State!=HLED_ENU_LOW)){
        Ret_enuErrorStatus=HLED_ENU_INVALID_LED_STATE;
    }else{
        if(Local_enuCurrentConnection==HLED_Forward){
            Ret_enuErrorStatus=MDIO_enuSetPinValue(Local_enuCurrentPort,Local_enuCurrentPin,Copy_u8State);
        }else if(Local_enuCurrentConnection==HLED_Reverse){
            Ret_enuErrorStatus=MDIO_enuSetPinValue(Local_enuCurrentPort,Local_enuCurrentPin,!Copy_u8State);
        }else{
                /* Shhhhhhhhhhhhhhhhhhhhh */
        } 
    }

    
    return Ret_enuErrorStatus;
}
