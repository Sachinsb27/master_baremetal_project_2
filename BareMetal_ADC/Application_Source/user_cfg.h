#ifndef USER_CFG_H
#define USER_CFG_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "./../Device_Drivers/GPIO/gpio.h"
#include "./../Special_Libraries/reset.h"
#include "./../Special_Libraries/cmsis_gcc.h"
#include "./../Device_Drivers/CLOCK/Sys_Clock.h"
#include "./../Device_Drivers/SYSTICK/systick.h"
#include "./../Device_Drivers/TIMER/timer.h"
#include "./../Device_Drivers/ADC/ADC.h"
#include "./../Device_Drivers/SCB/uart.h"
#include "./../Device_Drivers/SCB/i2c.h"
#include "./../Device_Drivers/TRNG/trng.h"

//MACRO DECLARATIONS
#define CY_SET_REG32(addr, value)       (*((uint32_t *)(addr)) = (uint32_t)(value))
#define CYREG_GPIO_PRT1_DR      0x40040100u
#define CYREG_GPIO_PRT1_PC      0x40040108u

#define CYREG_GPIO_PRT2_DR      0x40040200u
#define CYREG_GPIO_PRT2_PC      0x40040208u

#define CYREG_GPIO_PRT3_DR      0x40040300u
#define CYREG_GPIO_PRT3_PC      0x40040308u

#define CYREG_GPIO_PRT4_DR      0x40040400u
#define CYREG_GPIO_PRT4_PC      0x40040408u

#define CYREG_GPIO_PRT5_DR      0x40040500u
#define CYREG_GPIO_PRT5_PC      0x40040508u

#define CYREG_GPIO_PRT6_DR      0x40040600u
#define CYREG_GPIO_PRT6_PC      0x40040608u

#define CYREG_GPIO_PRT7_DR      0x40040700u
#define CYREG_GPIO_PRT7_PC      0x40040708u


#define HSIOM_SEL_GPIO          0u
#define HSIOM_SEL_PWM           8u
#define HSIOM_SEL_AMUXB         7u
#define HSIOM_SEL_UART          9u
#define HSIOM_SEL_I2C           14u

#define CYREG_SRSSLT_CLK_SELECT 0x40030028

#define CYBSP_TIMER_INPUT_DISABLED 0x7U

extern const cy_stc_gpio_pin_config_t UART_RX_P7_0_config;
extern const cy_stc_gpio_pin_config_t UART_TX_P7_1_config;
extern const cy_stc_gpio_pin_config_t USERLED_P3_4_config;
extern const cy_stc_gpio_pin_config_t LED10_P2_2_config;
extern const cy_stc_gpio_pin_config_t LED10_P2_0_config;
extern const cy_stc_gpio_pin_config_t ADC_P2_1_config;
extern const cy_stc_gpio_pin_config_t PWM_P1_2_config;

extern const cy_stc_scb_uart_config_t SCB_UART_config;
extern const cy_stc_tcpwm_counter_config_t TIMER2_config;
extern const cy_stc_tcpwm_counter_config_t TIMER1_config;
extern const cy_stc_tcpwm_counter_config_t TIMER0_config;
extern const cy_stc_tcpwm_pwm_config_t TIMER3_PWM_config;
extern const cy_stc_sar_config_t pass_0_sar_0_config ;
extern const cy_stc_trng_config_t TRNG_config;


extern void Delay(int32_t);
extern void init_peri_Clock_Config();
extern void timer_Delay_uS(uint32_t delay_uS);


#endif