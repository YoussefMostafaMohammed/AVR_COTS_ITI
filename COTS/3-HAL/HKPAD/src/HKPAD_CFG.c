#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MPORT.h"
#include "MDIO.h"
#include "HKPAD_CFG.h"
#include "HKPAD.h"

HKBAD_structLcdCfg_t HKBAD_enuArrKbadConfig[NUMBER_OF_KBADS]={
    [KPAD_ONE] = {
        .RowPins = {
            [HKBAD_ENU_ROW_1] = MPORT_enuPIN_C0,
            [HKBAD_ENU_ROW_2] = MPORT_enuPIN_C1,
            [HKBAD_ENU_ROW_3] = MPORT_enuPIN_C2,
            [HKBAD_ENU_ROW_4] = MPORT_enuPIN_C3,
        },
        .ColumnPins={
            [HKBAD_ENU_COLUMN_1] = MPORT_enuPIN_C4,
            [HKBAD_ENU_COLUMN_2] = MPORT_enuPIN_C5,
            [HKBAD_ENU_COLUMN_3] = MPORT_enuPIN_C6,
            [HKBAD_ENU_COLUMN_4] = MPORT_enuPIN_C7,
        }
    }
};



