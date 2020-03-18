/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		DAC API Source
* Filename:		dri_dac.c
* Author:		HS
* Origin Date:	02/23/2020
* Version:		1.0.0
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	dri_dac.c
 *  @brief:	This source file contains API function definitions for DAC
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


/******************************************************************************
* Private Function Declarations
*******************************************************************************/

static long dac_initalize_channel( void * p_channel,
	const unsigned char channel, const unsigned char mode );

static long dac_deinitalize_channel( void * p_channel,
	const unsigned char channel, const unsigned char mode );


/******************************************************************************
* Public Function Definitions
*******************************************************************************/

/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 *
 */
long DAC_init( void * p_channel, const unsigned char channel,
				const unsigned char mode, const unsigned char init )
{
	DRIVER_ASSERT( NULL == p_channel, DAC_STATUS_INVALID_ARGUMENT );
	DRIVER_ASSERT( channel > 1, DAC_STATUS_INVALID_ARGUMENT );
	/* Local Variables */
	long ret_status = DAC_STATUS_FAILED;

	/* Check initialization status */
	if( 1 == init )
	{
		ret_status = dac_initalize_channel( p_channel, channel, mode );
	}
	else if( 0 == init )/* De-initialize DAC Channel */
	{
		ret_status = dac_deinitalize_channel( p_channel, channel, mode );
	}
	else
	{
		/* Update return status */
		ret_status = DAC_STATUS_INVALID_ARGUMENT;
	}

	/* Return status */
	return ret_status;
}


/******************************************************************************
* Private Function Definitions
*******************************************************************************/

/**
 * @function
 *
 * @brief
 *
 * @param[in]
 *
 * \par<b>Description:</b><br>
 *
 * <i>Imp Note:</i>
 *
 */
long dac_initalize_channel( void * p_channel,
	const unsigned char channel, const unsigned char mode )
{
	/* Local Variables */
	long ret_status = DAC_STATUS_FAILED;

	/* Check mode of operation */
	switch( mode )
	{	/* Idel mode */
		case 0:
			/* Not considered for now */
			ret_status = DAC_STATUS_INVALID_ARGUMENT;
		break;

		/* Single value mode - single data value is updated and maintained */
		case 1:
			/* Not considered for now */
			ret_status = DAC_STATUS_INVALID_ARGUMENT;
		break;

		/* Data mode - continuous data processing */
		case 2:
		{
			tStDAC_DataProcessingConfiguartion * p_config_l = ((tStDAC_DataProcessing *)p_channel)->p_config;
			tStDAC_Control * p_control_l = ((tStDAC_DataProcessing *)p_channel)->p_control;

			/* Update channel number */
			p_control_l->state.channel = (unsigned long)channel;

			/* Initialize DAC Channel */
			XMC_DAC_CH_Init( (XMC_DAC_t *const) p_config_l->p_module_context, (unsigned char)p_control_l->state.channel,
								(const XMC_DAC_CH_CONFIG_t *const)p_config_l->p_config  );

			if( 0 == p_control_l->state.valid )
			{
				/* Set mode of channel */
				XMC_DAC_CH_SetMode( (XMC_DAC_t *const) p_config_l->p_module_context, (unsigned char)p_control_l->state.channel,
										p_config_l->channel_mode );
				/* Set Trigger */
				XMC_DAC_CH_SetTrigger( (XMC_DAC_t *const) p_config_l->p_module_context, (unsigned char)p_control_l->state.channel,
										p_config_l->channel_trigger );

				/* Enable Events */
				XMC_DAC_CH_EnableEvent( (XMC_DAC_t *const) p_config_l->p_module_context, (unsigned char)p_control_l->state.channel );
				/* NVIC Configurations */
				NVIC_SetPriority( (IRQn_Type)p_config_l->p_isr_config->irq.irq_num,
									NVIC_EncodePriority(NVIC_GetPriorityGrouping(),
									(IRQn_Type)p_config_l->p_isr_config->irq.irq_priority, 0U) );
				NVIC_EnableIRQ( (IRQn_Type)p_config_l->p_isr_config->irq.irq_num );
			}

			/* Set Frequency */
			ret_status = XMC_DAC_CH_SetFrequency( (XMC_DAC_t *const) p_config_l->p_module_context,
								(unsigned char)p_control_l->state.channel, p_config_l->frequency );
			/* Check status */
			if( XMC_DAC_CH_STATUS_OK == ret_status )
			{
				/* Start Data Mode */
				ret_status = XMC_DAC_CH_StartDataMode( (XMC_DAC_t *const) p_config_l->p_module_context,
								(unsigned char)p_control_l->state.channel, p_config_l->channel_trigger, p_config_l->frequency );

				/* Update parameters */
				p_control_l->state.init = (XMC_DAC_CH_STATUS_OK == ret_status) ? 1 : 0;
				/* Update return status */
				ret_status = (1 == p_control_l->state.init) ? DAC_STATUS_SUCCESS : DAC_STATUS_FAILED;
				p_control_l->state.valid = 1;
			}
			else
			{
				p_control_l->state.init = 0;
				ret_status = DAC_STATUS_FAILED;
			}
		}
		break;

		/* Pattern mode - inbuilt pattern waveform generation - Sine, Triangle, Rectangle */
		case 3:
			/* Not considered for now */
			ret_status = DAC_STATUS_INVALID_ARGUMENT;
		break;

		/* Noise mode - pseudo-random noise generation */
		case 4:
		{
			tStDAC_NoiseGeneratorConfiguartion * p_config_l = ((tStDAC_NoiseGenerator *)p_channel)->p_config;
			tStDAC_Control * p_control_l = ((tStDAC_DataProcessing *)p_channel)->p_control;

			/* Update channel number */
			p_control_l->state.channel = (unsigned long)channel;

			/* Initialize DAC Channel */
			XMC_DAC_CH_Init( (XMC_DAC_t *const) p_config_l->p_module_context, (unsigned char)p_control_l->state.channel,
								(const XMC_DAC_CH_CONFIG_t *const)p_config_l->p_config  );

			if( 0 == p_control_l->state.valid )
			{
				/* Set mode of channel */
				XMC_DAC_CH_SetMode( (XMC_DAC_t *const) p_config_l->p_module_context, (unsigned char)p_control_l->state.channel,
										p_config_l->channel_mode );
				/* Set Trigger */
				XMC_DAC_CH_SetTrigger( (XMC_DAC_t *const) p_config_l->p_module_context, (unsigned char)p_control_l->state.channel,
										p_config_l->channel_trigger );
				/* Enable Events */
				XMC_DAC_CH_EnableEvent( (XMC_DAC_t *const) p_config_l->p_module_context, (unsigned char)p_control_l->state.channel );
			}

			/* Set Frequency */
			ret_status = XMC_DAC_CH_SetFrequency( (XMC_DAC_t *const) p_config_l->p_module_context,
								(unsigned char)p_control_l->state.channel, p_config_l->frequency );
			/* Check status */
			if( XMC_DAC_CH_STATUS_OK == ret_status )
			{
				/* Start Data Mode */
				XMC_DAC_CH_StartNoiseMode( (XMC_DAC_t *const) p_config_l->p_module_context, (unsigned char)p_control_l->state.channel,
											p_config_l->channel_trigger, p_config_l->frequency );
				/* Update parameters */
				p_control_l->state.init = (XMC_DAC_CH_STATUS_OK == ret_status) ? 1 : 0;
				/* Update return status */
				ret_status = (1 == p_control_l->state.init) ? DAC_STATUS_SUCCESS : DAC_STATUS_FAILED;
				p_control_l->state.valid = 1;
			}
			else
			{
				p_control_l->state.init = 0;
				ret_status = DAC_STATUS_FAILED;
			}
		}
		break;

		/* Ramp mode - ramp generation */
		case 5:
			/* Not considered for now */
			ret_status = DAC_STATUS_INVALID_ARGUMENT;
		break;

		default:
			ret_status = DAC_STATUS_INVALID_ARGUMENT;
	}

	/* Return status */
	return ret_status;
}


