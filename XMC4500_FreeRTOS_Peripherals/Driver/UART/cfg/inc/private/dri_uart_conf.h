/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		UART Configuration Header
* Filename:		dri_uart_conf.h
* Author:		HS
* Origin Date:	09/29/2019
* Version:		1.0.0
* Notes:
*******************************************************************************/

/** @file:	dri_uart_conf.h
 *  @brief:	This file contains static configurations for UART channel on USIC
 */
#ifndef DRI_UART_CONF_H_
#define DRI_UART_CONF_H_


/******************************************************************************
* Includes
*******************************************************************************/


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define UART_INTERRUPT_USED				1

#if( UART_INTERRUPT_USED == 1U )
#define UART_TX_INTERRUPT_USED
#define UART_RX_INTERRUPT_USED
//#define UART_PROTOCOL_EVENT_USED	/* Does not seem to work properly! */
#endif

#define UART_CALLBACK_HANDLER_USED		1

/******************************************************************************
* Configuration Constants
*******************************************************************************/
#define UART_MAX_CHANNELS				6


/* TODO: <i>Imp Note:</>
 * 			We always need to explicitly configure channels for TX, RX
 * 			and ERR usage
 */

/* Total UART Channels used in system */
#define UART_CHANNELS_USED				2

/* UART Channels used in system */
#define UART_CHANNEL_0_USED
#define UART_CHANNEL_0_ERROR_USED

#define UART_CHANNEL_2_USED
#define UART_CHANNEL_2_ERROR_USED


/* Check channels availability */
#if (UART_CHANNELS_USED > UART_MAX_CHANNELS)
	#error	"Cannot instantiate more than available channels"
#endif

/* Check channels usage */
#if( 0 == UART_CHANNELS_USED )
	/* Check interrupt availability */
	#if ( defined(UART_TX_INTERRUPT_USED) ||	\
			defined(UART_RX_INTERRUPT_USED) ||	\
			defined(UART_PROTOCOL_EVENT_USED) )
		#error	"Cannot Enable Interrupt if O channels enabled"
	#endif
#endif

/* Check Channels wnforced with Interrupts */
#if ( UART_CHANNELS_USED > 0 )
#if ( !defined(UART_TX_INTERRUPT_USED) &&	\
		!defined(UART_RX_INTERRUPT_USED) &&	\
		!defined(UART_PROTOCOL_EVENT_USED) )
	#error "Channels cannot be used without interrupt"
#endif
#endif


/******************************************************************************
* Macros
*******************************************************************************/

/* Defining functions for UART ISR handlers,
 * can be changed by user according to availability */

/* UART_TX_INTERRUPT_USED Handlers */
#ifdef UART_TX_INTERRUPT_USED

#ifdef UART_CHANNEL_0_USED
#define UART_0_TX_HANDLER				IRQ_Hdlr_86
#define UART_0_TX_SR					2
#endif

#ifdef UART_CHANNEL_1_USED
#define UART_1_TX_HANDLER				IRQ_Hdlr_89
#define UART_1_TX_SR					5
#endif

#ifdef UART_CHANNEL_2_USED
#define UART_2_TX_HANDLER				IRQ_Hdlr_92
#define UART_2_TX_SR					2
#endif

#ifdef UART_CHANNEL_3_USED
#define UART_3_TX_HANDLER				IRQ_Hdlr_95
#define UART_3_TX_SR					5
#endif

#ifdef UART_CHANNEL_4_USED
#define UART_4_TX_HANDLER				IRQ_Hdlr_98
#define UART_4_TX_SR					2
#endif

#ifdef UART_CHANNEL_5_USED
#define UART_5_TX_HANDLER				IRQ_Hdlr_101
#define UART_5_TX_SR					5
#endif

#endif	/* UART_TX_INTERRUPT_USED */


/* UART_RX_INTERRUPT_USED Handlers */
#ifdef UART_RX_INTERRUPT_USED

#ifdef UART_CHANNEL_0_USED
#define UART_0_RX_HANDLER				IRQ_Hdlr_85
#define UART_0_RX_SR					1
#endif

#ifdef UART_CHANNEL_1_USED
#define UART_1_RX_HANDLER				IRQ_Hdlr_88
#define UART_1_RX_SR					4
#endif

#ifdef UART_CHANNEL_2_USED
#define UART_2_RX_HANDLER				IRQ_Hdlr_91
#define UART_2_RX_SR					1
#endif

#ifdef UART_CHANNEL_3_USED
#define UART_3_RX_HANDLER				IRQ_Hdlr_94
#define UART_3_RX_SR					4
#endif

#ifdef UART_CHANNEL_4_USED
#define UART_4_RX_HANDLER				IRQ_Hdlr_97
#define UART_4_RX_SR					1
#endif

#ifdef UART_CHANNEL_5_USED
#define UART_5_RX_HANDLER				IRQ_Hdlr_100
#define UART_4_RX_SR					4
#endif

#endif	/* UART_RX_INTERRUPT_USED */


/* UART_PROTOCOL_EVENT_USED Handlers */
#ifdef UART_PROTOCOL_EVENT_USED

#if ( defined (UART_CHANNEL_0_USED) && defined(UART_CHANNEL_0_ERROR_USED) )
#define UART_0_ERR_HANDLER				IRQ_Hdlr_84
#endif

#if ( defined (UART_CHANNEL_1_USED) && defined(UART_CHANNEL_1_ERROR_USED) )
#define UART_1_ERR_HANDLER				IRQ_Hdlr_87
#endif

#if ( defined (UART_CHANNEL_2_USED) && defined(UART_CHANNEL_2_ERROR_USED) )
#define UART_2_ERR_HANDLER				IRQ_Hdlr_90
#endif

#if ( defined (UART_CHANNEL_3_USED) && defined(UART_CHANNEL_3_ERROR_USED) )
#define UART_3_ERR_HANDLER				IRQ_Hdlr_93
#endif

#if ( defined (UART_CHANNEL_4_USED) && defined(UART_CHANNEL_4_ERROR_USED) )
#define UART_4_ERR_HANDLER				IRQ_Hdlr_96
#endif

#if ( defined (UART_CHANNEL_5_USED) && defined(UART_CHANNEL_5_ERROR_USED) )
#define UART_5_ERR_HANDLER				IRQ_Hdlr_99
#endif

#endif	/* UART_PROTOCOL_EVENT_USED */


#endif /* DRI_UART_CONF_H_ */

/********************************** End of File ******************************/
