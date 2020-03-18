/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		Master Configuration Header
* Filename:		master_config.h
* Author:		HS
* Origin Date:	03/09/2020
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	master_config.h
 *  @brief:	This file contains Configuratios for Project
 */
#ifndef MASTER_CONFIG_H_
#define MASTER_CONFIG_H_


/******************************************************************************
* Includes
*******************************************************************************/

/* Master Configuration for different parts */
#include <peripheral_config.h>
#include <device_config.h>
#include <core_config.h>
#include <app_config.h>

/* Master Application Data Types */
#include <master_app_types.h>

/* Include Trace headers */
#include <trace.h>


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

#define DEBUG_								1U


/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/


/******************************************************************************
* Variables
*******************************************************************************/

/* Reset reason storing global variable */
extern volatile unsigned long gResetReason;
/* Boot mode storing global variable */
extern volatile unsigned long gBootMode;
/* System State Global Variable */
extern volatile unsigned char gSystemState;



#endif /* MASTER_CONFIG_H_ */

/********************************** End of File *******************************/
