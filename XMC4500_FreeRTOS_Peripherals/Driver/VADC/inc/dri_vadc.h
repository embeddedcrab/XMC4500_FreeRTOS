/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		VADC API Header
* Filename:		dri_vadc.h
* Author:		HS
* Origin Date:	01/29/2020
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	dri_vadc.h
 *  @brief:	This file contains API function declarations for VADC
 */
#ifndef DRI_VADC_H_
#define DRI_VADC_H_


/******************************************************************************
* Includes
*******************************************************************************/
#include <dri_vadc_types.h>


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

#if( VADC_GROUP0_USED == 1U )
/* Change the data type according to ADC Resolution */
extern volatile unsigned short VADC_Group0_Channels[VADC_GROUP0_CHANNELS_USED];
#endif

#if( VADC_GROUP1_USED == 1U )
extern volatile unsigned short VADC_Group1_Channels[VADC_GROUP0_CHANNELS_USED];
#endif

#if( VADC_GROUP2_USED == 1U )
extern volatile unsigned short VADC_Group2_Channels[VADC_GROUP0_CHANNELS_USED];
#endif

#if( VADC_GROUP3_USED == 1U )
extern volatile unsigned short VADC_Group3_Channels[VADC_GROUP0_CHANNELS_USED];
#endif


/******************************************************************************
* Function Prototypes
*******************************************************************************/


/******************************************************************************
 *
 * @brief	VADC Instance for Background Scanning
 *
 * \par<b>Description:</b><br>:
 * 			This used for Background scanning of VADC.
 * 			It uses shared ISR lines for IRQ processing.
 *
 ******************************************************************************/
/******************************************************************************
 *
 * @brief	API Member functions
 *
 ******************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @function	VADC_init
 *
 * @brief		Initialization functionality for VADC
 *
 * @param[in]
 *
 * @param[out]	NA
 *
 * @return  	eVADC_Status_
 *
 * \par<b>Description:</b><br>
 * 				This function will initialize VADC
 *
 * <i>Imp Note:</i>
 *
 */
void VADC_global_init( void * p_global_channel );


/**
 * @function	VADC_init
 *
 * @brief		Initialization functionality for VADC
 *
 * @param[in]
 *
 * @param[out]	NA
 *
 * @return  	eVADC_Status_
 *
 * \par<b>Description:</b><br>
 * 				This function will initialize VADC
 *
 * <i>Imp Note:</i>
 *
 */
long VADC_background_request_init( void * p_group, const unsigned char group, const unsigned char init );


/**
 * @function	VADC_background_scan_start_conversion
 *
 * @brief		Start Background conversion for VADC Group
 *
 * \par<b>Description:</b><br>
 *
 */
void VADC_background_scan_start_conversion( void * p_context );


/**
 * @function	VADC_background_scan_start_conversion
 *
 * @brief		Start Background conversion for VADC Group
 *
 * \par<b>Description:</b><br>
 *
 */
unsigned char VADC_get_group( void * p_context );


#ifdef __cplusplus
}
#endif


#endif	/* DRI_VADC_H_ */

/********************************** End of File *******************************/
