#ifndef AFE_INTERFACE_H
#define AFE_INTERFACE_H


#include"afe4404_reg_map.h"
#include <nrf_drv_twi.h>
#include<stdint.h>
#include"nrf_delay.h"

void hw_afe4404_event_handler(nrf_drv_twi_evt_t const * p_event, void * p_context);
uint32_t hw_afe4404_init(void);
int32_t hw_afe4404_register_read(uint8_t reg);
uint32_t hw_afe4404_write_single_register(uint8_t reg, uint32_t data);
void hw_afe4404_reset(void);

#endif // AFE_INTERFACE_H