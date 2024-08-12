#include "user_cfg.h"

const cy_stc_trng_config_t TRNG_config = 
{
    .trng_firo_ctl_reg_value = 0x00000041u, //The polynomial for the programmable Fibonacci ring oscillator
    .trng_garo_ctl_reg_value = 0x00000041u, //The polynomial for programmable Galois ring oscillator
    .trng_ctl0_reg_value = 0x01FF4040,  // SAMPLE_CLOCK_DIV = 0x40, RED_CLOCK_DIV = 0x40, INIT_DELAY = 0xFF, VON_NEUMANN_CORR = 0x1 
    .trng_cmd_start_ro = 0x3F, /* Enable all ring oscillators */
    .trng_bit_size = 12, //Max number of TRNG bits to be generated

};

const cy_stc_gpio_pin_config_t UART_RX_P7_0_config = 
{
    .outVal = 1,
    .driveMode = 0x01UL, //HiZ
    .intEdge = 0x00UL, //disabled
    .vtrip = 0, //CMOS
    .slewRate = 0, //FAST
};

const cy_stc_gpio_pin_config_t UART_TX_P7_1_config = 
{
    .outVal = 1,
    .driveMode = 0x0EUL, //Strong Drive, Input buffer off
    .intEdge = 0x00UL, //disabled
    .vtrip = 0, //CMOS
    .slewRate = 0, //FAST
};


const cy_stc_gpio_pin_config_t USERLED_P3_4_config = 
{
    .outVal = 1,
    .driveMode = 0x06UL, // 1 - HZ, 2 - PU, 3 - PD, 6 - SD
    .intEdge = 0x0UL, // 0 - disabled, 1 - Rising, 2 - Falling, 3 - Both
    .vtrip = 0, //0 - CMOS, 1 - TTL
    .slewRate = 0, //0 - fast, 1 - slow
};

const cy_stc_gpio_pin_config_t LED10_P2_2_config = 
{
    .outVal = 1,
    .driveMode = 0x06UL, // 1 - HZ, 2 - PU, 3 - PD, 6 - SD
    .intEdge = 0x0UL, // 0 - disabled, 1 - Rising, 2 - Falling, 3 - Both
    .vtrip = 0, //0 - CMOS, 1 - TTL
    .slewRate = 0, //0 - fast, 1 - slow
};

const cy_stc_gpio_pin_config_t LED10_P2_0_config = 
{
    .outVal = 1,
    .driveMode = 0x06UL, // 1 - HZ, 2 - PU, 3 - PD, 6 - SD
    .intEdge = 0x0UL, // 0 - disabled, 1 - Rising, 2 - Falling, 3 - Both
    .vtrip = 0, //0 - CMOS, 1 - TTL
    .slewRate = 0, //0 - fast, 1 - slow
};

const cy_stc_gpio_pin_config_t ADC_P2_1_config = 
{
    .outVal = 1,
    .driveMode = 0x09UL,   //1001
    .intEdge = 0x00UL,
    .vtrip = 0,
    .slewRate = 0,
};

const cy_stc_gpio_pin_config_t PWM_P1_2_config = 
{
    .outVal = 1,
    .driveMode = 0x06UL, // 1 - HZ, 2 - PU, 3 - PD, 6 - SD
    .intEdge = 0x0UL, // 0 - disabled, 1 - Rising, 2 - Falling, 3 - Both
    .vtrip = 0, //0 - CMOS, 1 - TTL
    .slewRate = 0, //0 - fast, 1 - slow
};


