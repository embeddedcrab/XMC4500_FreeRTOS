/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		VADC data types Header
* Filename:		dri_vadc_types.h
* Author:		HS
* Origin Date:	01/29/2020
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	dri_vadc_types.h
 *  @brief:	This file contains data types definitions for VADC
 */
#ifndef DRI_VADC_TYPES_H_
#define DRI_VADC_TYPES_H_


/******************************************************************************
* Includes
*******************************************************************************/

/* Include XMC Headers */
#include <xmc_vadc.h>

/* Include private headers first */
#include <private/dri_vadc_conf.h>
/* Include typedefs */
#include <dri_types.h>


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

/*
 * @brief	Enum for Status of UART
 * */
typedef enum eVADC_Status_
{
	VADC_STATUS_SUCCESS = 0,
	VADC_STATUS_FAILED,
	VADC_STATUS_BUSY,
	VADC_STATUS_INVALID_ARGUMENT,
	VADC_STATUS_OUT_OF_BOUND,
	VADC_STATUS_ALREADY_INITIALIZED
} eVADC_Status;

/*
 * @brief	Enum for Open or close
 * */
typedef enum eVADC_Init_
{
	VADC_INIT_CLOSE = 0,
	VADC_INIT_OPEN
} eVADC_Init;

/*
 * @brief	Enum for Operating Mode of ADC
 * */
//typedef enum eVADC_Mode_
//{
//} eVADC_Mode;

/*
 * @brief	Enum for Operation Events of ADC
 * */
//typedef enum eVADC_Event_
//{
//} eVADC_Event;

/*
 * @brief	Enum for VADC ISR operation
 * */
//typedef enum eVADC_InterruptOperation_
//{
//} eVADC_InterruptOperation;

/*
 * @brief	Enum for VADC Channel Information
 * */
//typedef enum eVADC_Channel_
//{
//} eVADC_Channel;


/*
 * @brief	typedef for callback function pointer
 * */
typedef void (*vadc_callback_pointer) ( void * p_channel, unsigned short *p_data );


/******************************************************************************
 *
 * @brief	Data Types for VADC__ instance
 *
 *****************************************************************************/

/*
 * @brief	typedef for status control of VADC__
 */
typedef struct tStVADC_StatusControl_
{
	union
	{
		struct
		{
			unsigned long init			: 1;
			unsigned long state_res		: 31;
		};
		unsigned long state_value;
	};
} tStVADC_StatusControl;

/************************************************************************************/

/*
 * @brief	Structure for VADC Global Configurations
 */
typedef struct tStVADC_GlobalConfiguartion_
{
	/**< Pointer to VADC Channel context */
	void * p_channel_context;
	#if( VADC_BACKGROUND_REQUEST_SOURCE == 1U )
	/**< Pointer to VADC Background Configuration */
	XMC_VADC_BACKGROUND_CONFIG_t * p_background_config;
	#endif
	XMC_VADC_GLOBAL_CONFIG_t global_config;
} tStVADC_GlobalConfiguartion;

/************************************************************************************/

/*
 * @brief Structure for VADC channel interrupt configuration
 */
typedef struct tStVADC_InterruptConfiguartion_
{
	/**< Interrupt configuration */
	tStInterruptConfig irq;
	/**< Service request number assigned to interrupt */
	unsigned long sr;
} tStVADC_InterruptConfiguartion;

/************************************************************************************/

/*
 * @brief	Structure for VADC Background Scan Group Configurations
 */
typedef struct tStVADC_BackgroundScan_GroupConfiguartion_
{
	/**< Pointer to VADC Group context */
	void * p_group_context;
	/**< Pointer to VADC Channel configuration */
	XMC_VADC_GROUP_CONFIG_t group_config;
	/**< VADC interrupt configuration */
#if( VADC_INTERRUPT_USED == 1U )
	tStVADC_InterruptConfiguartion group_isr_config;
#endif
} tStVADC_BackgroundScan_GroupConfiguartion;

/*
 * @brief	Structure for VADC Channel Configurations
 */
typedef struct tStVADC_ChannelConfiguartion_
{
	/**< Channel configurations for VADC */
	XMC_VADC_CHANNEL_CONFIG_t channel_config;
	/**< Channel Result configuration for VADC */
	XMC_VADC_RESULT_CONFIG_t result_config;
} tStVADC_ChannelConfiguartion;

/************************************************************************************/

/*
 * @brief	Structure for VADC Control
 */
typedef struct tStVADC_Control_
{
	volatile tStVADC_StatusControl state;
} tStVADC_Control;

/*
 * @brief	Structure for VADC Background Request Resource Group Configuration
 */
typedef struct tStVADC_BackgroundScanConfiguartion_
{
	tStVADC_BackgroundScan_GroupConfiguartion * p_background_scan_group_config;
	tStVADC_ChannelConfiguartion * p_channel_config;
	unsigned long group_channels;
} tStVADC_BackgroundScanConfiguartion;

/*
 * @brief Structure for VADC channel callbacks
 */
typedef struct tStVADC_Callbacks_
{
#if (VADC_CALLBACK_HANDLER_USED == 1U)
	vadc_callback_pointer fp_callback;
#endif
} tStVADC_Callbacks;

/*
 * @brief Structure for VADC channel API
 */
typedef struct tStVADC_BackgroundScan_Api_
{
	void (*fp_global_init) ( void * );
	long (*fp_init) ( void *, const unsigned char, const unsigned char );
	void (*fp_start)( void * );
	unsigned char (*fp_get_group) ( void * );
} tStVADC_BackgroundScan_Api;

/*
 * @brief Structure for VADC channel instance and information
 */
typedef struct tStVADC_BackgroundScan_
{
	tStVADC_BackgroundScanConfiguartion * const p_config;
	tStVADC_Control * const p_control;
#if( VADC_CALLBACK_HANDLER_USED == 1U )
	tStVADC_Callbacks * p_callback;
#endif
} tStVADC_BackgroundScan;


/*
 * @brief Structure for VADC background scan group instance
 */
typedef struct tStVADC_Background_
{
	tStVADC_BackgroundScan * p_instance[VADC_GROUPS_USED];
} tStVADC_Background;


#endif /* DRI_VADC_TYPES_H_ */

/********************************** End of File *******************************/
