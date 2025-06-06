#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MPORT.h"
#include "MDIO.h"
#include "HCLCD_CFG.h"
#include "HCLCD.h"
#include <util/delay.h>

#define DDRAM_BASE_COMMAND 0b10000000
#define CGRAM_BASE_COMMAND 0b01000000

extern HCLCD_structLcdCfg_t HCLCD_enuArrLcdConfig[NUMBER_OF_LCDS];
static float64_t HCLCD_enuWriteNumberHelperPowerFunction(float64_t base, float64_t power);
static HCLCD_enuErrorStatus_t HCLCD_enuWriteNumberHelper(uint64_t Copyfloat64_number, uint8_t Copy_uint8LcdNum);

HCLCD_enuErrorStatus_t HCLCD_enuInit(void){
    HCLCD_enuErrorStatus_t Ret_enuErrorStatus=HCLCD_ENU_OK;
    for(uint8_t itr=0; itr < NUMBER_OF_LCDS; itr++){
        for(uint8_t pin=0; pin<HCLCD_enuArrLcdConfig[itr].ClcdMode; pin++){
            if(HCLCD_enuArrLcdConfig[itr].ClcdMode == HCLCD_4_BIT_MODE){
                MPORT_enuSetPinDirection(HCLCD_enuArrLcdConfig[itr].DataPins[pin + 4],MPORT_ENU_PIN_OUTPUT);
            }else{
                MPORT_enuSetPinDirection(HCLCD_enuArrLcdConfig[itr].DataPins[pin],MPORT_ENU_PIN_OUTPUT);
            }
        }
        for(int pin=0; pin <3; pin++){
            MPORT_enuSetPinDirection(HCLCD_enuArrLcdConfig[itr].PowerPins[pin],MPORT_ENU_PIN_OUTPUT);
        }

        _delay_ms(40);
        if(HCLCD_enuArrLcdConfig[itr].ClcdMode == HCLCD_4_BIT_MODE)
            HCLCD_enuWriteCommand(FUNCTION_SET_4BIT_2_LINES_5x8, itr);
        else
            HCLCD_enuWriteCommand(FUNCTION_SET_8BIT_2_LINES_5x8, itr);
        _delay_ms(2);
        HCLCD_enuWriteCommand(DISPLAY_ON_CURSOR_BLINK, itr);
        _delay_ms(2);
        HCLCD_enuWriteCommand(CLEAR_DISPLAY, itr);
        _delay_ms(2);
        HCLCD_enuWriteCommand(DISABLE_AUTO_SHIFT, itr);
        _delay_ms(2);
    }
    return Ret_enuErrorStatus;
}

