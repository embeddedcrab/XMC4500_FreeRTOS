/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		Logger API Header
* Filename:		logger.h
* Author:		HS
* Origin Date:	11/09/2019
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	logger.h
 *  @brief:	This file contains API function declarations
 *  		for Logger which acn use any hardware for logging
 */
#ifndef LOGGER_H_
#define LOGGER_H_


/******************************************************************************
* Includes
*******************************************************************************/
#include <dri_mem.h>
#include <dri_uart_extern.h>


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/

/* For Data conversion and storing into buffer */
constexpr unsigned char g_max_buffer_size = 20;

/* Logger buffer size */
static constexpr unsigned long sg_logger_buffer_size = 512;


/******************************************************************************
* Macros
*******************************************************************************/

/* Convert UART API for Logger */
#define LOGGER_COM_API( api )					((tStUART_Api *)api)
/* Convert UART Channel for Logger */
#define LOGGER_COMM_CHANNEL( channel )			((tStUART_Channel *)channel)


/******************************************************************************
* Typedefs
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/


/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
 *
 * @brief	Class for Logger__ Instance
 *
 * \par<b>Description:</b><br>	This logger class can be interfaced with any
 * 	peripheral like; UART, SD Card, Network
 *
 * 	<i>Imp Note:</i>	This is basic implementation and idea to get the whole
 * 	class done
 *
 ******************************************************************************/

class Logger__
{
/* public members */
public:
	/** Constructors and Destructors */
	explicit Logger__( void * p_channel_interface, void * p_comm_interface )
					: p_comm_(p_comm_interface), p_channel_( p_channel_interface ),
					  index_( 0 )
		{
			if( (nullptr == p_channel_interface) || (nullptr == p_comm_interface) )
			{
				for( ; ; )
				{
					__asm("NOP");
				}
			}
			else
			{
				/* Class memebers initialization */
				memset( (void *)buffer_, '\0', ::sg_logger_buffer_size );
			}
		}

	virtual ~Logger__()
	{
		__asm("NOP");
	}

	Logger__( const Logger__& ) = delete;
	Logger__& operator=( const Logger__& ) = delete;

	/******* API Member functions *******/

	/**
	 * @function	<< operator overloading for different values
	 *
	 * @brief		These functions will fill buffer with input data for logging
	 *
	 * @param[in]	value
	 *
	 * @param[out]	NA
	 *
	 * @return		object reference
	 *
	 * \par<b>Description:</b><br>
	 *
	 * <i>Imp Note:</i>	TODO: Add library support for other than character functionality
	 *
	 */
	/* Library dependencies */
	Logger__& operator<<( const signed short& value );
	Logger__& operator<<( const unsigned short& value );

	Logger__& operator<<( const signed int& value );
	Logger__& operator<<( const unsigned int& value );

	Logger__& operator<<( const signed long& value );
	Logger__& operator<<( const signed long long& value );
	Logger__& operator<<( const unsigned long& value );
	Logger__& operator<<( const unsigned long long& value );

	Logger__& operator<<( const float& value );
	Logger__& operator<<( const double& value );
	Logger__& operator<<( const long double& value );

	/* Working fine without additional libraries */
	Logger__& operator<<( const char& value );
	Logger__& operator<<( const signed char& value );
	Logger__& operator<<( const unsigned char& value );

	Logger__& operator<<( const char * p_value );
	Logger__& operator<<( const signed char * p_value );
	Logger__& operator<<( const unsigned char * p_value );

	/* Functions for endl functionality,
	 * Which is responsible for transferring the buffer value to the destination
	 * */
	static Logger__& endl( Logger__& stream )
	{
		return stream;
	}

	/* Function entry to send data to destination,
	 * This can be overridden for transferring data to hardware device
	 * */
	virtual Logger__& operator<<( Logger__& end(Logger__&) )
	{
		/* Get Mutex */
		while( UART_STATUS_BUSY == LOGGER_COM_API(p_comm_)->fp_transmit( p_channel_, (const unsigned char *)buffer_, index_ ) );
		memset( (void *)buffer_, '\0', index_ );
		index_ = 0;
		/* Release Mutex */
		/* Return object reference */
		return *this;
	}


/* private members */
private:
	/** Data Members **/
	void * p_comm_;	/**< Interface channel pointer for communication */
	void * p_channel_;	/**< Interface channel data structure pointer */

	volatile char buffer_[::sg_logger_buffer_size];
	volatile unsigned long index_;

	/******* Private Member Functions *******/

/* protected members, if any */
protected:

};



/******************************************************************************
* Variables
*******************************************************************************/
extern Logger__ logger;


#endif /* LOGGER_H_ */

/********************************** End of File *******************************/
