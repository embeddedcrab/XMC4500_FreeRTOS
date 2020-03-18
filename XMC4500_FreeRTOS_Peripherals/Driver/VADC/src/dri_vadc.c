/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		VADC API Source
* Filename:		dri_vadc.c
* Author:		HS
* Origin Date:	01/29/2020
* Version:		1.0.0
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	dri_vadc.c
 *  @brief:	This header file contains API function definitions for VADC
 */


/******************************************************************************
* Includes
*******************************************************************************/
#include <dri_vadc.h>


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

/* If Group available */
#if( VADC_GROUP0_USED == 1U )
/* Change the data type according to ADC Resolution */
volatile unsigned short VADC_Group0_Channels[VADC_GROUP0_CHANNELS_USED];
#endif

#if( VADC_GROUP1_USED == 1U )
volatile unsigned short VADC_Group1_Channels[VADC_GROUP1_CHANNELS_USED];
#endif

#if( VADC_GROUP2_USED == 1U )
volatile unsigned short VADC_Group2_Channels[VADC_GROUP2_CHANNELS_USED];
#endif

#if( VADC_GROUP3_USED == 1U )
volatile unsigned short VADC_Group3_Channels[VADC_GROUP3_CHANNELS_USED];
#endif


/******************************************************************************
* Private Function Declarations
*******************************************************************************/


/******************************************************************************
* Public Function Definitions
*******************************************************************************/

/**
 * @function	VADC_background_request_init
 *
 * @brief		Initialization function for VADC Background Group
 *
 * <i>Imp Note:</i>
 *
 */
long VADC_background_request_init( void * p_group, const unsigned char group, const unsigned char init )
{
	DRIVER_ASSERT( NULL== p_group, VADC_STATUS_FAILED );
	/* Local Variables */
	tStVADC_BackgroundScanConfiguartion * const p_group_config_l = ((tStVADC_BackgroundScan *)p_group)->p_config;
	tStVADC_Control * const p_control_l = ((tStVADC_BackgroundScan *)p_group)->p_control;
	eVADC_Status ret_status = VADC_STATUS_FAILED;
	unsigned char count_l  = 0;

	/* Check input argument */
	switch( init )
	{	/* Open VADC Channel */
		case VADC_INIT_OPEN:
			/* Check for initialization */
			if( 1 == p_control_l->state.init )
			{
				/* Update return status */
				ret_status = VADC_STATUS_ALREADY_INITIALIZED;
			}
			else
			{
				/* Initialize Group, Set power modes */
				XMC_VADC_GROUP_Init( (XMC_VADC_GROUP_t *)p_group_config_l->p_background_scan_group_config->p_group_context,
								(const XMC_VADC_GROUP_CONFIG_t *) &(p_group_config_l->p_background_scan_group_config->group_config) );

				XMC_VADC_GROUP_SetPowerMode( (XMC_VADC_GROUP_t *)p_group_config_l->p_background_scan_group_config->p_group_context,
											XMC_VADC_GROUP_POWERMODE_NORMAL );

				/* Initialize Group Channels */
				for( count_l = 0; count_l < p_group_config_l->group_channels; ++count_l )
				{
					XMC_VADC_GROUP_ChannelInit( (XMC_VADC_GROUP_t *)p_group_config_l->p_background_scan_group_config->p_group_context,
							count_l, (const XMC_VADC_CHANNEL_CONFIG_t *) &(p_group_config_l->p_channel_config[count_l].channel_config));

					XMC_VADC_GROUP_ResultInit( (XMC_VADC_GROUP_t *)p_group_config_l->p_background_scan_group_config->p_group_context,
							p_group_config_l->p_channel_config[count_l].channel_config.result_reg_number,
							(const XMC_VADC_RESULT_CONFIG_t *) &(p_group_config_l->p_channel_config[count_l].result_config) );

					/* Channel Configuration or Background Scanning */
					XMC_VADC_GLOBAL_BackgroundAddChannelToSequence( GLOBAL_VADC, group, count_l );
				}

				/* NVIC Settings */
				#if( (VADC_BACKGROUND_REQUEST_SOURCE == 1U) && (VADC_INTERRUPT_USED == 1U) )
				/* Set NVIC priority */
				NVIC_SetPriority( (IRQn_Type) p_group_config_l->p_background_scan_group_config->group_isr_config.irq.irq_num,
						NVIC_EncodePriority(NVIC_GetPriorityGrouping(),
								p_group_config_l->p_background_scan_group_config->group_isr_config.irq.irq_priority, 0U) );
				XMC_VADC_GLOBAL_BackgroundSetReqSrcEventInterruptNode( GLOBAL_VADC,
						(XMC_VADC_SR_t)p_group_config_l->p_background_scan_group_config->group_isr_config.sr );
				/* Enable NVIC */
				NVIC_EnableIRQ( (IRQn_Type) p_group_config_l->p_background_scan_group_config->group_isr_config.irq.irq_num );
				#endif	/* VADC_BACKGROUND_REQUEST_SOURCE && VADC_INTERRUPT_USED */

				/* Set initialize state */
				p_control_l->state.init = 1;
				/* Update return status */
				ret_status = VADC_STATUS_SUCCESS;
			}
			break;
		/* Close VADC Channel */
		case VADC_INIT_CLOSE:
			/* Set initialize state, not needed though */
			p_control_l->state.init = 0;
			/* Update return status */
			ret_status = VADC_STATUS_SUCCESS;
			break;
		/* Default parameters, invalid argument */
		default:
			/* Update return status */
			ret_status = VADC_STATUS_INVALID_ARGUMENT;
			break;
	}

	/* Return status */
	return ret_status;
}