HCLCD_enuErrorStatus_t HCLCD_enuWriteCommand(uint8_t Copyu8Command,uint8_t Copy_u8LcdNum){
    HCLCD_enuErrorStatus_t Ret_enuErrorStatus=HCLCD_ENU_OK;
    
    MDIO_enuPortNum_t Local_enuPortNumRS = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].PowerPins[HCLCD_ENU_PIN_RS]);
    MDIO_enuPinNum_t Local_enuPinNumRS = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].PowerPins[HCLCD_ENU_PIN_RS]);
    
    MDIO_enuPortNum_t Local_enuPortNumRW = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].PowerPins[HCLCD_ENU_PIN_RW]);
    MDIO_enuPinNum_t Local_enuPinNumRW = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].PowerPins[HCLCD_ENU_PIN_RW]);
    
    MDIO_enuPortNum_t Local_enuPortNumE = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].PowerPins[HCLCD_ENU_PIN_E]);
    MDIO_enuPinNum_t Local_enuPinNumE = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].PowerPins[HCLCD_ENU_PIN_E]);
    
    MDIO_enuSetPinValue(Local_enuPortNumRS,Local_enuPinNumRS,MDIO_ENU_PIN_LOW);
    MDIO_enuSetPinValue(Local_enuPortNumRW,Local_enuPinNumRW,MDIO_ENU_PIN_LOW);
    MDIO_enuSetPinValue(Local_enuPortNumE,Local_enuPinNumE,MDIO_ENU_PIN_LOW);

    if(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].ClcdMode == HCLCD_8_BIT_MODE){
        for(uint8_t itr=0; itr<HCLCD_enuArrLcdConfig[Copy_u8LcdNum].ClcdMode; itr++){
            MDIO_enuPortNum_t Local_enuPortNum = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].DataPins[itr]);
            MDIO_enuPinNum_t Local_enuPinNum = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].DataPins[itr]);
            MDIO_enuSetPinValue(Local_enuPortNum,Local_enuPinNum,(Copyu8Command>>itr)&1);
        }
    }
    else if(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].ClcdMode == HCLCD_4_BIT_MODE){
        for(uint8_t itr=0; itr<HCLCD_enuArrLcdConfig[Copy_u8LcdNum].ClcdMode; itr++){
            MDIO_enuPortNum_t Local_enuPortNum = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].DataPins[itr+4]);
            MDIO_enuPinNum_t Local_enuPinNum = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].DataPins[itr+4]);
            MDIO_enuSetPinValue(Local_enuPortNum,Local_enuPinNum,(Copyu8Command>>(itr+4))&1);
        }
        
        MDIO_enuSetPinValue(Local_enuPortNumE,Local_enuPinNumE,MDIO_ENU_PIN_HIGH);
        _delay_ms(3);
        MDIO_enuSetPinValue(Local_enuPortNumE,Local_enuPinNumE,MDIO_ENU_PIN_LOW);
        
        for(uint8_t itr=0; itr<HCLCD_enuArrLcdConfig[Copy_u8LcdNum].ClcdMode; itr++){
            MDIO_enuPortNum_t Local_enuPortNum = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].DataPins[itr+4]);
            MDIO_enuPinNum_t Local_enuPinNum = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].DataPins[itr+4]);
            MDIO_enuSetPinValue(Local_enuPortNum,Local_enuPinNum,(Copyu8Command>>(itr))&1);
        }
    }else{
        Ret_enuErrorStatus=HCLCD_ENU_INVALID_CLCD_MODE;
    }
    MDIO_enuSetPinValue(Local_enuPortNumE,Local_enuPinNumE,MDIO_ENU_PIN_HIGH);
    _delay_ms(3);
    MDIO_enuSetPinValue(Local_enuPortNumE,Local_enuPinNumE,MDIO_ENU_PIN_LOW);

    return Ret_enuErrorStatus;
}

