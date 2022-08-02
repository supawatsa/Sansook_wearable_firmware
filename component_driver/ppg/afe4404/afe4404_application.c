#include"afe4404_application.h"
#include <stdint.h>
#include <string.h>
#include "nrf_log.h"

#define PDNCYCLESTC_timing    5475
#define PDNCYCLEENDC_timing   79199
#define PRPCT_CNT             79999 //20ms period
#define INTER_CLOCK_100US     399
#define INTER_CLOCK_75US      299
#define INTER_CLOCK_25US      99
#define INTER_CLOCK_1US75     6
#define INTER_CLOCK_256US     1059

/*LED2 setting*/
#define LED2LEDSTC_timing     0
#define LED2LEDENDC_timing    LED2LEDSTC_timing+INTER_CLOCK_100US
#define LED2STC_timing        LED2LEDSTC_timing+INTER_CLOCK_25US
#define LED2ENDC_timing       LED2LEDSTC_timing+INTER_CLOCK_100US
#define ADCRSTSTCT0_timing    LED2LEDSTC_timing+401
#define ADCRSTENDCT0_timing   ADCRSTSTCT0_timing+INTER_CLOCK_1US75
#define LED2CONVST_timing     ADCRSTSTCT0_timing+INTER_CLOCK_1US75+2
#define LED2CONVEND_timing    ADCRSTSTCT0_timing+INTER_CLOCK_1US75+2+INTER_CLOCK_256US
/*LED3 setting*/
#define LED3LEDSTC_timing     LED2LEDSTC_timing+INTER_CLOCK_100US+2
#define LED3LEDENDC_timing    LED3LEDSTC_timing+INTER_CLOCK_100US
#define LED3STC_timing        LED3LEDSTC_timing+INTER_CLOCK_25US
#define LED3ENDC_timing       LED3LEDSTC_timing+INTER_CLOCK_100US
#define ADCRSTSTCT1_timing    LED3LEDSTC_timing+1069
#define ADCRSTENDCT1_timing   ADCRSTSTCT1_timing+INTER_CLOCK_1US75
#define LED3CONVST_timing     ADCRSTSTCT1_timing+INTER_CLOCK_1US75+2
#define LED3CONVEND_timing    ADCRSTSTCT1_timing+INTER_CLOCK_1US75+2+INTER_CLOCK_256US
/*LED1 setting*/
#define LED1LEDSTC_timing     LED3LEDSTC_timing+INTER_CLOCK_100US+2
#define LED1LEDENDC_timing    LED1LEDSTC_timing+INTER_CLOCK_100US
#define LED1STC_timing        LED1LEDSTC_timing+INTER_CLOCK_25US
#define LED1ENDC_timing       LED1LEDSTC_timing+INTER_CLOCK_100US
#define ADCRSTSTCT2_timing    LED1LEDSTC_timing+1737
#define ADCRSTENDCT2_timing   ADCRSTSTCT2_timing+INTER_CLOCK_1US75
#define LED1CONVST_timing     ADCRSTSTCT2_timing+INTER_CLOCK_1US75+2
#define LED1CONVEND_timing    ADCRSTSTCT2_timing+INTER_CLOCK_1US75+2+INTER_CLOCK_256US

/*amb setting*/
#define ALED1STC_timing       LED1LEDSTC_timing+INTER_CLOCK_100US+INTER_CLOCK_25US+4//1303
#define ALED1ENDC_timing      ALED1STC_timing+INTER_CLOCK_75US
#define ADCRSTSTCT3_timing    ALED1STC_timing+2305
#define ADCRSTENDCT3_timing   ADCRSTSTCT3_timing+INTER_CLOCK_1US75
#define ALED1CONVST_timing    ADCRSTENDCT3_timing+2
#define ALED1CONVEND_timing   ALED1CONVST_timing+INTER_CLOCK_256US


