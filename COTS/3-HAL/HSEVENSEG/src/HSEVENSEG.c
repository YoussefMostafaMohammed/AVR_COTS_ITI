#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MDIO.h"
#include "MPORT.h"
#include "HSEVENSEG_CFG.h"
#include "HSEVENSEG.h"

static const uint8_t HSEVENSEG_u8LookupTableArray[11] = {
    0x3F,  /*Num = 0*/
    0x06,  /*Num = 1*/
    0x5B,  /*Num = 2*/
    0x4F,  /*Num = 3*/
    0x66,  /*Num = 4*/
    0x6D,  /*Num = 5*/
    0x7D,  /*Num = 6*/
    0x07,  /*Num = 7*/
    0x7F,  /*Num = 8*/
    0x6F,  /*Num = 9*/
    0x00   /* 10: All segments are OFF (Clear Display) */
};

extern HSEVENSEG_structConfigrations_t HSEVENSEG_enuArrSevenSegConfig[NUMBER_OF_SEVENSEGS];

HSEVENSEG_enuErrorStatus_t HSEVENSEG_enuvInit(void)
{
    HSEVENSEG_enuErrorStatus_t Ret_enuErrorStatus = HSEVENSEG_ENU_OK;
    MDIO_enuPortNum_t Local_enuCurrentPort = MDIO_ENU_PORTA;
    MDIO_enuPinNum_t  Local_enuCurrentPin  = MDIO_ENU_PIN0;
    for(uint8_t SevenSeg_iterator = 0 ; SevenSeg_iterator < NUMBER_OF_SEVENSEGS ; SevenSeg_iterator++)
    {
        for(uint8_t Pins_iterator = 0 ; Pins_iterator < NUMBER_OF_SEVENSEG_PINS ; Pins_iterator++)
        {
            Ret_enuErrorStatus = MPORT_enuSetPinDirection(HSEVENSEG_enuArrSevenSegConfig[SevenSeg_iterator].HSEVENSEG_enuPinsNumArr[Pins_iterator],MPORT_ENU_PORT_PIN_OUTPUT);
            Local_enuCurrentPort = GET_HIGH_NIB(HSEVENSEG_enuArrSevenSegConfig[SevenSeg_iterator].HSEVENSEG_enuPinsNumArr[Pins_iterator]);
            Local_enuCurrentPin  = GET_LOW_NIB(HSEVENSEG_enuArrSevenSegConfig[SevenSeg_iterator].HSEVENSEG_enuPinsNumArr[Pins_iterator]);
            if(HSEVENSEG_enuArrSevenSegConfig[SevenSeg_iterator].HSEVENSEG_Connection == HSEVENSEG_COMMON_CATHODE)
            {
                Ret_enuErrorStatus = MDIO_enuSetPinValue(Local_enuCurrentPort,Local_enuCurrentPin,MDIO_ENU_PIN_LOW); 
            }
            else if(HSEVENSEG_enuArrSevenSegConfig[SevenSeg_iterator].HSEVENSEG_Connection == HSEVENSEG_COMMON_ANODE)
            {
                Ret_enuErrorStatus = MDIO_enuSetPinValue(Local_enuCurrentPort,Local_enuCurrentPin,MDIO_ENU_PIN_HIGH); 
            }
            else
            {
                /* Do Nothing */
            }
        }
    }
    return Ret_enuErrorStatus;
}

HSEVENSEG_enuErrorStatus_t HSEVENSEG_vSetValue(uint8_t Copy_enuSevenSegNum , uint8_t Copy_u8Value){
    HSEVENSEG_enuErrorStatus_t Ret_enuErrorStatus = HSEVENSEG_ENU_OK;
    MDIO_enuPortNum_t Local_enuCurrentPort = MDIO_ENU_PORTA;
    MDIO_enuPinNum_t  Local_enuCurrentPin  = MDIO_ENU_PIN0;
    
    if(Copy_u8Value>9){
        Ret_enuErrorStatus = HSEVENSEG_ENU_INVALID_NUMBER;
    }else{
        for(uint8_t Pins_iterator = 0 ; Pins_iterator < NUMBER_OF_SEVENSEG_PINS ; Pins_iterator++)
        {
            Ret_enuErrorStatus = MPORT_enuSetPinDirection(HSEVENSEG_enuArrSevenSegConfig[Copy_enuSevenSegNum].HSEVENSEG_enuPinsNumArr[Pins_iterator],MPORT_ENU_PORT_PIN_OUTPUT);
            Local_enuCurrentPort = GET_HIGH_NIB(HSEVENSEG_enuArrSevenSegConfig[Copy_enuSevenSegNum].HSEVENSEG_enuPinsNumArr[Pins_iterator]);
            Local_enuCurrentPin  = GET_LOW_NIB(HSEVENSEG_enuArrSevenSegConfig[Copy_enuSevenSegNum].HSEVENSEG_enuPinsNumArr[Pins_iterator]);
            if(HSEVENSEG_enuArrSevenSegConfig[Copy_enuSevenSegNum].HSEVENSEG_Connection == HSEVENSEG_COMMON_CATHODE)
            {
                Ret_enuErrorStatus = MDIO_enuSetPinValue(Local_enuCurrentPort,Local_enuCurrentPin,(HSEVENSEG_u8LookupTableArray[Copy_u8Value] >> Pins_iterator)&1); 
            }
            else if(HSEVENSEG_enuArrSevenSegConfig[Copy_enuSevenSegNum].HSEVENSEG_Connection == HSEVENSEG_COMMON_ANODE)
            {
                Ret_enuErrorStatus = MDIO_enuSetPinValue(Local_enuCurrentPort,Local_enuCurrentPin,!(HSEVENSEG_u8LookupTableArray[Copy_u8Value] >> Pins_iterator)&1); 
            }
            else
            {
                /* Do Nothing */
            }
        }
    }
    return Ret_enuErrorStatus;
}

HSEVENSEG_enuErrorStatus_t HSEVENSEG_enuSetMultiDigitValue(uint16_t Copy_u16Value){
    HSEVENSEG_enuErrorStatus_t Ret_enuErrorStatus = HSEVENSEG_ENU_OK;
    uint16_t Local_u16Value=Copy_u16Value;
    
    uint8_t Local_u8NumberOfDigites=0;
    while(Local_u16Value!=0){
        Local_u16Value/=10;
        Local_u8NumberOfDigites++;
    }
    
    if(Local_u8NumberOfDigites>NUMBER_OF_SEVENSEGS){
        Ret_enuErrorStatus = HSEVENSEG_ENU_INVALID_NUMBER_OF_DIGIT;
    }
    else{
        Local_u16Value=Copy_u16Value;
        for(uint8_t SevenSeg_iterator = 0 ; SevenSeg_iterator < NUMBER_OF_SEVENSEGS ; SevenSeg_iterator++)
        {
            Ret_enuErrorStatus = HSEVENSEG_vSetValue(SevenSeg_iterator,Local_u16Value%10);
            Local_u16Value/=10;
        }
    }
    return Ret_enuErrorStatus;
}