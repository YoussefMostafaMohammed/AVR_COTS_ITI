#ifndef HKPAD_H_
#define HKPAD_H_

#include "MPORT.h"
#include "MDIO.h"
#include "STD_TYPES.h"

typedef enum{
        HKBAD_ENU_OK,
        HKBAD_ENU_INVALID_CLCD_MODE,
        HKBAD_ENU_INVALID_ROW,
        HKBAD_ENU_INVALID_COLUMN,
        HKBAD_ENU_INVALID_PATTERN_NUM,
        HKBAD_ENU_INVALID_CLCD_NUM,
        HKBAD_ENU_INVALID_PIN_NUM,
        HKBAD_ENU_INVALID_PORT_NUM,
        HKBAD_ENU_INVALID_PIN_CONFIG,  
        HKBAD_ENU_INVALID_PORT_CONFIG,
        HKBAD_ENU_INVALID_PIN_STATE,  
        HKBAD_ENU_INVALID_PORT_STATE,
        HKBAD_ENU_NULL_PTR,
        HKBAD_ENU_NOK
}HKBAD_enuErrorStatus_t;

typedef enum{
    HKBAD_ENU_ROW_1,
    HKBAD_ENU_ROW_2,
    HKBAD_ENU_ROW_3,
    HKBAD_ENU_ROW_4
}HKBAD_enuRowPins_t;

typedef enum{
    HKBAD_ENU_COLUMN_1,
    HKBAD_ENU_COLUMN_2,
    HKBAD_ENU_COLUMN_3,
    HKBAD_ENU_COLUMN_4
}HKBAD_enuColumnPins_t;

typedef struct{
        MPORT_enuPinPortNum_t RowPins[4];
        MPORT_enuPinPortNum_t ColumnPins[4];
}HKBAD_structLcdCfg_t;

HKBAD_enuErrorStatus_t HKBAD_enuInit(void);
HKBAD_enuErrorStatus_t HKBAD_enuGetPressedKey(uint8_t* Addr_PressedValue,uint8_t Copyuint8_KpadNum);
#endif