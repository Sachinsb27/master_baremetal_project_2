#include "user_cfg.h"
#include <string.h>

#define ADC_VREF_MV 5000U // Reference voltage in millivolts (e.g., 3.3V)//
#define ADC_MAX_VALUE 4095U // Maximum ADC value for a 12-bit ADC//
#define TIMER_PERIOD_MSEC   1000U
#define ADC_THRESHOLD 1229

uint8_t app_heap[512] __attribute__((section (".heap")));
uint8_t app_stack[1024] __attribute__((section (".stack")));
uint16_t chanresult = 0;
//volatile int16_t adcResult_mV = 0;

/* SCB-UART Context*/
cy_stc_scb_uart_context_t SCB_UART_context;


int main()
{  
    /* HF CLOCK divider init*/
    Cy_SysClk_ClkHfSetDivider(0u); //0 - No Divider, 1 - DIV by 2, 2 = DIV by 4, 3 = DIV by 8
   
    /* Peripheral clock initializatio*/
    init_peri_Clock_Config();

    /*GPIO pin init LEDs*/

    /*GPIO pin init UART*/

    GPIO_Pin_Init((GPIO_PRT_Type *)CYREG_GPIO_PRT2_DR, 1u, &ADC_P2_1_config, HSIOM_SEL_GPIO); //ADC Init /*GPIO pin init ADC*/
    GPIO_Pin_Init((GPIO_PRT_Type *)CYREG_GPIO_PRT3_DR, 4u, &USERLED_P3_4_config, HSIOM_SEL_GPIO);//user led
    NVIC_SetPriority(3u, 1u);
    /* Clearing and enabling the GPIO interrupt in NVIC */
    NVIC_ClearPendingIRQ(3u);
    NVIC_EnableIRQ(3u);


    /* Peripheral clock initialization*/
    init_peri_Clock_Config();
    /*GPIO pin init PWM*/
     /*TIMER 2 - INTERRUPT*/
    NVIC_SetPriority(19, 1u); //timer 2 IRQn = 19, priority 1
    /* Clearing and enabling the GPIO interrupt in NVIC */
    NVIC_ClearPendingIRQ(19u);
    NVIC_EnableIRQ(19u);

    /*TIMER 2 - INIT*/
   

    /*TIMER 0 - INIT*/
   ;

    /*TIMER 3 - PWM - INIT*/
    //TCPWM_PWM_Init(TCPWM, 3U, &USER_PWM_config);
 

    /*Insert all Peripheral Initilization code of TRNG below*/

    /*Insert all Peripheral Initilization code of ADC below:*/

      /*GPIO pin init*/
    GPIO_Pin_Init((GPIO_PRT_Type *)CYREG_GPIO_PRT7_DR, 0u, &UART_RX_P7_0_config, HSIOM_SEL_UART);
    GPIO_Pin_Init((GPIO_PRT_Type *)CYREG_GPIO_PRT7_DR, 1u, &UART_TX_P7_1_config, HSIOM_SEL_UART);/*Insert all Peripheral Initilization code of UART*/

    /*Insert all Peripheral Initilization code of TIMER 0*/

    /*Insert all Peripheral Initilization code of TIMER 1*/

    /*Insert all Peripheral Initilization code of TIMER 2*/

    /*Insert all Peripheral Initilization code of TIMER 3-PWM*/
 
    /* ADC - Enable*/
    Cy_SAR_Init(SAR0, &pass_0_sar_0_config);
    init_cycfg_peripherals();
    Cy_SAR_Enable(SAR0);
    Cy_SCB_UART_Init(SCB3, &SCB_UART_config, &SCB_UART_context);  //driver (uart_init)
    Cy_SCB_UART_Enable(SCB3);
     
    /* Enable global interrupts */
    enable_irq();

    for(;;)
    {
      /* ADC Start conversion */ 
        Cy_SAR_StartConvert(SAR0, 1u);
        chanresult =  Cy_SAR_GetResult16(SAR0, 0u);
      //  adcResult_mV = (int16_t)((chanresult * ADC_VREF_MV) / ADC_MAX_VALUE);//
         if(chanresult > ADC_THRESHOLD){
                Cy_SCB_UART_PutString(SCB3, ">> VALUE GREATER THAN 1.5V OBSERVED \r\n\n");

            GPIO_write((GPIO_PRT_Type *)CYREG_GPIO_PRT3_DR, 4u, 1u);
            }
            else{
                GPIO_write((GPIO_PRT_Type *)CYREG_GPIO_PRT3_DR, 4u, 0u);
            }
 /* Write your application logic*/
    }
    
    return 0;
}

