/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		DAC Configuration Header
* Filename:		dri_dac_conf.h
* Author:		HS
* Origin Date:	02/23/2020
* Version:		1.0.0
* Notes:		DAC Channel 0 is used in Data Processing Mode
* 				DAC Channel 1 is used in Noise Generation Mode
*******************************************************************************/

/** @file:	dri_dac_conf.h
 *  @brief:	This file contains configurations for DAC
 */
#ifndef DRI_DAC_CONF_H_
#define DRI_DAC_CONF_H_


/******************************************************************************
* Includes
*******************************************************************************/


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/* Callback Handler */
#define DAC_CALLBACK_HANDLER_USED		1U


/******************************************************************************
* Configuration Constants
*******************************************************************************/

/* Note: Information Macros */
#define FDAC							120000000	/* Fwdt = Fsys */
/* End */

#define DAC_GLOBAL						XMC_DAC0


#define DAC_CHANNEL0_USED				1U	/* Used for Data processing mode */
#define DAC_CHANNEL1_USED				1U	/* Used for Noise generation mode */


/******************************************************************************
* Macros
*******************************************************************************/

/* DAC Interrupt Handlers */
#if (DAC_CHANNEL0_USED == 1U)
#define DAC0_DATA_NUMBER				10
#define DAC0_Handler					IRQ_Hdlr_42
#endif


/******************************************************************************
* Typedefs
*******************************************************************************/


/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/


#endif /* DRI_DAC_CONF_H_ */

/********************************** End of File ******************************/
