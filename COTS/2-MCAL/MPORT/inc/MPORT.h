#ifndef MPORT_H_
#define MPORT_H_

typedef enum{
        MPORT_ENU_OK,
        MPORT_ENU_INVALID_PARAM,
        MPORT_ENU_INVALID_PIN_NUM,
        MPORT_ENU_INVALID_PORT_NUM,
        MPORT_ENU_INVALID_DIRECTION,
        MPORT_ENU_INVALID_MODE,
        MPORT_ENU_INVALID_PIN_CONFIG,  
        MPORT_ENU_INVALID_PORT_CONFIG,
        MPORT_ENU_INVALID_PIN_STATE,  
        MPORT_ENU_INVALID_PORT_STATE,
        MPORT_ENU_NULL_PTR,
        MPORT_ENU_NOK
}MPORT_enuErrorStatus_t;

typedef enum{
    MPORT_ENU_PORTA,
    MPORT_ENU_PORTB,
    MPORT_ENU_PORTC,
    MPORT_ENU_PORTD
}MPORT_enuPortNum_t;

typedef enum{
    MPORT_ENU_PIN0,
    MPORT_ENU_PIN1,
    MPORT_ENU_PIN2,
    MPORT_ENU_PIN3,
    MPORT_ENU_PIN4,
    MPORT_ENU_PIN5,
    MPORT_ENU_PIN6,
    MPORT_ENU_PIN7
}MPORT_enuPinNum_t;

typedef enum{
    MPORT_ENU_PIN_OUTPUT=1,
    MPORT_ENU_PIN_INPUT_PULLUP=0,
    MPORT_ENU_PIN_INPUT_PULLDOWN=0,
}MPORT_enuPinConfigration_t;

typedef enum{
    MPORT_ENU_PORT_OUTPUT=0xFF,
    MPORT_ENU_PORT_INPUT_PULLUP=0x00,
    MPORT_ENU_PORT_INPUT_PULLDOWN=0x00,
}MPORT_enuPortConfigration_t;

/* enum for port pin directions */
typedef enum
{
    MPORT_ENU_PORT_PIN_INPUT = 0x00,
    MPORT_ENU_PORT_PIN_OUTPUT = 0x01,
} MPORT_enuPortPinDir_t;

/* enum for port pin modes */
typedef enum
{
    MPORT_ENU_PIN_MODE_INPUT_PULLUP,
    MPORT_ENU_PIN_MODE_INPUT_PULLDOWN,
    MPORT_ENU_PIN_MODE_UART,
    MPORT_ENU_PIN_MODE_NONE,
} MPORT_enuPortPinMode_t;

