#include "board_config.h"

#include "LCDConf_F103_24.h"
#include "stm32f1xx_hal.h"

/* compatibility macros */
#define wr_cmd8 LcdWriteReg8
#define wr_data8 LcdWriteData8
#define reg_write(cmd,data) {LcdWriteReg16(cmd);LcdWriteData16(data);}

#ifdef ILI9320

void lcd_ctrl_initialize(void)
{

	
//flipped = FLIP_X; // FLIP_NONE, FLIP_X, FLIP_Y, FLIP_X|FLIP_Y

	reg_write(0x00E5, 0x8000); // set the vcore voltage
	reg_write(0x0000, 0x0001); // start internal oscillator

	reg_write(0x0001, 0x0100); 
	reg_write(0x0002, 0x0700); 
	reg_write(0x0003, 0x1030); 
	reg_write(0x0004, 0x0000); 
	reg_write(0x0008, 0x0202);  
	reg_write(0x0009, 0x0000);
	reg_write(0x000A, 0x0000); 
	reg_write(0x000C, 0x0000); 
	reg_write(0x000D, 0x0000);
	reg_write(0x000F, 0x0000);
	//power on sequence
	reg_write(0x0010, 0x0000);   
	reg_write(0x0011, 0x0007);  
	reg_write(0x0012, 0x0000);  
	reg_write(0x0013, 0x0000); 
	reg_write(0x0007, 0x0001);
	HAL_Delay(200); 

	reg_write(0x0010, 0x10C0);   
	reg_write(0x0011, 0x0007);
	HAL_Delay(50); 

	reg_write(0x0012, 0x0110);
	HAL_Delay(50); 

	reg_write(0x0013, 0x0b00);
	HAL_Delay(50); 

	reg_write(0x0029, 0x0000); 
	reg_write(0x002B, 0x4010); // bit 14???
	HAL_Delay(50); 
//gamma
/*
 reg_write(0x0030,0x0004);
 reg_write(0x0031,0x0307);
 reg_write(0x0032,0x0002);// 0006
 reg_write(0x0035,0x0206);
 reg_write(0x0036,0x0408);
 reg_write(0x0037,0x0507); 
 reg_write(0x0038,0x0204);//0200
 reg_write(0x0039,0x0707); 
 reg_write(0x003C,0x0405);// 0504
 reg_write(0x003D,0x0F02);
 */
 //ram
	reg_write(0x0050, 0x0000); 
	reg_write(0x0051, 0x00EF);
	reg_write(0x0052, 0x0000); 
	reg_write(0x0053, 0x013F);  
	reg_write(0x0060, 0x2700); 
	reg_write(0x0061, 0x0001); 
	reg_write(0x006A, 0x0000); 
	//
	reg_write(0x0080, 0x0000); 
	reg_write(0x0081, 0x0000); 
	reg_write(0x0082, 0x0000); 
	reg_write(0x0083, 0x0000); 
	reg_write(0x0084, 0x0000); 
	reg_write(0x0085, 0x0000); 
	//
	reg_write(0x0090, 0x0000); 
	reg_write(0x0092, 0x0000); 
	reg_write(0x0093, 0x0001); 
	reg_write(0x0095, 0x0110); 
	reg_write(0x0097, 0x0000); 
	reg_write(0x0098, 0x0000);
 
	reg_write(0x0007, 0x0133); // display on
}

#elif defined(ILI9341)

