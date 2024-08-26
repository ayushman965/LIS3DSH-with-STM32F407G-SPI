/*
 * LIS3DH_Lib.c
 *
 *  Created on: Aug 22, 2024
 *      Author: Ayushman
 */

/*------------------------------------Library Includes-------------------------------*/
#include"main.h"
#include"LIS3DH_Lib.h"
#include<stdio.h>

/*------------------------------------Extern Variables-------------------------------*/
extern SPI_HandleTypeDef hspi1;

/*------------------------------------Function Definitions-------------------------------*/

uint8_t readRegister(uint8_t *outputPointer, uint8_t offset) {

	uint8_t TxData = (offset | 0x80);
	uint8_t RxData = 0;
	uint8_t error = 0x00;

	HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

	error = HAL_SPI_TransmitReceive(&hspi1, &TxData, &RxData, 1, 10);

	TxData = 0x00;

	error |= HAL_SPI_TransmitReceive(&hspi1, &TxData, &RxData, 1, 10);

	HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_SET);

	*outputPointer = RxData;

	return error;

}

uint8_t readRegisterInt16(int16_t *outputPointer, uint8_t offset) {

	uint8_t myBuffer[2];
	uint8_t returnError = readRegisterRegion(myBuffer, offset, 2); //Does memory transfer
	int16_t output = (int16_t) (myBuffer[0]) | ((int16_t) (myBuffer[1]) << 8);
	*outputPointer = output;
	return returnError;
}

uint8_t readRegisterRegion(uint8_t *outputPointer, uint8_t offset,
		uint8_t length) {

	uint8_t i = 0, TxData = 0, RxData = 0, tempFFCounter = 0,
			returnError = 0x00;

	// take the chip select low to select the device:
	HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

	//Ored with "read request" bit
	TxData = (offset | 0x80);

	// send the device the register you want to read:
	returnError = HAL_SPI_TransmitReceive(&hspi1, &TxData, &RxData, 1, 10);

	TxData = 0x00;

	while (i < length) // slave may send less than requested
	{
		returnError |= HAL_SPI_TransmitReceive(&hspi1, &TxData, &RxData, 1, 10); //receive a byte as character

		if (RxData == 0xFF) {
			//May have problem
			tempFFCounter++;
		}
		*outputPointer = RxData;
		outputPointer++;
		i++;
	}

	if (tempFFCounter == i) {
		returnError |= 0x01;	//Ok, we've recieved all ones, report
	}

	// take the chip select high to de-select:
	HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_SET);

	return returnError;
}

uint8_t writeRegister(uint8_t offset, uint8_t dataToWrite) {

	uint8_t RxData = 0x00;
	uint8_t error = HAL_OK;

	// take the chip select low to select the device:
	HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

	// send the device the register you want to read:
	error = HAL_SPI_TransmitReceive(&hspi1, &offset, &RxData, 1, 10);

	error |= HAL_SPI_TransmitReceive(&hspi1, &dataToWrite, &RxData, 1, 10);

	// take the chip select high to de-select:
	HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_SET);

	return error;
}

uint8_t Check_ID(void) {
	uint8_t returnError = 0x00;

	HAL_Delay(10);

	//Check the ID register to determine if the operation was a success.

	uint8_t Read_Data = 0x00;

	if (readRegister(&Read_Data, WHO_AM_I) != HAL_OK) {
		printf("\nSPI Failed!");
		Error_Handler();
	}

	if (readRegister(&Read_Data, WHO_AM_I) != HAL_OK) {
		printf("\nSPI Failed!");
		Error_Handler();
	}

	if (Read_Data != 0x3F) {

		printf("\nDevice ID not received:(\nWHO_AM_I: 0x%X", Read_Data);
		returnError = 0x01;
	} else {
		printf("\nDevice ID successfully received:)\nWHO_AM_I: 0x%X",
				Read_Data);
	}

	return returnError;

}

uint8_t LIS3DSH_Init(void) {

	uint8_t error = 0x00, ctrl = 0x67;//ODR: 100Hz, BDU:0(continuous update), Zen:1, Yen:1, Xen:1

	/* Write value to MEMS CTRL_REG4 register */
	error = writeRegister(CTRL_REG4, ctrl);

	/* Configure MEMS: full scale and self test */
	//ctrl = 0x20;
	ctrl = 0x08;
	/* Write value to MEMS CTRL_REG5 register */
	error |= writeRegister(CTRL_REG5, ctrl);

	return error;
}

