#ifndef MEXIT_H_
#define MEXIT_H_

typedef enum{
        MEXIT_ENU_OK,
        MEXIT_ENU_INVALID_INTERRUPT_NUMBER,
        MEXIT_ENU_INVALID_TRIGGER,
        MEXIT_ENU_INVALID_TRIGGER_FOR_INT2,
        MEXIT_ENU_NOK
}MEXIT_enuErrorStatus_t;

typedef enum{
    MEXIT_ENU_INTERRUPT_0,
    MEXIT_ENU_INTERRUPT_1,
    MEXIT_ENU_INTERRUPT_2,
}MEXTI_enuIntNum_t;

typedef enum{
    MEXIT_ENU_LOW_LEVEL,
    MEXIT_ENU_ANY_CHANGE,
    MEXIT_ENU_FALLING_EDGE,
    MEXIT_ENU_RISING_EDGE
}MEXTI_enuTrigger_t;



// typedef struct {

//     MEXTI_enuTrigger_t Trigger;
// }MEXIT_enuExitconfigration_t;

void MEXTI_voidInit(void);
MEXIT_enuErrorStatus_t MEXTI_voidEnable(MEXTI_enuIntNum_t Copy_enuIntSource);
MEXIT_enuErrorStatus_t MEXTI_voidDisable(MEXTI_enuIntNum_t Copy_enuIntSource);
MEXIT_enuErrorStatus_t MEXTI_vidSetSenseControl(MEXTI_enuIntNum_t Copy_enuIntSource, MEXTI_enuTrigger_t Copy_enuTrigger);

#endif