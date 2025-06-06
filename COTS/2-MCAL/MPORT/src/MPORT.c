#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MDIO_REG.h"
#include "MPORT_CFG.h"
#include "MPORT.h"

extern MPORT_enuPinConfigration_t MPORT_enuArrPinConfig[MPORT_NUM_OF_PORTS * MPORT_NUM_OF_PINS];

void MPORT_vInit(void){
    MPORT_enuPortNum_t Local_enuCurrentPort;
    MPORT_enuPinNum_t Local_enuCurrentPin;
    for(uint8_t itr=0;itr<(MPORT_NUM_OF_PORTS * MPORT_NUM_OF_PINS);itr++){
        Local_enuCurrentPort=itr/8;
        Local_enuCurrentPin=itr%8;
        MPORT_enuSetPinConfigration(Local_enuCurrentPort,Local_enuCurrentPin,MPORT_enuArrPinConfig[itr]);
    }
}

MPORT_enuErrorStatus_t MPORT_enuSetPinConfigration(MPORT_enuPortNum_t Copy_enuPortNum, MPORT_enuPinNum_t Copy_enuPinNum, MPORT_enuPinConfigration_t Copy_enuConfigration){
    MPORT_enuErrorStatus_t Ret_enuErrorStatus= MPORT_ENU_OK;  
    if(Copy_enuPortNum>3 || Copy_enuPortNum < 0){
            Ret_enuErrorStatus= MPORT_ENU_INVALID_PORT_NUM;
    }
    else if (Copy_enuPinNum>7 || Copy_enuPinNum <0){
            Ret_enuErrorStatus= MPORT_ENU_INVALID_PIN_NUM;
    }
    else if(Copy_enuConfigration <0 ||  Copy_enuConfigration >1 ){
            Ret_enuErrorStatus= MPORT_ENU_INVALID_PIN_CONFIG;
    }else{
        /* Shhhhhhhhhhhhhhhhhhhh */
    }

    MDIO_structPortRegElement_t* Local_structPtrCurrPort = MDIO_GET_PORT_ADD(Copy_enuPortNum);
    
    if(Copy_enuConfigration==MPORT_ENU_PIN_OUTPUT){
        SET_BIT(Local_structPtrCurrPort->DDR,Copy_enuPinNum);
    }
    else if(Copy_enuConfigration==MPORT_ENU_PIN_INPUT_PULLUP){
        CLR_BIT(Local_structPtrCurrPort->DDR,Copy_enuPinNum);  
        SET_BIT(Local_structPtrCurrPort->PORT,Copy_enuPinNum);
    }
    else if(Copy_enuConfigration==MPORT_ENU_PIN_INPUT_PULLDOWN){
        CLR_BIT(Local_structPtrCurrPort->DDR,Copy_enuPinNum);   
    }
    else{
        /* Shhhhhhhhhhhhhhhhhhhh */
    }

    return Ret_enuErrorStatus;
}

MPORT_enuErrorStatus_t MPORT_enuSetPortConfigration(MPORT_enuPortNum_t Copy_enuPortNum,MPORT_enuPortConfigration_t Copy_enuConfigration){
    MPORT_enuErrorStatus_t Ret_enuErrorStatus= MPORT_ENU_OK;  
    
    if(Copy_enuPortNum>3 || Copy_enuPortNum < 0){
            Ret_enuErrorStatus= MPORT_ENU_INVALID_PORT_NUM;
    }
    else if(Copy_enuConfigration <0 ||  Copy_enuConfigration >1 ){
            Ret_enuErrorStatus= MPORT_ENU_INVALID_PORT_CONFIG;
    }
    else {
        /* Shhhhhhhhhhhhhhhhhhhhh */
    }
    
    MDIO_structPortRegElement_t* Local_structPtrCurrPort = MDIO_GET_PORT_ADD(Copy_enuPortNum);

    if(Copy_enuConfigration==MPORT_ENU_PORT_OUTPUT){
        Local_structPtrCurrPort->DDR=Copy_enuConfigration;
    }
    else if(Copy_enuConfigration==MPORT_ENU_PORT_INPUT_PULLUP){
        Local_structPtrCurrPort->DDR=Copy_enuConfigration;
        Local_structPtrCurrPort->PORT=0xFF;
    }   
    else if(Copy_enuConfigration==MPORT_ENU_PORT_INPUT_PULLDOWN){
        Local_structPtrCurrPort->DDR=Copy_enuConfigration;
    }
    else{
        /* Shhhhhhhhhhhhhhhhhh */
    }
    return Ret_enuErrorStatus;
}


