/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		External Flash API Header
* Filename:		external_flash.h
* Author:		HS
* Origin Date:	03/04/2020
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	external_flash.h
 *  @brief:	This file contains API function declarations for External Flash
 */
#ifndef EXTERNAL_FLASH_H_
#define EXTERNAL_FLASH_H_


/******************************************************************************
* Includes
*******************************************************************************/
#include <external_flash.h>
#include <dri_spi_extern.h>


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/

#define EXT_FL_MANUFACTURER_ID					0x01
#define EXT_FL_DEVICE_ID						0x15


/******************************************************************************
* Macros
*******************************************************************************/

/* Convert SPI API for External Flash */
#define EXT_FL_COMM_API( api )					((tStSPI_MasterApi *)api)
/* Convert SPI Channel for External Flash */
#define EXT_FL_COMM_CHANNEL( channel )			((tStSPI_Master *)channel)


/* Configurations related to External Flash Memory Properties */

#define EXT_FL_PAGE_SIZE						0xFFU
#define EXT_FL_4K_SECTOR_SIZE					0x1000U
#define EXT_FL_8K_SECTOR_SIZE					( (EXT_FL_4K_SECTOR_SIZE << 1)U )
#define EXT_FL_SECTOR_SIZE						0x10000U

#define EXT_FL_NUMBER_OF_SECTORS				0x40U
#define EXT_FL_NUMBER_OF_SUB_SECTORS			0x10U

#define EXT_FL_MAX_ADDRESS_AVAILABLE			( (EXT_FL_NUMBER_OF_SECTORS * EXT_FL_SECTOR_SIZE)U )
#define EXT_FL_MIN_ADDRESS_AVAILABLE			0x0U


/** Commands for Cypress S25FL032P series **/
/* Read Operations */
#define EXT_FL_READ_COMMAND						0x03
#define EXT_FL_FAST_READ_COMMAND				0x0B
#define EXT_FL_DOR_COMMAND						0x3B
#define EXT_FL_QOR_COMMAND						0x6B
#define EXT_FL_DIOR_COMMAND						0xBB
#define EXT_FL_QIOR_COMMAND						0xEB
#define EXT_FL_RDID_COMMAND						0x9F
#define EXT_FL_READ_ID_COMMAND					0x90
/* Write Control operations */
#define EXT_FL_WREN_COMMAND						0x06
#define EXT_FL_WRDI_COMMAND						0x04
/* Erase Operations */
#define EXT_FL_SECTOR_ERASE_4K_COMMAND			0x20
#define EXT_FL_SECTOR_ERASE_8K_COMMAND			0x40
#define EXT_FL_SECTOR_ERASE_64K_COMMAND			0xD8
#define EXT_FL_BULK_ERASE_COMMAND				0x60 /* or 0xC7 */
/* Program Operations */
#define EXT_FL_PP_COMMAND						0x02
#define EXT_FL_QPP_COMMAND						0x32
/* Status and Configurations Register Operations */
#define EXT_FL_RDSR_COMMAND						0x05
#define EXT_FL_WRR_COMMAND						0x01
#define EXT_FL_RCR_COMMAND						0x35
#define EXT_FL_CLSR_COMMAND						0x30
/* Power Saving Operations */
#define EXT_FL_DP_COMMAND						0xB9
#define EXT_FL_RES_COMMAND						0xAB
/* OTP Operations */
#define EXT_FL_OTPP_COMMAND						0x42
#define EXT_FL_OTPR_COMMAND						0x4B


/******************************************************************************
* Typedefs
*******************************************************************************/

/*
 * @brief	Enum for Status of External Flash
 * */
typedef enum eEXT_FL_Status_	: unsigned char
{
	EXT_FL_STATUS_SUCCESS = 0,
	EXT_FL_STATUS_FAILED,
	EXT_FL_STATUS_BUSY,
	EXT_FL_STATUS_INVALID_ARGUMENT,
	EXT_FL_STATUS_OUT_OF_BOUND,
	EXT_FL_STATUS_ALREADY_INITIALIZED,
	EXT_FL_STATUS_NOT_INITIALIZED,
	EXT_FL_STATUS_NOT_AVAILABLE
} eEXT_FL_Status;


/*
 * @brief	Enum for Open or close
 * */