void LIS3DSH_ReadACC(int16_t* buffer) {

	uint8_t registerValue = 0;
	float sensitivity;

	readRegister(&registerValue, STATUS); //read STATUS to check new data updated in X,Y & Z registers

	if ((registerValue & 0x08) == 0x08)
	{
		readRegisterInt16(buffer, OUT_X_L);
		readRegisterInt16(buffer+1, OUT_Y_L);
		readRegisterInt16(buffer+2, OUT_Z_L);

		//printf("\nAccel_X:%d\tAccel_Y:%d\tAccel_Z:%d", buffer[0], buffer[1], buffer[2]);

		readRegister(&registerValue, CTRL_REG5);

		switch(registerValue & LIS3DSH__FULLSCALE_SELECTION)
		{
			/* FS bit = 000 ==> Sensitivity typical value = 0.06milligals/digit */
			case LIS3DSH_FULLSCALE_2:
			sensitivity = LIS3DSH_SENSITIVITY_0_06G;
			break;

			/* FS bit = 001 ==> Sensitivity typical value = 0.12milligals/digit */
			case LIS3DSH_FULLSCALE_4:
			sensitivity = LIS3DSH_SENSITIVITY_0_12G;
			break;

			/* FS bit = 010 ==> Sensitivity typical value = 0.18milligals/digit */
			case LIS3DSH_FULLSCALE_6:
			sensitivity = LIS3DSH_SENSITIVITY_0_18G;
			break;

			/* FS bit = 011 ==> Sensitivity typical value = 0.24milligals/digit */
			case LIS3DSH_FULLSCALE_8:
			sensitivity = LIS3DSH_SENSITIVITY_0_24G;
			break;

			/* FS bit = 100 ==> Sensitivity typical value = 0.73milligals/digit */
			case LIS3DSH_FULLSCALE_16:
			sensitivity = LIS3DSH_SENSITIVITY_0_73G;
			break;

			default:
			break;
		}

		/* Obtain the mg value for the three axis */
		buffer[0] = (int16_t)(buffer[0] * sensitivity);
		buffer[1] = (int16_t)(buffer[1] * sensitivity);
		buffer[2] = (int16_t)(buffer[2] * sensitivity);

		printf("\nAccel_X:%d\tAccel_Y:%d\tAccel_Z:%d", buffer[0], buffer[1], buffer[2]);
	}
}

void DropLed(int16_t* buffer)
{
	if(buffer[0] > 800 && buffer[0] < 1200 &&
	   buffer[1] > -500 && buffer[1] < 500 &&
	   buffer[2] > -500 && buffer[2] < 500)
	{
		HAL_GPIO_WritePin(GPIOD,LD5_Pin,GPIO_PIN_RESET);
		HAL_Delay(200);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOD,LD5_Pin,GPIO_PIN_SET);
		HAL_Delay(50);
	}

	if(buffer[0] > -500 && buffer[0] < 500 &&
	   buffer[1] > -1200 && buffer[1] < -800 &&
	   buffer[2] > -500 && buffer[2] < 500)
	{
		HAL_GPIO_WritePin(GPIOD,LD6_Pin,GPIO_PIN_RESET);
		HAL_Delay(200);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOD,LD6_Pin,GPIO_PIN_SET);
		HAL_Delay(50);
	}

	if(buffer[0] > -1200 && buffer[0] < -800 &&
	   buffer[1] > -500 && buffer[1] < 500 &&
	   buffer[2] > -500 && buffer[2] < 500)
	{
		HAL_GPIO_WritePin(GPIOD,LD4_Pin,GPIO_PIN_RESET);
		HAL_Delay(200);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOD,LD4_Pin,GPIO_PIN_SET);
		HAL_Delay(50);
	}

	if(buffer[0] > -500 && buffer[0] < 500 &&
	   buffer[1] > 900 && buffer[1] < 1300 &&
	   buffer[2] > -500 && buffer[2] < 500)
	{
		HAL_GPIO_WritePin(GPIOD,LD3_Pin,GPIO_PIN_RESET);
		HAL_Delay(200);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOD,LD3_Pin,GPIO_PIN_SET);
		HAL_Delay(50);
	}
}