/*Delay with simple for loops*/
void Delay(int32_t delayNumber)
{
    for(int32_t i=0; i<delayNumber; i++);
    for(int32_t i=0; i<delayNumber; i++);
    for(int32_t i=0; i<delayNumber; i++);
    for(int32_t i=0; i<delayNumber; i++);
}


/*Peripheral clock initilizations*/
void init_peri_Clock_Config()
{
    //SCB3 - CLOCK - UART
    SysClk_PeriphDisableDivider(CY_SYSCLK_DIV_16_BIT, 0U);
    SysClk_PeriphSetDivider(CY_SYSCLK_DIV_16_BIT, 0U, 26 - 1);
    SysClk_PeriphEnableDivider(CY_SYSCLK_DIV_16_BIT, 0U);
    SysClk_PeriphAssignDivider(PCLK_SCB3_CLOCK, CY_SYSCLK_DIV_16_BIT, 0U);

    //TIMER 0 for Code profiling
    SysClk_PeriphDisableDivider(CY_SYSCLK_DIV_16_BIT, 1U);
    SysClk_PeriphSetDivider(CY_SYSCLK_DIV_16_BIT, 1U, 24 - 1);
    SysClk_PeriphEnableDivider(CY_SYSCLK_DIV_16_BIT, 1U);
    SysClk_PeriphAssignDivider(PCLK_TCPWM_CLOCKS0, CY_SYSCLK_DIV_16_BIT, 1U);

    //TIMER 1 TIMER- CLOCK
    SysClk_PeriphDisableDivider(CY_SYSCLK_DIV_16_BIT, 2U);
    SysClk_PeriphSetDivider(CY_SYSCLK_DIV_16_BIT, 2U, 24000 - 1);
    SysClk_PeriphEnableDivider(CY_SYSCLK_DIV_16_BIT, 2U);
    SysClk_PeriphAssignDivider(PCLK_TCPWM_CLOCKS1, CY_SYSCLK_DIV_16_BIT, 2U);

    //TIMER 2 TIMER- CLOCK
    SysClk_PeriphDisableDivider(CY_SYSCLK_DIV_16_BIT, 3U);
    SysClk_PeriphSetDivider(CY_SYSCLK_DIV_16_BIT, 3U, 24000 - 1);
    SysClk_PeriphEnableDivider(CY_SYSCLK_DIV_16_BIT, 3U);
    SysClk_PeriphAssignDivider(PCLK_TCPWM_CLOCKS2, CY_SYSCLK_DIV_16_BIT, 3U);
    
    //TIMER 3 PWM- CLOCK
    SysClk_PeriphDisableDivider(CY_SYSCLK_DIV_16_BIT, 4U);
    SysClk_PeriphSetDivider(CY_SYSCLK_DIV_16_BIT, 4U, 240U - 1);
    SysClk_PeriphEnableDivider(CY_SYSCLK_DIV_16_BIT, 4U);
    SysClk_PeriphAssignDivider(PCLK_TCPWM_CLOCKS3, CY_SYSCLK_DIV_16_BIT, 4U);

    //ADC - CLOCK
    SysClk_PeriphDisableDivider(CY_SYSCLK_DIV_16_BIT, 5U);
    SysClk_PeriphSetDivider(CY_SYSCLK_DIV_16_BIT, 5U, 24U - 1);
    SysClk_PeriphEnableDivider(CY_SYSCLK_DIV_16_BIT, 5U);
    SysClk_PeriphAssignDivider(PCLK_PASS0_CLOCK_SAR ,CY_SYSCLK_DIV_16_BIT , 5U);
}