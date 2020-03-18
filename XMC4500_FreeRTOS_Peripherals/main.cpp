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
* Origin Date:
* Version:
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	main.cpp
 *  @brief:	This source file contains main function entry
 */


/******************************************************************************
* Includes
*******************************************************************************/

/* Include Master Headers */
#include <master_config.h>

/* Include Trace headers */
#include <trace.h>

/* Include peripheral device files */
#include <dri_gpio_pins.h>
#include <dri_uart_extern.h>
#include <dri_vadc_extern.h>
#include <dri_dac_extern.h>
#include <dri_spi_extern.h>
#include <dri_ccu_extern.h>
#include <dri_can_extern.h>
#include <dri_scu_extern.h>
#include <dri_rtc_extern.h>

/* Include memory Headers */
#include <dri_mem.h>

/* Include RTOS Headers */
#include <rtos_wrappers.h>

/* Include Application Headers */
#include <led_task.hpp>
#include <server_task.h>
#include <client_task.h>
#include <logger.h>

/* Include Device Headers */
#include <external_flash.h>


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

#define FREERTOS_TCP_CLIENT				1U


/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Variables
*******************************************************************************/

/* Extern "C" block for C variables
 *
 * C Linkage in CPP Application
 * */
#ifdef __cplusplus
extern "C"
{

}
#endif	/* __cplusplus */



/******************************************************************************
* Functions
*******************************************************************************/

/* Extern "C" block for C variables
 *
 * C Linkage in CPP Application
 * */
#ifdef __cplusplus
extern "C"
{
/******* User defined initialization functions *******/
void init_user_before_main( void );
}
#endif	/* __cplusplus */


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
	#pragma GCC diagnostic pop

	/* The MAC address array is not declared const as the MAC address will
	 * normally be read from an some Memory(like Flash OTP region) and not hard coded
	 * (in real deployed applications) or read using HAL API from ETH MAC */
	static uint8_t ucMACAddress[ 6 ] = { 0x00U, 0x03U, 0x19U, 0x45U, 0x00, 0x00 };

	/* Define the network addressing.  These parameters will be used if either
	 * ipconfigUDE_DHCP is 0 or if ipconfigUSE_DHCP is 1 but DHCP auto configuration failed. */
	static const uint8_t ucIPAddress[ 4 ] =
	{
		INFINEON_HOST_SERVER_IP_ADDRESS0, INFINEON_HOST_SERVER_IP_ADDRESS1,
		INFINEON_HOST_SERVER_IP_ADDRESS1, INFINEON_HOST_SERVER_IP_ADDRESS3
	};

	static const uint8_t ucNetMask[ 4 ] = { 255, 255, 255, 0 };
	static const uint8_t ucGatewayAddress[ 4 ] = { 192, 168, 1, 1 };
	/* The following is the address of an OpenDNS server. */
	static const uint8_t ucDNSServerAddress[ 4 ] = { 208, 67, 222, 222 };

	ITM_printf( (void *)"Main Entry Initiated", sizeof("Main Entry Initiated") );

	/* Create LED tasks
	 *
	 * <i>Imp Note:</i>
	 * Application task creation shall be done using new while creating objects
	 * otherwise Bus Fault Exception will come!!
	 * */
	LedTask__ * LedTask = new LedTask__( XMC_GPIO_PORT1 , 0, &TaskParams );
	LedTask->xvinit();
	
	/* Initialize the RTOS’s TCP/IP stack.  The tasks that use the network
	 * are created in the vApplicationIPNetworkEventHook() hook function below.
	 * The hook function is called when the network connects. */
	BaseType_t xReturn = FreeRTOS_IPInit( ucIPAddress, ucNetMask, ucGatewayAddress, ucDNSServerAddress, ucMACAddress );

	/* Check IP Init status */
	if( xReturn == pdPASS )
	{
		/* Create Server Handler task */
		ServerTask__ server( ipconfigIP_TASK_PRIORITY, configMINIMAL_STACK_SIZE );//-1

		#if( FREERTOS_TCP_CLIENT == 1U )
		ClientTask__ client( ipconfigIP_TASK_PRIORITY - 1, configMINIMAL_STACK_SIZE );
		#endif

		/* Start Task Scheduler */
		vTaskStartScheduler();
		/* Processor should never cross from here */
		for( ; ; )
		{
			__asm("NOP");
		}
	}
	else
	{
		/* Could not initialize Network, shall hang N/W related tasks */
		while(1U)
		{
			__asm("NOP");
		}
	}

	return 0;
}


