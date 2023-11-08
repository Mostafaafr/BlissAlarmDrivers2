// oled.h

#ifndef OLED_H
#define OLED_H

#include <stdint.h>

#define OLED_ADDRESS 0x3D // The I2C address for the OLED display

// Fundamental Commands
#define OLED_CMD_SET_CONTRAST_CONTROL 0x81
#define OLED_CMD_DISPLAY_ALL_ON_RESUME 0xA4
#define OLED_CMD_DISPLAY_ALL_ON 0xA5
#define OLED_CMD_NORMAL_DISPLAY 0xA6
#define OLED_CMD_INVERT_DISPLAY 0xA7
#define OLED_CMD_DISPLAY_OFF 0xAE
#define OLED_CMD_DISPLAY_ON 0xAF

// Addressing Setting Commands
#define OLED_CMD_SET_MEMORY_ADDRESSING_MODE 0x20
#define OLED_CMD_SET_COLUMN_ADDRESS 0x21
#define OLED_CMD_SET_PAGE_ADDRESS 0x22

// Hardware Configuration Commands
#define OLED_CMD_SET_DISPLAY_START_LINE 0x40
#define OLED_CMD_SET_SEGMENT_REMAP 0xA0
#define OLED_CMD_SET_MULTIPLEX_RATIO 0xA8
#define OLED_CMD_SET_COM_OUTPUT_SCAN_DIRECTION 0xC0
#define OLED_CMD_SET_DISPLAY_OFFSET 0xD3
#define OLED_CMD_SET_COM_PINS 0xDA
#define OLED_CMD_SET_VCOM_DESELECT 0xDB

// Timing & Driving Scheme Setting Commands
#define OLED_CMD_SET_DISPLAY_CLOCK_DIV_RATIO 0xD5
#define OLED_CMD_SET_PRECHARGE_PERIOD 0xD9
#define OLED_CMD_SET_VCOMH_DESELECT_LEVEL 0xDB
#define OLED_CMD_NOP 0xE3

//Charge Pump Command
#define OLED_CMD_SET_CHARGE_PUMP 0x8D

//Function prototypes
void OLED_Init(void);
void OLED_SendCommand(uint8_t command);
void OLED_DisplayOn(void);
void OLED_DisplayOff(void);


#endif