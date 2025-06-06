#ifndef MGIE_H_
#define MGIE_H_

typedef enum{
        MGIE_ENU_OK,
        MGIE_ENU_NOK
}MGIE_enuErrorStatus_t;

MGIE_enuErrorStatus_t MGIE_enuEnableGIE(void);

MGIE_enuErrorStatus_t MGIE_enuDisableGIE(void);

#endif
