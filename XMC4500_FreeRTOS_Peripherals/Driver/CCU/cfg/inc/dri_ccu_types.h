/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		CCU data types Header
* Filename:		dri_ccu_types.h
* Author:		HS
* Origin Date:	02/14/2020
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	dri_ccu_types.h
 *  @brief:	This file contains data types definitions for CCU
 */
#ifndef DRI_CCU_TYPES_H_
#define DRI_CCU_TYPES_H_


/******************************************************************************
* Includes
*******************************************************************************/

/* Include XMC Headers */
#include <xmc_ccu4.h>
#include <xmc_ccu8.h>

/* Include private headers first */
#include <private/dri_ccu_conf.h>
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
 * @brief	Enum for Status of CCU
 * */
typedef enum eCCU_Status_
{
	CCU_STATUS_SUCCESS = 0,
	CCU_STATUS_FAILED,
	CCU_STATUS_BUSY,
	CCU_STATUS_INVALID_ARGUMENT,
	CCU_STATUS_OUT_OF_BOUND,
	CCU_STATUS_ALREADY_INITIALIZED
} eCCU_Status;

/*
 * @brief	Enum for Open or close
 * */
typedef enum eCCU_Init_
{
	CCU_INIT_CLOSE = 0,
	CCU_INIT_OPEN
} eCCU_Init;

/*
 * @brief	typedef for callback function pointer
 * */
typedef void (*ccu4_callback_pointer) ( void * p_channel );
typedef void (*ccu4_capture_callback_pointer) ( void * p_channel, void * p_data );

typedef void (*ccu8_callback_pointer) ( void * p_channel );
typedef void (*ccu8_capture_callback_pointer) ( void * p_channel );


/******************************************************************************
 *
 * @brief	Data Types for CCU instance
 *
 *****************************************************************************/

/*
 * @brief	typedef for status control of CCU4
 */
typedef struct tStCCU4_StatusControl_
{
	union
	{
		struct
		{
			volatile unsigned long init	: 1;
			unsigned long module_num	: 2;
			unsigned long slice_num		: 2;
			unsigned long state_res		: 27;
		};
		unsigned long state_value;
	};
} tStCCU4_StatusControl;

/*
 * @brief	typedef for status control of CCU8
 */
typedef struct tStCCU8_StatusControl_
{
	union
	{
		struct
		{
			volatile unsigned long init	: 1;
			unsigned long module_num	: 1;
			unsigned long slice_num		: 2;
			unsigned long state_res		: 28;
		};
		unsigned long state_value;
	};
} tStCCU8_StatusControl;

/************************************************************************************/

/*
 * @brief Structure for CCU channel interrupt configuration
 */
typedef struct tStCCU_InterruptConfiguartion_
{
	/**< Interrupt configuration */
	tStInterruptConfig irq;
	/**< Service request number assigned to interrupt */
	unsigned long sr;
} tStCCU_InterruptConfiguartion;


/************************************************************************************/


/************************************************************************************/

/*
 * @brief	Structure for CCU4 Module Configuration
 */
typedef struct tStCCU4_ModuleConfiguartion_
{
	/**< Module Context for CCU4 module */
	void * p_module_context;
	/**< Module transfer request configuration for CCU4 module */
	XMC_CCU4_SLICE_MCMS_ACTION_t module_transfer_request;
	/**< Module clock for CCU4 module */
	XMC_CCU4_CLOCK_t module_clock;
} tStCCU4_ModuleConfiguartion;

/*
 * @brief	Structure for CCU4 Slice Compare Configuration
 */
typedef struct tStCCU4_SliceCompareConfiguartion_
{
	/**< Channel context for CCU4 Slice */
	void * p_slice_context;
	/**< Configuration for CCU4 Slice */
	XMC_CCU4_SLICE_COMPARE_CONFIG_t * p_config;
	/**< Event Configurations for CCU4 Slice */
	XMC_CCU4_SLICE_EVENT_CONFIG_t * p_event_config;
	tStCCU_InterruptConfiguartion * p_irq_config;

	/**< Period and Compare configuration for Compare Slice configuration */
	volatile unsigned short period;
	volatile unsigned short compare;

	/**< Events Configuration for Compare */
	XMC_CCU4_SLICE_EVENT_t event;
	XMC_CCU4_SLICE_START_MODE_t start_mode;
	XMC_CCU4_SLICE_IRQ_ID_t interrupt_event;
	XMC_CCU4_SHADOW_TRANSFER_t shadow_transfer;
} tStCCU4_SliceCompareConfiguartion;

