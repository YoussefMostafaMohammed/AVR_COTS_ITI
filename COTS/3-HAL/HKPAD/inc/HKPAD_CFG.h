#ifndef HKPAD_CFG_H_
#define HKPAD_CFG_H_

#define HKEYPAD_NO_OF_ROWS      (4)
#define HKEYPAD_NO_OF_COLS      (4)


// static const uint8_t HKEYPAD_uint8CharArr[4][4] = 
// {
// 	{'7', '8', '9', '/'},   
// 	{'4', '5', '6', '*'},   
// 	{'1', '2', '3', '-'},   
// 	{'C', '0', '=', '+'}    
// };

static const uint8_t HKEYPAD_uint8CharArr[4][4] = 
{
	{'0', '0', '0', '0'},   
	{'0', 'u', '0', '0'},   
	{'l', '0', 'r', '0'},   
	{'C', 'd', '0', '0'}    
};

// KPAD_TWO,
// KPAD_THREE,
typedef enum{
    KPAD_ONE,
    NUMBER_OF_KBADS
}HKBAD_enuLCDCFG;

#endif
