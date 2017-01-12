#pragma once
#ifndef _board_config_h
#define _board_config_h


// next 3 lines: choose which board you have
//#define NUCLEO
#define SWEEPER
//#define GD32_CLOCK



#ifdef SWEEPER
#define ILI9320
#else#define USING_TOUCH_ADC
#define ILI9341
#endif

#ifdef NUCLEO
#define NUCLEO_CLOCKS
#endif

#endif