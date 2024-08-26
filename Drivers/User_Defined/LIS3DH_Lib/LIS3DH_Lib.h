/*
 * LIS3DH_Lib.h
 *
 *  Created on: Aug 22, 2024
 *      Author: Ayushman
 */

#ifndef USER_DEFINED_LIS3DH_LIB_LIS3DH_LIB_H_
#define USER_DEFINED_LIS3DH_LIB_LIS3DH_LIB_H_

/*------------------------------------Library Includes-------------------------------*/
#include<stdint.h>

/*------------------------------------LIS3DSH Registers-------------------------------*/

#define	OUT_T  			0x0C 		// Temperature output
#define	INFO1 			0x0D  		//Information register 1
#define	INFO2 			0x0E 		//Information register 2
#define	WHO_AM_I		0x0F  		//Who I am ID
#define	OFF_X  			0x10  		//X-axis offset correction
#define	OFF_Y  			0x11 		//Y-axis offset correction
#define	OFF_Z  			0x12 		//Z-axis offset correction
#define	CS_X 	 		0x13 		//Constant shift X
#define	CS_Y	 		0x14 		//Constant shift Y
#define	CS_Z	 		0x15 		//Constant shift Z
#define	LC_L			0x16		//Long counter registers
#define	LC_H			0x17		//Long counter registers
#define	STAT			0x18		//Interrupt synchronization
#define	PEAK1			0x19 		//Peak value
#define	PEAK2			0x1A		//Peak value
#define	VFC_1			0x1B		//Vector filter coefficient 1
#define	VFC_2			0x1C		//Vector filter coefficient 2
#define	VFC_3			0x1D		//Vector filter coefficient 3
#define	VFC_4			0x1E		//Vector filter coefficient 4
#define	THRS3			0x1F		//Threshold value 3
#define	CTRL_REG4		0x20		//Control register
#define	CTRL_REG1		0x21 		//SM1 control register
#define	CTRL_REG2		0x22 		//SM2 control register
#define	CTRL_REG3		0x23 		//Control registers
#define	CTRL_REG5		0x24 		//Control registers
#define	CTRL_REG6		0x25 		//Control registers
#define	STATUS			0x27		//Status data register
#define	OUT_X_L  		0x28 		//Output registers
#define	OUT_X_H  		0x29 		//Output registers
#define	OUT_Y_L 		0x2A		//Output registers
#define	OUT_Y_H			0x2B 		//Output registers
#define	OUT_Z_L 		0x2C		//Output registers
#define	OUT_Z_H			0x2D		//Output registers
#define	FIFO_CTRL  		0x2E		//FIFO registers
#define	FIFO_SRC  		0x2F		//FIFO registers
#define	ST1_X  			0x40		//SM1 code register			add:0x40-4F
#define	TIM4_1			0x50 		//SM1 general timer
#define	TIM3_1			0x51		//SM1 general timer
#define	TIM2_1			0x52		//SM1 general timer			add:0x52-53
#define	TIM1_1			0x54		//SM1 general timer			add:0x54-55
#define	THRS2_1			0x56		//SM1 threshold value 1
#define	THRS1_1			0x57		//SM1 threshold value 2
#define	MASK1_B			0x59		//SM1 axis and sign mask
#define	MASK1_A			0x5A		//SM1 axis and sign mask
#define	SETT1			0x5B		//SM1 detection settings
#define	PR1  			0x5C 		//Program-reset pointer
#define	TC1  			0x5D 		//Timer counter				add:0x5D-5E
#define	OUTS1  			0x5F 		//Main set flag
#define	ST2_X			0x60 		//SM2 code register			add:0x60-6F
#define	TIM4_2 			0x70		//SM2 general timer
#define	TIM3_2			0x71
#define	TIM2_2			0x72		//0x72-73
#define	TIM1_2			0x74		//0x74-75
#define	THRS2_2			0x76		//SM2 threshold value 1
#define	THRS1_2			0x77		//SM2 threshold value 2
#define	DES2  			0x78  		//Decimation factor
#define	MASK2_B  		0x79 		//SM2 axis and sign mask
#define	MASK2_A  		0x7A 		//SM2 axis and sign mask
#define	SETT2  			0x7B 		//SM2 detection settings
#define	PR2  			0x7C 		//Program-reset pointer
#define	TC2  			0x7D 		//Timer counter				add:0x7D-7E
#define	OUTS2	 		0x7F 		//Main set flag

/*------------------------------------Sensor Calibration Values-------------------------------*/
#define LIS3DSH_SENSITIVITY_0_06G            0.06  /* 0.06 mg/digit*/
#define LIS3DSH_SENSITIVITY_0_12G            0.12  /* 0.12 mg/digit*/
#define LIS3DSH_SENSITIVITY_0_18G            0.18  /* 0.18 mg/digit*/
#define LIS3DSH_SENSITIVITY_0_24G            0.24  /* 0.24 mg/digit*/
#define LIS3DSH_SENSITIVITY_0_73G            0.73  /* 0.73 mg/digit*/

#define LIS3DSH_FULLSCALE_2                  ((uint8_t)0x00)  /* 2 g  */
#define LIS3DSH_FULLSCALE_4                  ((uint8_t)0x08)  /* 4 g  */
#define LIS3DSH_FULLSCALE_6                  ((uint8_t)0x10)  /* 6 g  */
#define LIS3DSH_FULLSCALE_8                  ((uint8_t)0x18)  /* 8 g  */
#define LIS3DSH_FULLSCALE_16                 ((uint8_t)0x20)  /* 16 g */
#define LIS3DSH__FULLSCALE_SELECTION         ((uint8_t)0x38)

/*------------------------------------Function Prototypes-------------------------------*/

uint8_t readRegister(uint8_t *outputPointer, uint8_t offset);
uint8_t readRegisterRegion(uint8_t *outputPointer, uint8_t offset,
		uint8_t length);
uint8_t readRegisterInt16(int16_t *outputPointer, uint8_t offset);
uint8_t writeRegister(uint8_t offset, uint8_t dataToWrite);

uint8_t Check_ID(void);

uint8_t LIS3DSH_Init(void);
void LIS3DSH_ReadACC(int16_t* buffer);

void DropLed(int16_t* buffer);

//Returns the raw bits from the sensor cast as 16-bit signed integers
//int16_t readRawAccelX(void);
//int16_t readRawAccelY(void);
//int16_t readRawAccelZ(void);

//Returns the values as floats.  Inside, this calls readRaw___();
//float readFloatAccelX(void);
//float readFloatAccelY(void);
//float readFloatAccelZ(void);

//FIFO stuff
//void fifoBegin(void);
//void fifoClear(void);
//uint8_t fifoGetStatus(void);
//void fifoStartRec();
//void fifoEnd(void);

//float calcAccel(int16_t);

#endif /* USER_DEFINED_LIS3DH_LIB_LIS3DH_LIB_H_ */
