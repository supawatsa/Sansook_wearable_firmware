#include "stk8321_application.h"
#include <string.h>
#include "nrf_log.h"


//------------------------------------------------------------------------
void stk8321_app_init(void)
{
  hw_stk8321_init();
    uint32_t err_code;
  uint8_t tempdata[2];
  uint8_t tempreturndata;
  tempdata[0] = RANGESEL;
  tempdata[1] = RANG2G;
  err_code = hw_stk8321_transfer(tempdata,sizeof(tempdata),&tempreturndata,0);

}
//------------------------------------------------------------------------
uint8_t stk8321_app_getid(void)
{
  uint32_t err_code;
  uint8_t tempdata= CHIP_ID|(1<<7);
  uint8_t tempreturndata;
  err_code = hw_stk8321_transfer(&tempdata,sizeof(tempdata),&tempreturndata,sizeof(tempreturndata));
  NRF_LOG_INFO("CHIP_ID =   %d  \n\r", tempreturndata);
  return tempreturndata;
}

void stk8321_app_get_acc_all(int32_t * pXdata)
{
  uint32_t err_code;
  uint8_t tempdata= XOUT1|(1<<7);
  uint8_t tempreturndata[6];
  err_code = hw_stk8321_transfer(&tempdata,sizeof(tempdata),tempreturndata,sizeof(tempreturndata));
  //NRF_LOG_INFO("xH =   %d  \n\r", tempreturndata[0]);
  //NRF_LOG_INFO("xL =   %d  \n\r", tempreturndata[1]);
  //NRF_LOG_INFO("yH =   %d  \n\r", tempreturndata[2]);
  //NRF_LOG_INFO("yL =   %d  \n\r", tempreturndata[3]);
  //NRF_LOG_INFO("zL =   %d  \n\r", tempreturndata[4]);
  //NRF_LOG_INFO("zL =   %d  \n\r", tempreturndata[5]);
  int32_t memtemp[3];
  memtemp[0] = ((tempreturndata[0]<<8)|(tempreturndata[1])>>4);
  memtemp[1] = ((tempreturndata[2]<<8)|(tempreturndata[3])>>4);
  memtemp[2] = ((tempreturndata[4]<<8)|(tempreturndata[5])>>4);
  memcpy(pXdata,&memtemp,sizeof(memtemp));
  //return tempreturndata;
}
//------------------------------------------------------------------------
