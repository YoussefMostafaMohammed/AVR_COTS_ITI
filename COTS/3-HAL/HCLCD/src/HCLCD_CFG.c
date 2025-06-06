#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MPORT.h"
#include "MDIO.h"
#include "HCLCD_CFG.h"
#include "HCLCD.h"

// use pins from HCLCD_ENU_PIN_D4 to HCLCD_ENU_PIN_D7 in 4 bit mode
HCLCD_structLcdCfg_t HCLCD_enuArrLcdConfig[NUMBER_OF_LCDS]={
    [LCD_ONE] = {
        .ClcdType = HCLCD_2x16,
        .ClcdMode = HCLCD_4_BIT_MODE,
        .DataPins = {
            [HCLCD_ENU_PIN_D0] = MPORT_enuPIN_A0,
            [HCLCD_ENU_PIN_D1] = MPORT_enuPIN_A1,
            [HCLCD_ENU_PIN_D2] = MPORT_enuPIN_A2,
            [HCLCD_ENU_PIN_D3] = MPORT_enuPIN_A3,
            [HCLCD_ENU_PIN_D4] = MPORT_enuPIN_A4,
            [HCLCD_ENU_PIN_D5] = MPORT_enuPIN_A5,
            [HCLCD_ENU_PIN_D6] = MPORT_enuPIN_A6,
            [HCLCD_ENU_PIN_D7] = MPORT_enuPIN_A7,
        },
        .PowerPins={
            [HCLCD_ENU_PIN_RS] = MPORT_enuPIN_B0,
            [HCLCD_ENU_PIN_RW] = MPORT_enuPIN_B1,
            [HCLCD_ENU_PIN_E]  = MPORT_enuPIN_B2,
        }
    }
};

