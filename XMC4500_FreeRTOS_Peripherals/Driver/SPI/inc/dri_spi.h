/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		SPI API Header
* Filename:		dri_spi.h
* Author:		HS
* Origin Date:	02/23/2020
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	dri_spi.h
 *  @brief:	This file contains API function declarations for SPI
 */
#ifndef DRI_SPI_H_
#define DRI_SPI_H_


/******************************************************************************
* Includes
*******************************************************************************/
#include <dri_spi_types.h>


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


/******************************************************************************
* Function Prototypes
*******************************************************************************/


/******************************************************************************
 *
 * @brief
 *
 * \par<b>Description:</b><br>:
 *
 ******************************************************************************/
/******************************************************************************
 *
 * @brief	API Member functions
 *
 ******************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @function
 *
 * @brief
 *
 * @param[in]
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
long SPI_Master_init( void * p_channel, const unsigned char init );


/**
 * @function
 *
 * @brief
 *
 * @param[in]
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
long SPI_Master_set_slave( void * p_channel, const unsigned char slave );


/**
 * @function
 *
 * @brief
 *
 * @param[in]
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
void SPI_Master_slave_select( void * p_channel, const unsigned char slave_state );


/**
 * @function
 *
 * @brief
 *
 * @param[in]
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
long SPI_Master_set_mode( void * p_channel, const unsigned char mode );


/**
 * @function
 *
 * @brief
 *
 * @param[in]
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
long SPI_Master_set_data_size( void * p_channel, const unsigned char size );


/**
 * @function
 *
 * @brief
 *
 * @param[in]
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
long SPI_Master_set_speed( void * p_channel, const unsigned long speed );


/**
 * @function
 *
 * @brief
 *
 * @param[in]
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
long SPI_Master_transmit( void * p_channel, const unsigned char * p_data, const unsigned long length );


/**
 * @function
 *
 * @brief
 *
 * @param[in]
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
long SPI_Master_receive( void * p_channel, unsigned char * const p_data, const unsigned long length );


/**
 * @function
 *
 * @brief
 *
 * @param[in]
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
long SPI_Master_abort( void * p_channel, const unsigned char tx_rx );



#ifdef __cplusplus
}
#endif


#endif	/* DRI_SPI_H_ */

/********************************** End of File *******************************/