/**
 * @function
 *
 * @brief
 *
 * @param[in]
 *
 * \par<b>Description:</b><br>
 *
 * <i>Imp Note:</i>
 *
 */
long dac_deinitalize_channel( void * p_channel,
	const unsigned char channel, const unsigned char mode )
{
	/* Local Variables */
	long ret_status = DAC_STATUS_FAILED;

	/* Check mode of operation */
	switch( mode )
	{	/* Idel mode */
		case 0:
			/* Not considered for now */
			ret_status = DAC_STATUS_INVALID_ARGUMENT;
		break;

		/* Single value mode - single data value is updated and maintained */
		case 1:
			/* Not considered for now */
			ret_status = DAC_STATUS_INVALID_ARGUMENT;
		break;

		/* Data mode - continuous data processing */
		case 2:
		{
			tStDAC_DataProcessingConfiguartion * p_config_l = ((tStDAC_DataProcessing *)p_channel)->p_config;
			tStDAC_Control * p_control_l = ((tStDAC_DataProcessing *)p_channel)->p_control;

			/* Disable DAC Channel */
			XMC_DAC_CH_DisableOutput( (XMC_DAC_t *const) p_config_l->p_module_context, (unsigned char)p_control_l->state.channel );

			/* Update parameters */
			p_control_l->state.init = 0;
			ret_status = DAC_STATUS_SUCCESS;
		}
		break;

		/* Pattern mode - inbuilt pattern waveform generation - Sine, Triangle, Rectangle */
		case 3:
			/* Not considered for now */
			ret_status = DAC_STATUS_INVALID_ARGUMENT;
		break;

		/* Noise mode - pseudo-random noise generation */
		case 4:
		{
			tStDAC_NoiseGeneratorConfiguartion * p_config_l = ((tStDAC_NoiseGenerator *)p_channel)->p_config;
			tStDAC_Control * p_control_l = ((tStDAC_DataProcessing *)p_channel)->p_control;

			/* Disable DAC Channel */
			XMC_DAC_CH_DisableOutput( (XMC_DAC_t *const) p_config_l->p_module_context, (unsigned char)p_control_l->state.channel );

			/* Update parameters */
			p_control_l->state.init = 0;
			ret_status = DAC_STATUS_SUCCESS;
		}
		break;

		/* Ramp mode - ramp generation */
		case 5:
			/* Not considered for now */
			ret_status = DAC_STATUS_INVALID_ARGUMENT;
		break;

		default:
			ret_status = DAC_STATUS_INVALID_ARGUMENT;
	}

	/* Return status */
	return ret_status;
}


/********************************** End of File *******************************/