HCLCD_enuErrorStatus_t HCLCD_enuReadCommand(uint8_t* Adduint8_Data, uint8_t Copy_uint8LcdNum){
    HCLCD_enuErrorStatus_t Ret_enuErrorStatus = HCLCD_ENU_OK;
    
    /* Input Validation */
    if(Copy_uint8LcdNum >= NUMBER_OF_LCDS) {
        return HCLCD_ENU_INVALID_CLCD_NUM;
    }
    if(Adduint8_Data == NULL) {
        return HCLCD_ENU_NULL_PTR;
    }

    /* Extract Control Pins */
    MDIO_enuPortNum_t Local_enuPortNumRS = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].PowerPins[HCLCD_ENU_PIN_RS]);
    MDIO_enuPinNum_t Local_enuPinNumRS = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].PowerPins[HCLCD_ENU_PIN_RS]);
    
    MDIO_enuPortNum_t Local_enuPortNumRW = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].PowerPins[HCLCD_ENU_PIN_RW]);
    MDIO_enuPinNum_t Local_enuPinNumRW = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].PowerPins[HCLCD_ENU_PIN_RW]);
    
    MDIO_enuPortNum_t Local_enuPortNumE = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].PowerPins[HCLCD_ENU_PIN_E]);
    MDIO_enuPinNum_t Local_enuPinNumE = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].PowerPins[HCLCD_ENU_PIN_E]);
    
    /* Set Control Pins */
    MDIO_enuSetPinValue(Local_enuPortNumRS, Local_enuPinNumRS, MDIO_ENU_PIN_LOW);  // Data mode
    MDIO_enuSetPinValue(Local_enuPortNumRW, Local_enuPinNumRW, MDIO_ENU_PIN_HIGH);  // Read mode
    MDIO_enuSetPinValue(Local_enuPortNumE, Local_enuPortNumE, MDIO_ENU_PIN_LOW);     // Ensure E starts low

    /* Temporary Data Storage */
    uint8_t temp_data = 0;
    uint8_t pin_state = 0;

    if(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].ClcdMode == HCLCD_8_BIT_MODE) {
        /* Set Data Pins as Inputs */
        for(uint8_t itr = 0; itr < 8; itr++) {
            MPORT_enuSetPinDirection(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr], MPORT_ENU_PORT_PIN_INPUT);
            MPORT_enuSetPinMode(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr],MPORT_ENU_PIN_MODE_INPUT_PULLUP);
        }

        /* Read Cycle */
        MDIO_enuSetPinValue(Local_enuPortNumE, Local_enuPinNumE, MDIO_ENU_PIN_HIGH);
        _delay_ms(1);
        
        for(uint8_t itr = 0; itr < 8; itr++) {
            MDIO_enuPortNum_t Local_enuPortNum = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr]);
            MDIO_enuPinNum_t Local_enuPinNum = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr]);
            MDIO_enuGetPinValue(Local_enuPortNum, Local_enuPinNum, &pin_state);
            temp_data |= (pin_state << itr);
        }
        
        MDIO_enuSetPinValue(Local_enuPortNumE, Local_enuPinNumE, MDIO_ENU_PIN_LOW);

        /* Restore Data Pins to Output */
        for(uint8_t itr = 0; itr < 8; itr++) {
            MPORT_enuSetPinDirection(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr], MPORT_ENU_PORT_PIN_OUTPUT);
        }
    }
    else if(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].ClcdMode == HCLCD_4_BIT_MODE) {
        /* Set D4-D7 as Inputs */
        for(uint8_t itr = 4; itr < 8; itr++) {
            MPORT_enuSetPinDirection(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr], MPORT_ENU_PORT_PIN_INPUT);
            MPORT_enuSetPinMode(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr],MPORT_ENU_PIN_MODE_INPUT_PULLUP);
            }

        /* Read High Nibble First */
        MDIO_enuSetPinValue(Local_enuPortNumE, Local_enuPinNumE, MDIO_ENU_PIN_HIGH);
        _delay_ms(1);
        
        for(uint8_t itr = 4; itr < 8; itr++) {
            MDIO_enuPortNum_t Local_enuPortNum = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr]);
            MDIO_enuPinNum_t Local_enuPinNum = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr]);
            MDIO_enuGetPinValue(Local_enuPortNum, Local_enuPinNum, &pin_state);
            temp_data |= (pin_state << (itr));
        }
        
        MDIO_enuSetPinValue(Local_enuPortNumE, Local_enuPinNumE, MDIO_ENU_PIN_LOW);
        _delay_ms(1);

        /* Read Low Nibble */
        MDIO_enuSetPinValue(Local_enuPortNumE, Local_enuPinNumE, MDIO_ENU_PIN_HIGH);
        _delay_ms(1);
        
        for(uint8_t itr = 4; itr < 8; itr++) {
            MDIO_enuPortNum_t Local_enuPortNum = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr]);
            MDIO_enuPinNum_t Local_enuPinNum = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr]);
            MDIO_enuGetPinValue(Local_enuPortNum, Local_enuPinNum, &pin_state);
            temp_data |= (pin_state << (itr - 4));
        }
        
        MDIO_enuSetPinValue(Local_enuPortNumE, Local_enuPinNumE, MDIO_ENU_PIN_LOW);

        /* Restore Data Pins to Output */
        for(uint8_t itr = 4; itr < 8; itr++) {
            MPORT_enuSetPinDirection(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr], MPORT_ENU_PORT_PIN_OUTPUT);
        }
    }
    else {
        Ret_enuErrorStatus = HCLCD_ENU_INVALID_CLCD_MODE;
    }

    *Adduint8_Data = temp_data;
    return Ret_enuErrorStatus;
}

