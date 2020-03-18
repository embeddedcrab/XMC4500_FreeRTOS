/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		VADC API Header
* Filename:		dri_ccu.h
* Author:		HS
* Origin Date:	02/14/2020
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	dri_ccu.h
 *  @brief:	This file contains API function declarations for CCU
 */
#ifndef DRI_CCU_H_
#define DRI_CCU_H_


/******************************************************************************
* Includes
*******************************************************************************/
#include <dri_ccu_types.h>
#include "xmc_scu.h"


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
long CCU4_module_init( void * p_module, const unsigned char init );


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
long CCU4_compare_channel_init( void * p_channel, const unsigned char module, const unsigned char slice,
								const unsigned char init );


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
long CCU4_capture_channel_init( void * p_channel, const unsigned char module, const unsigned char slice,
								const unsigned char init );


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
void CCU4_channel_timer_control( void * p_channel, const unsigned char start );


/*****************************************************************************/

/*****************************************************************************/


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
long CCU8_module_init( void * p_module );


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
long CCU8_compare_channel_init( void * p_channel, const unsigned char module, const unsigned char slice,
								const unsigned char init );


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
void CCU8_channel_timer_control( void * p_channel, const unsigned char start );


#ifdef __cplusplus
}
#endif


#endif	/* DRI_CCU_H_ */

/********************************** End of File *******************************/
