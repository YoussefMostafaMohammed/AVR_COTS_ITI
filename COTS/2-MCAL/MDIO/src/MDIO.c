#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MDIO_REG.h"
#include "MDIO_CFG.h"
#include "MDIO.h"

MDIO_enuErrorStatus_t MDIO_enuSetPinValue(MDIO_enuPortNum_t Copy_enuPortNum,MDIO_enuPinNum_t Copy_enuPinNum,MDIO_enuPinState_t Copy_enuPinState){
    MDIO_enuErrorStatus_t Ret_enuErrorStatus= MDIO_ENU_OK;  
    if(Copy_enuPortNum>3 || Copy_enuPortNum < 0){
        Ret_enuErrorStatus= MDIO_ENU_INVALID_PORT_NUM;
    }
    else if(Copy_enuPinNum <0 ||  Copy_enuPinNum >7 ){
        Ret_enuErrorStatus= MDIO_ENU_INVALID_PIN_NUM;
    }
    else if(Copy_enuPinState<0 || Copy_enuPinState >1){
        Ret_enuErrorStatus= MDIO_ENU_INVALID_PIN_STATE;
    }else{
        /*Shhhhhhhhhhhhhhhhh*/
    }
    
    MDIO_structPortRegElement_t* Local_structPtrCurrPort = MDIO_GET_PORT_ADD(Copy_enuPortNum);

    if(Copy_enuPinState==MDIO_ENU_PIN_HIGH){
        SET_BIT(Local_structPtrCurrPort->PORT,Copy_enuPinNum);
    }

    if(Copy_enuPinState==MDIO_ENU_PIN_LOW){
        CLR_BIT(Local_structPtrCurrPort->PORT,Copy_enuPinNum);
    }
    
    return Ret_enuErrorStatus;
}

MDIO_enuErrorStatus_t MDIO_enuSetPortValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPortState_t Copy_enuPortState){
    MDIO_enuErrorStatus_t Ret_enuErrorStatus= MDIO_ENU_OK;  
    if(Copy_enuPortNum>3 || Copy_enuPortNum < 0){
        Ret_enuErrorStatus= MDIO_ENU_INVALID_PORT_NUM;
    }
    else if(Copy_enuPortState<0 || Copy_enuPortState >1){
        Ret_enuErrorStatus= MDIO_ENU_INVALID_PORT_STATE;
    }else{
        /*Shhhhhhhhhhhhhhhhh*/
    }
    
    MDIO_structPortRegElement_t* Local_structPtrCurrPort = MDIO_GET_PORT_ADD(Copy_enuPortNum);
    Local_structPtrCurrPort->PORT=Copy_enuPortState;

    return Ret_enuErrorStatus;
}


MDIO_enuErrorStatus_t MDIO_enuSetPortCustomValue(MDIO_enuPortNum_t Copy_enuPortNum,uint8_t Copy_enuPortState){
    MDIO_enuErrorStatus_t Ret_enuErrorStatus= MDIO_ENU_OK;  
    
    if(Copy_enuPortNum>3 || Copy_enuPortNum < 0){
            Ret_enuErrorStatus= MDIO_ENU_INVALID_PORT_NUM;
    }
    else if((Copy_enuPortState>=255)){
        Ret_enuErrorStatus= MDIO_ENU_INVALID_PORT_STATE;
    }else{
        /*Shhhhhhhhhhhhhhhhh*/
    }
    
    MDIO_structPortRegElement_t* Local_structPtrCurrPort = MDIO_GET_PORT_ADD(Copy_enuPortNum);
    Local_structPtrCurrPort->PORT=Copy_enuPortState;

    return Ret_enuErrorStatus;
}

MDIO_enuErrorStatus_t MDIO_enuGetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum,uint8_t* Add_puint8_tPinValue){
    MDIO_enuErrorStatus_t Ret_enuErrorStatus= MDIO_ENU_OK;  
    
    if((Copy_enuPortNum>3) || (Copy_enuPortNum < 0)){
            Ret_enuErrorStatus= MDIO_ENU_INVALID_PARAM;
    }
    else if((Copy_enuPinNum <0) ||  (Copy_enuPinNum >7) ){
            Ret_enuErrorStatus = MDIO_ENU_INVALID_PARAM;
    }
    else if(Add_puint8_tPinValue == NULL){
            Ret_enuErrorStatus= MDIO_ENU_INVALID_PARAM;
    }
    else{
        /*Shhhhhhhhhhhhhhhhhhhhhhh*/
    }
    
    MDIO_structPortRegElement_t* Local_structPtrCurrPort = MDIO_GET_PORT_ADD(Copy_enuPortNum);
    (*Add_puint8_tPinValue)=GET_BIT(Local_structPtrCurrPort->PIN,Copy_enuPinNum);
    
    return Ret_enuErrorStatus;
}
