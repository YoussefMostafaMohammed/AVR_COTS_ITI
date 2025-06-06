#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MDIO.h"
#include "MPORT.h"
#include "HSEVENSEG_CFG.h"
#include "HSEVENSEG.h"


HSEVENSEG_structConfigrations_t HSEVENSEG_enuArrSevenSegConfig[NUMBER_OF_SEVENSEGS]=
{
    [SEVENSEG_ONE] = {
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_A]  = MPORT_enuPIN_A0,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_B]  = MPORT_enuPIN_A1,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_C]  = MPORT_enuPIN_A2,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_D]  = MPORT_enuPIN_A3,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_E]  = MPORT_enuPIN_A4,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_F]  = MPORT_enuPIN_A5,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_G]  = MPORT_enuPIN_A6,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_DP] = MPORT_enuPIN_A7,
        .HSEVENSEG_Connection = HSEVENSEG_COMMON_CATHODE
    },
    [SEVENSEG_TWO] = {
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_A]  = MPORT_enuPIN_B0,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_B]  = MPORT_enuPIN_B1,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_C]  = MPORT_enuPIN_B2,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_D]  = MPORT_enuPIN_B3,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_E]  = MPORT_enuPIN_B4,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_F]  = MPORT_enuPIN_B5,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_G]  = MPORT_enuPIN_B6,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_DP] = MPORT_enuPIN_B7,
        .HSEVENSEG_Connection = HSEVENSEG_COMMON_CATHODE
    },
    [SEVENSEG_THREE] = {
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_A]  = MPORT_enuPIN_C0,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_B]  = MPORT_enuPIN_C1,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_C]  = MPORT_enuPIN_C2,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_D]  = MPORT_enuPIN_C3,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_E]  = MPORT_enuPIN_C4,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_F]  = MPORT_enuPIN_C5,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_G]  = MPORT_enuPIN_C6,
        .HSEVENSEG_enuPinsNumArr[HSEVENSEG_PIN_DP] = MPORT_enuPIN_C7,
        .HSEVENSEG_Connection = HSEVENSEG_COMMON_CATHODE
    }

};





