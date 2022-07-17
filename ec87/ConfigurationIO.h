#include <stdbool.h>
#include "nrf.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"
#include "boards.h"


#define	GPIO_MOTOR		0
#define	GPIO_AFE_RESET		1
#define	GPIO_BATM		2
#define	GPIO_TEMP		3
#define	GPIO_VDD_EN		4
#define	GPIO_VLED_PWR_EN	5
#define	GPIO_ECG_PWR_EN		6
#define	GPIO_USB_INST		7
#define	GPIO_OLED_EN		8
#define	GPIO_TX			9
#define	GPIO_RX			10
#define	GPIO_PPG_INT		11
#define	GPIO_I2C_SDA		12
#define	GPIO_I2C_SCL		13
#define	GPIO_MEMSI		14
#define	GPIO_MEM_SO		15
#define	GPIO_MEM_WP		16
#define	GPIO_MEM_HOLD		17
#define	GPIO_LCM_SCLK		18
#define	GPIO_MEM_CS		19
#define	GPIO_LCM_DC		20
#define	GPIO_LCM_CS		21
#define	GPIO_LCM_RESET		22
#define	GPIO_TP_INT		23
#define	GPIO_TP_RES		24
#define	GPIO_SPI_ADS_CS		25
#define	GPIO_SPI_MOSI		26
#define	GPIO_SPI_SCLK		27
#define	GPIO_SPI_MISO		28
#define	GPIO_ADS_DRDY		29
#define	GPIO_ADS_PWDN_RST	30
#define	GPIO_8321_CS 		31