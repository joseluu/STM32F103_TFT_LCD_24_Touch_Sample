#include "board_config.h"

#include "LCDConf_F103_24.h"
#include "stm32f1xx_hal.h"

/* compatibility macros */
#define wr_cmd8 LcdWriteReg8
#define wr_data8 LcdWriteData8
#define reg_write(cmd,data) {LcdWriteReg16(cmd);LcdWriteData16(data);}
#define LCD_WriteRegister(cmd,data) {LcdWriteReg16(cmd);LcdWriteData16(data);}

#ifdef ILI9320

void lcd_ctrl_initialize(void)
{

//	LCD_Delay(10000);					// Wait a bit
//	LCD_WriteRegister(0x0000,0x0001);
//	LCD_Delay(10000);
//	Set_Sync;
//	LCD_DeviceCode = LCD_ReadRegister(0x0000);
//	LCD_Delay(10);
//	Clr_Sync;

	LCD_WriteRegister(0x00, 0x8000);	
	LCD_WriteRegister(0x00, 0x0001);		// Start Oscillation
	LCD_WriteRegister(0x01, 0x0100);		// Driver output control (makes it scan top left to bottom right, odd for top half, even for bottom)
	LCD_WriteRegister(0x02, 0x0700);		// Line inversion on the LCD Driving Wave Control
	LCD_WriteRegister(0x03, 0x1030);		// Entry mode set(may need changing)(0x1018)
	LCD_WriteRegister(0x04, 0x0000);		// Resizing stuff(not needed by me)

	LCD_WriteRegister(0x08, 0x0202);		// (Display control 2) Set 2 lines for for both front and back porch(minimum number, helps VSYNC)
	LCD_WriteRegister(0x09, 0x0000);		// (Display control 3) Sets 0 frame scan cycle(not needed for this communication) and normal scan
	LCD_WriteRegister(0x0a, 0x0000);		// Not necessary(FMARK signal stuff)

	//possible probleme si 8 bits ?????

	//		LCD_WriteRegister(0x0c,(1<<0));		// 16-bit RGB interface(1 transfer/pixel), using internal system clock and system interface (0x0001)
	LCD_WriteRegister(0x0a, 0x0000);			// 16-bit RGB interface
			
	LCD_WriteRegister(0x0d, 0x0000);		// Frame Marker at position 0(starts outputting frame right away
	LCD_WriteRegister(0x0f, 0x0000);		// Data input on rising edge of DOTCLK, data written when ENABLE=0,HSPL/VSPL(H/VSYNC pins) Low polarit = active

	//		LCD_WriteRegister(0x07,0x0101);		// (Display control 1) Set display to operate, VCOM output to GND
	LCD_WriteRegister(0x10, 0x0000);	
	//		LCD_WriteRegister(0x10,(1 << 12) | (0 << 8) | (1 << 7) | (1 << 6) | (0 << 4));		// (Power control 1) Enable power supply(0x10c0)

	LCD_WriteRegister(0x11, 0x0007);		// (Power control 2) Ref. voltage(VciOUT) = Vci1, operating frequency = Fosc in circuit 1 and Fosc/16 in circuit 2

	LCD_WriteRegister(0x12, 0x0000);	
	//	LCD_WriteRegister(0x12,(1 << 8) | (1 << 4) | (0 << 0));		// (Power control 3) Enable VGL output, use internal electric volume(VCM) to set VcomH(Vcom center voltage level(0x0110)

	LCD_WriteRegister(0x13, 0x0000);	
	//	LCD_WriteRegister(0x13,0x0b00);		// (Power control 4) VCOM Amplitude = VREG1OUT x 0.90
	HAL_Delay(50);
	HAL_Delay(50);
	HAL_Delay(50);
	HAL_Delay(50);								// 200ms
	LCD_WriteRegister(0x10, 0x17B0);
	LCD_WriteRegister(0x11, 0x0037);
	HAL_Delay(50);		
	LCD_WriteRegister(0x12, 0x013a);
	HAL_Delay(50);
	LCD_WriteRegister(0x13, 0x1600);
		
	LCD_WriteRegister(0x29, 0x000c);		// (Power control 7) VcomH voltage = VREG1OUT x .69
	HAL_Delay(50);
	LCD_WriteRegister(0x20, 0x0000);
	LCD_WriteRegister(0x21, 0x0000);

	LCD_WriteRegister(0x30, 0x0504);
	LCD_WriteRegister(0x31, 0x0703);
	LCD_WriteRegister(0x32, 0x0702);
	LCD_WriteRegister(0x35, 0x0101);
	LCD_WriteRegister(0x36, 0x0A1F);
	LCD_WriteRegister(0x37, 0x0504);
	LCD_WriteRegister(0x38, 0x0003);
	LCD_WriteRegister(0x39, 0x0706);
	LCD_WriteRegister(0x0C, 0x0707);
	LCD_WriteRegister(0x3D, 0x091F);

	/*
			LCD_WriteRegister(0x2b,(1 << 14) | (1 << 4));		// 90Hz frame rate, internal resistor. (maybe should be 0x0408)(0x0008)
			LCD_Delay(50000);
			// Horiz. and Vert. RAM Address Position. Set up for 320x240
			LCD_WriteRegister(0x50,0);			// X starts at 0
			LCD_Delay(50000);
			LCD_WriteRegister(0x51,239);		// X ends at 239
			LCD_Delay(50000);
			LCD_WriteRegister(0x52,0);			// Y starts at 0
			LCD_Delay(50000);
			LCD_WriteRegister(0x53,319);		// Y ends at 319
			LCD_Delay(50000);
			LCD_WriteRegister(0x60,0x2700);		// (Driver output control) Gate scans at 0, ends after 320 lines
			LCD_Delay(50000);
			LCD_WriteRegister(0x61,0x0001);		// (Driver output control) grayscale inversion
			LCD_Delay(50000);
			LCD_WriteRegister(0x6a,0x0000);		// (Vertical scroll control) not used
			LCD_Delay(50000);
			LCD_WriteRegister(0x80,0x0000);		// Display position for partial image 1
			LCD_Delay(50000);
			LCD_WriteRegister(0x81,0x0000);		// RAM address for start of partial image 1
			LCD_Delay(50000);
			LCD_WriteRegister(0x82,0x0000);		// RAM address for end of partial image 1
			LCD_Delay(50000);
			LCD_WriteRegister(0x83,0x0000);		// Display position for partial image 2
			LCD_Delay(50000);
			LCD_WriteRegister(0x84,0x0000);		// RAM address for start of partial image 2
			LCD_Delay(50000);
			LCD_WriteRegister(0x85,0x0000);		// RAM address for end of partial image 2
			LCD_Delay(50000);
			LCD_WriteRegister(0x90,(0 << 7) | (16 << 0));		// (Panel interface control 1) Sets clock number for internal clock
			LCD_Delay(50000);
			LCD_WriteRegister(0x92,0x0000);		// (Panel interface control 2) 0 Clocks of overlap when synced
			LCD_Delay(50000);
			LCD_WriteRegister(0x93,0x0001);		// (Panel interface control 3) 1 Clock output position when synced
			LCD_Delay(50000);
			LCD_WriteRegister(0x95,0x0110);		// (Panel interface control 4) Division ration of 1/4, 16 clocks per horizontal line
			LCD_Delay(50000);
			LCD_WriteRegister(0x97,(0 << 8));		// (Panel interface control 5) 0 Clock non-overlap
			LCD_Delay(50000);
			LCD_WriteRegister(0x98,0x0000);		// (Panel interface control 6) Source output position 0 clocks
			LCD_Delay(50000);
			LCD_WriteRegister(0x07,0x0173);		// (Display control 1) Set display to operate, base image display, normal display (maybe should be 0x0173)
			LCD_Delay(50000);
			LCD_Delay(5000);
			LCD_Clear(LCD_Black);
			LCD_Delay(50000);
			LCD_Delay(50000);
			LCD_Clear(LCD_Red);
			LCD_Delay(50000);
			LCD_Delay(50000);		
			}
			*/
											//  set GRAM area
	LCD_WriteRegister(0x50, 0x0000);
	LCD_WriteRegister(0x51, 0x00EF);
	LCD_WriteRegister(0x52, 0x0000);
	LCD_WriteRegister(0x53, 0x013F);
	LCD_WriteRegister(0x60, 0x2700);
	LCD_WriteRegister(0x61, 0x0001);
	LCD_WriteRegister(0x6A, 0x0000);		
		
					// partiazl display control
						
	LCD_WriteRegister(0x80, 0x0000);
	LCD_WriteRegister(0x81, 0x0000);
	LCD_WriteRegister(0x82, 0x0000);
	LCD_WriteRegister(0x83, 0x0000);
	LCD_WriteRegister(0x84, 0x0000);
	LCD_WriteRegister(0x85, 0x0000);
		
					//Panel control
	LCD_WriteRegister(0x90, 0x0010);
	LCD_WriteRegister(0x92, 0x0000);
	LCD_WriteRegister(0x93, 0x0003);
	LCD_WriteRegister(0x95, 0x0110);
	LCD_WriteRegister(0x97, 0x0000);
	LCD_WriteRegister(0x98, 0x0000);
	LCD_WriteRegister(0x07, 0x0173);		//262K color and display ON 
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
