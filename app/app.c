#include "app.h"
#include "app_timer.h"
#include "sdk_errors.h"
#include "nrf_gpio.h"
#include "ConfigurationIO.h"
#include "afe4404_application.h"
//------------------------------------------------------------------------------------

#define UPDATE_INTERVAL_MS              1000
#define  APP_TASK_INTERVAL    APP_TIMER_TICKS(UPDATE_INTERVAL_MS) 
ret_code_t err_code;
APP_TIMER_DEF(m_app_timer_id);   
uint32_t tempppg;

//------------------------------------------------------------------------------------
void app_task(void * p_context)
{
  ppg_task();
  imu_task();
  algorithm_task();
  ui_task();
  transfer_task();
}
//------------------------------------------------------------------------------------
void app_init(void)
{
  err_code = app_timer_create(&m_app_timer_id,APP_TIMER_MODE_REPEATED,app_task);
  APP_ERROR_CHECK(err_code);
  /*do somthing before start timer*/
  nrf_gpio_pin_dir_set(GPIO_VDD_EN, NRF_GPIO_PIN_DIR_OUTPUT); //enable power
  nrf_gpio_pin_dir_set(GPIO_MOTOR, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_set(GPIO_VDD_EN);
  afe4404_app_init();

  //nrf_gpio_pin_set(GPIO_MOTOR);
  /*start timer*/
  err_code = app_timer_start(m_app_timer_id, APP_TASK_INTERVAL, NULL);
  APP_ERROR_CHECK(err_code); 
}
//------------------------------------------------------------------------------------