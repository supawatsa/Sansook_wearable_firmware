#include "app.h"
#include "app_timer.h"
#include "sdk_errors.h"
#include "nrf_gpio.h"
#include "ConfigurationIO.h"
#include "afe4404_application.h"
#include "stk8321_application.h"
#include "ppg_app.h"
#include "nrf_log.h"
//------------------------------------------------------------------------------------

#define UPDATE_INTERVAL_MS    20
#define  APP_TASK_INTERVAL    APP_TIMER_TICKS(UPDATE_INTERVAL_MS) 
#define UPDATE_INTERVAL_10SEC    500
#define MAX_MILLIAMP    9
//------------------------------------------------------------------------------------
ret_code_t err_code;
APP_TIMER_DEF(m_app_timer_id);   
t_buftransfer debug_transfer_dat;
uint32_t transition_cnt ;
static uint32_t miliamp_step;
//------------------------------------------------------------------------------------
void test_transition(void)
{
  if( nrf_gpio_pin_read(GPIO_TX) == 0 )
  {
    miliamp_step = 0;
    memcpy(&debug_transfer_dat.currentsetting,&miliamp_step,sizeof(miliamp_step));
    afe4404_set_led_currents( miliamp_step,miliamp_step,miliamp_step ); //red,ir,green 
    transition_cnt = 0;
  }
  transition_cnt++;
  if(transition_cnt == UPDATE_INTERVAL_10SEC)
  {
    transition_cnt = 0;
    miliamp_step++;
    if(miliamp_step > MAX_MILLIAMP)
      miliamp_step = 0;
    memcpy(&debug_transfer_dat.currentsetting,&miliamp_step,sizeof(miliamp_step));
    afe4404_set_led_currents( miliamp_step,miliamp_step,miliamp_step ); //red,ir,green 
  }

}
//------------------------------------------------------------------------------------
void app_task(void * p_context)
{
  //ppg_task();
  //imu_task();
  //algorithm_task();
  //ui_task();
  //transfer_task();
  //nrf_gpio_pin_set(GPIO_VDD_EN);
 
  stk8321_app_get_acc_x(&debug_transfer_dat.accx);
  afe4404_app_getppg_all(&debug_transfer_dat.ppg1);
  test_transition();
  //stk8321_app_getid();
  
}
//------------------------------------------------------------------------------------
void app_init(void)
{
  err_code = app_timer_create(&m_app_timer_id,APP_TIMER_MODE_REPEATED,app_task);
  APP_ERROR_CHECK(err_code);
  /*do somthing before start timer*/
 // nrf_gpio_pin_dir_set(GPIO_VDD_EN, NRF_GPIO_PIN_DIR_OUTPUT);       //enable power
   nrf_gpio_pin_dir_set(GPIO_MOTOR, NRF_GPIO_PIN_DIR_OUTPUT);       //enable power
   nrf_gpio_cfg(
    GPIO_VDD_EN,
    NRF_GPIO_PIN_DIR_OUTPUT,
    NRF_GPIO_PIN_INPUT_DISCONNECT,
    NRF_GPIO_PIN_NOPULL,
    NRF_GPIO_PIN_S0S1,
    NRF_GPIO_PIN_NOSENSE);
  nrf_gpio_pin_dir_set(GPIO_VLED_PWR_EN, NRF_GPIO_PIN_DIR_OUTPUT);
 // nrf_gpio_pin_dir_set(GPIO_TX, NRF_GPIO_PIN_DIR_INPUT);
  nrf_gpio_cfg(
    GPIO_TX,
    NRF_GPIO_PIN_DIR_INPUT,
    NRF_GPIO_PIN_INPUT_CONNECT,
    NRF_GPIO_PIN_PULLUP,
    NRF_GPIO_PIN_S0S1,
    NRF_GPIO_PIN_NOSENSE);
  nrf_gpio_pin_clear(GPIO_VDD_EN);    //enable power
  nrf_gpio_pin_set(GPIO_VLED_PWR_EN); //enable power

  //nrf_gpio_pin_set(GPIO_VDD_EN);      //disable power
  //nrf_gpio_pin_clear(GPIO_VLED_PWR_EN); //disable power

  afe4404_app_init();
  stk8321_app_init();
  transition_cnt = 0;
  miliamp_step = 0;
  debug_transfer_dat.currentsetting = miliamp_step;
  /*start timer*/
  err_code = app_timer_start(m_app_timer_id, APP_TASK_INTERVAL, NULL);
  APP_ERROR_CHECK(err_code); 
}
//------------------------------------------------------------------------------------