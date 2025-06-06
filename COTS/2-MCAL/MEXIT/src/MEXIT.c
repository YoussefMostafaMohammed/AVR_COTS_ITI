#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MEXIT_CFG.h"
#include "MEXIT.h"

#define MCUCR *((volatile uint8_t*)(0x55))

#define MCUCSR *((volatile uint8_t*)(0x54))
#define MCUCSR_ISC2 64

#define GICR *((volatile uint8_t*)(0x5B))
#define GICR_INT2 32
#define GICR_INT1 64 
#define GICR_INT0 128 

void MEXTI_voidInit(void){

}

MEXIT_enuErrorStatus_t MEXTI_voidEnable(MEXTI_enuIntNum_t Copy_enuIntSource){
    MEXIT_enuErrorStatus_t Ret_enuErrotStatus = MEXIT_ENU_OK;
    switch (Copy_enuIntSource)
    {
        case MEXIT_ENU_INTERRUPT_0:
            GICR |=GICR_INT0;
            break;
        case MEXIT_ENU_INTERRUPT_1:
            GICR |=GICR_INT1;
            break;
        case MEXIT_ENU_INTERRUPT_2: 
            GICR |=GICR_INT2;
            break;
        default:
            Ret_enuErrotStatus = MEXIT_ENU_INVALID_INTERRUPT_NUMBER;
            break;
    }
    return Ret_enuErrotStatus;
}

MEXIT_enuErrorStatus_t MEXTI_voidDisable(MEXTI_enuIntNum_t Copy_enuIntSource){
    MEXIT_enuErrorStatus_t Ret_enuErrotStatus = MEXIT_ENU_OK;
    switch (Copy_enuIntSource)
    {
        case MEXIT_ENU_INTERRUPT_0:
            GICR &=~GICR_INT0;
            break;
        case MEXIT_ENU_INTERRUPT_1:
            GICR &=~GICR_INT1;
            break;
        case MEXIT_ENU_INTERRUPT_2: 
            GICR &=~GICR_INT2;
            break;
        default:
            Ret_enuErrotStatus = MEXIT_ENU_INVALID_INTERRUPT_NUMBER;
            break;
    }
    return Ret_enuErrotStatus;
}

MEXIT_enuErrorStatus_t MEXTI_vidSetSenseControl(MEXTI_enuIntNum_t Copy_enuIntSource, MEXTI_enuTrigger_t Copy_enuIntTrigger){
    MEXIT_enuErrorStatus_t Ret_enuErrotStatus = MEXIT_ENU_OK;
    if(Copy_enuIntSource > MEXIT_ENU_INTERRUPT_2){
        Ret_enuErrotStatus=MEXIT_ENU_INVALID_INTERRUPT_NUMBER;
    }else if(Copy_enuIntTrigger > MEXIT_ENU_RISING_EDGE){
        Ret_enuErrotStatus=MEXIT_ENU_INVALID_TRIGGER;        
    }else if( (Copy_enuIntSource == MEXIT_ENU_INTERRUPT_2) && (Copy_enuIntTrigger <= MEXIT_ENU_ANY_CHANGE)){
        Ret_enuErrotStatus=MEXIT_ENU_INVALID_TRIGGER_FOR_INT2;
    }else{
        if(Copy_enuIntSource!=MEXIT_ENU_INTERRUPT_2){
            MCUCR &= ~Copy_enuIntTrigger;
            MCUCR |= Copy_enuIntTrigger;
        }else {
            if(Copy_enuIntTrigger==MEXIT_ENU_FALLING_EDGE){
                MCUCSR |= MCUCSR_ISC2;
            }else{            
                MCUCSR &= ~MCUCSR_ISC2;
            }
        }
    }
    return Ret_enuErrotStatus;
}

void ISR(){

}


