#include"afe4404_interface.h"
#include"ConfigurationIO.h"
#include"nrf_delay.h"
#include <stdint.h>


#define DEVICE_ADDRESS    AFE4404_ADDRESS
#define TWI_TIMEOUT       10000 

static const nrf_drv_twi_t m_twi_instance = NRF_DRV_TWI_INSTANCE(0);
volatile static bool twi_tx_done = false;
volatile static bool twi_rx_done = false;

//-----------------------------------------------------------------------------------------------

void hw_afe4404_event_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_XFER_TX:
            twi_tx_done = true;
            break;
        case NRF_DRV_TWI_XFER_TXTX:
            twi_tx_done = true;
            break;
        case NRF_DRV_TWI_XFER_RX:
            twi_rx_done = true;
            break;
        case NRF_DRV_TWI_XFER_TXRX:
            twi_rx_done = true;
            break;
        default:
            break;
    }
}
//-----------------------------------------------------------------------------------------------
uint32_t hw_afe4404_init(void)
{
    
    uint32_t err_code;
    
    const nrf_drv_twi_config_t twi_mpu_config = {
       .scl                = GPIO_I2C_SCL,
       .sda                = GPIO_I2C_SDA,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGHEST,
       .clear_bus_init     = false
    };
    
    err_code = nrf_drv_twi_init(&m_twi_instance, &twi_mpu_config, hw_afe4404_event_handler, NULL);
    if(err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    
    nrf_drv_twi_enable(&m_twi_instance);
    
    return NRF_SUCCESS;
}
//-----------------------------------------------------------------------------------------------
uint32_t hw_afe4404_register_read(uint8_t reg, uint8_t * p_data, uint32_t length)
{
    uint32_t err_code;
    uint32_t timeout = TWI_TIMEOUT;

    err_code = nrf_drv_twi_tx(&m_twi_instance, DEVICE_ADDRESS, &reg, 1, false);
    if(err_code != NRF_SUCCESS) return err_code;

    while((!twi_tx_done) && --timeout);
    if(!timeout) return NRF_ERROR_TIMEOUT;
    twi_tx_done = false;

    err_code = nrf_drv_twi_rx(&m_twi_instance, DEVICE_ADDRESS, p_data, length);
    if(err_code != NRF_SUCCESS) return err_code;

    timeout = TWI_TIMEOUT;
    while((!twi_rx_done) && --timeout);
    if(!timeout) return NRF_ERROR_TIMEOUT;
    twi_rx_done = false;

    return err_code;
}

//-----------------------------------------------------------------------------------------------
uint32_t hw_afe4404_write_single_register(uint8_t reg, uint16_t data)
{
    uint32_t err_code;
    uint32_t timeout = TWI_TIMEOUT;
    uint8_t data0= data & 0xff;
    uint8_t data1= data >> 8 ;
    uint8_t data2= 0;
    uint8_t packet[4] = {reg,data2,data1, data0};

    err_code = nrf_drv_twi_tx(&m_twi_instance, DEVICE_ADDRESS, packet, 4, false);
    if(err_code != NRF_SUCCESS) return err_code;

    while((!twi_tx_done) && --timeout);

    if(!timeout) return NRF_ERROR_TIMEOUT;

    twi_tx_done = false;

    return err_code;
}
//-----------------------------------------------------------------------------------------------
void hw_afe4404_reset(void)
{
  nrf_gpio_pin_dir_set(GPIO_AFE_RESET, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_set(GPIO_AFE_RESET);
  nrf_gpio_pin_clear(GPIO_AFE_RESET);
  nrf_delay_us(40);
  nrf_gpio_pin_set(GPIO_AFE_RESET);

}
//-----------------------------------------------------------------------------------------------