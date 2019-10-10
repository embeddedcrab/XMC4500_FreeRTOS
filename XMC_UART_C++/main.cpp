/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		Main Source
* Filename:		main.cpp
* Author:		HS
* Origin Date:	18/02/2019
* Version:		1.0.1
* Notes:
*
* Change History
* --------------
*
* 30/09/2019	-	Hemant Sharma
* Updated file formatting
*
*******************************************************************************/

/** @file:	main.cpp
 *  @brief:	This source file contains main function entry with
 *  		Exception handlers and callback functions
 */


/******************************************************************************
* Includes
*******************************************************************************/

/* Include Application Headers */
#include <led_task.hpp>

/* Include peripheral device files */
#include <dri_uart_extern.h>


/******************************************************************************
* Variables
*******************************************************************************/

/* Extern "C" block for C linkage
 *
 * C Linkage in CPP Application
 * */
#ifdef __cplusplus
extern "C"
{

#define EXCEPTION_HANDLER_DEBUG_ON
#undef EXCEPTION_HANDLER_DEBUG_ON

/******* User defined initialization functions *******/
void init_user_before_main( void );

}
#endif	/* __cplusplus */


/******************************************************************************
* Function Definitions
*******************************************************************************/

/**
 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point.
 * It is invoked by the device startup code.
 */
int main(void)
{
	/* Task Parameters Variable */
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wwrite-strings"
	TaskCreationParams TaskParams = {"LED_TASK", configMINIMAL_STACK_SIZE, 1 };
	TaskCreationParams TaskParams1 = { "LED_TASK1", configMINIMAL_STACK_SIZE, 1 };
	#pragma GCC diagnostic push

	eUART_Status_ uart_status = eUART_Status_::UART_STATUS_FAILED;

	/* Create LED tasks
	 *
	 * <i>Imp Note:</i>
	 * Application task creation shall be done using new while creating objects
	 * otherwise Bus Fault Exception will come!!
	 * */
	LedTask_* LedTask = new LedTask_( XMC_GPIO_PORT1 , 1, &TaskParams );
	LedTask->xvinit();

	LedTask_* LedTask1 = new LedTask_( XMC_GPIO_PORT1 , 0, &TaskParams1 );
	LedTask1->xvinit();

	/* Call UART Object functions, can check the initialization status */
	uart_status = g_p_uart_obj[0]->init();
	uart_status = g_p_uart_obj[1]->init();
	uart_status = g_p_uart_obj[2]->init();

	/* Remove warning for variable */
	(void) uart_status;

	/* Start Task Scheduler */
	vTaskStartScheduler();

	/* Should never reach here! */
	while(1U)
	{
		__asm("NOP");
	}

	return -1;
}

/******************************************************************************/


/* Exception Handler functions for debugging and tracing */
extern "C"{

#ifdef EXCEPTION_HANDLER_DEBUG_ON

void get_registers_from_stack( unsigned long *pulFaultStackAddress )
{
	/* These are volatile to try and prevent the compiler/linker optimizing them
	 away as the variables never actually get used.  If the debugger won't show the
	 values of the variables, make them global my moving their declaration outside
	 of this function. */
	volatile uint32_t r0;
	volatile uint32_t r1;
	volatile uint32_t r2;
	volatile uint32_t r3;
	volatile uint32_t r12;
	volatile uint32_t lr;	/**< Link register. */
	volatile uint32_t pc;	/**< Program counter. */
	volatile uint32_t psr;	/**< Program status register. */

	/* Assign Register values into local variables */
	r0 = pulFaultStackAddress[0];
	r1 = pulFaultStackAddress[1];
	r2 = pulFaultStackAddress[2];
	r3 = pulFaultStackAddress[3];

	r12 = pulFaultStackAddress[4];
	lr = pulFaultStackAddress[5];
	pc = pulFaultStackAddress[6];
	psr = pulFaultStackAddress[7];

	/* When the following line is hit, the variables contain the register values. */
	for( ; ; );
}

#endif	/* EXCEPTION_HANDLER_DEBUG_ON */

void BusFault_Handler(void)
{
#ifdef EXCEPTION_HANDLER_DEBUG_ON
	__asm volatile
	(
			" tst lr, #4                                                \n"
			" ite eq                                                    \n"
			" mrseq r0, msp                                             \n"
			" mrsne r0, psp                                             \n"
			" ldr r1, [r0, #24]                                         \n"
			" ldr r2, bus_fault_handler_address_const                   \n"
			" bx r2                                                     \n"
			" bus_fault_handler_address_const: .word get_registers_from_stack    \n"
	);
#endif
	for( ; ; );
}

void HardFault_Handler(void)
{
#ifdef EXCEPTION_HANDLER_DEBUG_ON
	__asm volatile
	(
			" tst lr, #4                                                \n"
			" ite eq                                                    \n"
			" mrseq r0, msp                                             \n"
			" mrsne r0, psp                                             \n"
			" ldr r1, [r0, #24]                                         \n"
			" ldr r2, hard_fault_handler_address_const                  \n"
			" bx r2                                                     \n"
			" hard_fault_handler_address_const: .word get_registers_from_stack    \n"
	);
	for( ; ; );
#endif	/* EXCEPTION_HANDLER_DEBUG_ON */
}

void MemManage_Handler(void)
{
#ifdef EXCEPTION_HANDLER_DEBUG_ON
	/* Exception tracing */
#endif
	for( ; ; );
}

void UsageFault_Handler(void)
{
#ifdef EXCEPTION_HANDLER_DEBUG_ON
	/* Exception tracing */
#endif
	for( ; ; );
}

}/* } end */


/** User defined functions **/
extern "C" void init_user_before_main( void )
		{
			extern void gpio_init_c( void );
			gpio_init_c();
			extern void initialize_uart_objects_c( void );
			initialize_uart_objects_c();
		}


/* UART__ class callback handler function for User */
void uart_callback_handler(eUART_Channel_& channel, unsigned char *p_data, eUART_Event_ event)
{
	/* Can check the events for callback and do processing */
	(void) p_data;

	/* Check events */
	switch( event )
	{
	/* Including all events in default case */
		default:
		case eUART_Event_::UART_EVENT_TX_COMPLETE:
			if( eUART_Channel_::UART_CHANNEL_0 == channel )
			{
				/* Transmission successful! */
				__asm("NOP");
			}
			break;

		case eUART_Event_::UART_EVENT_RX_COMPLETE:
			if( eUART_Channel_::UART_CHANNEL_0 == channel )
			{
				/* Reception successful! */
				__asm("NOP");
			}
			break;

		/* Can add different events */
	}
}

/********************************** End of File *******************************/
