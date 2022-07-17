#include <stdbool.h>
#include "nrf.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"
#include "boards.h"


#define	GPIO_OLED_EN		0
#define	GPIO_KEY1			1
#define	GPIO_BATM			2
#define	GPIO_MOTOR			3
#define	GPIO_VDD_EN			4
#define	GPIO_VLED_PWR_EN	5
#define	GPIO_USB_INST		6
#define	GPIO_BP_PWR_EN		7
#define	GPIO_KEY2			8
#define	GPIO_TFT_TEST		9
#define	GPIO_PPG_RST		10
#define	GPIO_PPG_INT		11
#define	GPIO_I2C_SDA		12
#define	GPIO_I2C_SCL		13
#define	GPIO_MEM_SI			14
#define	GPIO_MEM_SO			15
#define	GPIO_MEM_WP			16
#define	GPIO_MEM_HOLD		17
#define	GPIO_MEM_CLK		18
#define	GPIO_MEM_CS			19
#define	GPIO_DISP_DC		20
#define	GPIO_DISP_CS		21
#define	GPIO_DISP_RST		22
#define	GPIO_PPG_RST		23
#define	GPIO_TP_RST			24
#define	GPIO_TP_INT			25
#define	GPIO_ISP_EN			26
#define	GPIO_SPK1			27
#define	GPIO_SPK0			28
#define	GPIO_UART_RX		29
#define	GPIO_UART_TX		30
#define	GPIO_TEMP			31