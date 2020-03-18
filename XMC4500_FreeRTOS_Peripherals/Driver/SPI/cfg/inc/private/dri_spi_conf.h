/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		SPI Configuration Header
* Filename:		dri_spi_conf.h
* Author:		HS
* Origin Date:	02/23/2020
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	dri_spi_conf.h
 *  @brief:	This file contains configurations for SPI
 */
#ifndef DRI_SPI_CONF_H_
#define DRI_SPI_CONF_H_


/******************************************************************************
* Includes
*******************************************************************************/


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/* Callback Handler */
#define SPI_CALLBACK_HANDLER_USED		1U
#define SPI_PROTOCOL_EVENTS_USED		1U


/******************************************************************************
* Configuration Constants
*******************************************************************************/

/* SPI Channel configurations */
#define SPI_MAX_CHANNELS				6U
#define SPI2_CHANNEL0_USED				1U

/* SPI Parameters availability configuration */
#define SPI_MAX_SLAVES_AVAILABLE		4U
#define SPI_MAX_MODES_AVAILABLE			4U

/* Slave Select operation selection */
#define SPI_INTERNAL_SLAVE_SELECT_USED	1U


/******************************************************************************
* Macros
*******************************************************************************/

/* SPI Interrupt Handlers */
#if (SPI2_CHANNEL0_USED == 1U)
#define SPI2_CHANNEL0_TX_SR				0
#define SPI2_CHANNEL0_RX_SR				1
#define SPI2_Channel0_Transmit_Handler	IRQ_Hdlr_96
#define SPI2_Channel0_Receive_Handler	IRQ_Hdlr_97

#if (SPI_PROTOCOL_EVENTS_USED == 1U)
#define SPI2_CHANNEL0_EVENT_SR			2
#define SPI2_Channel0_Protocol_Handler	IRQ_Hdlr_98
#endif	/* SPI_PROTOCOL_EVENTS_USED */
#endif	/* SPI2_CHANNEL0_USED */


#endif /* DRI_SPI_CONF_H_ */

/********************************** End of File ******************************/
