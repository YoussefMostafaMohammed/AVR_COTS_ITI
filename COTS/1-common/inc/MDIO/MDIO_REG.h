#ifndef MDIO_REG_H
#define MDIO_REG_H

// struct to represent each DIO port registers (in the same order as their addresses)
typedef struct 
{
    volatile uint8_t PIN;
    volatile uint8_t DDR;
    volatile uint8_t PORT;
} MDIO_structPortRegElement_t;

// add base register address
#define MDIO_PORT_REG_BASE_ADD  ((volatile MDIO_structPortRegElement_t*)(0x39))

// macro to find port address
#define MDIO_GET_PORT_ADD(PORT_NUM)  (MDIO_structPortRegElement_t*)((MDIO_PORT_REG_BASE_ADD)-((uint8_t)PORT_NUM))

#endif
