#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "AD.h"

void AD_Init(void)
{
	/* Initialize ADC peripheral here */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); /* Enable ADC1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); /* Enable GPIOA clock */
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; /* PA0 as ADC input */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; /* Analog input mode */
	GPIO_Init(GPIOA, &GPIO_InitStructure); /* Initialize GPIOA with the specified settings */


	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_1Cycles5);
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; /* Independent mode */
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; /* Right align data */
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; /* Disable scan mode */
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; /* Enable continuous conversion */
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; /* No external trigger */
	ADC_InitStructure.ADC_NbrOfChannel = 1; /* One channel */
	ADC_Init(ADC1, &ADC_InitStructure); /* Initialize ADC1 with the specified settings */

	ADC_Cmd(ADC1, ENABLE); /* Enable ADC1 */

	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1) == SET); /* Wait for calibration reset to complete */
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET); /* Wait for calibration to complete */

	ADC_SoftwareStartConvCmd(ADC1, ENABLE); /* Start ADC conversion */

}

uint16_t AD_GetValue(void)
{
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); /* Wait for conversion to complete */
	return ADC_GetConversionValue(ADC1); /* Return the converted value */
}