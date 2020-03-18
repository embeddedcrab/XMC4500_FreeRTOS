/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		CCU API Source
* Filename:		dri_ccu.c
* Author:		HS
* Origin Date:	02/14/2020
* Version:		1.0.0
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	dri_ccu.c
 *  @brief:	This header file contains API function definitions for CCU
 */


/******************************************************************************
* Includes
*******************************************************************************/
#include <dri_ccu.h>


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

static XMC_CCU4_MODULE_t * ccu4_get_module( const unsigned long module );
static XMC_CCU8_MODULE_t * ccu8_get_module( const unsigned long module );


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
long CCU4_module_init( void * p_module, const unsigned char init )
{
	DRIVER_ASSERT( NULL == p_module, CCU_STATUS_INVALID_ARGUMENT );
	/* Local Variables */
	tStCCU4_ModuleConfiguartion * const p_config_l = ((tStCCU4_Module *)p_module)->p_module_config;
	eCCU_Status ret_status = CCU_STATUS_SUCCESS;

	/* Check initialization */
	switch( init )
	{	/* Open CCU channel */
		case CCU_INIT_OPEN:
			/* Initialize Module */
			XMC_CCU4_Init( (XMC_CCU4_MODULE_t *const) p_config_l->p_module_context, p_config_l->module_transfer_request );
			/* Start prescaler and restore clocks to slices */
			XMC_CCU4_StartPrescaler( (XMC_CCU4_MODULE_t *const) p_config_l->p_module_context );
			/* Ensure Fccu reaches CCU40 */
			XMC_CCU4_SetModuleClock( (XMC_CCU4_MODULE_t *const) p_config_l->p_module_context, p_config_l->module_clock );
			break;

		case CCU_INIT_CLOSE:
			XMC_CCU4_EnableModule( (XMC_CCU4_MODULE_t *const) p_config_l->p_module_context );
			XMC_SCU_CLOCK_DisableClock( XMC_SCU_CLOCK_CCU );
			break;

		default:
			ret_status = CCU_STATUS_INVALID_ARGUMENT;
	}

	/* Return status */
	return ret_status;
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 *
 */
long CCU4_compare_channel_init( void * p_channel, const unsigned char module, const unsigned char slice,
								const unsigned char init )
{
	DRIVER_ASSERT( NULL == p_channel, CCU_STATUS_INVALID_ARGUMENT );
	/* Local Variables */
	tStCCU4_SliceCompareConfiguartion * const p_config_l = ((tStCCU4_Compare *)p_channel)->p_config;
	tStCCU4_Control * const p_control_l = ((tStCCU4_Compare *)p_channel)->p_control;
	eCCU_Status ret_status = CCU_STATUS_SUCCESS;

	/* Check input argument */
	switch( init )
	{	/* Open CCU4 Channel */
		case CCU_INIT_OPEN:
			/* Check for initialization */
			if( 1 == p_control_l->state.init )
			{
				/* Update return status */
				ret_status = CCU_STATUS_ALREADY_INITIALIZED;
			}
			else
			{
				/* Update module and slice number */
				p_control_l->state.module_num = module;
				p_control_l->state.slice_num = slice;
				/* Initialize compare slice */
				XMC_CCU4_SLICE_CompareInit( (XMC_CCU4_SLICE_t *const) p_config_l->p_slice_context,
				                                p_config_l->p_config);
				/* Enable shadow transfer */
				XMC_CCU4_EnableShadowTransfer( ccu4_get_module( p_control_l->state.module_num ),
												p_config_l->shadow_transfer );

				/* Configure events for Compare */
				XMC_CCU4_SLICE_ConfigureEvent( (XMC_CCU4_SLICE_t *const) p_config_l->p_slice_context,
												p_config_l->event, p_config_l->p_event_config );

				XMC_CCU4_SLICE_StartConfig( (XMC_CCU4_SLICE_t *const) p_config_l->p_slice_context,
											p_config_l->event, p_config_l->start_mode );

				/* Initialize compare parameters */
				XMC_CCU4_SLICE_SetTimerPeriodMatch( (XMC_CCU4_SLICE_t *const) p_config_l->p_slice_context,
													p_config_l->period );
				XMC_CCU4_SLICE_SetTimerCompareMatch( (XMC_CCU4_SLICE_t *const) p_config_l->p_slice_context,
													p_config_l->compare );

				/* Enable slice event */
				XMC_CCU4_SLICE_EnableEvent( (XMC_CCU4_SLICE_t *const) p_config_l->p_slice_context,
											p_config_l->interrupt_event );
				/* Connect event to SR */
				XMC_CCU4_SLICE_SetInterruptNode( (XMC_CCU4_SLICE_t *const) p_config_l->p_slice_context,
													p_config_l->interrupt_event, p_config_l->p_irq_config->sr );

				/* Setup NVIC priority */
				NVIC_SetPriority( (IRQn_Type)p_config_l->p_irq_config->irq.irq_num,
					NVIC_EncodePriority(NVIC_GetPriorityGrouping(), p_config_l->p_irq_config->irq.irq_priority, 0U) );
				/* Enable NVIC */
				NVIC_EnableIRQ( (IRQn_Type)p_config_l->p_irq_config->irq.irq_num );

				/* Get Slice out of Idle mode */
				XMC_CCU4_EnableClock( ccu4_get_module( p_control_l->state.module_num ), p_control_l->state.slice_num );

				/* Set initialize state */
				p_control_l->state.init = 1;
				/* Update return status */
				ret_status = CCU_STATUS_SUCCESS;
			}
			break;
		/* Close CCU4 Channel */
		case CCU_INIT_CLOSE:
			/* Disable Clock */
			XMC_CCU4_DisableClock( ccu4_get_module( p_control_l->state.module_num ), p_control_l->state.slice_num );
			/* Set initialize state, not needed though */
			p_control_l->state.init = 0;
			/* Update return status */
			ret_status = CCU_STATUS_SUCCESS;
			break;
		/* Default parameters, invalid argument */
		default:
			/* Update return status */
			ret_status = CCU_STATUS_INVALID_ARGUMENT;
			break;
	}

	/* Return status */
	return ret_status;
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 *
 */
long CCU4_capture_channel_init( void * p_channel, const unsigned char module, const unsigned char slice,
								const unsigned char init )
{
	DRIVER_ASSERT( NULL == p_channel, CCU_STATUS_INVALID_ARGUMENT );
	/* Local Variables */
	tStCCU4_SliceCaptureConfiguartion * const p_config_l = ((tStCCU4_Capture *)p_channel)->p_config;
	tStCCU4_Control * const p_control_l = ((tStCCU4_Capture *)p_channel)->p_control;
	eCCU_Status ret_status = CCU_STATUS_SUCCESS;

	/* Check input argument */
	switch( init )
	{	/* Open CCU4 Channel */
		case CCU_INIT_OPEN:
			/* Check for initialization */
			if( 1 == p_control_l->state.init )
			{
				/* Update return status */
				ret_status = CCU_STATUS_ALREADY_INITIALIZED;
			}
			else
			{
				/* Update module and slice number */
				p_control_l->state.module_num = module;
				p_control_l->state.slice_num = slice;
				/* Initialize Capture slice */
				XMC_CCU4_SLICE_CaptureInit( (XMC_CCU4_SLICE_t *const) p_config_l->p_slice_context,
				                                p_config_l->p_config);

				/* Configure events for Capture */
				XMC_CCU4_SLICE_Capture0Config( (XMC_CCU4_SLICE_t *const) p_config_l->p_slice_context,
												p_config_l->event0 );
				XMC_CCU4_SLICE_Capture1Config( (XMC_CCU4_SLICE_t *const) p_config_l->p_slice_context,
												p_config_l->event1 );

				XMC_CCU4_SLICE_ConfigureEvent( (XMC_CCU4_SLICE_t *const) p_config_l->p_slice_context,
												p_config_l->event0, p_config_l->p_event_config_off );
				XMC_CCU4_SLICE_ConfigureEvent( (XMC_CCU4_SLICE_t *const) p_config_l->p_slice_context,
												p_config_l->event1, p_config_l->p_event_config_on );

				/* Initialize capture parameters */
				p_config_l->period = 0;
				p_config_l->duty_cycle = 0;

				/* Enable slice event */
				XMC_CCU4_SLICE_EnableEvent( (XMC_CCU4_SLICE_t *const) p_config_l->p_slice_context,
											p_config_l->interrupt_event );
				/* Connect event to SR */
				XMC_CCU4_SLICE_SetInterruptNode( (XMC_CCU4_SLICE_t *const) p_config_l->p_slice_context,
													p_config_l->interrupt_event, p_config_l->p_irq_config->sr );

				/* Setup NVIC priority */
				NVIC_SetPriority( (IRQn_Type)p_config_l->p_irq_config->irq.irq_num,
					NVIC_EncodePriority(NVIC_GetPriorityGrouping(), p_config_l->p_irq_config->irq.irq_priority, 0U) );
				/* Enable NVIC */
				NVIC_EnableIRQ( (IRQn_Type)p_config_l->p_irq_config->irq.irq_num );

				/* Get Slice out of Idle mode */
				XMC_CCU4_EnableClock( ccu4_get_module( p_control_l->state.module_num ), p_control_l->state.slice_num );

				/* Set initialize state */
				p_control_l->state.init = 1;
				/* Update return status */
				ret_status = CCU_STATUS_SUCCESS;
			}
			break;
		/* Close CCU4 Channel */
		case CCU_INIT_CLOSE:
			/* Disable Clock */
			XMC_CCU4_DisableClock( ccu4_get_module( p_control_l->state.module_num ), p_control_l->state.slice_num );
			/* Set initialize state, not needed though */
			p_control_l->state.init = 0;
			/* Update return status */
			ret_status = CCU_STATUS_SUCCESS;
			break;
		/* Default parameters, invalid argument */
		default:
			/* Update return status */
			ret_status = CCU_STATUS_INVALID_ARGUMENT;
			break;
	}

	/* Return status */
	return ret_status;
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 * XMC_SCU_SetCcuTriggerLow( XMC_SCU_CCU_TRIGGER_CCU40 )
 * XMC_SCU_SetCcuTriggerHigh( XMC_SCU_CCU_TRIGGER_CCU40 )
 */
void CCU4_channel_timer_control( void * p_channel, const unsigned char start )
{
	DRIVER_ASSERT_NRET( NULL == p_channel );

	/* Check input arguments */
	switch( start )
	{
	default:
	case 0:
		XMC_CCU4_SLICE_StopTimer( (XMC_CCU4_SLICE_t *const) p_channel );
		break;
	case 1:
		XMC_CCU4_SLICE_StartTimer( (XMC_CCU4_SLICE_t *const) p_channel );
		break;
	}
}


/*****************************************************************************/

/*****************************************************************************/


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 *
 */
long CCU8_module_init( void * p_module )
{
	DRIVER_ASSERT( NULL == p_module, CCU_STATUS_INVALID_ARGUMENT );
	/* Local Variables */
	tStCCU8_ModuleConfiguartion * const p_config_l = ((tStCCU8_Module *)p_module)->p_module_config;
	eCCU_Status ret_status = CCU_STATUS_SUCCESS;

	/* Initialize Module */
	XMC_CCU8_Init( (XMC_CCU8_MODULE_t *const) p_config_l->p_module_context, p_config_l->module_transfer_request );
	/* Start prescaler and restore clocks to slices */
	XMC_CCU8_StartPrescaler( (XMC_CCU8_MODULE_t *const) p_config_l->p_module_context );
	/* Ensure Fccu reaches CCU40 */
	XMC_CCU8_SetModuleClock( (XMC_CCU8_MODULE_t *const) p_config_l->p_module_context, p_config_l->module_clock );

	/* Return status */
	return ret_status;
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 *
 */
long CCU8_compare_channel_init( void * p_channel, const unsigned char module, const unsigned char slice,
								const unsigned char init )
{
	DRIVER_ASSERT( NULL == p_channel, CCU_STATUS_INVALID_ARGUMENT );
	/* Local Variables */
	tStCCU8_SliceCompareConfiguartion * const p_config_l = ((tStCCU8_Compare *)p_channel)->p_config;
	tStCCU8_Control * const p_control_l = ((tStCCU8_Compare *)p_channel)->p_control;
	eCCU_Status ret_status = CCU_STATUS_SUCCESS;

	/* Check input argument */
	switch( init )
	{	/* Open CCU8 Channel */
		case CCU_INIT_OPEN:
			/* Check for initialization */
			if( 1 == p_control_l->state.init )
			{
				/* Update return status */
				ret_status = CCU_STATUS_ALREADY_INITIALIZED;
			}
			else
			{
				/* Update module and slice number */
				p_control_l->state.module_num = module;
				p_control_l->state.slice_num = slice;
				/* Initialize compare slice */
				XMC_CCU8_SLICE_CompareInit( (XMC_CCU8_SLICE_t *const) p_config_l->p_slice_context,
				                                p_config_l->p_config);
				/* Enable shadow transfer */
				XMC_CCU8_EnableShadowTransfer( ccu8_get_module( p_control_l->state.module_num ),
												p_config_l->shadow_transfer );

				/* Configure events for Compare */
				XMC_CCU8_SLICE_ConfigureEvent( (XMC_CCU8_SLICE_t *const) p_config_l->p_slice_context,
												p_config_l->event, p_config_l->p_event_config );

				XMC_CCU8_SLICE_StartConfig( (XMC_CCU8_SLICE_t *const) p_config_l->p_slice_context,
											p_config_l->event, p_config_l->start_mode );

				/* Initialize compare parameters */
				XMC_CCU8_SLICE_SetTimerPeriodMatch( (XMC_CCU8_SLICE_t *const) p_config_l->p_slice_context,
													p_config_l->period );
				XMC_CCU8_SLICE_SetTimerCompareMatch( (XMC_CCU8_SLICE_t *const) p_config_l->p_slice_context,
													p_config_l->compare_channel, p_config_l->compare );

				/* Init Dead Time */
				XMC_CCU8_SLICE_DeadTimeInit( (XMC_CCU8_SLICE_t *const) p_config_l->p_slice_context,
											p_config_l->p_dead_time_config );

				/* Enable slice event */
				XMC_CCU8_SLICE_EnableEvent( (XMC_CCU8_SLICE_t *const) p_config_l->p_slice_context,
											p_config_l->interrupt_event );
				/* Connect event to SR */
				XMC_CCU8_SLICE_SetInterruptNode( (XMC_CCU8_SLICE_t *const) p_config_l->p_slice_context,
													p_config_l->interrupt_event, p_config_l->p_irq_config->sr );

				/* Setup NVIC priority */
				NVIC_SetPriority( (IRQn_Type)p_config_l->p_irq_config->irq.irq_num,
					NVIC_EncodePriority(NVIC_GetPriorityGrouping(), p_config_l->p_irq_config->irq.irq_priority, 0U) );
				/* Enable NVIC */
				NVIC_EnableIRQ( (IRQn_Type)p_config_l->p_irq_config->irq.irq_num );

				/* Get Slice out of Idle mode */
				XMC_CCU8_EnableClock( ccu8_get_module( p_control_l->state.module_num ), p_control_l->state.slice_num );

				/* Set initialize state */
				p_control_l->state.init = 1;
				/* Update return status */
				ret_status = CCU_STATUS_SUCCESS;
			}
			break;
		/* Close CCU8 Channel */
		case CCU_INIT_CLOSE:
			/* Disable Clock */
			XMC_CCU8_DisableClock( ccu8_get_module( p_control_l->state.module_num ), p_control_l->state.slice_num );
			/* Set initialize state, not needed though */
			p_control_l->state.init = 0;
			/* Update return status */
			ret_status = CCU_STATUS_SUCCESS;
			break;
		/* Default parameters, invalid argument */
		default:
			/* Update return status */
			ret_status = CCU_STATUS_INVALID_ARGUMENT;
			break;
	}

	/* Return status */
	return ret_status;
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 *	XMC_SCU_SetCcuTriggerHigh(XMC_SCU_CCU_TRIGGER_CCU80)
 *	XMC_SCU_SetCcuTriggerLow(XMC_SCU_CCU_TRIGGER_CCU80)
 */
void CCU8_channel_timer_control( void * p_channel, const unsigned char start )
{
	DRIVER_ASSERT_NRET( NULL == p_channel );

	/* Check input arguments */
	switch( start )
	{
	default:
	case 0:
		XMC_CCU8_SLICE_StopTimer( (XMC_CCU8_SLICE_t *const) p_channel );
		break;
	case 1:
		XMC_CCU8_SLICE_StartTimer( (XMC_CCU8_SLICE_t *const) p_channel );
		break;
	}
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
XMC_CCU4_MODULE_t * ccu4_get_module( const unsigned long module )
{
	/* Local variables */
	XMC_CCU4_MODULE_t * module_l = CCU40;

	/* Check module number */
	switch( module )
	{
	default:
	case 0:
		break;
	case 1:
		module_l = CCU41;
		break;
	case 2:
		module_l = CCU42;
		break;
	case 3:
		module_l = CCU43;
		break;
	}

	/* Return module */
	return module_l;
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
XMC_CCU8_MODULE_t * ccu8_get_module( const unsigned long module )
{
	/* Local variables */
	XMC_CCU8_MODULE_t * module_l = CCU80;

	/* Check module number */
	switch( module )
	{
	default:
	case 0:
		break;
	case 1:
		module_l = CCU81;
		break;
	}

	/* Return module */
	return module_l;
}


/********************************** End of File *******************************/
