#ifndef AFE_REG_MAP_H
#define AFE_REG_MAP_H


#define AFE_ADDR 88

/* AFE4404 Registers*/

//Diagnosis
#define DIAGNOSIS         0x00
#define DIAGNOSIS_SWRESET 1<<3
#define DIAGNOSIS_CNRESET 1<<1
#define DIAGNOSIS_WRMODE  0<<0
#define DIAGNOSIS_RDMODE  1<<0

//PRPCT ( timer counter )
#define PRPCT             0x1D   /**< Bits 0-15 for writing counter value      */

//Timer Module enable / NUMAV ( # of times to sample and average )
#define TIM_NUMAV         0x1E

#define TIA_GAINS1        0x21

//TIA Gains 2
#define TIA_GAINS2        0x20


//Sample LED2 Start / End
#define LED2STC           0x01
#define LED2ENDC          0x02

//LED1 Start / End
#define LED1LEDSTC        0x03
#define LED1LEDENDC       0x04

//Sample Ambient 2 ( or LED3 ) Start / End
#define LED3STC           0x05
#define LED3ENDC          0x06

//Sample LED1 Start / End
#define LED1STC           0x07
#define LED1ENDC          0x08

//LED2 Start / End
#define LED2LEDSTC        0x09
#define LED2LEDENDC       0x0A

//Sample Ambient 1 Start / End
#define ALED1STC          0x0B
#define ALED1ENDC         0x0C

//LED2 Convert Start / End
#define LED2CONVST        0x0D
#define LED2CONVEND       0x0E

//Ambient 2 ( or LED3 ) Convert Start / End
#define LED3CONVST        0x0F
#define LED3CONVEND       0x10

//LED1 Convert Start / End
#define LED1CONVST        0x11
#define LED1CONVEND       0x12

//Ambient 1 Convert Start / End
#define ALED1CONVST       0x13
#define ALED1CONVEND      0x14

//ADC Reset Phase 0 Start / End
#define ADCRSTSTCT0       0x15
#define ADCRSTENDCT0      0x16

//ADC Reset Phase 1 Start / End
#define ADCRSTSTCT1       0x17
#define ADCRSTENDCT1      0x18

//ADC Reset Phase 2 Start / End
#define ADCRSTSTCT2       0x19
#define ADCRSTENDCT2      0x1A

//ADC Reset Phase 3 Start / End
#define ADCRSTSTCT3       0x1B
#define ADCRSTENDCT3      0x1C

//LED Current Control
#define LED_CONFIG        0x22
/* ********************************************************************
 * LED current control is a 24 bit register where                     *
 * LED1: bits 0-5 LED2: bits 6-11 LED3: bits 12-17 and the rest are 0 *
 * ****************************************************************** *
 * LED1, LED2, LED3 Register Values | LED Current Setting (mA)        *
 *                   0              |              0                  *
 *                   1              |             0.8                 *
 *                   2              |             1.6                 *
 *                   3              |             2.4                 *
 *                  ...             |             ...                 *
 *                   63             |              50                 *
 **********************************************************************/


#define SETTINGS           0x23  /**< Settings Address */
#define SETTINGS_AFE_EN    1<<0 //Entire AFE is powered down
#define SETTINGS_AFE_DIS   0<<0 //Normal mode
#define SETTINGS_RX_EN     1<<1 //RX portion of the AFE is powered do
#define SETTINGS_RX_DIS    0<<1 //Normal mode
#define SETTINGS_DY4_EN    1<<3 //Rest of ADC is powered down in dynamic power-down mode
#define SETTINGS_DY4_DIS   0<<3 //Rest of ADC is not powered down
#define SETTINGS_DY3_EN    1<<4 //TIA is powered down in dynamic power-down mode
#define SETTINGS_DY3_DIS   0<<4 //TIA is not powered down
#define SETTINGS_OSC_EN    1<<9 // internal oscillator is enabled.
#define SETTINGS_OSC_DIS   0<<9 // External clock mode
#define SETTINGS_DY2_EN    1<<14 //ADC is powered down in dynamic power-down mode
#define SETTINGS_DY2_DIS   0<<14 //ADC is not powered down
#define SETTINGS_ILED_100  1<<17 //LED current range is 0 mA to 100 mA
#define SETTINGS_ILED_50   0<<17 //LED current range is 0 mA to 50 mA
#define SETTINGS_DY1_EN    1<<20 //Transmitter is powered down in dynamic power-down mode
#define SETTINGS_DY1_DIS   0<<20 //Transmitter is not powered down

//Clockout Settings
#define CLKOUT            0x29  /**< Clockout Address */
/* *****************************************************************************
	*  CLKOUT_DIV Register Settings Graph
	* ****************************************************************************
	* CLKOUT_DIV Register Settings | Division Ratio | Output Clock Freq. ( MHz ) *
	*             0                |         1      |             4              *
	*             1                |         2      |             2              *
	*             2                |         4      |             1              *
	*             3                |         8      |            0.5             *
	*             4                |        16      |           0.25             *
	*             5                |        32      |          0.125             *
	*             6                |        64      |         0.0625             *
	*             7                |       128      |        0.03125             *
	*         8..15                |    Do not use  |      Do not use            *
	*****************************************************************************/

//LED1 Output Value
#define LED1VAL           0x2C  /**< LED1 Output code in twos complement      */

