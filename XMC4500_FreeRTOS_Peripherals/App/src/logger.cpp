/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		Logger API Source
* Filename:		logger.cpp
* Author:		HS
* Origin Date:	11/09/2019
* Version:		1.0.0
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	logger.cpp
 *  @brief:	This source file contains API function definitions for
 *  		Logger class.
 */


/******************************************************************************
* Includes
*******************************************************************************/

/* Include class headers */
#include <logger.h>


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

/* Declare static data member of class
 *
 * Note: Tell linker to take variable from this source file
 * */

/* Logger instance */
Logger__ logger( &UART_Channel_2, &UART_Api_Functions );


/******************************************************************************
* Function Definitions
*******************************************************************************/


/******* Public Member function for Logger__ class *******/

/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 */
Logger__& Logger__::operator<<( const char& value )
{
	/* Cross check index */
	if( index_ < ::sg_logger_buffer_size )
	{
		/* Fill buffer with the char values from string */
		memcpy( (char *)(buffer_ + index_), &value, 1 );
		/* Update index value */
		index_ += 1;
	}
	/* return for cascading */
	return *this;
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 */
Logger__& Logger__::operator<<( const signed char& value )
{
	if( index_ < ::sg_logger_buffer_size )
	{
		/* Fill buffer with the char values from string */
		memcpy( (char *)(buffer_ + index_), &value, 1 );
		/* Update index value */
		index_ += 1;
	}
	/* return for cascading */
	return *this;
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 */
Logger__& Logger__::operator<<( const unsigned char& value )
{
	if( index_ < ::sg_logger_buffer_size )
	{
		/* Fill buffer with the char values from string */
		memcpy( (char *)(buffer_ + index_), &value, 1 );
		/* Update index value */
		index_ += 1;
	}
	/* return for cascading */
	return *this;
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 */
Logger__& Logger__::operator<<( const char * p_value )
{
	unsigned long size_l = strlen(p_value);
	if( (index_ < ::sg_logger_buffer_size) && (size_l < (::sg_logger_buffer_size - index_) ) )
	{
		/* Fill buffer with the char values from string */
		memcpy( (char *)(buffer_ + index_), p_value, size_l );
		/* Update index value */
		index_ += size_l;
	}

	/* return for cascading */
	return *this;
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 */
Logger__& Logger__::operator<<( const signed char * p_value )
{
	unsigned long size_l = strlen((const char *)p_value);
	/* Fill buffer with the char values from string */
	memcpy( (char *)(buffer_ + index_), p_value, size_l );
	/* Update index value */
	index_ += size_l;

	/* return for cascading */
	return *this;
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 */
Logger__& Logger__::operator<<( const unsigned char * p_value )
{
	unsigned long size_l = strlen((const char *)p_value);
	/* Fill buffer with the char values from string */
	memcpy( (char *)(buffer_ + index_), p_value, size_l );
	/* Update index value */
	index_ += size_l;

	/* return for cascading */
	return *this;
}


/********************************** End of File *******************************/
