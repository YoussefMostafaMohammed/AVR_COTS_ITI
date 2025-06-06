#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MPORT.h"
#include "MDIO.h"
#include "HLED_CFG.h"
#include "HLED.h"


HLED_structConfigrations_t HLED_enuArrLedConfig[NUMBER_OF_LEDS]={

    [LED_START] = {
        .HLED_PORT = MDIO_ENU_PORTC,
        .HLED_Pin = MDIO_ENU_PIN0,
        .HLED_Connection = HLED_Forward
    },
    [LED_STOP] = {
        .HLED_PORT = MDIO_ENU_PORTC,
        .HLED_Pin = MDIO_ENU_PIN1,
        .HLED_Connection = HLED_Forward
    },
    [LED_ALERT] = {
        .HLED_PORT = MDIO_ENU_PORTC,
        .HLED_Pin = MDIO_ENU_PIN2,
        .HLED_Connection = HLED_Forward
    }
};