typedef enum eEXT_FL_Init_	: unsigned char
{
	EXT_FL_INIT_CLOSE = 0,
	EXT_FL_INIT_OPEN
} eEXT_FL_Init;


/*
 * @brief	typedef for status control of External Flash
 */
typedef struct tStExternalFlash_StatusControl_
{
	union
	{
		struct
		{
			volatile unsigned long init			: 1;
			volatile unsigned long busy			: 1;
			volatile unsigned long power_down	: 1;
			unsigned long state_res				: 29;
		};
		unsigned long state_value = 0;
	};
} tStExternalFlash_StatusControl;


/******************************************************************************
* Function Prototypes
*******************************************************************************/


/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
 *
 * @brief	Class for ExternalFlash__
 *
 * \par<b>Description:</b><br>
 *
 * 	<i>Imp Note:</i>
 *
 ******************************************************************************/

class ExternalFlash__
{
/* public members */
public:
	/** Constructors and Destructors */
	explicit ExternalFlash__( void * p_channel_interface, void * p_comm_interface )
				: p_comm_(p_comm_interface), p_channel_( p_channel_interface ),
				  status_register_( 0x00 ), configuration_register_( 0x00 ),
				  manufacturer_id_( 0x00 ), device_id_( 0x00 )
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
			/* Initialize External Flash parameters */
			control_.state_value = 0;
		}
	}
	virtual ~ExternalFlash__()
	{
		/* Update states of external flash,
		 * though it would not be needed in application to destroy it */
		for( ; ; );
	}

	/* Restricted constructors */
	ExternalFlash__( const ExternalFlash__& ) = delete;
	ExternalFlash__& operator=( const ExternalFlash__& ) = delete;


	/******* API Member functions *******/

	/**
	 * @function
	 *
	 * @brief
	 *
	 * @param[in]	value
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
	long init( const unsigned char& initialize );

	/**
	 * @function
	 *
	 * @brief
	 *
	 * @param[in]	value
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
	long write( const char * p_src, const unsigned long& length, const unsigned long& address );

	/**
	 * @function
	 *
	 * @brief
	 *
	 * @param[in]	value
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
	long read( char * const p_dest, const unsigned long& length, const unsigned long& address );

	/**
	 * @function
	 *
	 * @brief
	 *
	 * @param[in]	value
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
	long erase( const unsigned char& sector, const unsigned char& sector_type, const unsigned long& address );

	/* Power-Down option */
	/**
	 * @function
	 *
	 * @brief
	 *
	 * @param[in]	value
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
	long power_down( const unsigned char& power_state );

	/* Write protect and Hold option using external hardware pins */
	/**
	 * @function
	 *
	 * @brief
	 *
	 * @param[in]	value
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
	long write_protect( const unsigned char& state );

	/**
	 * @function
	 *
	 * @brief
	 *
	 * @param[in]	value
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
	long hold( const unsigned char& state );


	/**
	 * @function	OTP functionality related
	 *
	 * @brief
	 *
	 * @param[in]	value
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


/* private members */
private:
	/** Data Members **/
	void * p_comm_;	/**< Interface channel pointer for communication */
	void * p_channel_;	/**< Interface channel data structure pointer */
	tStExternalFlash_StatusControl control_;

	/** Data members for External Flash properties **/
	unsigned char status_register_;
	unsigned char configuration_register_;
	unsigned char manufacturer_id_;
	unsigned char device_id_;

	/******* Private Member Functions *******/

	/**
	 * @function
	 *
	 * @brief
	 *
	 * @param[in]	value
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
	long write_control( const unsigned char& state );

	/**
	 * @function
	 *
	 * @brief
	 *
	 * @param[in]	value
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
	char read_status( void );

	/**
	 * @function
	 *
	 * @brief
	 *
	 * @param[in]	value
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
	void write_status( const unsigned char& status, const unsigned char& configuration );

	/**
	 * @function
	 *
	 * @brief
	 *
	 * @param[in]	value
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
	void clear_status( void );


/* protected members, if any */
protected:
};


/******************************************************************************
* Variables
*******************************************************************************/
extern ExternalFlash__ ext_flash;


#endif /* LOGGER_H_ */

/********************************** End of File *******************************/
