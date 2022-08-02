#include "stk8321_application.h"
#include <string.h>
#include "nrf_log.h"


//------------------------------------------------------------------------
void stk8321_app_init(void)
{
  hw_stk8321_init();

}
//------------------------------------------------------------------------
uint8_t stk8321_app_getid(void)
{
  uint32_t err_code;
  uint8_t tempdata= CHIP_ID|(1<<7);
  //uint8_t tempdata= CHIP_ID;
  uint8_t tempreturndata;
    err_code = hw_stk8321_transfer(&tempdata,sizeof(tempdata),&tempreturndata,sizeof(tempreturndata));
    NRF_LOG_INFO("CHIP_ID =   %d  \n\r", tempreturndata);
  return tempreturndata;
}
uint8_t stk8321_app_get_acc_xL(void)
{
  uint32_t err_code;
  uint8_t tempdata= XOUT1|(1<<7);
  uint8_t tempreturndata;
  err_code = hw_stk8321_transfer(&tempdata,sizeof(tempdata),&tempreturndata,1);
  return tempreturndata;
}

uint8_t stk8321_app_get_acc_xH(void)
{
  uint32_t err_code;
  uint8_t tempdata= XOUT2|(1<<7);
  uint8_t tempreturndata;
  err_code = hw_stk8321_transfer(&tempdata,sizeof(tempdata),&tempreturndata,1);
  return tempreturndata;
}
void stk8321_app_get_acc_x(uint32_t * pXdata)
{
  uint32_t err_code;
  uint8_t tempdata= XOUT1|(1<<7);
  uint16_t tempreturndata[2];
  tempreturndata[0]=stk8321_app_get_acc_xL();
  tempreturndata[1]=stk8321_app_get_acc_xH();
  uint32_t memtemp;
  memtemp = (tempreturndata[1]<<4)|(tempreturndata[0]>>4);

  NRF_LOG_INFO("accx =   %d  \n\r",  memtemp);
  memcpy(pXdata,&memtemp,sizeof(memtemp));
  //return tempreturndata;
}
//------------------------------------------------------------------------