HCLCD_enuErrorStatus_t HCLCD_enuWriteData(uint8_t Copyu8Data,uint8_t Copy_u8LcdNum){
    HCLCD_enuErrorStatus_t Ret_enuErrorStatus=HCLCD_ENU_OK;
    
    MDIO_enuPortNum_t Local_enuPortNumRS = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].PowerPins[HCLCD_ENU_PIN_RS]);
    MDIO_enuPinNum_t Local_enuPinNumRS = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].PowerPins[HCLCD_ENU_PIN_RS]);
    
    MDIO_enuPortNum_t Local_enuPortNumRW = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].PowerPins[HCLCD_ENU_PIN_RW]);
    MDIO_enuPinNum_t Local_enuPinNumRW = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].PowerPins[HCLCD_ENU_PIN_RW]);
    
    MDIO_enuPortNum_t Local_enuPortNumE = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].PowerPins[HCLCD_ENU_PIN_E]);
    MDIO_enuPinNum_t Local_enuPinNumE = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].PowerPins[HCLCD_ENU_PIN_E]);
    
    MDIO_enuSetPinValue(Local_enuPortNumRS,Local_enuPinNumRS,MDIO_ENU_PIN_HIGH);
    
    MDIO_enuSetPinValue(Local_enuPortNumRW,Local_enuPinNumRW,MDIO_ENU_PIN_LOW);
    
    MDIO_enuSetPinValue(Local_enuPortNumE,Local_enuPinNumE,MDIO_ENU_PIN_LOW);

    if(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].ClcdMode == HCLCD_8_BIT_MODE){
        for(uint8_t itr=0; itr<HCLCD_enuArrLcdConfig[Copy_u8LcdNum].ClcdMode; itr++){
            MDIO_enuPortNum_t Local_enuPortNum = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].DataPins[itr]);
            MDIO_enuPinNum_t Local_enuPinNum = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].DataPins[itr]);
            MDIO_enuSetPinValue(Local_enuPortNum,Local_enuPinNum,(Copyu8Data>>(itr))&1);
        }
    }
    else if(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].ClcdMode == HCLCD_4_BIT_MODE){
        for(uint8_t itr=0; itr<HCLCD_enuArrLcdConfig[Copy_u8LcdNum].ClcdMode; itr++){
            MDIO_enuPortNum_t Local_enuPortNum = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].DataPins[itr+4]);
            MDIO_enuPinNum_t Local_enuPinNum = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].DataPins[itr+4]);
            MDIO_enuSetPinValue(Local_enuPortNum,Local_enuPinNum,(Copyu8Data>>(itr+4))&1);
        }
        
        MDIO_enuSetPinValue(Local_enuPortNumE,Local_enuPinNumE,MDIO_ENU_PIN_HIGH);
        _delay_ms(3);
        MDIO_enuSetPinValue(Local_enuPortNumE,Local_enuPinNumE,MDIO_ENU_PIN_LOW);
        
        for(uint8_t itr=0; itr<HCLCD_enuArrLcdConfig[Copy_u8LcdNum].ClcdMode; itr++){
            MDIO_enuPortNum_t Local_enuPortNum = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].DataPins[itr+4]);
            MDIO_enuPinNum_t Local_enuPinNum = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_u8LcdNum].DataPins[itr+4]);
            MDIO_enuSetPinValue(Local_enuPortNum,Local_enuPinNum,(Copyu8Data>>(itr))&1);
        }
    }else{
        Ret_enuErrorStatus=HCLCD_ENU_INVALID_CLCD_MODE;
    }
    MDIO_enuSetPinValue(Local_enuPortNumE,Local_enuPinNumE,MDIO_ENU_PIN_HIGH);
    _delay_ms(3);
    MDIO_enuSetPinValue(Local_enuPortNumE,Local_enuPinNumE,MDIO_ENU_PIN_LOW);

    return Ret_enuErrorStatus;
}

