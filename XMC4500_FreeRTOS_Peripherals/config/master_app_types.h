/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		Master Application Data Types Header
* Filename:		master_app_types.h
* Author:		HS
* Origin Date:	03/09/2020
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	master_app_types.h
 *  @brief:	This file contains Data Types for Application
 */
#ifndef MASTER_APP_TYPES_H_
#define MASTER_APP_TYPES_H_


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

/*
 * @brief	Enum for Master Data Types
 * */
typedef enum eMasterAppTypes_
{
	MASTER_APP_STATE_IDLE = 0,
	MASTER_APP_STATE_ACTIVE,
	MASTER_APP_STATE_SLEEP,
	MASTER_APP_STATE_DEEP_SLEEP,
	MASTER_APP_STATE_HIBERNATE,
	MASTER_APP_STATE_NOT_STARTED
} eMasterAppTypes;



#endif /* MASTER_APP_TYPES_H_ */

/********************************** End of File *******************************/
