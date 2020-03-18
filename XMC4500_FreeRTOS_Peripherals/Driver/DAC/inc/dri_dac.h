/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		DAC API Header
* Filename:		dri_dac.h
* Author:		HS
* Origin Date:	02/23/2020
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	dri_dac.h
 *  @brief:	This file contains API function declarations for DAC
 */
#ifndef DRI_DAC_H_
#define DRI_DAC_H_


/******************************************************************************
* Includes
*******************************************************************************/
#include <dri_dac_types.h>


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
* Function Prototypes
*******************************************************************************/


/******************************************************************************
 *
 * @brief
 *
 * \par<b>Description:</b><br>:
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
 * @function
 *
 * @brief
 *
 * @param[in]
 *
 * @param[out]	NA
 *
 * @return
 *
 * \par<b>Description:</b><br>
 *
 * <i>Imp Note:</i>
 *
 */
long DAC_init( void * p_channel, const unsigned char channel,
				const unsigned char mode, const unsigned char init );


/**
 * @function
 *
 * @brief
 *
 * @param[in]
 *
 * @param[out]	NA
 *
 * @return
 *
 * \par<b>Description:</b><br>
 *
 * <i>Imp Note:</i>	Do not use this until power consumption is a big concern!
 *
 */
static inline void DAC_disable( void )
{
	XMC_DAC_Disable( (XMC_DAC_t *const) DAC_GLOBAL );
}


/**
 * @function
 *
 * @brief
 *
 * @param[in]
 *
 * @param[out]	NA
 *
 * @return
 *
 * \par<b>Description:</b><br>
 *
 * <i>Imp Note:</i>
 *
 */
static inline void DAC_trigger( const unsigned char channel )
{
	DRIVER_ASSERT_NRET( channel > 1 );
	XMC_DAC_CH_SoftwareTrigger( (XMC_DAC_t *const) DAC_GLOBAL, channel );
}


#ifdef __cplusplus
}
#endif


#endif	/* DRI_DAC_H_ */

/********************************** End of File *******************************/