HCLCD_enuErrorStatus_t HCLCD_enuReadData(uint8_t* Adduint8_Data, uint8_t Copy_uint8LcdNum){
    HCLCD_enuErrorStatus_t Ret_enuErrorStatus = HCLCD_ENU_OK;
    
    /* Input Validation */
    if(Copy_uint8LcdNum >= NUMBER_OF_LCDS) {
        return HCLCD_ENU_INVALID_CLCD_NUM;
    }
    if(Adduint8_Data == NULL) {
        return HCLCD_ENU_NULL_PTR;
    }

    /* Extract Control Pins */
    MDIO_enuPortNum_t Local_enuPortNumRS = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].PowerPins[HCLCD_ENU_PIN_RS]);
    MDIO_enuPinNum_t Local_enuPinNumRS = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].PowerPins[HCLCD_ENU_PIN_RS]);
    
    MDIO_enuPortNum_t Local_enuPortNumRW = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].PowerPins[HCLCD_ENU_PIN_RW]);
    MDIO_enuPinNum_t Local_enuPinNumRW = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].PowerPins[HCLCD_ENU_PIN_RW]);
    
    MDIO_enuPortNum_t Local_enuPortNumE = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].PowerPins[HCLCD_ENU_PIN_E]);
    MDIO_enuPinNum_t Local_enuPinNumE = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].PowerPins[HCLCD_ENU_PIN_E]);
    
    /* Set Control Pins */
    MDIO_enuSetPinValue(Local_enuPortNumRS, Local_enuPinNumRS, MDIO_ENU_PIN_HIGH);  // Data mode
    MDIO_enuSetPinValue(Local_enuPortNumRW, Local_enuPinNumRW, MDIO_ENU_PIN_HIGH);  // Read mode
    MDIO_enuSetPinValue(Local_enuPortNumE, Local_enuPortNumE, MDIO_ENU_PIN_LOW);     // Ensure E starts low

    /* Temporary Data Storage */
    uint8_t temp_data = 0;
    uint8_t pin_state = 0;

    if(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].ClcdMode == HCLCD_8_BIT_MODE) {
        /* Set Data Pins as Inputs */
        for(uint8_t itr = 0; itr < 8; itr++) {
            MPORT_enuSetPinDirection(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr], MPORT_ENU_PORT_PIN_INPUT);
            MPORT_enuSetPinMode(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr],MPORT_ENU_PIN_MODE_INPUT_PULLUP);
        }

        /* Read Cycle */
        MDIO_enuSetPinValue(Local_enuPortNumE, Local_enuPinNumE, MDIO_ENU_PIN_HIGH);
        _delay_ms(1);
        
        for(uint8_t itr = 0; itr < 8; itr++) {
            MDIO_enuPortNum_t Local_enuPortNum = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr]);
            MDIO_enuPinNum_t Local_enuPinNum = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr]);
            MDIO_enuGetPinValue(Local_enuPortNum, Local_enuPinNum, &pin_state);
            temp_data |= (pin_state << itr);
        }
        
        MDIO_enuSetPinValue(Local_enuPortNumE, Local_enuPinNumE, MDIO_ENU_PIN_LOW);

        /* Restore Data Pins to Output */
        for(uint8_t itr = 0; itr < 8; itr++) {
            MPORT_enuSetPinDirection(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr], MPORT_ENU_PORT_PIN_OUTPUT);
        }
    }
    else if(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].ClcdMode == HCLCD_4_BIT_MODE) {
        /* Set D4-D7 as Inputs */
        for(uint8_t itr = 4; itr < 8; itr++) {
            MPORT_enuSetPinDirection(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr], MPORT_ENU_PORT_PIN_INPUT);
            MPORT_enuSetPinMode(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr],MPORT_ENU_PIN_MODE_INPUT_PULLUP);
        }

        /* Read High Nibble First */
        MDIO_enuSetPinValue(Local_enuPortNumE, Local_enuPinNumE, MDIO_ENU_PIN_HIGH);
        _delay_ms(1);
        
        for(uint8_t itr = 4; itr < 8; itr++) {
            MDIO_enuPortNum_t Local_enuPortNum = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr]);
            MDIO_enuPinNum_t Local_enuPinNum = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr]);
            MDIO_enuGetPinValue(Local_enuPortNum, Local_enuPinNum, &pin_state);
            temp_data |= (pin_state << (itr));
        }
        
        MDIO_enuSetPinValue(Local_enuPortNumE, Local_enuPinNumE, MDIO_ENU_PIN_LOW);
        _delay_ms(1);

        /* Read Low Nibble */
        MDIO_enuSetPinValue(Local_enuPortNumE, Local_enuPinNumE, MDIO_ENU_PIN_HIGH);
        _delay_ms(1);
        
        for(uint8_t itr = 4; itr < 8; itr++) {
            MDIO_enuPortNum_t Local_enuPortNum = GET_HIGH_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr]);
            MDIO_enuPinNum_t Local_enuPinNum = GET_LOW_NIB(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr]);
            MDIO_enuGetPinValue(Local_enuPortNum, Local_enuPinNum, &pin_state);
            temp_data |= (pin_state << (itr - 4));
        }
        
        MDIO_enuSetPinValue(Local_enuPortNumE, Local_enuPinNumE, MDIO_ENU_PIN_LOW);

        /* Restore Data Pins to Output */
        for(uint8_t itr = 4; itr < 8; itr++) {
            MPORT_enuSetPinDirection(HCLCD_enuArrLcdConfig[Copy_uint8LcdNum].DataPins[itr], MPORT_ENU_PORT_PIN_OUTPUT);
        }
    }
    else {
        Ret_enuErrorStatus = HCLCD_ENU_INVALID_CLCD_MODE;
    }

    *Adduint8_Data = temp_data;
    return Ret_enuErrorStatus;
}

