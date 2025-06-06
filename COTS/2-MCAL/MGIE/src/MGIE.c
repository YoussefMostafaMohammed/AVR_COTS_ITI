#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MGIE.h"   

#define SREG *((volatile uint8_t *)0x5F)
#define SREG_I 7

MGIE_enuErrorStatus_t MGIE_enuEnableGIE(void){
    MGIE_enuErrorStatus_t Ret_enuErrorStatus = MGIE_ENU_OK;
    (SREG) |= (1<<SREG_I);
    return Ret_enuErrorStatus;
}

MGIE_enuErrorStatus_t MGIE_enuDisableGIE(void){
    MGIE_enuErrorStatus_t Ret_enuErrorStatus=MGIE_ENU_OK;
    (SREG) &= ~(1<<SREG_I);
    return Ret_enuErrorStatus;
}
