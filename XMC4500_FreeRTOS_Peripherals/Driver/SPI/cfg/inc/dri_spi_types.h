/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		SPI data types Header
* Filename:		dri_spi_types.h
* Author:		HS
* Origin Date:	02/23/2020
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	dri_spi_types.h
 *  @brief:	This file contains data types definitions for SPI
 */
#ifndef DRI_SPI_TYPES_H_
#define DRI_SPI_TYPES_H_


/******************************************************************************
* Includes
*******************************************************************************/

/* Include XMC Headers */
#include <xmc_spi.h>

/* Include private headers first */
#include <private/dri_spi_conf.h>
/* Include typedefs */
#include <dri_types.h>


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
 * @brief	Enum for Status of SPI
 * */
typedef enum eSPI_Status_
{
	SPI_STATUS_SUCCESS = 0,
	SPI_STATUS_FAILED,
	SPI_STATUS_BUSY,
	SPI_STATUS_INVALID_ARGUMENT,
	SPI_STATUS_OUT_OF_BOUND,
	SPI_STATUS_ALREADY_INITIALIZED,
	SPI_STATUS_NOT_INITIALIZED
} eSPI_Status;

/*
 * @brief	Enum for Open or close
 * */
typedef enum eSPI_Init_
{
	SPI_INIT_CLOSE = 0,
	SPI_INIT_OPEN
} eSPI_Init;

/*
 * @brief	Enum for SPI bit order
 * */
typedef enum eSPI_BitOrder_
{
	SPI_BIT_ORDER_MSB_FIRST = 0,
	SPI_BIT_ORDER_LSB_FIRST
} eSPI_BitOrder;

/*
 * @brief	Enum for Abort operation
 * */
typedef enum eSPI_Abort_
{
	SPI_ABORT_TX = 0,
	SPI_ABORT_RX,
	SPI_ABORT_TX_RX
} eSPI_Abort;

/*
 * @brief	Enum for SPI data size
 * */
typedef enum eSPI_DataSize_
{
	SPI_DATA_SIZE_BYTE = 0,
	SPI_DATA_SIZE_WORD
} eSPI_DataSize;

/*
 * @brief	Enum for SPI Events
 * */
typedef enum eSPI_Events_
{
	SPI_EVENT_TRANSMIT = 0,
	SPI_EVENT_RECEIVE,
	SPI_EVENT_DATA_LOST,
	SPI_EVENT_BAUDRATE_ERROR,
	SPI_EVENT_PARITY_ERROR
} eSPI_Events;

/*
 * @brief	Enum for SPI ISR operation
 * */
typedef enum eSPI_InterruptOperation_
{
	SPI_INTERRUPT_OPERATION_TX = 0,
	SPI_INTERRUPT_OPERATION_RX,
	SPI_INTERRUPT_PROTOCOl_ERROR
} eSPI_InterruptOperation;


/*
 * @brief	Enum for SPI Slaves available
 * */
typedef enum eSPI_Slave_
{
	SPI_SLAVE_SEL0 = XMC_SPI_CH_SLAVE_SELECT_0,
	SPI_SLAVE_SEL1 = XMC_SPI_CH_SLAVE_SELECT_1,
	SPI_SLAVE_SEL2 = XMC_SPI_CH_SLAVE_SELECT_2,
	SPI_SLAVE_SEL3 = XMC_SPI_CH_SLAVE_SELECT_3
} eSPI_Slave;


/*
 * @brief	typedef for callback function pointer
 * */
typedef void (*spi_callback_pointer) ( void * p_channel, void * p_data, const eSPI_Events event );


/******************************************************************************
 *
 * @brief	Data Types for SPI instance
 *
 *****************************************************************************/

/*
 * @brief	typedef for status control of SPI
 */
typedef struct tStSPI_StatusControl_
{
	union
	{
		struct
		{
			unsigned long init			: 1;
			unsigned long tx_busy		: 1;
			unsigned long rx_busy		: 1;
			unsigned long slave		: 24;/* SS functionality */
			unsigned long tx_dummy		: 1;
			unsigned long slave_set	: 1;
			unsigned long size			: 1;/* Size of data, sued for 8/16 bits transfer */
			unsigned long state_res				: 2;
		};
		unsigned long state_value;
	};
} tStSPI_MasterStatusControl;

