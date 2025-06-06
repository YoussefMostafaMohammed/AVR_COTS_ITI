#include "HSWITCH_CFG.h"

HSWITCH_structConfigrations_t HSWITCH_enuArrSwitchConfig[NUMBER_OF_SWITCHS] = {
    [SWITCH_START] = {
        .HSWITCH_PORT = MDIO_ENU_PORTA,
        .HSWITCH_Pin = MDIO_ENU_PIN0,
        .HSWITCH_Connection = HSWITCH_PULLUP
    },
    [SWITCH_STOP] = {
        .HSWITCH_PORT = MDIO_ENU_PORTA,
        .HSWITCH_Pin = MDIO_ENU_PIN1,
        .HSWITCH_Connection = HSWITCH_PULLUP
    },
    [SWITCH_ALERT] = {
        .HSWITCH_PORT = MDIO_ENU_PORTA,
        .HSWITCH_Pin = MDIO_ENU_PIN2,
        .HSWITCH_Connection = HSWITCH_PULLUP
    }
};