/**
 * @function	VADC_background_scan_start_conversion
 *
 * @brief		Start conversion for VADC channels
 *
 * <i>Imp Note:</i>
 *
 */
void VADC_background_scan_start_conversion( void * p_context )
{
	/* Trigger conversion for group in Background Request Scan mode */
	XMC_VADC_GLOBAL_BackgroundTriggerConversion( (XMC_VADC_GLOBAL_t *)p_context );
}


/******************************************************************************
* Private Function Definitions
*******************************************************************************/

/**
 * @function	global_init
 *
 * @brief		Initialize Global VADC
 *
 * @param[in]	NA
 *
 * \par<b>Description:</b><br>
 *
 * <i>Imp Note:</i>
 *
 */
void VADC_global_init( void * p_global_channel )
{
	DRIVER_ASSERT_NRET( NULL == p_global_channel );
	/* Local variables */
	tStVADC_GlobalConfiguartion * const p_config_l = (tStVADC_GlobalConfiguartion *)p_global_channel;

	/* Initialize VADC Global */
	XMC_VADC_GLOBAL_Init( (XMC_VADC_GLOBAL_t *)(p_config_l->p_channel_context),
				(const XMC_VADC_GLOBAL_CONFIG_t *) &p_config_l->global_config );

	#if(VADC_STARTUP_CALIBRATION == 1U)
	/* Initialize Global Startup Calibration */
	XMC_VADC_GLOBAL_StartupCalibration( (XMC_VADC_GLOBAL_t *)(p_config_l->p_channel_context) );
	#endif	/* VADC_STARTUP_CALIBRATION */

	#if( (VADC_CHANNEL_BACKGROUND_REQUEST_SOURCE == 1U) || (VADC_BACKGROUND_REQUEST_SOURCE == 1U) )
	/* Initialize Background Configuration */
	XMC_VADC_GLOBAL_BackgroundInit( (XMC_VADC_GLOBAL_t *)(p_config_l->p_channel_context),
										(const XMC_VADC_BACKGROUND_CONFIG_t *) p_config_l->p_background_config );
	#endif
}


/**
 * @function	VADC_get_group
 *
 * @brief		Get VADC Group number using Context information
 *
 * @param[in]	NA
 *
 * \par<b>Description:</b><br>
 *
 * <i>Imp Note:</i>
 *
 */
unsigned char VADC_get_group( void * p_context )
{
	/* Local variables */
	XMC_VADC_GROUP_t * p_group_l = (XMC_VADC_GROUP_t *) p_context;
	unsigned char group_l = 0;

	/* Check for group and update group number */
	if( VADC_G0 == p_group_l )
	{ /* Do Nothing */ }
	else if( VADC_G1 == p_group_l )
	{ group_l = 1; }
	else if( VADC_G2 == p_group_l )
	{ group_l = 2; }
	else if( VADC_G3 == p_group_l )
	{ group_l = 3; }

	return group_l;
}


/******* ISR entries for VADC *******/


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
#ifdef VADC_INTERRUPT_USED
#if( VADC_BACKGROUND_REQUEST_SOURCE == 1U )
/* ISR entry function for VADC */
void VADC_isr_entry( void * p_group, const unsigned char group );
void VADC_isr_entry( void * p_group, const unsigned char group )
{
	/* Local variables */
	tStVADC_BackgroundScan * const p_config_l = (tStVADC_BackgroundScan *)p_group;
	static unsigned char xcount = 0;

	/* Check group number of VADC */
	switch( group )
	{
	default:
		#if( VADC_GROUP0_USED == 1U )
		/* Group Number 0 */
		case 0:
			/* Loop and get the results */
			for( xcount = 0; xcount < VADC_GROUP0_CHANNELS_USED; ++xcount )
			{
				VADC_Group0_Channels[xcount] = XMC_VADC_GROUP_GetResult(
												(XMC_VADC_GROUP_t *)p_config_l->p_config->p_background_scan_group_config->p_group_context,
												xcount );
			}
			#if( VADC_CALLBACK_HANDLER_USED == 1U )
			if( p_config_l->p_callback->fp_callback != NULL )
			{
				p_config_l->p_callback->fp_callback( p_group, (unsigned short *)VADC_Group0_Channels );
			}
			#endif
		break;
		#endif
		#if( VADC_GROUP1_USED == 1U )
		/* Group Number 1 */
		case 1:
			/* Loop and get the results */
			for( xcount = 0; xcount < VADC_GROUP1_CHANNELS_USED; ++xcount )
			{
				VADC_Group0_Channels[xcount] = XMC_VADC_GROUP_GetResult(
												(XMC_VADC_GROUP_t *)p_config_l->p_background_scan_config[1]->p_channel_context,
												xcount );
			}
		break;
		#endif
		#if( VADC_GROUP2_USED == 1U )
		/* Group Number 2 */
		case 2:
			/* Loop and get the results */
			for( xcount = 0; xcount < VADC_GROUP2_CHANNELS_USED; ++xcount )
			{
				VADC_Group0_Channels[xcount] = XMC_VADC_GROUP_GetResult(
												(XMC_VADC_GROUP_t *)p_config_l->p_background_scan_config[2]->p_channel_context,
												xcount );
			}
		break;
		#endif
		#if( VADC_GROUP3_USED == 1U )
		/* Group Number 3 */
		case 3:
			/* Loop and get the results */
			for( xcount = 0; xcount < VADC_GROUP3_CHANNELS_USED; ++xcount )
			{
				VADC_Group0_Channels[xcount] = XMC_VADC_GROUP_GetResult(
												(XMC_VADC_GROUP_t *)p_config_l->p_background_scan_config[3]->p_channel_context,
												xcount );
			}
		break;
		#endif
	}
}
#endif
#endif


/********************************** End of File *******************************/
