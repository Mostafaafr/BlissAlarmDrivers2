// oled.c

#include "oled.h"
#include "twi.h" 


// Function to send an OLED command
void OLED_SendCommand(uint8_t command) {
	uint8_t commandBuffer[2] = {0x00, command}; // OLED command always prefixed with 0x00

	// Start TWI communication
	TWI_MT_Start(OLED_ADDRESS);
	
	// Send command sequence
	TWI_MT_Send_Data(commandBuffer[0]); // Control byte
	TWI_MT_Send_Data(commandBuffer[1]); // Actual command byte
	
	// Stop TWI communication
	TWI_Stop();
}

void OLED_Init(void) {
	// Initialize TWI/I2C interface
	TWI_Init();

	// Turn off the OLED display
	OLED_SendCommand(OLED_CMD_DISPLAY_OFF);

	// Set display clock divide ratio/oscillator frequency
	OLED_SendCommand(OLED_CMD_SET_DISPLAY_CLOCK_DIV_RATIO);
	OLED_SendCommand(0x80);

	// Set multiplex ratio
	OLED_SendCommand(OLED_CMD_SET_MULTIPLEX_RATIO);
	OLED_SendCommand(0x3F); // 0x3F for 128x64

	// Set display offset
	OLED_SendCommand(OLED_CMD_SET_DISPLAY_OFFSET);
	OLED_SendCommand(0x00); // no offset

	// Set display start line
	OLED_SendCommand(OLED_CMD_SET_DISPLAY_START_LINE | 0x00); // Start at line 0

	// Charge pump setting
	OLED_SendCommand(OLED_CMD_SET_CHARGE_PUMP);
	OLED_SendCommand(0x14); // Enable charge pump

	// Set memory addressing mode
	OLED_SendCommand(OLED_CMD_SET_MEMORY_ADDRESSING_MODE);
	OLED_SendCommand(0x00); // Horizontal addressing mode

	// Set segment re-map
	OLED_SendCommand(OLED_CMD_SET_SEGMENT_REMAP | 0x01);

	// Set COM output scan direction
	OLED_SendCommand(OLED_CMD_SET_COM_OUTPUT_SCAN_DIRECTION | 0x08);

	// Set COM pins hardware configuration
	OLED_SendCommand(OLED_CMD_SET_COM_PINS);
	OLED_SendCommand(0x12);

	// Set contrast control
	OLED_SendCommand(OLED_CMD_SET_CONTRAST_CONTROL);
	OLED_SendCommand(0xCF);

	// Set precharge period
	OLED_SendCommand(OLED_CMD_SET_PRECHARGE_PERIOD);
	OLED_SendCommand(0xF1);

	// Set VCOMH deselect level
	OLED_SendCommand(OLED_CMD_SET_VCOM_DESELECT);
	OLED_SendCommand(0x40);

	// Entire display ON, resume to RAM content display
	OLED_SendCommand(OLED_CMD_DISPLAY_ALL_ON_RESUME);

	// Set normal display
	OLED_SendCommand(OLED_CMD_NORMAL_DISPLAY);

	// Turn on the OLED display
	OLED_SendCommand(OLED_CMD_DISPLAY_ON);
}

void OLED_DisplayOn(void) {
	// Turn on the OLED display
	OLED_SendCommand(OLED_CMD_DISPLAY_ON);
}

void OLED_DisplayOff(void) {
	// Turn off the OLED display
	OLED_SendCommand(OLED_CMD_DISPLAY_OFF);
}

void OLED_SendData(uint8_t *data, uint16_t length) {
    // Start TWI communication
    TWI_MT_Start(OLED_ADDRESS << 1); // Left shift for write operation

    // Control byte for data stream
    TWI_MT_Send_Data(0x40); // Indicate that we're sending data

    // Send data
    for (uint16_t i = 0; i < length; i++) {
        TWI_MT_Send_Data(data[i]);
    }

    // Stop TWI communication
    TWI_Stop();
}

// Function to turn the whole screen white
void OLED_FillScreenWhite(void) {
    // A single page is 8 pixels high and as wide as the screen
    const uint8_t screenWidth = 128; // Assuming a 128x64 display
    const uint8_t screenHeightPages = 8; // 64 pixels / 8 pixels per page
    uint8_t data[screenWidth]; // Data buffer to fill a single page

    // Fill the data buffer with 0xFF to turn every pixel on the page white
    for (uint8_t i = 0; i < screenWidth; i++) {
        data[i] = 0xFF;
    }

    // Write to each page to fill the entire screen
    for (uint8_t page = 0; page < screenHeightPages; page++) {
        // Set the page address
        OLED_SendCommand(0xB0 | page); // 0xB0 to 0xB7 for pages 0 to 7
        // Set the column address to 0
        OLED_SendCommand(0x00); // Lower column start address
        OLED_SendCommand(0x10); // Higher column start address

        // Write the data to fill the page
        OLED_SendData(data, screenWidth);
    }
}
