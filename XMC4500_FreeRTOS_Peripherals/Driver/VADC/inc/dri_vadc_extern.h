/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		VADC Extern Header
* Filename:		dri_vadc_extern.h
* Author:		HS
* Origin Date:	01/29/2020
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	dri_vadc_extern.h
 *  @brief:	This file contains extern variable for VADC and VADC API header
 */
#ifndef DRI_VADC_EXTERN_H_
#define DRI_VADC_EXTERN_H_


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

/*
 * @brief	API functions Instance for VADC
 */
extern tStVADC_BackgroundScan_Api VADC_BackgroundScan_Api_Functions;

/*
 * @brief	Instances for VADC
 */
extern tStVADC_GlobalConfiguartion VADC_Global_Configuration;

extern tStVADC_Background VADC_BackgroundScan_Handle;


#if( VADC_GROUP0_USED == 1U )
/* Change the data type according to ADC Resolution */
extern volatile unsigned short VADC_Group0_Channels[VADC_GROUP0_CHANNELS_USED];
#endif

#if( VADC_GROUP1_USED == 1U )
extern volatile unsigned short VADC_Group1_Channels[VADC_GROUP1_CHANNELS_USED];
#endif

#if( VADC_GROUP2_USED == 1U )
extern volatile unsigned short VADC_Group2_Channels[VADC_GROUP2_CHANNELS_USED];
#endif

#if( VADC_GROUP3_USED == 1U )
extern volatile unsigned short VADC_Group3_Channels[VADC_GROUP3_CHANNELS_USED];
#endif


/******************************************************************************
* Function Prototypes
*******************************************************************************/



#endif /* DRI_VADC_EXTERN_H_ */

/********************************** End of File *******************************/
