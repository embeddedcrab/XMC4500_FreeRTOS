/*
 * led_task.hpp
 *
 *  Created on: 19-Feb-2019
 *      Author: hp
 */

#ifndef APP_INC_LED_TASK_HPP_
#define APP_INC_LED_TASK_HPP_

/* Include XMC Headers */
#include <xmc_common.h>
#include <xmc_gpio.h>

/* Include FreeRTOS Headers */
#include <FreeRTOS.h>
#include <task.h>


/* Parameters for task creation */
typedef struct TaskCreationParams_{
	char *name;
	configSTACK_DEPTH_TYPE stackDepth;
	UBaseType_t priority;
}TaskCreationParams;


class LedTask_{
public:
	/* Constructor */
	LedTask_( XMC_GPIO_PORT_t * port, XMC_GPIO_CONFIG_t * config, uint8_t pin, TaskCreationParams *param ){
		xLedPort = port;
		xLedPortConfig = *config;
		xLedPin = pin;
		LedTaskParams.name = param->name;
		LedTaskParams.priority = param->priority;
		LedTaskParams.stackDepth = param->stackDepth;
	}

	/* Task Initialization Function */
	void xvinit( void );

private:
	/* Port Info */
	volatile XMC_GPIO_PORT_t * xLedPort;
	XMC_GPIO_CONFIG_t xLedPortConfig;
	uint8_t xLedPin;

	/* Task Info */
	TaskCreationParams LedTaskParams;
	TaskHandle_t xHandle;

	/* Will work as a linker to the actual task function */
	static void xsvTaskEntryPoint( void *params ){
		((LedTask_ *) params)->xvTaskEntry(params);
	}

	/* Initialize Hardware Peripherals */
	void xvInitializeGPIO( void );

	/* This function contains the actual body of task */
	void xvTaskEntry( void *pvParams );
};


#endif /* APP_INC_LED_TASK_HPP_ */