/******************************************************************************/

/**
 * @function
 *
 * @brief		User defined initialization before main entry
 *
 * @param[in]
 *
 * @param[out]	NA
 *
 * @return
 *
 * \par<b>Description:</b><br>
 *
 * <i>Imp Note:</i>
 *
 */
extern "C" void init_user_before_main( void )
{
	/* Intialize Trace output using ITM */
	ITM_init();

	ITM_printf( (void *)"Initializing System Booting", sizeof("Initializing System Booting") );
	extern void init_system_before_main( void );
	init_system_before_main();

	/* Initialize GPIO Pin functionalities */
	extern void gpio_init_c( void );
	ITM_printf( (void *)"Initializing GPIO and Peripherals",
			sizeof("Initializing GPIO and Peripherals") );
	gpio_init_c();

	/*----------------- Initialize Peripherals --------------------*/

	/* Initialize UART Channels */
	UART_init( &UART_Channel_2, 1 );	/* Used for Application Logging */
	UART_init( &UART_Channel_0, 1 );

	/* Initialize SPI Channels */
	SPI_Master_init( &SPI2_Channel0_Handle, 1 );

	/* Initialize Global VADC and Groups/Channels */
	VADC_global_init( &VADC_Global_Configuration );
	VADC_background_request_init( VADC_BackgroundScan_Handle.p_instance[0], 0, 1 );

	/* Initialize DAC Channels */
	DAC_init( &DAC0_DataProcessing, 0, DAC_MODE_DATA, 1 );
	DAC_init( &DAC1_NoiseGeneration, 1, DAC_MODE_NOISE, 1 );

	/* Initialize CCU4 Modules */
	CCU4_module_init( &CCU4_Module0, 1 );
	CCU4_module_init( &CCU4_Module2, 1 );
	/* Initialize CCU4 Channels */
	CCU4_capture_channel_init( &CCU40_Channel0_Handle, 0, 0, 1 );
	CCU4_capture_channel_init( &CCU40_Channel1_Handle, 0, 1, 1 );
	CCU4_compare_channel_init( &CCU40_Channel3_Handle, 0, 3, 1 );
	CCU4_compare_channel_init( &CCU42_Channel0_Handle, 2, 0, 1 );

	/* Initialize CCU8 Channels */
	CCU8_module_init( &CCU8_Module0 );
	/* Initialize CCU8 Channels */
	CCU8_compare_channel_init( &CCU80_Channel0_Handle, 0, 0, 1 );
	CCU8_compare_channel_init( &CCU80_Channel1_Handle, 0, 1, 1 );
	CCU8_compare_channel_init( &CCU80_Channel2_Handle, 0, 2, 1 );

	/* Initialize CAN Module */
	CAN_module_init( &CAN_Global, 1 );
	/* Initialize CAN Nodes */
	CAN_node_init( &CAN1, 1, 1 );
	CAN_node_init( &CAN2, 2, 1 );

	/* Initialize Ethernet MAC */
	extern void initialize_ethernet_mac( void );	/* MAC Initialization fucntion */
	initialize_ethernet_mac();

	/* Initilize SDMMC */

	/* Initialize USB Device */


	/*----------------- Initialize Devices --------------------*/

	/* Initialize External Flash */
//	ext_flash.init( 1 );/* TODO: Not tested fully, using SPI2 Channel 0 */


	/* Initialize SCU and WDT */
	SCU_init( &SCU, 1 );
	/* Initialize RTC */
	RTC_init( &RTC_, 1 );
}

/********************************** End of File *******************************/
