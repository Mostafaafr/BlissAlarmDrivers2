 /**************************************************************************//**
* @file      UiHandlerThread.c
* @brief     File that contains the task code and supporting code for the UI Thread for ESE516 Spring (Online) Edition
* @author    You! :)
* @date      2020-04-09 

******************************************************************************/


/******************************************************************************
* Includes
******************************************************************************/
#include <errno.h>
#include "asf.h"
#include "UiHandlerThread/UiHandlerThread.h"
#include "SeesawDriver/Seesaw.h"
#include "SerialConsole.h"
#include "main.h"

/******************************************************************************
* Defines
******************************************************************************/

/******************************************************************************
* Variables
******************************************************************************/
uiStateMachine_state uiState;
/******************************************************************************
* Forward Declarations
******************************************************************************/

/******************************************************************************
* Callback Functions
******************************************************************************/


/******************************************************************************
* Task Function
******************************************************************************/

/**************************************************************************//**
* @fn		void vUiHandlerTask( void *pvParameters )
* @brief	STUDENT TO FILL THIS
* @details 	student to fill this
                				
* @param[in]	Parameters passed when task is initialized. In this case we can ignore them!
* @return		Should not return! This is a task defining function.
* @note         
*****************************************************************************/
void vUiHandlerTask( void *pvParameters )
{
//Do initialization code here
SerialConsoleWriteString("UI Task Started!");
uiState = UI_STATE_HANDLE_BUTTONS;
uint8_t buttonBuffer[16];
uint8_t NUM_BUTTONS = 16;

//Here we start the loop for the UI State Machine
while(1)
{
	switch(uiState)
	{
		case(UI_STATE_HANDLE_BUTTONS):
		{
		//Do the handle buttons code here!
		/* NOTE:
		Do not call SeesawReadKeypad(uint8_t *buffer, uint8_t count) with the argument count being zero. 
		There seems to be a bug with ASF when this is called (i2c_master_read_packet_job).
		The following guard can be used:

		if(count != 0)		{
			SeesawReadKeypad(buffer, count);
		}
		
		*/
		char countStr[10];
		int count = SeesawGetKeypadCount();
		sprintf(countStr, "%u", NUM_BUTTONS); 
		// Convert count to string 
		SerialConsoleWriteString("Count: "); 
		SerialConsoleWriteString(countStr); 
		SerialConsoleWriteString("\r\n");
		
		for (int i = 0; i < NUM_BUTTONS; i++) {
			buttonBuffer[i] = 0;
		}
		
		 if (count != 0 && SeesawReadKeypad(buttonBuffer, count) == ERROR_NONE)
		 {
			 /*SeesawReadKeypad(buttonBuffer, count)*/;
			 // Iterate through the button buffer to control LEDs
			 for (uint8_t i = 0; i < NUM_BUTTONS; i++)
			 {
				uint8_t curr_button = NEO_TRELLIS_SEESAW_KEY((buttonBuffer[i] & 0b11111100) >> 2);
				uint8_t action = buttonBuffer[i] & 0b00000011;
				if (action == 0x03) {
					SeesawSetLed(curr_button,79,134,247);
					SeesawOrderLedUpdate();
				} else {
					SeesawSetLed(curr_button,0,0,0);
					SeesawOrderLedUpdate();
				}
// 				 uint8_t key = buttonBuffer[i];
//  
// 				 // Check if the highest bit is set, indicating a press event.
// 				 bool isPressed = (key & 0x80) != 0; 
// 				 key &= 0x0F; // Mask out the event information to get the key number.
// 
// 				 // Set LED color based on press state.
// 				 SeesawSetLed(key, isPressed ? 255, 0, 0 : 0, 0, 0); // Red color for pressed, no color for not pressed.
			 }
			 SeesawOrderLedUpdate();
		 }

		break;
		}

		case(UI_STATE_IGNORE_PRESSES):
		{
		//Ignore me for now
			break;
		}

		case(UI_STATE_SHOW_MOVES):
		{
		//Ignore me as well
			break;
		}

		default: //In case of unforseen error, it is always good to sent state machine to an initial state.
			uiState = UI_STATE_HANDLE_BUTTONS;
		break;
	}

	//After execution, you can put a thread to sleep for some time.
	vTaskDelay(50);
}



}




/******************************************************************************
* Functions
******************************************************************************/