/*****************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		DAC Configuration Source
* Filename:		dri_dac_conf.c
* Author:		HS
* Origin Date:	02/23/2020
* Version:		1.0.0
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	dri_dac_conf.c
 *  @brief:	This source file contains configuration function definitions for DAC
 */


/******************************************************************************
* Includes
*******************************************************************************/
#include <dri_dac.h>


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

/*
 * @brief	DAC API functions
 *
 * \par<b>Description:</b><br>
 * 			This is data structure for DAC API functions to be used by Application
 */


/*****************************************************************************/

/* Callback handler for user */
#if (DAC_CALLBACK_HANDLER_USED == 1U)
extern void DAC_callback_handler( void * p_channel );
#endif


/* DAC 0 for Data Processing Mode */
#if (DAC_CHANNEL0_USED == 1U)
static XMC_DAC_CH_CONFIG_t DAC0_DataProcessing_ChannelConfiguration =
{
	/**< cfg0 */
	.data_type = XMC_DAC_CH_DATA_TYPE_UNSIGNED,
	.output_negation = XMC_DAC_CH_OUTPUT_NEGATION_DISABLED,

	/**< cfg1 */
	.output_scale = XMC_DAC_CH_OUTPUT_SCALE_NONE,
	.output_offset = 0
};

static tStDAC_InterruptConfiguartion DAC0_DataProcessing_InterruptConfiguration =
{
	.irq = { .irq_num = DAC0_0_IRQn, .irq_priority = 55 }
};

static tStDAC_DataProcessingConfiguartion DAC0_DataProcessing_Configuration =
{
	.p_module_context = XMC_DAC0,
	.p_config = &DAC0_DataProcessing_ChannelConfiguration,
	.p_isr_config = &DAC0_DataProcessing_InterruptConfiguration,
	.frequency = 50000,	/* 5 KHz */
	.channel_mode = XMC_DAC_CH_MODE_DATA,
	.channel_trigger = XMC_DAC_CH_TRIGGER_SOFTWARE
};

/* Control for DAC 0 Data Processing */
tStDAC_Control DAC0_DataProcessing_Control;

#if (DAC_CALLBACK_HANDLER_USED == 1U)
tStDAC_Callbacks DAC0_DataProcessing_Callback =
{
	.fp_callback = &DAC_callback_handler
};
#endif	/* DAC_CALLBACK_HANDLER_USED */
#endif	/* DAC_CHANNEL0_USED */


/* DAC Channel 1 for Noise generation */
#if (DAC_CHANNEL1_USED == 1U)
static XMC_DAC_CH_CONFIG_t DAC1_NoiseGeneration_ChannelConfiguration =
{
	/**< cfg0 */
	.data_type = XMC_DAC_CH_DATA_TYPE_SIGNED,
	.output_negation = XMC_DAC_CH_OUTPUT_NEGATION_DISABLED,

	/**< cfg1 */
	.output_scale = XMC_DAC_CH_OUTPUT_SCALE_NONE,
	.output_offset = 0
};

static tStDAC_NoiseGeneratorConfiguartion DAC1_NoiseGeneration_Configuration =
{
	.p_module_context = XMC_DAC0,
	.p_config = &DAC1_NoiseGeneration_ChannelConfiguration,
	.frequency = 50000,	/* 50 KHz */
	.channel_mode = XMC_DAC_CH_MODE_NOISE,
	.channel_trigger = XMC_DAC_CH_TRIGGER_SOFTWARE
};

/* Control for DAC 1 Noise Generation */
tStDAC_Control DAC1_NoiseGeneration_Control;
#endif	/* DAC_CHANNEL0_USED */




/* DAC Channel 0 for Data Processing Global Handle */
#if (DAC_CHANNEL0_USED == 1U)
tStDAC_DataProcessing DAC0_DataProcessing =
{
	.p_config = &DAC0_DataProcessing_Configuration,
	.p_control = &DAC0_DataProcessing_Control
	#if (DAC_CALLBACK_HANDLER_USED == 1U)
	,.p_callback = &DAC0_DataProcessing_Callback
	#endif
};
#endif


/* DAC Channel 1 for Noise generation Global Handle */
#if (DAC_CHANNEL1_USED == 1U)
tStDAC_NoiseGenerator DAC1_NoiseGeneration =
{
	.p_config = &DAC1_NoiseGeneration_Configuration,
	.p_control = &DAC1_NoiseGeneration_Control
};
#endif



/******************************************************************************
* Function Definitions
*******************************************************************************/

/******* ISR Handlers for DAC channels *******/


unsigned short DAC0_Data[DAC0_DATA_NUMBER] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

/* TODO: This data needs to be reset by linking with trigger function call */
unsigned long DAC0_Data_Count = 0;

/*****************************************************************************/

/* Channels ISR Entries */
#if (DAC_CHANNEL0_USED == 1U)
void DAC0_Handler( void )
{
	/* Process data */
	XMC_DAC_CH_Write( XMC_DAC0, 0, *(DAC0_Data + DAC0_Data_Count) );
	if( DAC0_DATA_NUMBER ==  DAC0_Data_Count )
	{
		/* Reset Index */
		DAC0_Data_Count = 0;
	}
	else
	{
		/* Increment Index for every iteration */
		DAC0_Data_Count += 1;
	}
}
#endif


/*********************************** End of File ******************************/
