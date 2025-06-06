#include "HSWITCH.h"

extern HSWITCH_structConfigrations_t HSWITCH_enuArrSwitchConfig[NUMBER_OF_SWITCHS];

HSWITCH_enuErrorStatus_t HSWITCH_enuInit(void){
    HSWITCH_enuErrorStatus_t Ret_enuErrorStatus = HSWITCH_ENU_OK;
    MDIO_enuPortNum_t Local_enuCurrentPort;
    MDIO_enuPinNum_t Local_enuCurrentPin;
    HSWITCH_ConnectioOpt_t Local_enuCurrentConnection;

    for(uint8_t itr=0;(itr<NUMBER_OF_SWITCHS);itr++){
        Local_enuCurrentPort=HSWITCH_enuArrSwitchConfig[itr].HSWITCH_PORT;
        Local_enuCurrentPin=HSWITCH_enuArrSwitchConfig[itr].HSWITCH_Pin;
        Local_enuCurrentConnection=HSWITCH_enuArrSwitchConfig[itr].HSWITCH_Connection;
        MPORT_enuPinPortNum_t Local_enuCurrentPinPort=(Local_enuCurrentPort<<4U | Local_enuCurrentPin) ;
        
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
        Ret_enuErrorStatus = MPORT_enuSetPinDirection(Local_enuCurrentPinPort,MPORT_ENU_PORT_PIN_INPUT);
            /*Set the Led to low*/
        if(Local_enuCurrentConnection==HSWITCH_PULLUP){
            Ret_enuErrorStatus=MDIO_enuSetPinValue(Local_enuCurrentPort,Local_enuCurrentPin,MDIO_ENU_PIN_HIGH);
        }else if(Local_enuCurrentConnection==HSWITCH_PULLDOWN){
            Ret_enuErrorStatus=MDIO_enuSetPinValue(Local_enuCurrentPort,Local_enuCurrentPin,MDIO_ENU_PIN_LOW);
        }else{
            /* Shhhhhhhhhhhhhhhhhhhhh */
        }

    }
    return Ret_enuErrorStatus;
}

HSWITCH_enuErrorStatus_t HSWITCH_enuGetSwitchState(uint8_t Copy_u8SwitchName, uint8_t*Add_pu8State)
{
    HSWITCH_enuErrorStatus_t Ret_enuErrorStatus = HSWITCH_ENU_NOK;
    
    MDIO_enuPortNum_t Local_enuCurrentPort = HSWITCH_enuArrSwitchConfig[Copy_u8SwitchName].HSWITCH_PORT;
    MDIO_enuPinNum_t Local_enuCurrentPin=HSWITCH_enuArrSwitchConfig[Copy_u8SwitchName].HSWITCH_Pin;
    HSWITCH_ConnectioOpt_t Local_enuCurrentConnection=HSWITCH_enuArrSwitchConfig[Copy_u8SwitchName].HSWITCH_Connection;
    
    if(Local_enuCurrentPort>3 || Local_enuCurrentPort < 0){
        Ret_enuErrorStatus= HSWITCH_ENU_INVALID_PORT_NUM;
    }else if(Local_enuCurrentPin <0 ||  Local_enuCurrentPin >7 ){
        Ret_enuErrorStatus= HSWITCH_ENU_INVALID_PIN_NUM;
    }else if((Local_enuCurrentConnection!=HSWITCH_PULLDOWN) && (Local_enuCurrentConnection != HSWITCH_PULLUP)){
        Ret_enuErrorStatus= HSWITCH_ENU_INVALID_SWITCH_CONNECTION;
    }else if(Add_pu8State == NULL){
        Ret_enuErrorStatus=HSWITCH_ENU_NULL_PTR;
    }else{
        Ret_enuErrorStatus=MDIO_enuGetPinValue(Local_enuCurrentPort,Local_enuCurrentPin,Add_pu8State);  
        if(Ret_enuErrorStatus!=HSWITCH_ENU_OK){
            Ret_enuErrorStatus=HSWITCH_ENU_OK;
        }
    }
    
    return Ret_enuErrorStatus;
}