HCLCD_enuErrorStatus_t HCLCD_enuWriteString(sint8_t *Addu8_string ,uint8_t Copy_uint8LcdNum){
    HCLCD_enuErrorStatus_t Ret_enuErrorStatus=HCLCD_ENU_OK;
    while(*Addu8_string)Ret_enuErrorStatus=HCLCD_enuWriteData(*(Addu8_string++),Copy_uint8LcdNum);
    return Ret_enuErrorStatus;
}

static float64_t HCLCD_enuWriteNumberHelperPowerFunction(float64_t base, float64_t power) {
    if (power == 0) return 1.0;
    float64_t result = HCLCD_enuWriteNumberHelperPowerFunction(base, power / 2);
    result *= result;
    if ((uint64_t)power % 2 == 1) {
        result *= base;
    }
    return result;
}

static HCLCD_enuErrorStatus_t HCLCD_enuWriteNumberHelper(uint64_t Copy_uint64Number, uint8_t Copy_uint8LcdNum) {
    HCLCD_enuErrorStatus_t Ret_enuErrorStatus = HCLCD_ENU_OK;
    if (!Copy_uint64Number) return Ret_enuErrorStatus;
    HCLCD_enuWriteNumberHelper(Copy_uint64Number / 10, Copy_uint8LcdNum);
    HCLCD_enuWriteData((Copy_uint64Number % 10) + '0', Copy_uint8LcdNum);
    return Ret_enuErrorStatus;
}

HCLCD_enuErrorStatus_t HCLCD_enuWriteNumber(float64_t Copyfloat64_number, uint8_t Copy_uint8LcdNum) {
    HCLCD_enuErrorStatus_t Ret_enuErrorStatus = HCLCD_ENU_OK;

    if (Copyfloat64_number < 0) {
        HCLCD_enuWriteData('-', Copy_uint8LcdNum);
        Copyfloat64_number = -Copyfloat64_number;
    }

    uint64_t Local_uint64IntgerValue = (uint64_t)Copyfloat64_number;
    float64_t Local_float64Fraction = Copyfloat64_number - Local_uint64IntgerValue;

    if (Local_uint64IntgerValue == 0) {
        HCLCD_enuWriteData('0', Copy_uint8LcdNum);
    } else {
        HCLCD_enuWriteNumberHelper(Local_uint64IntgerValue, Copy_uint8LcdNum);
    }
    uint64_t Local_uint64FractionValue = (uint64_t)((Local_float64Fraction * HCLCD_enuWriteNumberHelperPowerFunction(10, HCLCD_NUMBER_FRACTION_RESOLUTION)));
    if(Local_uint64FractionValue!=0){
        HCLCD_enuWriteData('.', Copy_uint8LcdNum);
        HCLCD_enuWriteNumberHelper(Local_uint64FractionValue, Copy_uint8LcdNum);
    }

    return Ret_enuErrorStatus;
}

HCLCD_enuErrorStatus_t HCLCD_enuGotoRowColumn(HCLCD_enuRow_t Copyenu_Row, uint8_t Copyenu_Column, uint8_t Copy_uint8LcdNum){
    HCLCD_enuErrorStatus_t Ret_enuErrorStatus = HCLCD_ENU_OK;
    if(Copyenu_Column>39){
        Ret_enuErrorStatus=HCLCD_ENU_INVALID_COLUMN;
    }else if(Copy_uint8LcdNum>NUMBER_OF_LCDS){
        Ret_enuErrorStatus=HCLCD_ENU_INVALID_CLCD_NUM;
    }else if(Copyenu_Row<0 || Copyenu_Row>1){
        Ret_enuErrorStatus=HCLCD_ENU_INVALID_ROW;
    }else{
        uint8_t Localu8_AddressDDRAM=(Copyenu_Row==HCLCD_FIRST_ROW)?Copyenu_Column:0x40+Copyenu_Column;
        HCLCD_enuWriteCommand(DDRAM_BASE_COMMAND | Localu8_AddressDDRAM,Copy_uint8LcdNum);
    }

    return Ret_enuErrorStatus;
}        

