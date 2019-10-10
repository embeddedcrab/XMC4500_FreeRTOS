/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		LED Task Class
* Filename:		led_task.hpp
* Author:		Hemant Sharma
* Origin Date:	01/19/2019
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	led_task.hpp
 *  @brief:	This file contains Led class for tasks
 */
#ifndef LED_TASK_HPP_
#define LED_TASK_HPP_

/******************************************************************************
* Includes
*******************************************************************************/
/* Include FreeRTOS Headers */
#include <FreeRTOS.h>
#include <task.h>

/* Include type headers */
#include <app_types.h>

/* Include class headers */
#include <dri_gpio.h>


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/


/******************************************************************************
* Typedefs
*******************************************************************************/


/******************************************************************************
* Variables
*******************************************************************************/



/******************************************************************************
* Function Prototypes
*******************************************************************************/


/******************************************************************************
 *
 * @brief	Class for LED Task
 *
 ******************************************************************************/

/* Define a class for LED task */
class LedTask_
{
public:
	/* Constructor */
	LedTask_( XMC_GPIO_PORT_t * port, uint8_t pin, TaskCreationParams *param )
	{
		xLedPort = port;
		xLedPin = pin;
		xLedTaskParams.p_name = param->p_name;
		xLedTaskParams.priority = param->priority;
		xLedTaskParams.stackDepth = param->stackDepth;
	}

	/* Destructor for Led task class */
	~LedTask_()
	{
		;/* Do Nothing for now
		or Free Dynamic Allocated Memory (if any) */
		vTaskDelete( xHandle );
	}

	/**
	 * @function	xvinit
	 *
	 * @brief		Task Initialization Function for LEDTask__ Class
	 *
	 * @param[in]	NA
	 *
	 * @param[out]	NA
	 *
	 * @return  	NA
	 *
	 * \par<b>Description:</b><br>
	 * 				This function will create task and pass the control to
	 * 				task entry
	 *
	 * <i>Imp Note:</i>
	 *
	 */
	void xvinit( void );

private:
	/* Port Info */
	volatile XMC_GPIO_PORT_t * xLedPort;
	uint8_t xLedPin;

	/* Task Info */
	TaskCreationParams xLedTaskParams;
	TaskHandle_t xHandle;

	/* Will work as a linker to the actual task function */
	static void xsvTaskEntryPoint( void *params )
	{
		((LedTask_ *) params)->xvTaskEntry(params);
	}

	/* This function contains the actual body of task */
	void xvTaskEntry( void *pvParams );
};


#endif /* LED_TASK_HPP_ */

/********************************** End of File *******************************/
