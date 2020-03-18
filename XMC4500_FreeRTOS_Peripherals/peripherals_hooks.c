/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		Peripherals Hooks Source
* Filename:		peripherals_hooks.c
* Author:		HS
* Origin Date:
* Version:
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	peripherals_hooks.c
 *  @brief:	This source file contains callback functions for peripherals
 */


/******************************************************************************
* Includes
*******************************************************************************/

/* Include Master Configuration */
#include <master_config.h>

/* Include peripherals files*/
#include <dri_uart_extern.h>
#include <dri_vadc_extern.h>
#include <dri_ccu_extern.h>
#include <dri_can_extern.h>
#include <dri_spi_extern.h>
#include <dri_dac_extern.h>
#include <dri_rtc_extern.h>
#include <dri_scu_extern.h>


/* Include Standard Headers */
#include <stdio.h>
#include <dri_mem.h>



/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Functions
*******************************************************************************/

#if (UART_CALLBACK_HANDLER_USED == 1U)
/* UART Callback handler */
void UART_callback_handler( const eUART_Channel channel, unsigned char *p_data, const eUART_Event event );
void UART_callback_handler( const eUART_Channel channel, unsigned char *p_data, const eUART_Event event )
{
	/* Local variables */
	unsigned char * p_data_l = p_data;

	/* Check events */
	switch( event )
	{
		default:
		case UART_EVENT_TX_COMPLETE:
			if( UART_CHANNEL_0 == channel )
			{
				/* Transmission successful! */
				__asm("NOP");
			}
			break;

		case UART_EVENT_RX_COMPLETE:
			if( UART_CHANNEL_0 == channel )
			{
				/* Reception successful! */
				__asm("NOP");
			}
			break;
		case UART_EVENT_RX_CHAR:
			switch( channel )
			{
			default:
			case UART_CHANNEL_0:
				/* Reception successfull, transmit received data */
				UART_Api_Functions.fp_transmit( &UART_Channel_0, p_data_l, 1 );
				break;
			case UART_CHANNEL_2:
				/* Reception successfull, transmit received data */
				UART_Api_Functions.fp_transmit( &UART_Channel_2, p_data_l, 1 );/* Utilized in Logging, disabled for now */
				break;
			}

			break;
	}
}
#endif	/* UART_CALLBACK_HANDLER_USED */