void afe4404_set_led_currents_max50ma( uint8_t led1_current, uint8_t led2_current, uint8_t led3_current)
{
	uint32_t val;
        float current_temp;
        current_temp = (float)led1_current/0.8f;
	val |= ((uint8_t)current_temp << 0);		// LED 1 addrss space -> 0-5 bits
        current_temp = (float)led2_current/0.8f;
	val |= ((uint8_t)current_temp << 6);		// LED 2 addrss space -> 6-11 bits
        current_temp = (float)led3_current/0.8f;
	val |= ((uint8_t)current_temp << 12);            // LED 3 addrss space -> 12-17 bits
	hw_afe4404_write_single_register(LED_CONFIG, val);
}

void afe4404_set_led_currents_max100ma( uint8_t led1_current, uint8_t led2_current, uint8_t led3_current)
{
        uint32_t val;
        float current_temp;
        current_temp = (float)led1_current/1.6f;
	val |= ((uint8_t)current_temp << 0);		// LED 1 addrss space -> 0-5 bits
        current_temp = (float)led2_current/1.6f;
	val |= ((uint8_t)current_temp << 6);		// LED 2 addrss space -> 6-11 bits
        current_temp = (float)led3_current/1.6f;
	val |= ((uint8_t)current_temp << 12);            // LED 3 addrss space -> 12-17 bits
	hw_afe4404_write_single_register(LED_CONFIG, val);
}


void afe4404_set_power(void)
{
	hw_afe4404_write_single_register(DIAGNOSIS,DIAGNOSIS_SWRESET|DIAGNOSIS_WRMODE|DIAGNOSIS_TM_RESET);
	uint32_t reg_val =0;
	reg_val = SETTINGS_DY1_DIS|SETTINGS_ILED_100|SETTINGS_DY2_EN|SETTINGS_OSC_EN|SETTINGS_DY3_DIS|
                  SETTINGS_DY4_EN|SETTINGS_RX_DIS|SETTINGS_AFE_DIS;
   
	hw_afe4404_write_single_register(SETTINGS, reg_val);		//	clock div 0->4Mhz, 1=2=3 -> do not use, 4-> 2Mhz, 5->1Mhz, 6->0.5Mhz, 7-> 0.25Mhz
}

//---------------------------------------------------------------------------------------------
void afe4404_set_softreset(void)
{
	hw_afe4404_write_single_register(DIAGNOSIS,DIAGNOSIS_SWRESET);
}
//---------------------------------------------------------------------------------------------
void afe4404_app_power_low(void)
{


}
void afe4404_app_power_down(void)
{
  //nrf_gpio_pin_dir_set(GPIO_AFE_RESET, NRF_GPIO_PIN_DIR_OUTPUT);
// hold reset pin forv 200 us

}
//---------------------------------------------------------------------------------------------
void afe4404_app_power_normal(void)
{

	
}
//---------------------------------------------------------------------------------------------

