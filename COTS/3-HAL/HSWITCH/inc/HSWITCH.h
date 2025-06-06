#ifndef HSWITCH_H_
#define HSWITCH_H_

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MDIO.h"
#include "MPORT.h"
#include "HSWITCH_CFG.h"

typedef enum{
        HSWITCH_ENU_OK,
        HSWITCH_ENU_INVALID_PARAM,
        HSWITCH_ENU_INVALID_PIN_NUM,
        HSWITCH_ENU_INVALID_PORT_NUM,
        HSWITCH_ENU_INVALID_SWITCH_CONNECTION,
        HSWITCH_ENU_INVALID_MODE,
        HSWITCH_ENU_INVALID_SWITCH_STATE,  
        HSWITCH_ENU_NULL_PTR,
        HSWITCH_ENU_NOK
}HSWITCH_enuErrorStatus_t;

typedef enum{
   HSWITCH_ENU_LOW,
   HSWITCH_ENU_HIGH,
}HSWITCH_enuPinState_t;


typedef enum{
    HSWITCH_PULLUP,
    HSWITCH_PULLDOWN
}HSWITCH_ConnectioOpt_t;

typedef struct {
    MDIO_enuPortNum_t HSWITCH_PORT;
    MDIO_enuPortNum_t HSWITCH_Pin;
    HSWITCH_ConnectioOpt_t HSWITCH_Connection;
}HSWITCH_structConfigrations_t;

HSWITCH_enuErrorStatus_t HSEVENSEG_enuInit(void);
HSWITCH_enuErrorStatus_t HSEVENSEG_vSetValue(uint8_t Copy_enuSevenSegNum , uint8_t Copy_u8Value);
#endif