static HCLCD_enuErrorStatus_t HCLCD_enuGotoCGRAM(uint8_t Copyu8_PatternNumber, uint8_t Copy_uint8LcdNum){
    HCLCD_enuErrorStatus_t Ret_enuErrorStatus = HCLCD_ENU_OK;
      if(Copyu8_PatternNumber>8){
        Ret_enuErrorStatus=HCLCD_ENU_INVALID_PATTERN_NUM;
    }else if(Copy_uint8LcdNum>NUMBER_OF_LCDS){
        Ret_enuErrorStatus=HCLCD_ENU_INVALID_CLCD_NUM;
    }else{
        uint8_t Localu8_AddressCGRAM=Copyu8_PatternNumber*8;
        HCLCD_enuWriteCommand(CGRAM_BASE_COMMAND | Localu8_AddressCGRAM,Copy_uint8LcdNum);
    }
    return Ret_enuErrorStatus;
}

static HCLCD_enuErrorStatus_t HCLCD_enuWriteSpecialChar(uint8_t * Addu8_pattern, uint8_t Copy_uint8LcdNum ){
    HCLCD_enuErrorStatus_t Ret_enuErrorStatus = HCLCD_ENU_OK;
    if(Addu8_pattern == NULL){
        Ret_enuErrorStatus  =HCLCD_ENU_NULL_PTR;
    }else if(Copy_uint8LcdNum>NUMBER_OF_LCDS){
        Ret_enuErrorStatus= HCLCD_ENU_INVALID_CLCD_NUM;
    }else{
        for(uint8_t itr =0; itr<8; itr++){
            HCLCD_enuWriteData(Addu8_pattern[itr],Copy_uint8LcdNum);
        }
    }
    return Ret_enuErrorStatus;
}

HCLCD_enuErrorStatus_t HCLCD_enuStoreSpecialChar(uint8_t *Addu8_pattern, uint8_t Copyu8_PatternNumber, uint8_t Copy_uint8LcdNum){
    HCLCD_enuErrorStatus_t Ret_enuErrorStatus = HCLCD_ENU_OK;
    if(Addu8_pattern == NULL){
        Ret_enuErrorStatus  =HCLCD_ENU_NULL_PTR;
    }else if( Copyu8_PatternNumber>8){
        Ret_enuErrorStatus= HCLCD_ENU_INVALID_PATTERN_NUM;
    }else if(Copy_uint8LcdNum>NUMBER_OF_LCDS){
        Ret_enuErrorStatus= HCLCD_ENU_INVALID_CLCD_NUM;
    }else{
        Ret_enuErrorStatus = HCLCD_enuGotoCGRAM(Copyu8_PatternNumber,Copy_uint8LcdNum);
        Ret_enuErrorStatus = HCLCD_enuWriteSpecialChar(Addu8_pattern,Copy_uint8LcdNum);
        HCLCD_enuGotoRowColumn(HCLCD_FIRST_ROW,0,Copy_uint8LcdNum);
    }
    return Ret_enuErrorStatus;
}

HCLCD_enuErrorStatus_t HCLCD_enuDisplaySpecialChar(uint8_t Copyu8_PatternNumber, HCLCD_enuRow_t Copyenu_Row, uint8_t Copyenu_Column, uint8_t Copy_uint8LcdNum){
    HCLCD_enuErrorStatus_t Ret_enuErrorStatus = HCLCD_ENU_OK;
    if( Copyu8_PatternNumber>8){
        Ret_enuErrorStatus= HCLCD_ENU_INVALID_PATTERN_NUM;
    }else if(Copy_uint8LcdNum>NUMBER_OF_LCDS){
        Ret_enuErrorStatus= HCLCD_ENU_INVALID_CLCD_NUM;
    }else{
        Ret_enuErrorStatus = HCLCD_enuGotoRowColumn(Copyenu_Row,Copyenu_Column,Copy_uint8LcdNum);
        Ret_enuErrorStatus = HCLCD_enuWriteData(Copyu8_PatternNumber, Copy_uint8LcdNum);
    }
    return Ret_enuErrorStatus;
}
