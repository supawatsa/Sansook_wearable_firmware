#include "stk8321_interface.h"
#include"ConfigurationIO.h"
#include "nrf_drv_spi.h"


//-----------------------------------------------------------------------------------------------
#define SPI_TIMEOUT 10000
#define SPI_INSTANCE  1 /**< SPI instance index. */

//-----------------------------------------------------------------------------------------------
static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE);  /**< SPI instance. */
static volatile bool spi_xfer_done;  /**< Flag used to indicate that SPI instance completed the transfer. */
static uint8_t       m_tx_buf[10];           /**< TX buffer. */
static uint8_t       m_rx_buf[10];    /**< RX buffer. */
//-----------------------------------------------------------------------------------------------
void hw_stk8321_event_handler(nrf_drv_spi_evt_t const * p_event, void * p_context)
{
    spi_xfer_done = true;
    //NRF_LOG_INFO("Transfer completed.");


}
//-----------------------------------------------------------------------------------------------
uint32_t hw_stk8321_init(void)
{
    uint32_t err_code;
    nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
    spi_config.ss_pin   = GPIO_8321_CS;
    spi_config.miso_pin = GPIO_SPI_MISO;
    spi_config.mosi_pin = GPIO_SPI_MOSI;
    spi_config.sck_pin  = GPIO_SPI_SCLK;
    spi_config.mode  = NRF_DRV_SPI_MODE_3;
    spi_config.frequency = NRF_DRV_SPI_FREQ_500K;
   // spi_config.bit_order  = NRF_DRV_SPI_BIT_ORDER_LSB_FIRST;
    err_code  = nrf_drv_spi_init(&spi, &spi_config, hw_stk8321_event_handler, NULL);
    return err_code;
}

//-----------------------------------------------------------------------------------------------
uint32_t hw_stk8321_transfer(uint8_t *txdata,uint8_t t_length, uint8_t *rxdata,uint8_t r_length)
{
    uint32_t timeout = SPI_TIMEOUT;
    uint32_t err_code;
    spi_xfer_done = false;
    err_code  = nrf_drv_spi_transfer(&spi, txdata, t_length, rxdata, r_length);
    if(err_code != NRF_SUCCESS) return err_code;

    while((!spi_xfer_done) && --timeout);

    if(!timeout) return NRF_ERROR_TIMEOUT;
      spi_xfer_done = false;

    return err_code;
}
//-----------------------------------------------------------------------------------------------
void hw_stk8321_reset(void)
{

}
//-----------------------------------------------------------------------------------------------