/************************************************************************************/

/*
 * @brief Structure for SPI channel interrupt configuration
 */
typedef struct tStSPI_InterruptConfiguartion_
{
	/**< Interrupt configuration */
	tStInterruptConfig irq;
	/**< Service request number assigned to interrupt */
	unsigned long sr;
} tStSPI_InterruptConfiguartion;


/************************************************************************************/

/************************************************************************************/

/*
 * @brief Structure for SPI channel fifo size configuration
 */
typedef struct tStSPI_FIFO_Configuartion_
{
	/* fifo size configuration for tx and rx */
	XMC_USIC_CH_FIFO_SIZE_t tx_fifo_size;
	XMC_USIC_CH_FIFO_SIZE_t rx_fifo_size;
} tStSPI_FIFO_Configuartion;


/*
 * @brief	Structure for SPI Master Configuration
 */
typedef struct tStSPI_MasterConfiguartion_
{
	/**< Module Context for SPI Master */
	void * p_channel_context;
	XMC_SPI_CH_CONFIG_t * p_channel_config;
	tStSPI_FIFO_Configuartion * p_fifo_config;
	/**< Interrupt configuration */
	tStSPI_InterruptConfiguartion * tx_isr_config;
	tStSPI_InterruptConfiguartion * rx_isr_config;
	#if (SPI_PROTOCOL_EVENTS_USED == 1U)
	tStSPI_InterruptConfiguartion * protocol_isr_config;
	#endif
	/**< Frame configurations */
	unsigned char word_length;
	unsigned char frame_length;
	/**< Input pin configuration */
	unsigned char input_pin_source;
	/**< Bit order of SPI data */
	unsigned char bit_order;
	XMC_SPI_CH_INPUT_t input_pin;
	XMC_SPI_CH_MODE_t channel_mode;
} tStSPI_MasterConfiguartion;


/*
 * @brief	Structure for SPI Control
 */
typedef struct tStSPI_Control_
{
	/**< Data control for SPI Master */
	unsigned char * p_tx_data;
	unsigned char * p_rx_data;
	unsigned long tx_data_count;
	unsigned long tx_data_index;
	unsigned long rx_data_count;
	unsigned long rx_data_index;
	volatile tStSPI_MasterStatusControl state;
} tStSPI_MasterControl;

/*
 * @brief Structure for SPI channel callbacks
 */
typedef struct tStSPI_Callbacks_
{
#if (SPI_CALLBACK_HANDLER_USED == 1U)
	spi_callback_pointer fp_callback;
#endif
} tStSPI_MasterCallbacks;


/*
 * @brief Structure for SPI master module
 */
typedef struct tStSPI_Master_
{
	/**< Configurations for configuration */
	tStSPI_MasterConfiguartion * p_config;
	/**< Configurations for control */
	tStSPI_MasterControl * p_control;
	#if (SPI_CALLBACK_HANDLER_USED == 1U)
	tStSPI_MasterCallbacks * p_callback;
	#endif
} tStSPI_Master;


/************************************************************************************/

/*
 * @brief Structure for SPI channel API
 */
typedef struct tStSPI_Api_
{
	long (*fp_init) ( void *, const unsigned char );
	long (*fp_set_slave) ( void *, const unsigned char );
	void (*fp_slave_select)( void *, const unsigned char );
	long (*fp_set_mode) ( void *, const unsigned char );
	long (*fp_set_data_size) ( void *,  const unsigned char );
	long (*fp_set_speed) ( void *, const unsigned long );
	long (*fp_write) ( void *, const unsigned char *, const unsigned long );
	long (*fp_read) ( void *, unsigned char * const, const unsigned long );
	long (*fp_abort) ( void *, const unsigned char );
} tStSPI_MasterApi;


#endif /* DRI_SPI_TYPES_H_ */

/********************************** End of File *******************************/