MPORT_enuErrorStatus_t MPORT_enuSetPinDirection( MPORT_enuPinPortNum_t Copy_enuPinNum  ,  MPORT_enuPortPinDir_t  Copy_enuPinDirection  ){
    MPORT_enuErrorStatus_t Ret_enuErrorStatus=MPORT_ENU_OK;
    
    uint8_t Local_uint8PinNum = GET_LOW_NIB(Copy_enuPinNum);
    uint8_t Local_uint8PortNum = GET_HIGH_NIB(Copy_enuPinNum);

    if((Local_uint8PinNum >= MPORT_NUM_OF_PINS) ){
        Ret_enuErrorStatus=MPORT_ENU_INVALID_PIN_NUM;
    }else if(Local_uint8PortNum>=MPORT_NUM_OF_PORTS){
        Ret_enuErrorStatus= MPORT_ENU_INVALID_PORT_NUM;    
    }else if( (Copy_enuPinDirection != MPORT_ENU_PORT_PIN_OUTPUT) && (Copy_enuPinDirection!=MPORT_ENU_PORT_PIN_INPUT) ){
        Ret_enuErrorStatus= MPORT_ENU_INVALID_DIRECTION;
    }    
    else{
        /* Shhhhhhhhhhhhhhhhhh */
    }
    MDIO_structPortRegElement_t* Local_structPtrCurrPort = MDIO_GET_PORT_ADD(Local_uint8PortNum);

    if(Copy_enuPinDirection==MPORT_ENU_PORT_PIN_OUTPUT){
        SET_BIT(Local_structPtrCurrPort->DDR, Local_uint8PinNum);
    }else if(Copy_enuPinDirection==MPORT_ENU_PORT_PIN_INPUT){
        CLR_BIT(Local_structPtrCurrPort->DDR, Local_uint8PinNum);
    }else{
        /* Shhhhhhhhhhhhhhhhhh */
    }
    return Ret_enuErrorStatus;
}

MPORT_enuErrorStatus_t MPORT_enuSetPinMode( MPORT_enuPinPortNum_t Copy_enuPinNum  ,  MPORT_enuPortPinMode_t Copy_enuPinMode ){
    MPORT_enuErrorStatus_t Ret_enuErrorStatus=MPORT_ENU_OK;
    
    uint8_t Local_uint8PinNum = GET_LOW_NIB(Copy_enuPinNum);
    uint8_t Local_uint8PortNum = GET_HIGH_NIB(Copy_enuPinNum);

    if((Local_uint8PinNum >= MPORT_NUM_OF_PINS)){
        Ret_enuErrorStatus=MPORT_ENU_INVALID_PIN_NUM;
    } 
    else if((Local_uint8PortNum>=MPORT_NUM_OF_PORTS)){
        Ret_enuErrorStatus= MPORT_ENU_INVALID_PORT_NUM;
    } 
    else if((Copy_enuPinMode <0 ) ||(Copy_enuPinMode >=4 ) ){
        Ret_enuErrorStatus= MPORT_ENU_INVALID_MODE;
    } 
    else{
        /* shhhhhhhhhhhhh */
    }

    MDIO_structPortRegElement_t* Local_structPtrCurrPort = MDIO_GET_PORT_ADD(Local_uint8PortNum);

    if(Copy_enuPinMode==MPORT_ENU_PIN_MODE_INPUT_PULLUP){
        SET_BIT(Local_structPtrCurrPort->PORT, Local_uint8PinNum);
    }else if(Copy_enuPinMode==MPORT_ENU_PIN_MODE_INPUT_PULLDOWN){
        CLR_BIT(Local_structPtrCurrPort->PORT, Local_uint8PinNum);
    }else if(Copy_enuPinMode==MPORT_ENU_PIN_MODE_UART){
        /* Not Now */
    }else{
        /* shhhhhhhhhhhh */
    }

    return Ret_enuErrorStatus;
}


