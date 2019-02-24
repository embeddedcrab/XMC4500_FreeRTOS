/*
 * main.cpp
 *
 *  Created on: 2019 Feb 18 21:13:56
 *  Author: hp
 */


/* Include Application Headers */
#include <led_task.hpp>


/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. 
 */


int main(void)
{
	/* Task Parameters Variable */
	TaskCreationParams TaskParams = {"LED_TASK", configMINIMAL_STACK_SIZE, 1 };
	TaskCreationParams TaskParams1 = {"LED_TASK1", configMINIMAL_STACK_SIZE, 1 };

	/* Port Configurations */
	XMC_GPIO_CONFIG_t LedConfig = { XMC_GPIO_MODE_OUTPUT_PUSH_PULL, XMC_GPIO_OUTPUT_LEVEL_LOW, XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE };
	XMC_GPIO_CONFIG_t LedConfig1 = { XMC_GPIO_MODE_OUTPUT_PUSH_PULL, XMC_GPIO_OUTPUT_LEVEL_LOW, XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE };

	/* Create a demo task */
	LedTask_* LedTask = new LedTask_( XMC_GPIO_PORT1 , &LedConfig, 1, &TaskParams );
	LedTask->xvinit();

	LedTask_* LedTask1 = new LedTask_( XMC_GPIO_PORT1 , &LedConfig1, 0, &TaskParams1 );
	LedTask1->xvinit();

	/* Start Task Scheduler */
	vTaskStartScheduler();

	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while(1U)
	{
		;// NOP
	}

	return 0;
}

/************************************************************************************************/


extern "C"{
	void BusFault_Handler(void) {
		while(1U);
	}

	void HardFault_Handler(void)
	{
		while(1U);
	}
}

