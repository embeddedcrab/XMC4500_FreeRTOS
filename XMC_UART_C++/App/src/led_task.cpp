/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		LED Task Class Source
* Filename:		led_task.cpp
* Author:		Hemant Sharma
* Origin Date:	01/19/2019
* Version:		1.0.0
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	led_task.cpp
 *  @brief:	This source file contains led task class source functions
 */


/******************************************************************************
* Includes
*******************************************************************************/
#include <led_task.hpp>
#include <dri_uart_extern.h>


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

/* Declare static data member
 *
 * Note: Tell linker to take variable from this source file
 * */


/******************************************************************************
* Function Definitions
*******************************************************************************/

/**
 * @function	xvinit
 *
 * @brief		Task Initialization Function
 *
 * <i>Imp Note:</i>
 *
 */
void LedTask_ :: xvinit( void )
{
	/* Return Status of Task */
	BaseType_t xReturned = pdFAIL;
	/* Initialize parameters */
	xHandle = NULL;

	/* Create task */
	xReturned = xTaskCreate( LedTask_::xsvTaskEntryPoint,
							xLedTaskParams.p_name, xLedTaskParams.stackDepth,
							this, xLedTaskParams.priority, &xHandle
							);

	/* Delete task if not created successfully */
	if( xReturned != pdPASS )
	{
		vTaskDelete( xHandle );
	}
	else
	{
		/* Can do some initial processing if needed */
	}
}


/**
 * @function	xvTaskEntry
 *
 * @brief		LED Task Entry function
 *
 * <i>Imp Note:</i>
 *
 */
void LedTask_ :: xvTaskEntry( void *pvParams )
{
	/* Not using */
	(void)pvParams;

	/* Local Variables */
	TickType_t xLastWakeTime = 0;
	const TickType_t xFrequency = 100;

	 /* Initialize the xLastWakeTime variable with the current time. */
	 xLastWakeTime = xTaskGetTickCount();

	 /* <i> Imp Note: </> This operations for UART will happen for every task creation
	  * 					using LedTask_ Class because objects are not local to task entry
	  */

	 /* Does not seem to work properly with Protocol interrupts,
	  * fills the FIFO but does not complete the transmission */
	 g_p_uart_obj[0]->transmit( (const unsigned char *)"Hello World\r\n", 13 );

	 /* No USB to TTL converter for testing!, triggering the RX interrupt
	  * and waiting for data then transmitting data on same channel.
	  *
	  * Tx and Rx pins have been shorted to work as Loopback mode explicitly!
	  */
	 unsigned char data_l[13] = {0};
	 g_p_uart_obj[0]->receive( data_l, 13 );
	 g_p_uart_obj[0]->transmit( (const unsigned char *)"Hello World\r\n", 13 );
	 /* Check data in data_l, should be "Hello World\r\n" */
	 __asm("NOP");
	 g_p_uart_obj[1]->transmit( (const unsigned char *)"Porld Pello\r\n", 13 );
	 g_p_uart_obj[2]->transmit( (const unsigned char *)"Torld Tello\r\n", 13 );

	 /* Task execution entry */
	for( ; ; )
	{
		GPIO__::fp_toggle( (XMC_GPIO_PORT_t *)xLedPort, xLedPin );
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
		GPIO__::fp_toggle( (XMC_GPIO_PORT_t *)xLedPort, xLedPin );
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}

	/* Should never reach here, if so the delete the task and free memory */
}

/********************************** End of File *******************************/
