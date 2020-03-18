/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		DAC data types Header
* Filename:		dri_dac_types.h
* Author:		HS
* Origin Date:	02/23/2020
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	dri_dac_types.h
 *  @brief:	This file contains data types definitions for DAC
 */
#ifndef DRI_DAC_TYPES_H_
#define DRI_DAC_TYPES_H_


/******************************************************************************
* Includes
*******************************************************************************/

/* Include XMC Headers */
#include <xmc_dac.h>

/* Include private headers first */
#include <private/dri_dac_conf.h>
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
 * @brief	Enum for Status of DAC
 * */
typedef enum eDAC_Status_
{
	DAC_STATUS_SUCCESS = 0,
	DAC_STATUS_FAILED,
	DAC_STATUS_BUSY,
	DAC_STATUS_INVALID_ARGUMENT,
	DAC_STATUS_OUT_OF_BOUND,
	DAC_STATUS_ALREADY_INITIALIZED
} eDAC_Status;

/*
 * @brief	Enum for Open or close
 * */
typedef enum eDAC_Init_
{
	DAC_INIT_CLOSE = 0,
	DAC_INIT_OPEN
} eDAC_Init;


/*
 * @brief	Enum for DAC Event
 * */
typedef enum eDAC_Events_
{
	DAC_EVENT = 0
} eDAC_Events;

/*
 * @brief	Enum for DAC Modes
 * */
typedef enum eDAC_Modes_
{
	DAC_MODE_IDLE = 0,
	DAC_MODE_DATA = 2,
	DAC_MODE_NOISE = 4
} eDAC_Modes;

/*
 * @brief	typedef for callback function pointer
 * */
typedef void (*dac_callback_pointer) ( void * p_channel /*, void * p_data, const eDAC_Events event */ );


/******************************************************************************
 *
 * @brief	Data Types for DAC instance
 *
 *****************************************************************************/

/*
 * @brief	typedef for status control of DAC
 */
typedef struct tStDAC_StatusControl_
{
	union
	{
		struct
		{
			unsigned long init			: 1;
			unsigned long channel		: 1;
			unsigned long valid			: 1;
			unsigned long run			: 1;
			unsigned long state_res		: 29;
		};
		unsigned long state_value;
	};
} tStDAC_StatusControl;

/************************************************************************************/

/*
 * @brief Structure for DAC channel interrupt configuration
 */
typedef struct tStDAC_InterruptConfiguartion_
{
	/**< Interrupt configuration */
	tStInterruptConfig irq;
} tStDAC_InterruptConfiguartion;


/************************************************************************************/


/************************************************************************************/

/*
 * @brief	Structure for DAC Data Processing Configuration
 */
typedef struct tStDAC_DataProcessingConfiguartion_
{
	/**< Module Context for DAC module */
	void * p_module_context;

	/**< DAC Channel configuration */
	XMC_DAC_CH_CONFIG_t * p_config;
	/**< DAC Channel Interrupt configuration */
	tStDAC_InterruptConfiguartion * p_isr_config;

	unsigned long frequency;
	XMC_DAC_CH_MODE_t channel_mode;
	XMC_DAC_CH_TRIGGER_t channel_trigger;
} tStDAC_DataProcessingConfiguartion;

/*
 * @brief	Structure for DAC Noise Generator Configuration
 */
typedef struct tStDAC_NoiseGeneratorConfiguartion_
{
	/**< Module Context for DAC module */
	void * p_module_context;

	/**< DAC Channel configuration */
	XMC_DAC_CH_CONFIG_t * p_config;

	unsigned long frequency;
	XMC_DAC_CH_MODE_t channel_mode;
	XMC_DAC_CH_TRIGGER_t channel_trigger;
} tStDAC_NoiseGeneratorConfiguartion;


/*
 * @brief	Structure for DAC Control
 */
typedef struct tStDAC_Control_
{
	volatile tStDAC_StatusControl state;
} tStDAC_Control;

/*
 * @brief Structure for DAC channel callbacks
 */
typedef struct tStDAC_Callbacks_
{
#if (DAC_CALLBACK_HANDLER_USED == 1U)
	dac_callback_pointer fp_callback;
#endif
} tStDAC_Callbacks;

/*
 * @brief Structure for DAC Data Processing Module
 */
typedef struct tStDAC_DataProcessing_
{
	/**< Configurations for Data processing mode */
	tStDAC_DataProcessingConfiguartion * p_config;
	/* Control for Data processing */
	tStDAC_Control * p_control;
	#if (DAC_CALLBACK_HANDLER_USED == 1U)
	tStDAC_Callbacks * p_callback;
	#endif
} tStDAC_DataProcessing;


/*
 * @brief Structure for DAC Noise Generator Module
 */
typedef struct tStDAC_NoiseGenerator_
{
	/**< Configurations for Noise generator mode */
	tStDAC_NoiseGeneratorConfiguartion * p_config;
	/* Control for Data processing */
	tStDAC_Control * p_control;
} tStDAC_NoiseGenerator;


/******************************************************************************/


#endif /* DRI_DAC_TYPES_H_ */

/********************************** End of File *******************************/
