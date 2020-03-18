/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		CCU Configuration Header
* Filename:		dri_ccu_conf.h
* Author:		HS
* Origin Date:	02/14/2020
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	dri_ccu_conf.h
 *  @brief:	This file contains configurations for CCU
 */
#ifndef DRI_CCU_CONF_H_
#define DRI_CCU_CONF_H_


/******************************************************************************
* Includes
*******************************************************************************/


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/* Callback Handler */
#define CCU4_CALLBACK_HANDLER_USED		1U
#define CCU8_CALLBACK_HANDLER_USED		1U


/******************************************************************************
* Configuration Constants
*******************************************************************************/

/* Note: Information Macros */
#define FCCU							120000000	/* Fccu = Fsys */
#define CCU4_MODULES_USED				2U
#define CCU8_MODULES_USED				1U
/* End */

/* CCU4 Configurations */
#define CCU40_USED						1U
#define CCU41_USED						0U
#define CCU42_USED						1U
#define CCU43_USED						0U

/* CCU40 Channels */
#if (CCU40_USED > 0)
#define CCU40_CHANNEL0_USED				1U	/* Capture mode */
#define CCU40_CHANNEL1_USED				1U	/* Capture mode */
#define CCU40_CHANNEL3_USED				1U	/* Compare mode */
#endif

/* CCU42 Channels */
#if (CCU42_USED > 0)
#define CCU42_CHANNEL0_USED				1U	/* Capture mode */
#endif

/*****************************************************************************/

/* CCU8 Configurations */
#define CCU80_USED						1U

/* CCU80 Channels */
#if (CCU80_USED > 0)
#define CCU80_CHANNEL0_USED				1U	/* Compare mode */
#define CCU80_CHANNEL1_USED				1U	/* Compare mode */

#define CCU80_CHANNEL2_USED				1U	/* Compare mode */
#endif


/******************************************************************************
* Macros
*******************************************************************************/

/* CCU4 Interrupt Handlers */
#if ( CCU40_CHANNEL0_USED == 1U )
#define CCU40_Channel0_Handler			IRQ_Hdlr_44
#endif

#if ( CCU40_CHANNEL1_USED == 1U )
#define CCU40_Channel1_Handler			IRQ_Hdlr_45
#endif

#if ( CCU40_CHANNEL3_USED == 1U )
#define CCU40_Channel3_Handler			IRQ_Hdlr_47
#endif

#if ( CCU42_CHANNEL0_USED == 1U )
#define CCU42_Channel0_Handler			IRQ_Hdlr_52
#endif

/*****************************************************************************/

/* CCU8 Interrupt Handlers */
#if ( (CCU80_CHANNEL0_USED == 1U) && (CCU80_CHANNEL1_USED == 1U) )
#define CCU80_Ch0_Ch1_Handler			IRQ_Hdlr_60
#endif	/* CCU80_CHANNEL0_USED && CCU80_CHANNEL1_USED */

#if (CCU80_CHANNEL2_USED == 1U )
#define CCU80_Channel2_Handler			IRQ_Hdlr_62
#endif	/* CCU80_CHANNEL2_USED */


#endif /* DRI_CCU_CONF_H_ */

/********************************** End of File ******************************/
