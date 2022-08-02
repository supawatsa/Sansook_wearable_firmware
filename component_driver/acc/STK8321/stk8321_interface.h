#ifndef STK8321_INTERFACE_H
#define STK8321_INTERFACE_H
#include "nrf_drv_spi.h"
#include "stk8321_reg_map.h"

void hw_stk8321_event_handler(nrf_drv_spi_evt_t const * p_event, void * p_context);
uint32_t hw_stk8321_init(void);
uint32_t hw_stk8321_transfer(uint8_t *txdata,uint8_t t_length, uint8_t *rxdata,uint8_t r_length);
void hw_stk8321_reset(void);

#endif //STK8321_INTERFACE_H