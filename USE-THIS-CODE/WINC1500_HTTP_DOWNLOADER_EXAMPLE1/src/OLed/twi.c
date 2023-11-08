// twi.c

#include <stdint.h>
#include "twi.h"
#include <i2c_master.h>

struct i2c_master_module i2c_master_instance;

void TWI_Init(void) {
	struct i2c_master_config config_i2c_master;
	i2c_master_get_config_defaults(&config_i2c_master);

	// Adjust the baud rate and buffer timeout as necessary
	config_i2c_master.buffer_timeout = 10000;
	config_i2c_master.baud_rate = I2C_MASTER_BAUD_RATE_400KHZ;

	// Pinmux setting for SDA/SCL - adjust to your board's specific pinout
	config_i2c_master.pinmux_pad0 = PINMUX_PA08C_SERCOM0_PAD0;
	config_i2c_master.pinmux_pad1 = PINMUX_PA09C_SERCOM0_PAD1;

	// Initialize and enable the I2C master module
	i2c_master_init(&i2c_master_instance, SERCOM0, &config_i2c_master);
	i2c_master_enable(&i2c_master_instance);
}

enum status_code TWI_MT_Start(uint8_t address) {
	// This function now expects the address as a parameter
	enum status_code status;

	// Create and write packet for I2C master write
	struct i2c_master_packet packet = {
		.address     = address,
		.data_length = 0,
		.data        = NULL,
	};
	// Start with the write request, without sending a stop condition
	status = i2c_master_write_packet_wait_no_stop(&i2c_master_instance, &packet);
	
	return status;
}

enum status_code TWI_MT_Send_SLAW(uint8_t slaw) {
	return TWI_MT_Start(slaw);
}

enum status_code TWI_MT_Send_Data(uint8_t data) {
	enum status_code status;
	uint8_t write_data = data;

	struct i2c_master_packet packet = {
		.address     = 0, // Address should be set previously
		.data_length = 1,
		.data        = &write_data,
	};

	// Write data to slave, expecting a stop condition
	status = i2c_master_write_packet_wait(&i2c_master_instance, &packet);

	return status;
}

void TWI_Stop(void) {
	// Send a stop condition
	i2c_master_send_stop(&i2c_master_instance);
}