//LED2 Output Value
#define LED2VAL           0x2A  /**< LED2 Output code in twos complement      */

//LED3 or Ambient 2 Value
#define LED3VAL           0x2B  /**< LED3 / Ambient 2 value in twos complement*/

//Ambient 1 Value
#define ALED1VAL          0x2D  /**< Ambient 1 value in twos complement       */

//LED1-Ambient 1 Value
#define LED1_ALED1VAL     0x2F  /**< LED1-ambient1 in twos complement         */

//LED2-Ambient 2 Value
#define LED2_ALED2VAL     0x2E  /**< LED2-ambient2 in twos complement         */


//Diagnostics Flag
#define PD_SHORT_FLAG     0x30  /**< 0: No short across PD 1: Short across PD */

//PD disconnect / INP, INN settings / EXT clock Division settings
#define PD_INP_EXT        0x31
#define PD_DISCONNECT        2  /**< Disconnects PD signals (INP, INM)        */
#define ENABLE_INPUT_SHORT   5  /**< INP, INN are shorted to VCM when TIA dwn */
#define CLKDIV_EXTMODE       0  /**< Ext Clock Div Ration bits 0-2            */

/* *****************************************************************************
	*  CLKDIV_EXTMODE Register Settings Graph
	* ****************************************************************************
	* CLKDIV_EXTMODE Settings      | Division Ratio | Allowed Clock Freq ( MHz ) *
	*             0                |         2      |           8-12             *
	*             1                |         8      |          32-48             *
	*             2                |    Do Not Use  |       Do Not Use           *
	*             3                |         8      |          48-60             *
	*             4                |        16      |          16-24             *
	*             5                |        32      |            4-6             *
	*             6                |        64      |          24-36             *
	*             7                |    Do Not Use  |       Do Not Use           *
	*****************************************************************************/

//PDN_CYCLE Start / End
#define PDNCYCLESTC       0x32  /**< Bits 0-15                                */
#define PDNCYCLEENDC      0x33  /**< Bits 0-15                                */

//Programmable Start / End time for ADC_RDY replacement
#define PROG_TG_STC       0x34  /**< Bits 0-15 Define Start Time              */
#define PROG_TG_ENDC      0x35  /**< Bits 0-15 Define End Time                */

//LED3C Start / End
#define LED3LEDSTC        0x36  /**< LED3 Start, if not used set to 0         */
#define LED3LEDENDC       0x37  /**< LED3 End, if not used set to 0           */

//PRF Clock Division settings
#define CLKDIV_PRF        0x39  /**< Clock Division Ratio for timing engine   */
/* ****************************************************************************
	*   CLKDIV_PRF Register Settings Graph
	* ****************************************************************************
	* CLKDIV_PRF Settings|Division Ratio|Clock Freq(MHz)| Lowest PRF Setting (Hz)*
	*          0         |       1      |       4       |           61           *
	*          1         |  Do Not Use  |  Do Not Use   |      Do Not Use        *
	*          2         |  Do Not Use  |  Do Not Use   |      Do Not Use        *
	*          3         |  Do Not Use  |  Do Not Use   |      Do Not Use        *
	*          4         |       2      |       2       |           31           *
	*          5         |       4      |       1       |           15           *
	*          6         |       8      |     0.5       |            8           *
	*          7         |      16      |    0.25       |            4           *
	*****************************************************************************/

//DAC Settings
#define DAC_SETTING       0x3A  /**< DAC Settings Address                     */
#define POL_OFFDAC_LED2     19  /**< Polarity for LED2                        */
#define I_OFFDAC_LED2       15  /**< Setting for LED2                         */
#define POL_OFFDAC_AMB1     14  /**< Polarity for Ambient 1                   */
#define I_OFFDAC_AMB1       10  /**< Setting for Ambient 1                    */
#define POL_OFFDAC_LED1      9  /**< Polarity for LED1                        */
#define I_OFFDAC_LED1        5  /**< Setting for LED1                         */
#define POL_OFFDAC_LED3      4  /**< Polarity for LED3                        */
#define I_OFFDAC_LED3        0  /**< Setting for LED3                         */
/* **************************************************************
 *  I_OFFDAC Register Settings                                  *
 * **************************************************************
 * * Reg. Settings | Offset Cancellation | Offset Cancellation  |
 * *               |   POL_OFFDAC = 0    |   POL_OFFDAC = 1     |
 * **************************************************************
 *        0        |          0          |           0          *
 *        1        |       0.47          |       –0.47          *
 *        2        |       0.93          |       –0.93          *
 *        3        |        1.4          |        –1.4          *
 *        4        |       1.87          |       –1.87          *
 *        5        |       2.33          |       –2.33          *
 *        6        |        2.8          |        –2.8          *
 *        7        |       3.27          |       –3.27          *
 *        8        |       3.73          |       –3.73          *
 *        9        |        4.2          |        –4.2          *
 *       10        |       4.67          |       –4.67          *
 *       11        |       5.13          |       –5.13          *
 *       12        |        5.6          |        –5.6          *
 *       13        |       6.07          |       –6.07          *
 *       14        |       6.53          |       –6.53          *
 *       15        |          7          |          –7          *
 ****************************************************************/



#endif // AFE_REG_MAP_H