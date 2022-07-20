#include "app.h"
#include "app_timer.h"
#include "sdk_errors.h"
#include "nrf_gpio.h"
#include "ble_nus.h"
#define GREEN_PIN 18

BLE_NUS_DEF(m_nus, 1); 
#define UPDATE_INTERVAL_MS              1000
#define  APP_TASK_INTERVAL    APP_TIMER_TICKS(UPDATE_INTERVAL_MS) 
ret_code_t err_code;
APP_TIMER_DEF(m_app_timer_id);   

void app_task(void * p_context)
{
  nrf_gpio_pin_toggle(GREEN_PIN);
}

void app_init(void)
{
  err_code = app_timer_create(&m_app_timer_id,APP_TIMER_MODE_REPEATED,app_task);
  APP_ERROR_CHECK(err_code);
/*
do somthing before start timer


*/
  nrf_gpio_pin_dir_set(GREEN_PIN, NRF_GPIO_PIN_DIR_OUTPUT);
  nrf_gpio_pin_set(GREEN_PIN);
  err_code = app_timer_start(m_app_timer_id, APP_TASK_INTERVAL, NULL);
  APP_ERROR_CHECK(err_code); 
}