typedef enum {
    /* PORTA Pins */ 
    MPORT_enuPIN_A0 = ((MPORT_ENU_PORTA << 4U) | (MPORT_ENU_PIN0)),
    MPORT_enuPIN_A1 = ((MPORT_ENU_PORTA << 4U) | (MPORT_ENU_PIN1)),
    MPORT_enuPIN_A2 = ((MPORT_ENU_PORTA << 4U) | (MPORT_ENU_PIN2)),
    MPORT_enuPIN_A3 = ((MPORT_ENU_PORTA << 4U) | (MPORT_ENU_PIN3)),
    MPORT_enuPIN_A4 = ((MPORT_ENU_PORTA << 4U) | (MPORT_ENU_PIN4)),
    MPORT_enuPIN_A5 = ((MPORT_ENU_PORTA << 4U) | (MPORT_ENU_PIN5)),
    MPORT_enuPIN_A6 = ((MPORT_ENU_PORTA << 4U) | (MPORT_ENU_PIN6)),
    MPORT_enuPIN_A7 = ((MPORT_ENU_PORTA << 4U) | (MPORT_ENU_PIN7)),

    /* PORTB Pins */
    MPORT_enuPIN_B0 = ((MPORT_ENU_PORTB << 4U) | (MPORT_ENU_PIN0)),
    MPORT_enuPIN_B1 = ((MPORT_ENU_PORTB << 4U) | (MPORT_ENU_PIN1)),
    MPORT_enuPIN_B2 = ((MPORT_ENU_PORTB << 4U) | (MPORT_ENU_PIN2)),
    MPORT_enuPIN_B3 = ((MPORT_ENU_PORTB << 4U) | (MPORT_ENU_PIN3)),
    MPORT_enuPIN_B4 = ((MPORT_ENU_PORTB << 4U) | (MPORT_ENU_PIN4)),
    MPORT_enuPIN_B5 = ((MPORT_ENU_PORTB << 4U) | (MPORT_ENU_PIN5)),
    MPORT_enuPIN_B6 = ((MPORT_ENU_PORTB << 4U) | (MPORT_ENU_PIN6)),
    MPORT_enuPIN_B7 = ((MPORT_ENU_PORTB << 4U) | (MPORT_ENU_PIN7)),

    /* PORTC Pins */
    MPORT_enuPIN_C0 = ((MPORT_ENU_PORTC << 4U) | (MPORT_ENU_PIN0)),
    MPORT_enuPIN_C1 = ((MPORT_ENU_PORTC << 4U) | (MPORT_ENU_PIN1)),
    MPORT_enuPIN_C2 = ((MPORT_ENU_PORTC << 4U) | (MPORT_ENU_PIN2)),
    MPORT_enuPIN_C3 = ((MPORT_ENU_PORTC << 4U) | (MPORT_ENU_PIN3)),
    MPORT_enuPIN_C4 = ((MPORT_ENU_PORTC << 4U) | (MPORT_ENU_PIN4)),
    MPORT_enuPIN_C5 = ((MPORT_ENU_PORTC << 4U) | (MPORT_ENU_PIN5)),
    MPORT_enuPIN_C6 = ((MPORT_ENU_PORTC << 4U) | (MPORT_ENU_PIN6)),
    MPORT_enuPIN_C7 = ((MPORT_ENU_PORTC << 4U) | (MPORT_ENU_PIN7)),

    /* PORTD Pins */
    MPORT_enuPIN_D0 = ((MPORT_ENU_PORTD << 4U) | (MPORT_ENU_PIN0)),
    MPORT_enuPIN_D1 = ((MPORT_ENU_PORTD << 4U) | (MPORT_ENU_PIN1)),
    MPORT_enuPIN_D2 = ((MPORT_ENU_PORTD << 4U) | (MPORT_ENU_PIN2)),
    MPORT_enuPIN_D3 = ((MPORT_ENU_PORTD << 4U) | (MPORT_ENU_PIN3)),
    MPORT_enuPIN_D4 = ((MPORT_ENU_PORTD << 4U) | (MPORT_ENU_PIN4)),
    MPORT_enuPIN_D5 = ((MPORT_ENU_PORTD << 4U) | (MPORT_ENU_PIN5)),
    MPORT_enuPIN_D6 = ((MPORT_ENU_PORTD << 4U) | (MPORT_ENU_PIN6)),
    MPORT_enuPIN_D7 = ((MPORT_ENU_PORTD << 4U) | (MPORT_ENU_PIN7))
} MPORT_enuPinPortNum_t;



void MPORT_vInit(void);

MPORT_enuErrorStatus_t MPORT_enuSetPinConfigration(MPORT_enuPortNum_t Copy_enuPortNum, MPORT_enuPinNum_t Copy_enuPinNum, MPORT_enuPinConfigration_t Copy_enuConfigration);

MPORT_enuErrorStatus_t MPORT_enuSetPortConfigration(MPORT_enuPortNum_t Copy_enuPortNum,MPORT_enuPortConfigration_t Copy_enuConfigration);

MPORT_enuErrorStatus_t MPORT_enuSetPinDirection( MPORT_enuPinPortNum_t Copy_enuPinNum  ,  MPORT_enuPortPinDir_t  Copy_enuPinDirection  );

MPORT_enuErrorStatus_t MPORT_enuSetPinMode( MPORT_enuPinPortNum_t Copy_enuPinNum  ,  MPORT_enuPortPinMode_t Copy_enuPinMode );

#endif