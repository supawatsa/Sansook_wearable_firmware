#ifndef STK8321_APP_H
#define STK8321_APP_H

#include "stk8321_interface.h"
void stk8321_app_init(void);
uint8_t stk8321_app_getid(void);
void stk8321_app_get_acc_all(int32_t * pXdata);

#endif //STK8321_APP_H