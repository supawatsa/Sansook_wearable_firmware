
#ifndef AFE_APP_H
#define AFE_APP_H

#include"afe4404_interface.h"

void afe4404_app_init(void);
void afe4404_set_led_currents( uint8_t led1_current, uint8_t led2_current, uint8_t led3_current);
void afe4404_app_getppg_1(uint32_t * p_data);
void afe4404_app_getppg_all(uint32_t * p_data);
void afe4404_app_power_low(void);
void afe4404_app_power_down(void);

#endif //AFE_APP_H