/*
 * @brief	Structure for CCU4 Slice Capture Configuration
 */
typedef struct tStCCU4_SliceCaptureConfiguartion_
{
	/**< Channel context for CCU4 Slice */
	void * p_slice_context;
	/**< Configuration for CCU4 Slice */
	XMC_CCU4_SLICE_CAPTURE_CONFIG_t * p_config;
	/**< Event Configurations for CCU4 Slice */
	XMC_CCU4_SLICE_EVENT_CONFIG_t * p_event_config_off;
	XMC_CCU4_SLICE_EVENT_CONFIG_t * p_event_config_on;
	tStCCU_InterruptConfiguartion * p_irq_config;

	/**< Period and Duty cycle for Capture events */
	volatile unsigned short period;
	volatile unsigned short duty_cycle;

	/**< Events Configuration for Capture */
	XMC_CCU4_SLICE_EVENT_t event0;
	XMC_CCU4_SLICE_EVENT_t event1;
	XMC_CCU4_SLICE_IRQ_ID_t interrupt_event;
} tStCCU4_SliceCaptureConfiguartion;

/*
 * @brief	Structure for CCU4 Control
 */
typedef struct tStCCU4_Control_
{
	tStCCU4_StatusControl state;
} tStCCU4_Control;

/*
 * @brief Structure for CCU4 channel callbacks
 */
typedef struct tStCCU4_Callbacks_
{
#if (CCU4_CALLBACK_HANDLER_USED == 1U)
	ccu4_callback_pointer fp_callback;
#endif
} tStCCU4_Callbacks;

/*
 * @brief Structure for CCU4 capture channel callbacks
 */
typedef struct tStCCU4_CaptureCallbacks_
{
#if (CCU4_CALLBACK_HANDLER_USED == 1U)
	ccu4_capture_callback_pointer fp_callback;
#endif
} tStCCU4_CaptureCallbacks;

/*
 * @brief Structure for CCU4 channel API
 */
typedef struct tStCCU4_Api_
{
	long (*fp_module_init) ( void * );
	long (*fp_compare_channel_init)( void *, const unsigned char, const unsigned char, const unsigned char );
	long (*fp_capture_channel_init)( void *, const unsigned char, const unsigned char, const unsigned char );
	void (*fp_channel_timer_control)( void *, const unsigned char );
} tStCCU4_Api;

/*
 * @brief Structure for CCU4 Compare channel instance and information
 */
typedef struct tStCCU4_Module_
{
	/**< Configurations ofr Module */
	tStCCU4_ModuleConfiguartion * p_module_config;
	/* Can add other parameters for control */
} tStCCU4_Module;


/*
 * @brief Structure for CCU4 Compare channel instance and information
 */
typedef struct tStCCU4_Compare_
{
	tStCCU4_SliceCompareConfiguartion * const p_config;
	tStCCU4_Control * const p_control;
#if( CCU4_CALLBACK_HANDLER_USED == 1U )
	tStCCU4_Callbacks * p_callback;
#endif
} tStCCU4_Compare;


/*
 * @brief Structure for CCU4 Capture channel instance and information
 */
typedef struct tStCCU4_Capture_
{
	tStCCU4_SliceCaptureConfiguartion * const p_config;
	tStCCU4_Control * const p_control;
#if( CCU4_CALLBACK_HANDLER_USED == 1U )
	tStCCU4_CaptureCallbacks * p_callback;
#endif
} tStCCU4_Capture;


/************************************************************************************/


/************************************************************************************/


/*
 * @brief	Structure for CCU8 Module Configuration
 */
typedef struct tStCCU8_ModuleConfiguartion_
{
	/**< Module Context for CCU8 module */
	void * p_module_context;
	/**< Module transfer request configuration for CCU8 module */
	XMC_CCU8_SLICE_MCMS_ACTION_t module_transfer_request;
	/**< Module clock for CCU8 module */
	XMC_CCU8_CLOCK_t module_clock;
} tStCCU8_ModuleConfiguartion;

/*
 * @brief Structure for CCU8 channel instance and information
 */
typedef struct tStCCU8_Module_
{
	/**< Configurations ofr Module */
	tStCCU8_ModuleConfiguartion * p_module_config;
	/* Can add other parameters for control */
} tStCCU8_Module;


/*
 * @brief	Structure for CCU8 Slice Compare Configuration
 */