const cy_stc_scb_uart_config_t SCB_UART_config = 
{
    .uartMode = CY_SCB_UART_STANDARD,
    .oversample = 8,
    .enableMsbFirst = false,
    .dataWidth = 8UL,
    .parity = CY_SCB_UART_PARITY_NONE,
    .stopBits = CY_SCB_UART_STOP_BITS_1,
    .enableCts = false,
    .ctsPolarity = CY_SCB_UART_ACTIVE_LOW,
    .rtsRxFifoLevel = 0UL,
    .rtsPolarity = CY_SCB_UART_ACTIVE_LOW,
    .rxFifoTriggerLevel = 7UL,
    .rxFifoIntEnableMask = 0UL,
    .txFifoTriggerLevel = 7UL,
    .txFifoIntEnableMask = 0UL,
};


const cy_stc_tcpwm_counter_config_t TIMER1_config = 
{
    .period = 32768,
    .clockPrescaler = 0, //Prescalar divide by 1
    .runMode = 0u, //0 - Contineous, 1 - OneShot
    .countDirection = 0, //0- Count Up, 1 - Count Down
    .compareOrCapture = 2U, //2- Capture, 0 - Compare mode
    .compare0 = 16384,
    .compare1 = 16384,
    .enableCompareSwap = false,
    .interruptSources = 1U, // (0U) No Interrupt, (1U) Interrupt on Terminal count(TC), (2U) Interrupt on Compare/Capture(CC), (3U) Interrupt on TC or CC
    .captureInputMode = CYBSP_TIMER_INPUT_DISABLED & 0x3U,
    .captureInput = 0, //0 Logic 0, 1- logic 1
    .reloadInputMode = CYBSP_TIMER_INPUT_DISABLED & 0x3U,
    .reloadInput = 0, //0 Logic 0, 1- logic 1
    .startInputMode = CYBSP_TIMER_INPUT_DISABLED & 0x3U,
    .startInput = 0, //0 Logic 0, 1- logic 1
    .stopInputMode = CYBSP_TIMER_INPUT_DISABLED & 0x3U,
    .stopInput = 0, //0 Logic 0, 1- logic 1
    .countInputMode = CYBSP_TIMER_INPUT_DISABLED & 0x3U,
    .countInput = 1u,
};

