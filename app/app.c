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
ret_code_t err_code;
APP_TIMER_DEF(m_app_timer_id);   

t_buftransfer debug_transfer_dat;


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
  nrf_gpio_pin_clear(GPIO_VDD_EN);    //enable power
  nrf_gpio_pin_set(GPIO_VLED_PWR_EN); //enable power

  //nrf_gpio_pin_set(GPIO_VDD_EN);      //disable power
  //nrf_gpio_pin_clear(GPIO_VLED_PWR_EN); //disable power

  afe4404_app_init();
  stk8321_app_init();

  /*start timer*/
  err_code = app_timer_start(m_app_timer_id, APP_TASK_INTERVAL, NULL);
  APP_ERROR_CHECK(err_code); 
}
//------------------------------------------------------------------------------------