/*
 * led_task.cpp
 *
 *  Created on: 19-Feb-2019
 *      Author: hp
 */

#include <led_task.hpp>


void LedTask_ :: xvInitializeGPIO( void ){
	/* Initialize LED port with led pin */
	XMC_GPIO_Init( (XMC_GPIO_PORT_t *)xLedPort, xLedPin, &xLedPortConfig);
}


/* Task Initialization Function */
void LedTask_ :: xvinit( void ){
	/* Return Status of Task */
	BaseType_t xReturned = pdFAIL;
	/* Initialize parameters */
	xHandle = NULL;

	/* Create task */
	xReturned = xTaskCreate( LedTask_::xsvTaskEntryPoint, LedTaskParams.name, LedTaskParams.stackDepth, this, LedTaskParams.priority, &xHandle );

	/* Delete task if not created successfully */
	if( xReturned != pdPASS ){
		vTaskDelete( xHandle );
	} else{
		/* Initialize GPIO */
		xvInitializeGPIO();
	}
}


/* LED Task Entry function */
void LedTask_ :: xvTaskEntry( void *pvParams ){

	/* Local Variables */
	TickType_t xLastWakeTime = 0;
	const TickType_t xFrequency = 500;

	(void)pvParams;

	 // Initialize the xLastWakeTime variable with the current time.
	 xLastWakeTime = xTaskGetTickCount();

	for( ; ; ){
		XMC_GPIO_ToggleOutput( (XMC_GPIO_PORT_t *)xLedPort, xLedPin );
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}
