/*
* Touch driver for the adafruit 2.4 LCD
* resistive screen, uses the D0 and D1 lines for sensing
* and the CS and xxx line
*
* This file is used in conjonction with the GUI_X_Touch.c unchanged
* from the emWin/samples
*/

#include "stm32f1xx_hal.h"
#include <GUI.h>
#include "Board_Touch.h"
#include "Touch_ADC.h"
#include "LCDConf_F103_24.h"


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3) {
		if (LCD_SafeToInterrupt()){
			GUI_TOUCH_Exec(); 
		}
	}
}



#define USE_EMWIN_ANALOG_DRIVER
#ifdef USE_EMWIN_ANALOG_DRIVER


void Touch_GetState(TOUCH_STATE *touch_state)
{
	touch_state->pressed = 0;
}

volatile static int pressure;
void GUI_TOUCH_X_ActivateY(void){ // for X measurements
	GPIO_Z_MeasurementSetup();
	pressure = GPIO_Z_Measurement();
}

int GUI_TOUCH_X_MeasureX(void){
	int xValue=-1;
	if (pressure > 500) {
		GPIO_X_MeasurementSetup();
		xValue = GPIO_X_Measurement();
	}
	return xValue;
}

void GUI_TOUCH_X_ActivateX(void) { //  for Y measurements
}

int GUI_TOUCH_X_MeasureY(void){
	int yValue = -1;
	if (pressure > 500) {
		GPIO_Y_MeasurementSetup();
		yValue = GPIO_Y_Measurement();
	}
	return yValue;
}

#define TOUCH_AD_LEFT 3500
#define TOUCH_AD_RIGHT 400
#define TOUCH_AD_TOP 3500
#define TOUCH_AD_BOTTOM 500

#define XSIZE_PHYS  240
#define YSIZE_PHYS  320

void   Touch_Initialize(void)
{
/* initializes the ADC and GPIOs */
	GUI_TOUCH_Calibrate(GUI_COORD_X, 0, XSIZE_PHYS - 1, TOUCH_AD_LEFT, TOUCH_AD_RIGHT);    	
	/* Calibrate y */
	GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, YSIZE_PHYS - 1, TOUCH_AD_TOP, TOUCH_AD_BOTTOM); 

	LCD_Touch_ADC_Init();
}
#else#endif