![Proto Board](./IMG20240828220818.jpg)

# LIS3DSH with STM32F407G (SPI Interface)

This project demonstrates how to interface the LIS3DSH accelerometer with the STM32F407G microcontroller to capture acceleration data on the X, Y, and Z axes. It includes fun examples to explore the capabilities of the sensor.

## Project Overview
- **Development Board**: STM32F407G-DISC1
- **Sensor**: LIS3DSH (mounted on the STM32F407G-DISC1 dev kit)
- **Communication Protocol**: SPI (Serial Peripheral Interface)

## Features
- The LIS3DSH accelerometer can communicate via both I2C and SPI protocols, but SPI is used in this project.
- The project includes `LIS3DSH_Lib.h` and `LIS3DSH_Lib.c` files, which contain all the code necessary to interact with the LIS3DSH sensor.

## Tools and Libraries
- **STM32CubeMX**: Used to initialize the STM32F407G microcontroller.
- **HAL (Hardware Abstraction Layer) Libraries**: Provided by STMicroelectronics and used throughout the project for peripheral management.
