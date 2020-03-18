/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		External Flash API Source
* Filename:		external_flash.cpp
* Author:		HS
* Origin Date:	03/04/2020
* Version:		1.0.0
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	external_flash.cpp
 *  @brief:	This source file contains API function definitions for
 *  		External Flash class.
 */


/******************************************************************************
* Includes
*******************************************************************************/

/* Include class headers */
#include <external_flash.h>


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


/* Gloabl constructor for External Flash Module over SPI2 Channel 0 */
ExternalFlash__ ext_flash( &SPI2_Channel0_Handle, &SPI_Channel_API );


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
long ExternalFlash__::init( const unsigned char& initialize )
{
	/* Local variable */
	long ret_status = EXT_FL_STATUS_FAILED;
	unsigned char data_l[4] = { EXT_FL_READ_ID_COMMAND, 0x00, 0x00, 0x00 };

	/* Check input */
	switch( initialize )
	{
		case EXT_FL_INIT_OPEN:
			/* Check intiaization state */
			ret_status = (0 == control_.init) ? EXT_FL_STATUS_SUCCESS : EXT_FL_STATUS_ALREADY_INITIALIZED;
		break;

		case EXT_FL_INIT_CLOSE:
			/* Update power down mode */
			power_down( 1 );
			/* Update parameters */
			control_.state_value = 0;
			ret_status = EXT_FL_STATUS_SUCCESS;
		break;

		default:
			ret_status = EXT_FL_STATUS_INVALID_ARGUMENT;
	}

	/* Check status */
	if( EXT_FL_STATUS_SUCCESS == ret_status )
	{
		/* Initialzie interface channel if not yet */
		if( 0 == EXT_FL_COMM_CHANNEL(p_channel_)->p_control->state.init )
		{
			ret_status = EXT_FL_COMM_API(p_comm_)->fp_init( p_channel_, 1 );
		}

		/* Check status */
		if( (SPI_STATUS_SUCCESS == ret_status) || (SPI_STATUS_ALREADY_INITIALIZED == ret_status) )
		{
			/* Set Slave as SEL01 and confirm the state of SS */
			EXT_FL_COMM_API(p_comm_)->fp_set_slave( p_channel_, 1 );
			/* Disable power down */
			power_down( 0 );

			/* Read Device ID */
			EXT_FL_COMM_API(p_comm_)->fp_slave_select( p_channel_, 1 );
			EXT_FL_COMM_API(p_comm_)->fp_write( p_channel_, (const unsigned char *)&data_l, 4 );
			EXT_FL_COMM_API(p_comm_)->fp_read( p_channel_, (unsigned char *const )&data_l, 2 );
			EXT_FL_COMM_API(p_comm_)->fp_slave_select( p_channel_, 0 );
			/* Update Manufacturer ID and Device ID */
			manufacturer_id_ = data_l[0];
			device_id_ = data_l[1];

			/* Send Read Status register */
			data_l[0] = EXT_FL_RDSR_COMMAND;
			EXT_FL_COMM_API(p_comm_)->fp_slave_select( p_channel_, 1 );
			EXT_FL_COMM_API(p_comm_)->fp_write( p_channel_, (const unsigned char *)&data_l, 1 );
			EXT_FL_COMM_API(p_comm_)->fp_read( p_channel_, (unsigned char *const)&data_l[1], 1 );
			EXT_FL_COMM_API(p_comm_)->fp_slave_select( p_channel_, 0 );
			/* Update Manufacturer ID and Device ID */
			status_register_ = data_l[1];

			/* Check the device ID for Authentication of Device */
			if( (manufacturer_id_ != EXT_FL_MANUFACTURER_ID) || (device_id_ != EXT_FL_DEVICE_ID) )
			{
				control_.state_value = 0;
				ret_status = EXT_FL_STATUS_FAILED;
			}
			else
			{
				/* Update parameters */
				control_.init = 1;
				control_.power_down = 0;
				control_.busy = 0;
				ret_status = EXT_FL_STATUS_SUCCESS;
			}
		}
		else
		{
			ret_status = EXT_FL_STATUS_FAILED;
		}
	}
	else
	{
		/* Operation has failed due to Invalid argument or Already initialized status */
	}

	/* Return status */
	return ret_status;
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 */
long ExternalFlash__::write( const char * p_src, const unsigned long& length, const unsigned long& address )
{
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 */
long ExternalFlash__::read( char * const p_dest, const unsigned long& length, const unsigned long& address )
{
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 */
long ExternalFlash__::erase( const unsigned char& sector, const unsigned char& sector_type, const unsigned long& address )
{
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 */
long ExternalFlash__::power_down( const unsigned char& power_state )
{
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 * 	TODO: Need to define pins explicitly for this fucntionality
 */
long ExternalFlash__::write_protect( const unsigned char& state )
{
	/* Local variable */
	long ret_status = EXT_FL_STATUS_FAILED;
	/* Check SPI mode and decide control of fucntion
	 * If QSPI enabled then cannot perform this operation
	 * */
	if( XMC_SPI_CH_MODE_QUAD == EXT_FL_COMM_CHANNEL(p_channel_)->p_config->channel_mode )
	{
		/* Update return with failed operation */
		ret_status = EXT_FL_STATUS_NOT_AVAILABLE;
	}
	else
	{
		/* Proceed further */
	}

	/* Return status */
	return ret_status;
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 * TODO: Need to define pins explicitly for this fucntionality
 */
long ExternalFlash__::hold( const unsigned char& state )
{
	/* Local variable */
	long ret_status = EXT_FL_STATUS_FAILED;

	/* Check SPI mode and decide control of fucntion
	 * If QSPI enabled then cannot perform this operation
	 * */
	if( XMC_SPI_CH_MODE_QUAD == EXT_FL_COMM_CHANNEL(p_channel_)->p_config->channel_mode )
	{
		/* Update return with failed operation */
		ret_status = EXT_FL_STATUS_NOT_AVAILABLE;
	}
	else
	{
		/* Proceed further */
	}

	/* Return status */
	return ret_status;
}


/******* Private Member function for Logger__ class *******/


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 */
long ExternalFlash__::write_control( const unsigned char& state )
{
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 */
char ExternalFlash__::read_status( void )
{
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 */
void ExternalFlash__::write_status( const unsigned char& status, const unsigned char& configuration )
{
}


/********************************** End of File *******************************/