typedef struct tStCCU8_SliceCompareConfiguartion_
{
	/**< Channel context for CCU8 Slice */
	void * p_slice_context;
	/**< Configuration for CCU8 Slice */
	XMC_CCU8_SLICE_COMPARE_CONFIG_t * p_config;
	XMC_CCU8_SLICE_DEAD_TIME_CONFIG_t * p_dead_time_config;
	/**< Event Configurations for CCU8 Slice */
	XMC_CCU8_SLICE_EVENT_CONFIG_t * p_event_config;
	tStCCU_InterruptConfiguartion * p_irq_config;

	/**< Period and Compare configuration for Compare Slice configuration */
	volatile unsigned short period;
	volatile unsigned short compare;

	/**< Events Configuration for Compare */
	XMC_CCU8_SLICE_COMPARE_CHANNEL_t compare_channel;
	XMC_CCU8_SLICE_EVENT_t event;
	XMC_CCU8_SLICE_START_MODE_t start_mode;
	XMC_CCU8_SLICE_IRQ_ID_t interrupt_event;
	XMC_CCU8_SHADOW_TRANSFER_t shadow_transfer;
} tStCCU8_SliceCompareConfiguartion;

/*
 * @brief	Structure for CCU8 Slice Capture Configuration
 */
typedef struct tStCCU8_SliceCaptureConfiguartion_
{
	/**< Channel context for CCU8 Slice */
	void * p_slice_context;
	/**< Configuration for CCU8 Slice */
	XMC_CCU8_SLICE_CAPTURE_CONFIG_t * p_config;
	/**< Event Configurations for CCU8 Slice */
	XMC_CCU8_SLICE_EVENT_CONFIG_t * p_event_config_off;
	XMC_CCU8_SLICE_EVENT_CONFIG_t * p_event_config_on;
	tStCCU_InterruptConfiguartion * p_irq_config;

	/**< Period and Duty cycle for Capture events */
	volatile unsigned short period;
	volatile unsigned short duty_cycle;

	/**< Events Configuration for Capture */
	XMC_CCU8_SLICE_EVENT_t event0;
	XMC_CCU8_SLICE_EVENT_t event1;
	XMC_CCU8_SLICE_IRQ_ID_t interrupt_event;
} tStCCU8_SliceCaptureConfiguartion;

/*
 * @brief	Structure for CCU8 Control
 */
typedef struct tStCCU8_Control_
{
	tStCCU8_StatusControl state;
} tStCCU8_Control;

/*
 * @brief Structure for CCU8 channel callbacks
 */
typedef struct tStCCU8_Callbacks_
{
#if (CCU8_CALLBACK_HANDLER_USED == 1U)
	ccu8_callback_pointer fp_callback;
#endif
} tStCCU8_Callbacks;

/*
 * @brief Structure for CCU8 capture channel callbacks
 */
typedef struct tStCCU8_CaptureCallbacks_
{
#if (CCU8_CALLBACK_HANDLER_USED == 1U)
	ccu8_capture_callback_pointer fp_callback;
#endif
} tStCCU8_CaptureCallbacks;

/*
 * @brief Structure for CCU8 channel API
 */
typedef struct tStCCU8_Api_
{
	long (*fp_module_init) ( void * );
	long (*fp_compare_channel_init)( void *, const unsigned char, const unsigned char, const unsigned char );
//	long (*fp_capture_channel_init)( void *, const unsigned char, const unsigned char, const unsigned char );
	void (*fp_channel_timer_control)( void *, const unsigned char );
} tStCCU8_Api;

/*
 * @brief Structure for CCU8 Compare channel instance and information
 */
typedef struct tStCCU8_Compare_
{
	tStCCU8_SliceCompareConfiguartion * const p_config;
	tStCCU8_Control * const p_control;
#if( CCU8_CALLBACK_HANDLER_USED == 1U )
	tStCCU8_Callbacks * p_callback;
#endif
} tStCCU8_Compare;


/*
 * @brief Structure for CCU8 Capture channel instance and information
 */
typedef struct tStCCU8_Capture_
{
	tStCCU8_SliceCaptureConfiguartion * const p_config;
	tStCCU8_Control * const p_control;
#if( CCU8_CALLBACK_HANDLER_USED == 1U )
	tStCCU8_CaptureCallbacks * p_callback;
#endif
} tStCCU8_Capture;


#endif /* DRI_CCU_TYPES_H_ */

/********************************** End of File *******************************/