#if (VADC_CALLBACK_HANDLER_USED == 1U)
/* VADC Callback Handler */
void VADC_callback_handler( void * p_group, unsigned short *p_data );
void VADC_callback_handler( void * p_group, unsigned short *p_data )
{
	/* Local variables */
	XMC_VADC_GROUP_t * group_l = (XMC_VADC_GROUP_t *) (((tStVADC_BackgroundScan *)p_group)->p_config->p_background_scan_group_config->p_group_context);
	unsigned short * p_data_l = p_data;
	unsigned char data_l[20];

	/* Can trigger conversion for VADC Group */
	switch( VADC_get_group(group_l) )
	{
	default:
		case 0:
			/* Send ADC Channels data for Logging,
			 * Note: for Test only (not to be used in projects)
			 *
			 * Rather you can fill the data values in a queue and trigger a task to send values to Console */
			for( unsigned char count_l = 0; count_l < VADC_GROUP0_CHANNELS_USED; ++count_l )
			{
				sprintf( (char *)data_l, "VADC G0 Ch%d - %d", count_l, p_data_l[count_l] );
//				UART_Api_Functions.fp_transmit( &UART_Channel_0, data_l, strlen((char *)data_l) );
			}
			/* Trigger Conversion again */
			VADC_background_scan_start_conversion( GLOBAL_VADC );
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
#endif	/* VADC_CALLBACK_HANDLER_USED */


/* Callback handler for user */
#if (DAC_CALLBACK_HANDLER_USED == 1U)
void DAC_callback_handler( void * p_channel );
void DAC_callback_handler( void * p_channel )
{
	(void) p_channel;
}
#endif	/* DAC_CALLBACK_HANDLER_USED */


/* CCU4 Callback Handler */
#if (CCU4_CALLBACK_HANDLER_USED == 1U)
void CCU4_callback_handler( void * p_channel, unsigned long *p_data );
void CCU4_callback_handler( void * p_channel, unsigned long *p_data )
{
	(void) p_channel;
	(void) p_data;
}
#endif	/* CCU4_CALLBACK_HANDLER_USED */


/* CCU8 Callback Handler */
#if (CCU8_CALLBACK_HANDLER_USED == 1U)
void CCU8_callback_handler( void * p_channel );
void CCU8_callback_handler( void * p_channel )
{
	(void) p_channel;
}
#endif	/* CCU8_CALLBACK_HANDLER_USED */


/* CAN Callback Handler */
#if (CAN_CALLBACK_HANDLER_USED == 1U)
void CAN_callback_handler( void * p_channel, const eCAN_EventType event_type, const eCAN_Event event );
void CAN_callback_handler( void * p_channel, const eCAN_EventType event_type, const eCAN_Event event )
{
	DRIVER_ASSERT_NRET( NULL == p_channel );
	/* Local Variables */
	tStCAN_NodeConfiguartion * const p_config_l = ((tStCAN_Node *)p_channel)->p_config;
	tStCAN_Control * const p_control_l = ((tStCAN_Node *)p_channel)->p_control;

	/* Check Event Type */
	switch( event_type )
	{
	default:
		case CAN_EVENT_TYPE_NODE_TRANSFER:
		/* Check Node Transfer event */
		switch( event )
		{
		default:
			case CAN_EVENT_NODE_TRANSFER_TRANSMIT:
				if( (1 == p_control_l->state.init) && (1 == p_control_l->state.tx_busy) )
				{
					p_control_l->state.tx_busy = 0;
				}
			break;
			case CAN_EVENT_NODE_TRANSFER_RECEIVE:
				if( (1 == p_control_l->state.init) && (0 == p_control_l->state.rx_busy) )
				{
					XMC_CAN_MO_ReceiveData( p_config_l->p_message_rx );
					p_control_l->state.rx_busy = 0;
				}
				else/* Direct Read Data from CAN Node in a common Mo */
				{
				}
			break;
		}
		break;	/* CAN_EVENT_TYPE_NODE_TRANSFER */
	}
}
#endif


/* SPI Callback Handler */
#if (SPI_CALLBACK_HANDLER_USED == 1U)
void SPI_callback_handler( void * p_channel, void * p_data, const eSPI_Events event );
void SPI_callback_handler( void * p_channel, void * p_data, const eSPI_Events event )
{
	/* Local Variables */
	tStSPI_MasterConfiguartion * p_config_l = ((tStSPI_Master *)p_channel)->p_config;
	tStSPI_MasterControl * p_control_l = ((tStSPI_Master *)p_channel)->p_control;
	(void) p_config_l;
	(void) p_control_l;

	/* Check event type */
	switch( event )
	{
	default:
		/* Data Transfer Events */
		case SPI_EVENT_TRANSMIT:
		break;
		case SPI_EVENT_RECEIVE:
		break;
		/* Error Events */
		case SPI_EVENT_DATA_LOST:
		break;
		case SPI_EVENT_BAUDRATE_ERROR:
		break;
		case SPI_EVENT_PARITY_ERROR:
		break;
	}
}
#endif


/* IIC Callback Handler */
#if (IIC_CALLBACK_HANDLER_USED == 1U)
void IIC_callback_handler( void * p_channel, void * p_data, const eIIC_Events event );
void IIC_callback_handler( void * p_channel, void * p_data, const eIIC_Events event )
{
	/* Local Variables */
	tStIIC_MasterConfiguartion * p_config_l = ((tStIIC_Master *)p_channel)->p_config;
	tStIIC_MasterControl * p_control_l = ((tStIIC_Master *)p_channel)->p_control;

	/* Check event type */
	switch( event )
	{
	default:
		case IIC_EVENT_TRANSMIT:
		break;
		case IIC_EVENT_RECEIVE:
		break;
		/* Error Events */
		case IIC_EVENT_DATA_LOST:
		break;
		case IIC_EVENT_BAUDRATE_ERROR:
		break;
		case IIC_EVENT_PARITY_ERROR:
		break;
	}
}
#endif


/* SCU Callback Handler */
#if (SCU_CALLBACK_HANDLER_USED == 1U)
void SCU_callback_handler( void );
void SCU_callback_handler( void )
{
	__asm("NOP");
}
#endif


/* RTC Callback Handler */
#if (RTC_CALLBACK_HANDLER_USED == 1U)
void RTC_callback_handler( void * p_channel, const eRTC_Events event );
void RTC_callback_handler( void * p_channel, const eRTC_Events event )
{
	(void) p_channel;
	(void) event;
}
#endif


/* SDMMC Callback Handler */
#if (SDMMC_CALLBACK_HANDLER_USED == 1U)
void SDMMC_callback_handler( void * p_channel, const eSDMMC_CardInterrupt interrupt );
void SDMMC_callback_handler( void * p_channel, const eSDMMC_CardInterrupt interrupt )
{
	/* Local variables */
	tStSDMMC_Control * p_control_l = ((tStSDMMC_Module *)p_channel)->p_control;
	long status_l = 0;

	/* Check card state and take action */
	switch( interrupt )
	{
	default:
		case SDMMC_SD_INTERRUPT_CARD_INSERTION:
			/* Process if Host controller ahs been initialized fully */
			if( (1 == p_control_l->state.init) && (0 == p_control_l->state.card_present)/* && check card detect pin status */ )
			{
				/* Initialize SD Card and its registers */
				status_l = SDMMC_RTOS_init_card( p_channel );
				if( SDMMC_STATUS_SUCCESS == status_l )
				{
					status_l = SDMMC_RTOS_init_card_registers( p_channel );
					/* Initialize SD card registers */
					if( SDMMC_STATUS_SUCCESS == status_l )
					{
						/* Set state of SDMMC channel */
						p_control_l->state.card_present = 1;
					}
					else
					{
						/* Set state of SDMMC card state */
						p_control_l->state.card_present = 0;
					}
				}
			}
		break;

		case SDMMC_SD_INTERRUPT_CARD_REMOVAL:
			/* De-Initialize SD Card and its registers,
			 * Process if Host controller ahs been initialized fully */
			if( 1 == p_control_l->state.init )
			{
				/* Do processing */
			}
		break;
	}
}
#endif


/********************************** End of File *******************************/
