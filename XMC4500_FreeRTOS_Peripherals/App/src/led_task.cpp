/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		LED Flasher API Source
* Filename:		led_task.cpp
* Author:		HS
* Origin Date:	03/04/2020
* Version:		1.0.0
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	led_task.cpp
 *  @brief:	This source file contains API function definitions for LED Flasher
 */


/******************************************************************************
* Includes
*******************************************************************************/

/* Include class headers */
#include <led_task.hpp>

/* Include Required headers */
#include <dri_scu_extern.h>
#include <dri_uart_extern.h>
#include <dri_ccu_extern.h>
#include <dri_vadc_extern.h>
#include <dri_can_extern.h>

/* Include Application Headers */
#include <logger.h>

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

/* Declare static data member of class
 *
 * Note: Tell linker to take variable from this source file
 * */



/******************************************************************************
* Function Definitions
*******************************************************************************/

/******* Public Member function for LED_Task__ class *******/


/**
 * @function
 *
 * @brief		LED Task iniitalization function
 *
 * <i>Imp Note:</i>
 */
void LedTask__ :: xvinit( void )
{
	/* Return Status of Task */
	BaseType_t xReturned = pdFAIL;

	/* Create task */
	xReturned = xTaskCreate( LedTask__::xsvTaskEntryPoint, xLedTaskParams.p_name,
			xLedTaskParams.stackDepth, this, xLedTaskParams.priority, &xHandle );

	/* Delete task if not created successfully */
	if( xReturned != pdPASS )
	{
		vTaskDelete( xHandle );

		/* Halt if LED Flasher task is not started */
		for( ; ; );
	}
	else
	{
		/* Can do some initial processing if needed */
	}
}


/**
 * @function
 *
 * @brief		LED Task Entry function
 *
 * <i>Imp Note:</i>
 * 				Example taken from FreeRTOS-Plus TCP demo
 */
void LedTask__ :: xvTaskEntry( void *pvParams )
{
	/* Not using */
	(void)pvParams;

	/* Local Variables */
    TickType_t xLastWakeTime = 0;
    const TickType_t xFrequency = 500;
	/* CAN Bus Data */
    tStCAN_DataBytes can_data_l;
    can_data_l.data_qword = 0;

	gSystemState = MASTER_APP_STATE_ACTIVE;
	ITM_printf( (void *)"System State is: ACTIVE", sizeof("System State is: ACTIVE") );

    /**-- Demo for Preipherals --**/

	/* Send data to UART Channel */
	logger << "LED Task has started\r\n" << logger.endl;
	logger << "Starting Peripherals Now\r\n" << logger.endl;
	UART_transmit( &UART_Channel_0, (const unsigned char *)"Hello Embedded World\r\n",
					sizeof("Hello Embedded World\r\n") );

	/* Start ADC Conversion on Group 0 channels */
	VADC_background_scan_start_conversion( GLOBAL_VADC );

    /* Start Capture on CCU40_0 and CCU40_1 */
	CCU4_channel_timer_control( CCU40_Channel0_Handle.p_config->p_slice_context, 1 );
	CCU4_channel_timer_control( CCU40_Channel1_Handle.p_config->p_slice_context, 1 );
	/* Start PWM generation on CCU40_3 and CCU42_0 Channel */
	CCU4_channel_timer_control( CCU40_Channel3_Handle.p_config->p_slice_context, 1 );
	CCU4_channel_timer_control( CCU42_Channel0_Handle.p_config->p_slice_context, 1 );

	/* Start PWM generation on CCU80 Module Channel 0,1 and 2 */
	CCU8_channel_timer_control( CCU80_Channel0_Handle.p_config->p_slice_context, 1 );
	CCU8_channel_timer_control( CCU80_Channel2_Handle.p_config->p_slice_context, 1 );

	CAN_node_transmit( &CAN1, 1, &can_data_l, 2 );
	can_data_l.data_word[0] = VADC_Group0_Channels[0];

    /* Initialize the xLastWakeTime variable with the current time. */
    xLastWakeTime = xTaskGetTickCount();

    /* Initialize SCU interrupt */
    SCU_interrupt_init();

    /* Task execution entry */
    for( ; ; )
    {
		GPIO__::fp_toggle( (XMC_GPIO_PORT_t *)xLedPort, xLedPin );
		/* Service Watchdog */
		if( XMC_WDT_GetCounter() > SCU.p_module_config->p_wdt_config->window_lower_bound )
		{
			XMC_WDT_Service();
		}
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}

	/* Should never reach here, if so the delete the task and free memory */
	vTaskDelete( NULL );
}


/********************************** End of File *******************************/
