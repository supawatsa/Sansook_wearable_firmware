#include"afe4404_reg_map.h"

void hw_afe4404_event_handler(nrf_drv_twi_evt_t const * p_event, void * p_context);
uint32_t hw_afe4404_init(void);
uint32_t hw_afe4404_register_read(uint8_t reg, uint8_t * p_data, uint32_t length);
uint32_t hw_afe4404_write_single_register(uint8_t reg, uint8_t data);