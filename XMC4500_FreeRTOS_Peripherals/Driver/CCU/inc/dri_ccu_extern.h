/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		CCU Extern Header
* Filename:		dri_ccu_extern.h
* Author:		HS
* Origin Date:	02/14/2020
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	dri_ccu_extern.h
 *  @brief:	This file contains extern variable for CCU and CCU API header
 */
#ifndef DRI_CCU_EXTERN_H_
#define DRI_CCU_EXTERN_H_


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

/*
 * @brief	API functions Instance for CCU
 */

/*
 * @brief	Instances for CCU4 Modules
 */
#if (CCU40_USED == 1U)
extern tStCCU4_Module CCU4_Module0;
#endif	/* CCU40_USED */

#if (CCU42_USED == 1U)
extern tStCCU4_Module CCU4_Module2;
#endif	/* CCU42_USED */

/*
 * @brief	Instances for CCU4 Channels
 */
#if( CCU40_CHANNEL0_USED == 1U )
extern tStCCU4_Capture CCU40_Channel0_Handle;
#endif	/* CCU40_CHANNEL0_USED */

#if( CCU40_CHANNEL1_USED == 1U )
extern tStCCU4_Capture CCU40_Channel1_Handle;
#endif	/* CCU40_CHANNEL1_USED */

#if( CCU40_CHANNEL3_USED == 1U )
extern tStCCU4_Compare CCU40_Channel3_Handle;
#endif	/* CCU40_CHANNEL0_USED */

#if( CCU42_CHANNEL0_USED == 1U )
extern tStCCU4_Compare CCU42_Channel0_Handle;
#endif	/* CCU40_CHANNEL0_USED */

/*****************************************************************************/

/*
 * @brief	Instances for CCU4 Modules
 */
#if (CCU80_USED == 1U)
extern tStCCU8_Module CCU8_Module0;
#endif

/*
 * @brief	Instances for CCU8 Channels
 */
#if ( (CCU80_CHANNEL0_USED == 1U) && (CCU80_CHANNEL1_USED == 1U) )
extern tStCCU8_Compare CCU80_Channel0_Handle;
extern tStCCU8_Compare CCU80_Channel1_Handle;
#endif	/* CCU80_CHANNEL0_USED && CCU80_CHANNEL1_USED */

#if (CCU80_CHANNEL2_USED == 1U)
extern tStCCU8_Compare CCU80_Channel2_Handle;
#endif	/* CCU80_CHANNEL2_USED */

/******************************************************************************
* Function Prototypes
*******************************************************************************/



#endif /* DRI_CCU_EXTERN_H_ */

/********************************** End of File *******************************/
