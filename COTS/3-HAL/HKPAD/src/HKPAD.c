#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MPORT.h"
#include "MDIO.h"
#include "HKPAD_CFG.h"
#include "HKPAD.h"
#include <util/delay.h>

extern HKBAD_structLcdCfg_t HKBAD_enuArrKbadConfig[NUMBER_OF_KBADS];

HKBAD_enuErrorStatus_t HKBAD_enuInit(void){
    HKBAD_enuErrorStatus_t Ret_enuErrorStatus = HKBAD_ENU_OK;
    for(int itr =0; itr<NUMBER_OF_KBADS; itr++){
        for(int pinItr =0; pinItr<4; pinItr++){
            MPORT_enuSetPinDirection(HKBAD_enuArrKbadConfig[itr].RowPins[pinItr],MPORT_ENU_PORT_PIN_INPUT);
            MPORT_enuSetPinMode(HKBAD_enuArrKbadConfig[itr].RowPins[pinItr],MPORT_ENU_PIN_MODE_INPUT_PULLUP);
            MPORT_enuSetPinDirection(HKBAD_enuArrKbadConfig[itr].ColumnPins[pinItr],MPORT_ENU_PORT_PIN_OUTPUT);
            MDIO_enuSetPinValue((HKBAD_enuArrKbadConfig[itr].ColumnPins[pinItr]>>4),(HKBAD_enuArrKbadConfig[itr].ColumnPins[pinItr]&0x0F),MDIO_ENU_PIN_HIGH);
        }
    }
    return Ret_enuErrorStatus;   
}

HKBAD_enuErrorStatus_t HKBAD_enuGetPressedKey(uint8_t* Addr_PressedValue,uint8_t Copyuint8_KpadNum){
    HKBAD_enuErrorStatus_t Ret_enuErrorStatus = HKBAD_ENU_OK;   
    uint8_t Localuint8_Status=1,Localuint8_isPressed=0;
    *Addr_PressedValue=0xFF;
    for(uint8_t columnItr = 0; columnItr <  HKEYPAD_NO_OF_COLS; columnItr++){
        MDIO_enuSetPinValue((HKBAD_enuArrKbadConfig[Copyuint8_KpadNum].ColumnPins[columnItr]>>4),(HKBAD_enuArrKbadConfig[Copyuint8_KpadNum].ColumnPins[columnItr]&0x0F),MDIO_ENU_PIN_LOW);
        for(uint8_t rowItr = 0; rowItr <  HKEYPAD_NO_OF_ROWS; rowItr++){
            Ret_enuErrorStatus = MDIO_enuGetPinValue((HKBAD_enuArrKbadConfig[Copyuint8_KpadNum].RowPins[rowItr]>>4),(HKBAD_enuArrKbadConfig[Copyuint8_KpadNum].RowPins[rowItr]&0x0F),&Localuint8_Status);
            if(Localuint8_Status == MDIO_ENU_PIN_LOW){
                *Addr_PressedValue=HKEYPAD_uint8CharArr[rowItr][columnItr];
                while(Localuint8_Status == MDIO_ENU_PIN_LOW)
                    Ret_enuErrorStatus = MDIO_enuGetPinValue((HKBAD_enuArrKbadConfig[Copyuint8_KpadNum].RowPins[rowItr]>>4),(HKBAD_enuArrKbadConfig[Copyuint8_KpadNum].RowPins[rowItr]&0x0F),&Localuint8_Status);
                Localuint8_isPressed=1;
                break;
            }
        }
        MDIO_enuSetPinValue((HKBAD_enuArrKbadConfig[Copyuint8_KpadNum].ColumnPins[columnItr]>>4),(HKBAD_enuArrKbadConfig[Copyuint8_KpadNum].ColumnPins[columnItr]&0x0F),MDIO_ENU_PIN_HIGH);
        if(Localuint8_isPressed)
            break;
    }
    return Ret_enuErrorStatus;
}

