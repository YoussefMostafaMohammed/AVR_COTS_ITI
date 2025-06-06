#ifndef HSEVENSEG_H_
#define HSEVENSEG_H_

#include "STD_TYPES.h"
#include "MPORT.h"

typedef enum{
        HSEVENSEG_ENU_OK,
        HSEVENSEG_ENU_INVALID_PARAM,
        HSEVENSEG_ENU_INVALID_PIN_NUM,
        HSEVENSEG_ENU_INVALID_PORT_NUM,
        HSEVENSEG_ENU_INVALID_NUMBER_OF_DIGIT,
        HSEVENSEG_ENU_INVALID_NUMBER,
        HSEVENSEG_ENU_INVALID_SEVENSEG_CONNECTION,
        HSEVENSEG_ENU_INVALID_SEVENSEG_STATE,  
        HSEVENSEG_ENU_NULL_PTR,
        HSEVENSEG_ENU_NOK
}HSEVENSEG_enuErrorStatus_t;

typedef enum{
   HSEVENSEG_ENU_LOW,
   HSEVENSEG_ENU_HIGH,
}HSEVENSEG_enuPinState_t;

typedef enum{
    HSEVENSEG_COMMON_CATHODE,
    HSEVENSEG_COMMON_ANODE
}HSEVENSEG_ConnectioOpt_t;

typedef struct {
        MPORT_enuPinPortNum_t HSEVENSEG_enuPinsNumArr[NUMBER_OF_SEVENSEG_PINS];
        HSEVENSEG_ConnectioOpt_t HSEVENSEG_Connection;
}HSEVENSEG_structConfigrations_t;

HSEVENSEG_enuErrorStatus_t HSEVENSEG_enuvInit(void);
HSEVENSEG_enuErrorStatus_t HSEVENSEG_vSetValue(uint8_t Copy_enuSevenSegNum , uint8_t Copy_u8Value);
HSEVENSEG_enuErrorStatus_t HSEVENSEG_enuSetMultiDigitValue(uint16_t Copy_u16Value);

#endif