void lcd_ctrl_initialize(void)
{


	/* Start Initial Sequence ----------------------------------------------------*/
    
	wr_cmd8(0xCB);  // POWER_ON_SEQ_CONTROL             
	wr_data8(0x39);
	wr_data8(0x2C);
	wr_data8(0x00);
	wr_data8(0x34);
	wr_data8(0x02);
     
	wr_cmd8(0xCF);  // POWER_CONTROL_B              
	wr_data8(0x00);
	wr_data8(0xC1);  // Applic Notes 81, was 83, C1 enables PCEQ: PC and EQ operation for power saving
	wr_data8(0x30);
     
	wr_cmd8(0xE8);  // DRIVER_TIMING_CONTROL_A               
	wr_data8(0x85);
	wr_data8(0x00);  // AN 10, was 01
	wr_data8(0x78);  // AN 7A, was 79
     
	wr_cmd8(0xEA);  // DRIVER_TIMING_CONTROL_B                    
	wr_data8(0x00);
	wr_data8(0x00);
     
	wr_cmd8(0xED);                     
	wr_data8(0x64);
	wr_data8(0x03);
	wr_data8(0x12);
	wr_data8(0x81);
     
	wr_cmd8(0xF7);  // PUMP_RATIO_CONTROL                   
	wr_data8(0x20);
     
	wr_cmd8(0xC0);                     // POWER_CONTROL_1
	wr_data8(0x23);  // AN 21, was 26
     
	wr_cmd8(0xC1);                     // POWER_CONTROL_2
	wr_data8(0x10);  // AN 11, was 11
     
	wr_cmd8(0xC5);                     // VCOM_CONTROL_1
	wr_data8(0x3E);  // AN 3F, was 35
	wr_data8(0x28);  // AN 3C, was 3E
     
	wr_cmd8(0xC7);                     // VCOM_CONTROL_2
	wr_data8(0x86);  // AN A7, was BE
     
     
     
	wr_cmd8(0xB1);                     // Frame Rate
	wr_data8(0x00);
	wr_data8(0x18);  // AN 1B, was 1B  1B=70hz             
     
	wr_cmd8(0xB6);                       // display function control, INTERESTING
	wr_data8(0x08);  // AN 0A, was 0A
	wr_data8(0x82);  // AN A2
	wr_data8(0x27);  // AN not present
	//   wr_data8(0x00);  // was present
     
	wr_cmd8(0xF2);                     // Gamma Function Disable
	wr_data8(0x00);  // AN 00, was 08
     
	wr_cmd8(0x26);                     
	wr_data8(0x01);                 // gamma set for curve 01/2/04/08
     
	wr_cmd8(0xE0);                     // positive gamma correction
	wr_data8(0x0F); 
	wr_data8(0x31); 
	wr_data8(0x2B); 
	wr_data8(0x0C); 
	wr_data8(0x0E); 
	wr_data8(0x08); 
	wr_data8(0x4E); 
	wr_data8(0xF1); 
	wr_data8(0x37); 
	wr_data8(0x07); 
	wr_data8(0x10); 
	wr_data8(0x03); 
	wr_data8(0x0E);
	wr_data8(0x09); 
	wr_data8(0x00);
     
	wr_cmd8(0xE1);                     // negativ gamma correction
	wr_data8(0x00); 
	wr_data8(0x0E); 
	wr_data8(0x14); 
	wr_data8(0x03); 
	wr_data8(0x11); 
	wr_data8(0x07); 
	wr_data8(0x31); 
	wr_data8(0xC1); 
	wr_data8(0x48); 
	wr_data8(0x08); 
	wr_data8(0x0F); 
	wr_data8(0x0C); 
	wr_data8(0x31);
	wr_data8(0x36); 
	wr_data8(0x0F);
     
	//wr_cmd8(0x34);                     // tearing effect off
     
	//wr_cmd8(0x35);                     // tearing effect on
      
	//   wr_cmd8(0xB7);                       // ENTRY_MODE_SET
	//   wr_data8(0x07);
  
	wr_cmd8(0x36);      // MEMORY_ACCESS_CONTROL (orientation stuff)
	wr_data8(0x48);
     
	wr_cmd8(0x3A);      // COLMOD_PIXEL_FORMAT_SET
	wr_data8(0x55);     // 16 bit pixel 

	wr_cmd8(0x13); // Normal Displaymode
    
	wr_cmd8(0x11);                     // sleep out
	HAL_Delay(150); 
     
	wr_cmd8(0x29);                     // display on
	HAL_Delay(150); 
}

#else

#error  no LCD controler defined

#endif
