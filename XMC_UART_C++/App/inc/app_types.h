/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		Data types Header for application
* Filename:		app_types.h
* Author:		Hemant Sharma
* Origin Date:	06/30/2019
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	app_types.h
 *  @brief:	This file contains data types definitions and macros for application
 */
#ifndef APP_TYPES_H_
#define APP_TYPES_H_

/******************************************************************************
* Includes
*******************************************************************************/


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
 * @brief	Parameters for task creation
 */
typedef struct TaskCreationParams_
{
	char * p_name;
	configSTACK_DEPTH_TYPE stackDepth;
	UBaseType_t priority;
}TaskCreationParams;


#ifdef __cplusplus
extern "C"{
#endif


/* Add */


#ifdef __cplusplus
}
#endif


#endif /* APP_TYPES_H_ */

/********************************** End of File *******************************/
