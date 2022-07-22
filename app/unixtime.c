#include<stdint.h>
#define YEAR0 1970

//----------------------------------------------------------------------------------------------------
typedef struct
{
  uint8_t sec;
  uint8_t min;
  uint8_t hr;
  uint8_t year;
  uint8_t month;
  uint8_t date;
}DateTime;

unsigned char calendar [] = {31, 28, 31, 30,
                            31, 30, 31, 31,
                            30, 31, 30, 31};
//----------------------------------------------------------------------------------------------------
unsigned long unixtime(DateTime crtime)
{
  unsigned long unixtime_sec=0;                                     // stores how many seconds passed from 1.1.1970, 00:00:00
  if ((!(crtime.year%4)) && (crtime.month>2)) 
      unixtime_sec+=86400;                                        // if the current year is a leap one -> add one day (86400 sec)
      crtime.month-- ;                                             // dec the current month (find how many months have passed from the current year)
    while (crtime.month)                                           // sum the days from January to the current month
    {
      crtime.month--;                                              // dec the month
      unixtime_sec+=(calendar[crtime.month])*86400 ;                         // add the number of days from a month * 86400 sec
    }
    unixtime_sec += ((((crtime.year-YEAR0)*365)
                    +((crtime.year-YEAR0)/4))*(unsigned long)86400)
                    +(crtime.date-1)*(unsigned long)86400
                    +(crtime.hr*(unsigned long)3600)
                    +(crtime.min*(unsigned long)60)
                    +(unsigned long)crtime.sec;
  return unixtime_sec ;                                                      // return the UNIX TIME
}
//----------------------------------------------------------------------------------------------------