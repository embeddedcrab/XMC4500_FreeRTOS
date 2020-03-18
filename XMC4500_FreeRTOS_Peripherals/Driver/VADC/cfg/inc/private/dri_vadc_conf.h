/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		VADC Configuration Header
* Filename:		dri_vadc_conf.h
* Author:		HS
* Origin Date:	01/29/2020
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	dri_vadc_conf.h
 *  @brief:	This file contains configurations for VADC
 */
#ifndef DRI_VADC_CONF_H_
#define DRI_VADC_CONF_H_


/******************************************************************************
* Includes
*******************************************************************************/


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

#define VADC_INTERRUPT_USED				1U
#define VADC_DMA_USED					0U

/* Callback Handler */
#define VADC_CALLBACK_HANDLER_USED		1U


/** Type of ADC Conversion operation **/
#define VADC_BACKGROUND_REQUEST_SOURCE	1U

#define VADC_SCAN_REQUEST_CONVERSION	0U
#define VADC_QUEUE_REQUEST_SOURCE		0U


/******************************************************************************
* Configuration Constants
*******************************************************************************/

#define GLOBAL_VADC						VADC

/* Startup calibration flag */
#define VADC_STARTUP_CALIBRATION		1U

/* Groups used in project */
#if(XMC_VADC_GROUP_AVAILABLE == 1U)
#define VADC_GROUPS_USED				1U
#endif
/* Group Check */
#if (VADC_GROUPS_USED > XMC_VADC_MAXIMUM_NUM_GROUPS)
#error "Groups Number Exceeded!!"
#endif


/* Group Configurations */
#if( VADC_GROUPS_USED > 0U )

/* Group ad Channel configurations(separately) */
#define VADC_GROUP0_USED				1U
#define VADC_GROUP0_CHANNELS_USED		8U

#define VADC_GROUP1_USED				0U
#define VADC_GROUP1_CHANNELS_USED		0U
#define VADC_GROUP2_USED				0U
#define VADC_GROUP2_CHANNELS_USED		0U
#define VADC_GROUP3_USED				0U
#define VADC_GROUP3_CHANNELS_USED		0U

#endif


/******************************************************************************
* Macros
*******************************************************************************/

/* VADC Handlers */
#ifdef VADC_INTERRUPT_USED

#if( VADC_CHANNEL_BACKGROUND_REQUEST_SOURCE == 1U )

#if( VADC_GROUP0_CHANNEL0_USED == 1U )
#define VADC_Group0_Channel0_Handler	IRQ_Hdlr_18
#endif

/* Using Background Request Source for VADC Interrupt processing */
#elif( VADC_BACKGROUND_REQUEST_SOURCE == 1U )
#if( VADC_GROUP0_USED == 1U )
#define VADC_Group0_Handler		IRQ_Hdlr_14
#endif
#if( VADC_GROUP1_USED == 1U )
#define VADC_Group0_Handler		IRQ_Hdlr_15
#endif
#if( VADC_GROUP2_USED == 1U )
#define VADC_Group0_Handler		IRQ_Hdlr_16
#endif
#if( VADC_GROUP3_USED == 1U )
#define VADC_Group0_Handler		IRQ_Hdlr_17
#endif
#endif

#endif	/* VADC_INTERRUPT_USED */


#endif /* DRI_VADC_CONF_H_ */

/********************************** End of File ******************************/
