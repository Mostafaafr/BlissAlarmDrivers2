// twi.h

#ifndef TWI_H
#define TWI_H

#include <stdint.h>
#include <i2c_master.h> 

// I2C Master module instance from the SAMW25 I2C driver library
extern struct i2c_master_module i2c_master_instance;

// Function prototypes for the I2C interface
void TWI_Init(void);
enum status_code TWI_MT_Start(uint8_t address);
enum status_code TWI_MT_Send_SLAW(uint8_t slaw);
enum status_code TWI_MT_Send_Data(uint8_t data);
enum status_code TWI_MR_Send_SLAR(uint8_t slar, uint8_t *data, uint16_t length);
void TWI_Stop(void);

#endif // TWI_H