void afe4404_app_init(void)
{
        hw_afe4404_reset();
	hw_afe4404_init();
	afe4404_set_power();
	//afe4404_app_power_normal();
        
	hw_afe4404_write_single_register(LED2STC,LED2STC_timing);
 
	hw_afe4404_write_single_register(LED2ENDC,LED2ENDC_timing);
	hw_afe4404_write_single_register(LED1LEDSTC,LED1LEDSTC_timing);
	hw_afe4404_write_single_register(LED1LEDENDC,LED1LEDENDC_timing);
	hw_afe4404_write_single_register(LED3STC,LED3STC_timing);
	hw_afe4404_write_single_register(LED3ENDC,LED3ENDC_timing);

	hw_afe4404_write_single_register(LED1STC,LED1STC_timing);
	hw_afe4404_write_single_register(LED1ENDC,LED1ENDC_timing);
	hw_afe4404_write_single_register(LED2LEDSTC,LED2LEDSTC_timing);
	hw_afe4404_write_single_register(LED2LEDENDC,LED2LEDENDC_timing);
	hw_afe4404_write_single_register(ALED1STC,ALED1STC_timing);
	hw_afe4404_write_single_register(ALED1ENDC,ALED1ENDC_timing);

	hw_afe4404_write_single_register(LED2CONVST,LED2CONVST_timing);
	hw_afe4404_write_single_register(LED2CONVEND,LED2CONVEND_timing);
	hw_afe4404_write_single_register(LED3CONVST,LED3CONVST_timing);
	hw_afe4404_write_single_register(LED3CONVEND,LED3CONVEND_timing);
	hw_afe4404_write_single_register(LED1CONVST,LED1CONVST_timing);
	hw_afe4404_write_single_register(LED1CONVEND,LED1CONVEND_timing);

	hw_afe4404_write_single_register(ALED1CONVST,ALED1CONVST_timing);
	hw_afe4404_write_single_register(ALED1CONVEND,ALED1CONVEND_timing);
	hw_afe4404_write_single_register(ADCRSTSTCT0,ADCRSTSTCT0_timing);
	hw_afe4404_write_single_register(ADCRSTENDCT0,ADCRSTENDCT0_timing);
	hw_afe4404_write_single_register(ADCRSTSTCT1,ADCRSTSTCT1_timing);
	hw_afe4404_write_single_register(ADCRSTENDCT1,ADCRSTENDCT1_timing);

	hw_afe4404_write_single_register(ADCRSTSTCT2,ADCRSTSTCT2_timing);
	hw_afe4404_write_single_register(ADCRSTENDCT2,ADCRSTENDCT2_timing);
	hw_afe4404_write_single_register(ADCRSTSTCT3,ADCRSTSTCT3_timing);
	hw_afe4404_write_single_register(ADCRSTENDCT3,ADCRSTENDCT3_timing);
        hw_afe4404_write_single_register(LED3LEDSTC,LED3LEDSTC_timing);
        hw_afe4404_write_single_register(LED3LEDENDC,LED3LEDENDC_timing);
	

        hw_afe4404_write_single_register(PRPCT,PRPCT_CNT);
        hw_afe4404_write_single_register(TIA_GAINS1, TIA_PROG_TG_DIS|TIA_CF_5PF|TIA_GAIN_RES_50K);
	hw_afe4404_write_single_register(TIA_GAINS2, TIA_GAIN_SEPERATE_GAIN|TIA_CF_5PF|TIA_GAIN_RES_25K);
	
	afe4404_set_led_currents_max100ma( 5,5,5 ); //red,ir,green 

	hw_afe4404_write_single_register(CLKOUT, CLKOUT_DIS|CLKOUT_DIVISIONBY_4);
	hw_afe4404_write_single_register(CLKDIV_PRF, CLKDIV_PRF_0);

        hw_afe4404_write_single_register(PDNCYCLESTC,PDNCYCLESTC_timing);
	hw_afe4404_write_single_register(PDNCYCLEENDC,PDNCYCLEENDC_timing);

        hw_afe4404_write_single_register(TIM_NUMAV, TIM_TIMEREN|NUMAV_4AVG);
        nrf_delay_ms(10);


}
//---------------------------------------------------------------------------------------------
void afe4404_app_getppg_1(uint32_t * p_data)
{
    uint32_t ppg1temp = hw_afe4404_register_read(LED1VAL);
    memcpy(&ppg1temp,p_data,sizeof(uint32_t));
	
}
//---------------------------------------------------------------------------------------------
void afe4404_app_getppg_all(uint32_t * p_data)
{
    uint32_t temp_data[6];
    temp_data[0] = hw_afe4404_register_read(LED1VAL);
    temp_data[1] = hw_afe4404_register_read(LED2VAL);
    temp_data[2] = hw_afe4404_register_read(LED3VAL);
    temp_data[3] = hw_afe4404_register_read(ALED1VAL);
    temp_data[4] = hw_afe4404_register_read(LED1_ALED1VAL);
    temp_data[5] = hw_afe4404_register_read(LED2_ALED2VAL);//Ignore the content of this register when LED3 
    
    
    memcpy(p_data,temp_data,sizeof(uint32_t)*6);
    NRF_LOG_INFO("ppg1  %d  \n\r", temp_data[0]);
    NRF_LOG_INFO("ppg2  %d  \n\r", temp_data[1]);
    NRF_LOG_INFO("ppg3  %d  \n\r", temp_data[2]);
    NRF_LOG_INFO("amb   %d  \n\r", temp_data[3]);
    NRF_LOG_INFO("led2+3  %d  \n\r", temp_data[4]);
    NRF_LOG_INFO("led1+amb  %d  \n\r", temp_data[5]);

}
//---------------------------------------------------------------------------------------------