const cy_stc_tcpwm_counter_config_t TIMER2_config = 
{
    .period = 32768,
    .clockPrescaler = 0, //Prescalar divide by 1
    .runMode = 0u, //0 - Contineous, 1 - OneShot
    .countDirection = 0, //0- Count Up, 1 - Count Down
    .compareOrCapture = 2U, //2- Capture, 0 - Compare mode
    .compare0 = 16384,
    .compare1 = 16384,
    .enableCompareSwap = false,
    .interruptSources = 1U, // (0U) No Interrupt, (1U) Interrupt on Terminal count(TC), (2U) Interrupt on Compare/Capture(CC), (3U) Interrupt on TC or CC
    .captureInputMode = CYBSP_TIMER_INPUT_DISABLED & 0x3U,
    .captureInput = 0, //0 Logic 0, 1- logic 1
    .reloadInputMode = CYBSP_TIMER_INPUT_DISABLED & 0x3U,
    .reloadInput = 0, //0 Logic 0, 1- logic 1
    .startInputMode = CYBSP_TIMER_INPUT_DISABLED & 0x3U,
    .startInput = 0, //0 Logic 0, 1- logic 1
    .stopInputMode = CYBSP_TIMER_INPUT_DISABLED & 0x3U,
    .stopInput = 0, //0 Logic 0, 1- logic 1
    .countInputMode = CYBSP_TIMER_INPUT_DISABLED & 0x3U,
    .countInput = 1u,
};
const cy_stc_tcpwm_counter_config_t TIMER0_config = 
{
    .period = 32768,
    .clockPrescaler = 0, //Prescalar divide by 1
    .runMode = 0u, //0 - Contineous, 1 - OneShot
    .countDirection = 0, //0- Count Up, 1 - Count Down
    .compareOrCapture = 2U, //2- Capture, 0 - Compare mode
    .compare0 = 16384,
    .compare1 = 16384,
    .enableCompareSwap = false,
    .interruptSources = 0U, // (0U) No Interrupt, (1U) Interrupt on Terminal count(TC), (2U) Interrupt on Compare/Capture(CC), (3U) Interrupt on TC or CC
    .captureInputMode = CYBSP_TIMER_INPUT_DISABLED & 0x3U,
    .captureInput = 0, //0 Logic 0, 1- logic 1
    .reloadInputMode = CYBSP_TIMER_INPUT_DISABLED & 0x3U,
    .reloadInput = 0, //0 Logic 0, 1- logic 1
    .startInputMode = CYBSP_TIMER_INPUT_DISABLED & 0x3U,
    .startInput = 0, //0 Logic 0, 1- logic 1
    .stopInputMode = CYBSP_TIMER_INPUT_DISABLED & 0x3U,
    .stopInput = 0, //0 Logic 0, 1- logic 1
    .countInputMode = CYBSP_TIMER_INPUT_DISABLED & 0x3U,
    .countInput = 1u,
};
const cy_stc_tcpwm_pwm_config_t TIMER3_PWM_config = 
{
    .pwmMode = 4U,    /* Standard PWM Mode*/
    .clockPrescaler = 0U, //Divide by 1
    .pwmAlignment = 0U, // 0 = LEFT ALIGH, 1= RIGHT ALIGN, 2U = CENTER ALIGN
    .deadTimeClocks = 0,
    .runMode = 0U, //0 = CONTINUOUS, 1 = One Shot
    .period0 = 5500,
    .period1 = 5000,
    .enablePeriodSwap = false,
    .compare0 = 5000,
    .compare1 = 1000,
    .enableCompareSwap = false,
    .interruptSources = 0U, //0 = No Interrupt, 1 = TC, 2 = CC, 3 = TC & CC
    .invertPWMOut = 0U, //0 = Disable Invert Mode
    .invertPWMOutN = 0U, //0 = Do not invert
    .killMode = 2U, //PWM stops counting on kill
    .swapInputMode = 0x7U & 0x3U,
    .swapInput = 0u,
    .reloadInputMode = 0x7U & 0x3U,
    .reloadInput = 0u,
    .startInputMode = 0x7U & 0x3U,
    .startInput = 0u,
    .killInputMode = 0x7U & 0x3U,
    .killInput = 0u,
    .countInputMode = 0x7U & 0x3U,
    .countInput = 1U,
};

const cy_stc_sar_channel_config_t pass_0_sar_0_channel_0_config = 
{
    .addr = (cy_en_sar_chan_config_port_pin_addr_t)(CY_SAR_ADDR_SARMUX_1),
    .differential = false,
    .resolution = 0UL, //12bit res = 0
    .avgEn = false,
    .sampleTimeSel = 0UL,
    .rangeIntrEn = false,
    .satIntrEn = false,
};
const cy_stc_sar_config_t pass_0_sar_0_config = 
{
    .vrefSel = 7UL, //CY_SAR_VREF_SEL_VDDA - 5V
    .vrefBypCapEn = false,
    .negSel = 0UL, //CY_SAR_NEG_SEL_VSSA_KELVIN - Negative ip selection
    .negVref = 1UL,
    .boostPump = false,
    .power = 1UL,
    .sarMuxDsEn = false,
    .switchDisable = false,
    .subResolution = 1UL, //10-bit Sub resolution
    .leftAlign = false,
    .singleEndedSigned = false,
    .differentialSigned = true,
    .avgCnt = 7UL, //average - 256
    .avgShift = true,
    .trigMode = 0UL,
    .eosEn = false,
    .sampleTime0 = 13,
    .sampleTime1 = 2,
    .sampleTime2 = 2,
    .sampleTime3 = 2,
    .rangeThresLow = 0UL,
    .rangeThresHigh = 0UL,
    .rangeCond = 0UL,
    .chanEn = 1UL,
    .channelConfig = {&pass_0_sar_0_channel_0_config, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    .routingConfig = NULL,
    .vrefMvValue = 5000UL,
};