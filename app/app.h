#ifndef APP_H
#define APP_H

#include <stdint.h>
typedef struct
{
  uint32_t  header;
  uint32_t utc_time; 
  uint32_t subsec;
  int32_t  accx;
  int32_t  accy;
  int32_t  accz;

  uint32_t ppg1;
  uint32_t ppg2;
  uint32_t ppg3;
  uint32_t amb;
  uint32_t led1amb;
  uint32_t currentsetting;
  //uint32_t amb;
  //uint32_t ppg2_ppg3;
  //uint32_t ppg1_amb;

}t_buftransfer;
extern t_buftransfer debug_transfer_dat;
void app_init(void);
#endif //APP_H