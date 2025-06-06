#ifndef MDIO_H_
#define MDIO_H_



#include "MDIO.h"
#include "STD_TYPES.h"

typedef enum{
        MDIO_ENU_OK,
        MDIO_ENU_INVALID_PARAM,
        MDIO_ENU_INVALID_PIN_NUM,
        MDIO_ENU_INVALID_PORT_NUM,  
        MDIO_ENU_INVALID_PIN_CONFIG,  
        MDIO_ENU_INVALID_PORT_CONFIG,
        MDIO_ENU_INVALID_PIN_STATE,  
        MDIO_ENU_INVALID_PORT_STATE,
        MDIO_ENU_NULL_PTR,
        MDIO_ENU_NOK
}MDIO_enuErrorStatus_t;

typedef enum{
    MDIO_ENU_PORTA,
    MDIO_ENU_PORTB,
    MDIO_ENU_PORTC,
    MDIO_ENU_PORTD
}MDIO_enuPortNum_t;

typedef enum{
    MDIO_ENU_PIN0,
    MDIO_ENU_PIN1,
    MDIO_ENU_PIN2,
    MDIO_ENU_PIN3,
    MDIO_ENU_PIN4,
    MDIO_ENU_PIN5,
    MDIO_ENU_PIN6,
    MDIO_ENU_PIN7
}MDIO_enuPinNum_t;

typedef enum{
    MDIO_ENU_PIN_LOW,
    MDIO_ENU_PIN_HIGH,
}MDIO_enuPinState_t;

typedef enum{
    MDIO_ENU_PORT_LOW=0x00,
    MDIO_ENU_PORT_HIGH=0xFF,
}MDIO_enuPortState_t;

MDIO_enuErrorStatus_t MDIO_enuSetPortCustomValue(MDIO_enuPortNum_t Copy_enuPortNum,uint8_t Copy_enuPortState);

MDIO_enuErrorStatus_t MDIO_enuSetPinValue(MDIO_enuPortNum_t Copy_enuPortNum,MDIO_enuPinNum_t Copy_enuPinNum,MDIO_enuPinState_t Copy_enuPinState);

MDIO_enuErrorStatus_t MDIO_enuSetPortValue(MDIO_enuPortNum_t Copy_enuPortNum,MDIO_enuPortState_t Copy_enuPortState);

MDIO_enuErrorStatus_t MDIO_enuGetPinValue(MDIO_enuPortNum_t Copy_enuPortNum, MDIO_enuPinNum_t Copy_enuPinNum,uint8_t* Add_puint8_tPinValue);

#endif