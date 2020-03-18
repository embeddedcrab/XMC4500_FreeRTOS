/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		SPI API Source
* Filename:		dri_spi.c
* Author:		HS
* Origin Date:	02/23/2020
* Version:		1.0.0
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	dri_spi.c
 *  @brief:	This header file contains API function definitions for SPI
 */


/******************************************************************************
* Includes
*******************************************************************************/
#include <dri_spi.h>


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
* Private Function Declarations
*******************************************************************************/

static void spi_reconfigure_rx_fifo( void * p_channel, unsigned long data_size );

static void SPI_tx_isr_entry( void * p_channel );
static void SPI_rx_isr_entry( void * p_channel );
static void SPI_err_isr_entry( void * p_channel );



/******************************************************************************
* Public Function Definitions
*******************************************************************************/

/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 *
 */
long SPI_Master_init( void * p_channel, const unsigned char init )
{
	DRIVER_ASSERT( NULL == p_channel, SPI_STATUS_INVALID_ARGUMENT );
	/* Local Variables */
	tStSPI_MasterConfiguartion * p_config_l = ((tStSPI_Master *)p_channel)->p_config;
	tStSPI_MasterControl * p_control_l = ((tStSPI_Master *)p_channel)->p_control;
	eSPI_Status ret_status = SPI_STATUS_FAILED;

	/* Check Initiallization */
	switch( init )
	{
		/* Open SPI Channel */
		case SPI_INIT_OPEN:
			/* Check initialization state */
			if( 1 == p_control_l->state.init )
			{
				ret_status = SPI_STATUS_ALREADY_INITIALIZED;
			}
			else
			{
				/* Initialize SPI channel */
				XMC_SPI_CH_Init( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
									(const XMC_SPI_CH_CONFIG_t *const) p_config_l->p_channel_config );
				/* Set transmit mode of SPI channel */
				XMC_SPI_CH_SetTransmitMode( (XMC_USIC_CH_t *const) p_config_l->p_channel_context, p_config_l->channel_mode );

				/* Check bit order */
				if( SPI_BIT_ORDER_MSB_FIRST == p_config_l->bit_order )
				{
					XMC_SPI_CH_SetBitOrderMsbFirst( (XMC_USIC_CH_t *const) p_config_l->p_channel_context );
				}
				else if( SPI_BIT_ORDER_LSB_FIRST == p_config_l->bit_order )
				{
					XMC_SPI_CH_SetBitOrderLsbFirst( (XMC_USIC_CH_t *const) p_config_l->p_channel_context );
				} else{ /* Not required */ }
				/* Set Farme and Word length */
				XMC_SPI_CH_SetWordLength( (XMC_USIC_CH_t *const) p_config_l->p_channel_context, p_config_l->word_length );
				XMC_SPI_CH_SetFrameLength( (XMC_USIC_CH_t *const) p_config_l->p_channel_context, p_config_l->frame_length );

				/* Set Input pin source configuration */
				XMC_SPI_CH_SetInputSource( (XMC_USIC_CH_t *const) p_config_l->p_channel_context, p_config_l->input_pin,
											p_config_l->input_pin_source );

				/* Configure transmit FIFO */
				XMC_USIC_CH_TXFIFO_Configure( (XMC_USIC_CH_t *const) p_config_l->p_channel_context, 32,
												p_config_l->p_fifo_config->tx_fifo_size, 1U );
				/* Configure receive FIFO */
				XMC_USIC_CH_RXFIFO_Configure( (XMC_USIC_CH_t *const) p_config_l->p_channel_context, 0,
												p_config_l->p_fifo_config->rx_fifo_size, 1U );

				/* Set service request for TX FIFO transmit interrupt */
				XMC_USIC_CH_TXFIFO_SetInterruptNodePointer( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
						XMC_USIC_CH_TXFIFO_INTERRUPT_NODE_POINTER_STANDARD, p_config_l->tx_isr_config->sr );

				/* Set service request for RX FIFO receive interrupt */
				XMC_USIC_CH_RXFIFO_SetInterruptNodePointer( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
								XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD, p_config_l->rx_isr_config->sr );
				XMC_USIC_CH_RXFIFO_SetInterruptNodePointer( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
							XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_ALTERNATE, p_config_l->rx_isr_config->sr );

				/* Protocol Events ISR Configuration */
				#if (SPI_PROTOCOL_EVENTS_USED == 1U)/* XMC_SPI_CH_EVENT_PARITY_ERROR */
				XMC_SPI_CH_EnableEvent( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
										(XMC_SPI_CH_EVENT_DATA_LOST | XMC_SPI_CH_EVENT_BAUD_RATE_GENERATOR ) );
				XMC_SPI_CH_SelectInterruptNodePointer( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
						XMC_USIC_CH_INTERRUPT_NODE_POINTER_PROTOCOL, p_config_l->protocol_isr_config->sr );
				#endif

				/* Configure NVIC */
				NVIC_SetPriority( (IRQn_Type)p_config_l->tx_isr_config->irq.irq_num,
									NVIC_EncodePriority(NVIC_GetPriorityGrouping(),
									(IRQn_Type)p_config_l->tx_isr_config->irq.irq_priority, 0U) );
				NVIC_SetPriority( (IRQn_Type)p_config_l->rx_isr_config->irq.irq_num,
									NVIC_EncodePriority(NVIC_GetPriorityGrouping(),
									(IRQn_Type)p_config_l->rx_isr_config->irq.irq_priority, 0U) );
				#if (SPI_PROTOCOL_EVENTS_USED == 1U)
				NVIC_SetPriority( (IRQn_Type)p_config_l->protocol_isr_config->irq.irq_num,
									NVIC_EncodePriority(NVIC_GetPriorityGrouping(),
									(IRQn_Type)p_config_l->protocol_isr_config->irq.irq_priority, 0U) );
				NVIC_EnableIRQ( (IRQn_Type)p_config_l->protocol_isr_config->irq.irq_num );
				#endif
				NVIC_EnableIRQ( (IRQn_Type)p_config_l->tx_isr_config->irq.irq_num );
				NVIC_EnableIRQ( (IRQn_Type)p_config_l->rx_isr_config->irq.irq_num );

				/* Enable data transmission */
				XMC_SPI_CH_EnableDataTransmission( (XMC_USIC_CH_t *const) p_config_l->p_channel_context );
				XMC_SPI_CH_ConfigureShiftClockOutput( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
					XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_1_DELAY_DISABLED, XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK );
				XMC_SPI_CH_DisableSlaveSelect( (XMC_USIC_CH_t *const) p_config_l->p_channel_context );
				/* Start SPI Channel */
				XMC_SPI_CH_Start( (XMC_USIC_CH_t *const) p_config_l->p_channel_context );

				/* Update Channel parameters */
				p_control_l->p_tx_data = NULL; p_control_l->p_rx_data = NULL;
				p_control_l->tx_data_index = 0; p_control_l->tx_data_count = 0;
				p_control_l->rx_data_index = 0; p_control_l->rx_data_count = 0;
				p_control_l->state.tx_busy = 0; p_control_l->state.rx_busy = 0;
				p_control_l->state.tx_dummy = 0;
				p_control_l->state.slave = SPI_SLAVE_SEL0;
				p_control_l->state.init = 1;

				/* Update return status */
				ret_status = SPI_STATUS_SUCCESS;
			}
		break;
		/* Close SPI Channel */
		case SPI_INIT_CLOSE:
		{
			XMC_SPI_CH_STATUS_t status_l;
			status_l = XMC_SPI_CH_Stop( (XMC_USIC_CH_t *const) p_config_l->p_channel_context );
			if( (XMC_SPI_CH_STATUS_ERROR == status_l) || (XMC_SPI_CH_STATUS_BUSY == status_l) )
			{
				ret_status = SPI_STATUS_FAILED;
			}
			else
			{
				ret_status = SPI_STATUS_SUCCESS;
				/* update initialization satte */
				p_control_l->state.init = 0;
			}
		}
		break;
		/* Error input in SPI Channel */
		default:
			ret_status = SPI_STATUS_INVALID_ARGUMENT;
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
 *
 */
long SPI_Master_set_slave( void * p_channel, const unsigned char slave )
{
	DRIVER_ASSERT( NULL == p_channel, SPI_STATUS_INVALID_ARGUMENT );
	DRIVER_ASSERT( slave > (SPI_MAX_SLAVES_AVAILABLE - 1), SPI_STATUS_OUT_OF_BOUND );
	/* Local Variables */
	tStSPI_MasterControl * p_control_l = ((tStSPI_Master *)p_channel)->p_control;
	eSPI_Status ret_status = SPI_STATUS_SUCCESS;

	/* Check busy status */
	if( (0 == p_control_l->state.tx_busy) && (0 == p_control_l->state.rx_busy) && (0 == p_control_l->state.slave_set) )
	{
		/* Check slave number */
		switch( slave )
		{
			case 0:
				p_control_l->state.slave = SPI_SLAVE_SEL0;
			break;
			case 1:
				p_control_l->state.slave = SPI_SLAVE_SEL1;
			break;
			case 2:
				p_control_l->state.slave = SPI_SLAVE_SEL2;
			break;
			case 3:
				p_control_l->state.slave = SPI_SLAVE_SEL3;
			break;
			default:
				ret_status = SPI_STATUS_OUT_OF_BOUND;
		}
	}
	else
	{
		ret_status = SPI_STATUS_BUSY;
	}

	/* Update return status */
	return ret_status;
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 *
 */
void SPI_Master_slave_select( void * p_channel, const unsigned char slave_state )
{
	DRIVER_ASSERT_NRET( NULL == p_channel );
	/* Local Variables */
	tStSPI_MasterConfiguartion * p_config_l = ((tStSPI_Master *)p_channel)->p_config;
	tStSPI_MasterControl * p_control_l = ((tStSPI_Master *)p_channel)->p_control;

	/* Check state */
	if( 1 == slave_state )
	{
		XMC_SPI_CH_EnableSlaveSelect( (XMC_USIC_CH_t *const) p_config_l->p_channel_context, p_control_l->state.slave );
		/* Disable Slave select operation for other Slaves */
		p_control_l->state.slave_set = 1;
	}
	else if( 0 == slave_state )
	{
		XMC_SPI_CH_DisableSlaveSelect( (XMC_USIC_CH_t *const) p_config_l->p_channel_context );
		/* Enable Slave select operation for other Slaves */
		p_control_l->state.slave_set = 0;
	} else{ /* Not Required */ }
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 *
 */
long SPI_Master_set_mode( void * p_channel, const unsigned char mode )
{
	DRIVER_ASSERT_NRET( NULL == p_channel );
	DRIVER_ASSERT_NRET( mode > (SPI_MAX_MODES_AVAILABLE - 1) );
	/* Local Variables */
	tStSPI_MasterConfiguartion * p_config_l = ((tStSPI_Master *)p_channel)->p_config;
	tStSPI_MasterControl * p_control_l = ((tStSPI_Master *)p_channel)->p_control;
	eSPI_Status ret_status = SPI_STATUS_SUCCESS;

	/* Check busy state */
	if( (0 == p_control_l->state.tx_busy) && (0 == p_control_l->state.rx_busy) )
	{
		/* Check slave number */
		switch( mode )
		{
		default:
			case 0:
				p_config_l->channel_mode = XMC_SPI_CH_MODE_STANDARD;
			break;
			case 1:
				p_config_l->channel_mode = XMC_SPI_CH_MODE_STANDARD_HALFDUPLEX;
			break;
			case 2:
				p_config_l->channel_mode = XMC_SPI_CH_MODE_DUAL;
			break;
			case 3:
				p_config_l->channel_mode = XMC_SPI_CH_MODE_QUAD;
			break;
		}
	}
	else
	{
		ret_status = SPI_STATUS_BUSY;
	}

	/* Update return status */
	return ret_status;
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 *
 */
long SPI_Master_set_data_size( void * p_channel, const unsigned char size )
{
	DRIVER_ASSERT( NULL == p_channel, SPI_STATUS_INVALID_ARGUMENT );
	/* Local Variables */
	tStSPI_MasterControl * p_control_l = ((tStSPI_Master *)p_channel)->p_control;
	eSPI_Status ret_status = SPI_STATUS_SUCCESS;;

	/* Check data size */
	switch( size )
	{
		case SPI_DATA_SIZE_BYTE:
			p_control_l->state.size = 0;
		break;
		case SPI_DATA_SIZE_WORD:
			p_control_l->state.size = 1;
		break;
		default:
			ret_status = SPI_STATUS_INVALID_ARGUMENT;
		break;
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
 *
 */
long SPI_Master_set_speed( void * p_channel, const unsigned long speed )
{
	DRIVER_ASSERT( NULL == p_channel, SPI_STATUS_INVALID_ARGUMENT );
	/* Local Variables */
	tStSPI_MasterConfiguartion * p_config_l = ((tStSPI_Master *)p_channel)->p_config;
	eSPI_Status ret_status = SPI_STATUS_FAILED;
	XMC_SPI_CH_STATUS_t status_l = XMC_SPI_CH_STATUS_ERROR;

	/* Set Baud rate of SPI channel */
	status_l = XMC_SPI_CH_SetBaudrate( (XMC_USIC_CH_t *const) p_config_l->p_channel_context, speed );
	/* Check status */
	if( status_l != XMC_SPI_CH_STATUS_ERROR )
	{
		/* Update parameters */
		ret_status = SPI_STATUS_SUCCESS;
		p_config_l->p_channel_config->baudrate = speed;
	}
	else
	{
		/* Do Nothing */
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
 *
 */
long SPI_Master_transmit( void * p_channel, const unsigned char * p_data, const unsigned long length )
{
	DRIVER_ASSERT( NULL == p_channel, SPI_STATUS_INVALID_ARGUMENT );
	DRIVER_ASSERT( NULL == p_data, SPI_STATUS_INVALID_ARGUMENT );
	DRIVER_ASSERT( 0 == length, SPI_STATUS_INVALID_ARGUMENT );
	/* Local Variables */
	tStSPI_MasterConfiguartion * p_config_l = ((tStSPI_Master *)p_channel)->p_config;
	tStSPI_MasterControl * p_control_l = ((tStSPI_Master *)p_channel)->p_control;
	eSPI_Status ret_status = SPI_STATUS_FAILED;

	/* Check initialization of SPI Channel */
	if( 1 == p_control_l->state.init )
	{
		/* Check busy status */
		if( 1 == p_control_l->state.tx_busy )
		{
			ret_status = SPI_STATUS_BUSY;
		}
		else
		{
			#if (SPI_INTERNAL_SLAVE_SELECT_USED == 1U)
			/* Select Slave */
			XMC_SPI_CH_EnableSlaveSelect( (XMC_USIC_CH_t *const) p_config_l->p_channel_context, p_control_l->state.slave );
			#endif
			/* Update data parameters */
			p_control_l->state.tx_busy = 1;
			p_control_l->p_tx_data = (1 == p_control_l->state.tx_dummy) ? NULL : (unsigned char *)p_data;
			p_control_l->tx_data_count = length;
			p_control_l->tx_data_index = 0;

			/* Check FIFO usage */
			if( p_config_l->p_fifo_config->tx_fifo_size != XMC_USIC_CH_FIFO_DISABLED )
			{
				/* Clear transmit FIFO */
				XMC_USIC_CH_TXFIFO_Flush( (XMC_USIC_CH_t *const) p_config_l->p_channel_context );
				/* Enable transmit buffer event */
				XMC_USIC_CH_TXFIFO_EnableEvent( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
												XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD );
			}
			else
			{
				/* Enable Event */
				XMC_SPI_CH_EnableEvent( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
										XMC_USIC_CH_EVENT_TRANSMIT_BUFFER );
			}

			/* Trigger transmission */
			XMC_SPI_CH_TriggerServiceRequest( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
												p_config_l->tx_isr_config->sr );
			ret_status = SPI_STATUS_SUCCESS;
			/* Wait while transmission is not completed */
			while( 1 == p_control_l->state.tx_busy );
		}
	}
	else
	{
		/* Update status */
		ret_status = SPI_STATUS_NOT_INITIALIZED;
	}

	/* Update return status */
	return ret_status;
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 *
 */
long SPI_Master_receive( void * p_channel, unsigned char * const p_data, const unsigned long length )
{
	DRIVER_ASSERT( NULL == p_channel, SPI_STATUS_INVALID_ARGUMENT );
	DRIVER_ASSERT( NULL == p_data, SPI_STATUS_INVALID_ARGUMENT );
	DRIVER_ASSERT( 0 == length, SPI_STATUS_INVALID_ARGUMENT );
	/* Local Variables */
	tStSPI_MasterConfiguartion * p_config_l = ((tStSPI_Master *)p_channel)->p_config;
	tStSPI_MasterControl * p_control_l = ((tStSPI_Master *)p_channel)->p_control;

	static unsigned char data_dummy[2] = {0xFF, 0xFF};
	eSPI_Status ret_status = SPI_STATUS_FAILED;

	/* Check initialization of SPI Channel */
	if( 1 == p_control_l->state.init )
	{
		/* Check busy status */
		if( (1 == p_control_l->state.rx_busy) || (1 == p_control_l->state.tx_busy) )
		{
			ret_status = SPI_STATUS_BUSY;
		}
		else
		{
			#if (SPI_INTERNAL_SLAVE_SELECT_USED == 1U)
			/* Select Slave */
			XMC_SPI_CH_EnableSlaveSelect( (XMC_USIC_CH_t *const) p_config_l->p_channel_context, p_control_l->state.slave );
			#endif
			/* Update data parameters */
			p_control_l->state.rx_busy = 1;
			p_control_l->state.tx_dummy = 1;
			p_control_l->p_rx_data = (unsigned char *)p_data;

			p_control_l->rx_data_count = (0 == p_control_l->state.size) ? length : (length >> 1);
			p_control_l->rx_data_index = 0;

			/* Check FIFO usage */
			if( p_config_l->p_fifo_config->rx_fifo_size != XMC_USIC_CH_FIFO_DISABLED )
			{
				/* Clear receiver FIFO */
				XMC_USIC_CH_RXFIFO_Flush( (XMC_USIC_CH_t *)(p_config_l->p_channel_context) );
				/* TODO: Nullify Receive Buffer */
				(void) XMC_USIC_CH_RXFIFO_GetData( (XMC_USIC_CH_t *)(p_config_l->p_channel_context) );
				(void) XMC_USIC_CH_RXFIFO_GetData( (XMC_USIC_CH_t *)(p_config_l->p_channel_context) );

				/* Reconfigure FIFO for current data size */
				spi_reconfigure_rx_fifo( p_channel, p_control_l->rx_data_count );

				/* Enable receive buffer event */
				XMC_USIC_CH_RXFIFO_EnableEvent( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
					(XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD | XMC_USIC_CH_RXFIFO_EVENT_CONF_ALTERNATE) );
			}
			else
			{
				/* TODO: Nullify Receive Buffer */
				(void) XMC_USIC_CH_RXFIFO_GetData( (XMC_USIC_CH_t *)(p_config_l->p_channel_context) );
				(void) XMC_USIC_CH_RXFIFO_GetData( (XMC_USIC_CH_t *)(p_config_l->p_channel_context) );

				/* Enable receive buffer event */
				XMC_USIC_CH_RXFIFO_EnableEvent( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
						(XMC_USIC_CH_EVENT_STANDARD_RECEIVE | XMC_USIC_CH_EVENT_ALTERNATIVE_RECEIVE) );
			}
			/* Start dummy transmission for reception */
			ret_status = SPI_Master_transmit( p_channel, data_dummy, p_control_l->rx_data_count );
			/* Wait while reception is not completed */
			while( 1 == p_control_l->state.rx_busy );
		}
	}
	else
	{
		/* Update status */
		ret_status = SPI_STATUS_NOT_INITIALIZED;
	}

	/* Update return status */
	return ret_status;
}


/**
 * @function
 *
 * @brief
 *
 * <i>Imp Note:</i>
 *
 */
long SPI_Master_abort( void * p_channel, const unsigned char tx_rx )
{
}


/******************************************************************************
* Private Function Definitions
*******************************************************************************/

/**
 * @function
 *
 * @brief
 *
 * @param[in]
 *
 * \par<b>Description:</b><br>
 *
 * <i>Imp Note:</i>
 *
 */
void spi_reconfigure_rx_fifo( void * p_channel, unsigned long data_size )
{
	/* Local Variables */
	tStSPI_MasterConfiguartion * p_config_l = ((tStSPI_Master *)p_channel)->p_config;
	unsigned long fifo_size = 0U;
	unsigned long ret_limit_val = 0U;

	/* Get FIFO size in bytes */
	fifo_size = (unsigned long) ( 0x01UL << (unsigned char) (p_config_l->p_fifo_config->rx_fifo_size) );
	/* If data size is more than FIFO size, configure the limit to the FIFO size */
	ret_limit_val = ( data_size < fifo_size ) ? data_size - 1U : fifo_size - 1U;
	/* Set the limit value */
	XMC_USIC_CH_RXFIFO_SetSizeTriggerLimit( (XMC_USIC_CH_t *const)p_config_l->p_channel_context,
											p_config_l->p_fifo_config->rx_fifo_size, ret_limit_val );
}


/*****************************************************************************/

void SPI_tx_isr_entry( void * p_channel )
{
	/* Local Arguments */
	tStSPI_MasterConfiguartion * p_config_l = ((tStSPI_Master *)p_channel)->p_config;
	tStSPI_MasterControl * p_control_l = ((tStSPI_Master *)p_channel)->p_control;

	/* Check the busy flag for authentication */
	if( 1 == p_control_l->state.tx_busy )
	{
		/* Check data count and take decision */
		if( p_control_l->tx_data_index < p_control_l->tx_data_count )
		{
			/* Check FIFO used or not */
			if( p_config_l->p_fifo_config->tx_fifo_size != XMC_USIC_CH_FIFO_DISABLED )
			{
				/* Fill FIFO and send data */
				while( 0 == XMC_USIC_CH_TXFIFO_IsFull( (XMC_USIC_CH_t *const) p_config_l->p_channel_context ) )
				{
					if( p_control_l->tx_data_index < p_control_l->tx_data_count )
					{
						/* Check for dummy transfer */
						if( 1 == p_control_l->state.tx_dummy )
						{
							/* Load the FIFO byte by byte till either FIFO is full or all data is loaded */
							XMC_USIC_CH_TXFIFO_PutDataHPCMode( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
																0xFFFF, (unsigned long)p_config_l->channel_mode );
						}
						else
						{
							if( 0 == p_control_l->state.size )
							{
								/* Load the FIFO byte by byte till either FIFO is full or all data is loaded */
								XMC_USIC_CH_TXFIFO_PutDataHPCMode( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
												*((unsigned char *)(p_control_l->p_tx_data + p_control_l->tx_data_index)),
												(unsigned long)p_config_l->channel_mode );
								/* Increment data index for byte addressing */
								++(p_control_l->tx_data_index);
							}
							else
							{
								/* Load the FIFO byte by byte till either FIFO is full or all data is loaded */
								XMC_USIC_CH_TXFIFO_PutDataHPCMode( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
												*((unsigned short *)(p_control_l->p_tx_data + p_control_l->tx_data_index)),
												(unsigned long)p_config_l->channel_mode );
								/* Increment data index for word addressing */
								p_control_l->tx_data_index += 2;
							}
						}
					}
					else
					{
						/* FIFO has been filled completely or data has been loaded into it */
						break;
					}
				}
			}
			else/* Send directly */
			{
				/* Check for dummy transfer */
				if( 1 == p_control_l->state.tx_dummy )
				{
					XMC_USIC_CH_WriteToTBUFTCI( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
													0xFFFF, (unsigned long)p_config_l->channel_mode );
				}
				else
				{
					/* Check data size format */
					if( 0 == p_control_l->state.size )
					{
						XMC_USIC_CH_WriteToTBUFTCI( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
									*((unsigned short *)(p_control_l->p_tx_data + p_control_l->tx_data_index)),
									(unsigned long)p_config_l->channel_mode );
						/* Increment data index for byte addressing */
						++(p_control_l->tx_data_index);
					}
					else
					{
						XMC_USIC_CH_WriteToTBUFTCI( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
									*((unsigned char *)(p_control_l->p_tx_data + p_control_l->tx_data_index)),
									(unsigned long)p_config_l->channel_mode );
						/* Increment data index for word addressing */
						p_control_l->tx_data_index += 2;
					}
				}
			}
		}
		else
		{/* Data was sent, ensure complete transfer */
			/* Check FIFO empty status now */
			if( 1 == XMC_USIC_CH_TXFIFO_IsEmpty( (XMC_USIC_CH_t *const) p_config_l->p_channel_context ) )
			{
				if( p_config_l->p_fifo_config->tx_fifo_size != XMC_USIC_CH_FIFO_DISABLED )
				{
					/* Disable fifo transmit event event */
					XMC_USIC_CH_TXFIFO_DisableEvent( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
														XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD );
				}
				else
				{
					/* Disable standard transmit event */
					XMC_USIC_CH_DisableEvent( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
												XMC_USIC_CH_EVENT_TRANSMIT_BUFFER );
				}
				/* Wait for transmit buffer to get free to ensure data has been sent */
				while( XMC_USIC_CH_TBUF_STATUS_BUSY ==
						XMC_USIC_CH_GetTransmitBufferStatus( (XMC_USIC_CH_t *const) p_config_l->p_channel_context )
						);

				/* Release resources for transmission */
				p_control_l->p_tx_data = NULL;
				p_control_l->state.tx_busy = 0;
				/* Select Slave */
				if( 0 == p_control_l->state.tx_dummy )
				{
					#if (SPI_INTERNAL_SLAVE_SELECT_USED == 1U)
					XMC_SPI_CH_DisableSlaveSelect( (XMC_USIC_CH_t *const) p_config_l->p_channel_context );
					#endif
				}
				/* Call callback if available */
				#if( SPI_CALLBACK_HANDLER_USED == 1U )
				((tStSPI_Master*)p_channel)->p_callback->fp_callback( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
																		NULL, SPI_EVENT_TRANSMIT );
				#endif
			}
		}
	}
}


/**
 * @function	SPI_rx_isr_entry
 *
 * @brief		SPI Reception ISR body
 *
 * <i>Imp Note:</i>
 *
 */
void SPI_rx_isr_entry( void * p_channel )
{
	/* Local Arguments */
	tStSPI_MasterConfiguartion * p_config_l = ((tStSPI_Master *)p_channel)->p_config;
	tStSPI_MasterControl * p_control_l = ((tStSPI_Master *)p_channel)->p_control;
	unsigned short data_l = 0;

	/* Check the busy flag for authentication */
	if( 1 == p_control_l->state.rx_busy )
	{
		/* Check data count and take decision */
		if( p_config_l->p_fifo_config->tx_fifo_size != XMC_USIC_CH_FIFO_DISABLED )
		{
			/* Read data from FIFO */
			while( 0 == XMC_USIC_CH_RXFIFO_IsEmpty( (XMC_USIC_CH_t *const) p_config_l->p_channel_context ) )
			{
				/* Receive data */
				if( p_control_l->rx_data_index < p_control_l->rx_data_count )
				{
					data_l = XMC_SPI_CH_GetReceivedData( (XMC_USIC_CH_t *const) p_config_l->p_channel_context );
					/* Get data into Buffer */
					p_control_l->p_rx_data[p_control_l->rx_data_index] = (unsigned char)(data_l & 0xFF);
					if( 1 == p_control_l->state.size )
					{
						p_control_l->p_rx_data[p_control_l->rx_data_index + 1] = (unsigned char)((data_l >> 8) & 0xFF);
						/* Increment data index */
						p_control_l->rx_data_index += 2;
					}
					else
					{
						/* Increment data index */
						++(p_control_l->rx_data_index);
					}
				}
				/* Check for data count and index equality */
				if( p_control_l->rx_data_index == p_control_l->rx_data_count )
				{
					/* Release FIFO and reset parameters*/
					p_control_l->state.rx_busy = 0;
					XMC_USIC_CH_RXFIFO_DisableEvent( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
						(XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD | XMC_USIC_CH_RXFIFO_EVENT_CONF_ALTERNATE) );
					/* Select Slave */
					if( 1 == p_control_l->state.tx_dummy )
					{
						#if (SPI_INTERNAL_SLAVE_SELECT_USED == 1U)
						XMC_SPI_CH_DisableSlaveSelect( (XMC_USIC_CH_t *const) p_config_l->p_channel_context );
						#endif
						p_control_l->state.tx_dummy = 0;
					}

					/* Call callback if available */
					#if( SPI_CALLBACK_HANDLER_USED == 1U )
					((tStSPI_Master*)p_channel)->p_callback->fp_callback( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
																			NULL, SPI_EVENT_RECEIVE );
					#endif
					/* Break operation */
					break;
				}
			}
			/* Dynamically setup the trigger limit for FIFO */
			if( p_control_l->rx_data_index < p_control_l->rx_data_count )
			{
				spi_reconfigure_rx_fifo( p_channel, p_control_l->rx_data_count - p_control_l->rx_data_index );
			}
		}
		else/* Direct Read and read completion check */
		{
			/* Check Buffer status */
			if( XMC_USIC_CH_GetReceiveBufferStatus( (XMC_USIC_CH_t *const) p_config_l->p_channel_context ) !=
					XMC_USIC_CH_RBUF_STATUS_DATA_VALID0
			)
			{
				/* Directly receive data from Buffers, FIFO is disabled */
				if( p_control_l->rx_data_index < p_control_l->rx_data_count )
				{
					data_l = XMC_SPI_CH_GetReceivedData( (XMC_USIC_CH_t *const) p_config_l->p_channel_context );
					/* Get data into Buffer */
					p_control_l->p_rx_data[p_control_l->rx_data_index] = (unsigned char)(data_l & 0xFF);
					if( 1 == p_control_l->state.size )
					{
						p_control_l->p_rx_data[p_control_l->rx_data_index + 1] = (unsigned char)((data_l >> 8) & 0xFF);
						/* Increment data index */
						p_control_l->rx_data_index += 2;
					}
					else
					{
						/* Increment data index */
						++(p_control_l->rx_data_index);
					}
				}
			}
			if( XMC_USIC_CH_RBUF_STATUS_DATA_VALID1 ==
					XMC_USIC_CH_GetReceiveBufferStatus( (XMC_USIC_CH_t *const) p_config_l->p_channel_context )
			)
			{
				/* Directly receive data from Buffers, FIFO is disabled */
				if( p_control_l->rx_data_index < p_control_l->rx_data_count )
				{
					data_l = XMC_SPI_CH_GetReceivedData( (XMC_USIC_CH_t *const) p_config_l->p_channel_context );
					/* Get data into Buffer */
					p_control_l->p_rx_data[p_control_l->rx_data_index] = (unsigned char)(data_l & 0xFF);
					if( 1 == p_control_l->state.size )
					{
						p_control_l->p_rx_data[p_control_l->rx_data_index + 1] = (unsigned char)((data_l >> 8) & 0xFF);
						/* Increment data index */
						p_control_l->rx_data_index += 2;
					}
					else
					{
						/* Increment data index */
						++(p_control_l->rx_data_index);
					}
				}
			}

			/* Check for data count and index equality */
			if( p_control_l->rx_data_index == p_control_l->rx_data_count )
			{
				/* Release resources for transmission */
				p_control_l->p_rx_data = NULL;
				p_control_l->state.rx_busy = 0;
				/* Disable events */
				XMC_USIC_CH_RXFIFO_DisableEvent( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
						(XMC_USIC_CH_EVENT_STANDARD_RECEIVE | XMC_USIC_CH_EVENT_ALTERNATIVE_RECEIVE) );
				/* Select Slave */
				if( 1 == p_control_l->state.tx_dummy )
				{
					#if (SPI_INTERNAL_SLAVE_SELECT_USED == 1U)
					XMC_SPI_CH_DisableSlaveSelect( (XMC_USIC_CH_t *const) p_config_l->p_channel_context );
					#endif
					p_control_l->state.tx_dummy = 0;
				}
				/* Call callback if available */
				#if( SPI_CALLBACK_HANDLER_USED == 1U )
				((tStSPI_Master*)p_channel)->p_callback->fp_callback( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
						NULL, SPI_EVENT_RECEIVE );
				#endif
			}
		}
	}
}


#if (SPI_PROTOCOL_EVENTS_USED == 1U)
/**
 * @function	SPI_err_isr_entry
 *
 * @brief		SPI Protocol Error ISR body
 *
 * <i>Imp Note:</i>
 *
 */
void SPI_err_isr_entry( void * p_channel )
{
	/* Local Arguments */
	tStSPI_MasterConfiguartion * p_config_l = ((tStSPI_Master *)p_channel)->p_config;

	unsigned long status_l = 0;

	/* Check status of Error */
	status_l = XMC_SPI_CH_GetStatusFlag( (XMC_USIC_CH_t *const) p_config_l->p_channel_context );

	/* Data Lost Error */
	if( status_l & XMC_SPI_CH_STATUS_FLAG_DATA_LOST_INDICATION )
	{
		/* Call callback */
		#if( SPI_CALLBACK_HANDLER_USED == 1U )
		((tStSPI_Master*)p_channel)->p_callback->fp_callback( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
																NULL, SPI_EVENT_DATA_LOST );
		#endif
	}

	/* Baud Rate Generator Error */
	if( status_l & XMC_SPI_CH_STATUS_FLAG_BAUD_RATE_GENERATOR_INDICATION )
	{
		/* Call callback */
		#if( SPI_CALLBACK_HANDLER_USED == 1U )
		((tStSPI_Master*)p_channel)->p_callback->fp_callback( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
																NULL, SPI_EVENT_BAUDRATE_ERROR );
		#endif
	}

	/* Parity Error */
	if( status_l & XMC_SPI_CH_STATUS_FLAG_PARITY_ERROR_EVENT_DETECTED )
	{
		/* Call callback */
		#if( SPI_CALLBACK_HANDLER_USED == 1U )
		((tStSPI_Master*)p_channel)->p_callback->fp_callback( (XMC_USIC_CH_t *const) p_config_l->p_channel_context,
																NULL, SPI_EVENT_PARITY_ERROR );
		#endif
	}
}

#endif	/* SPI_PROTOCOL_EVENTS_USED */


/*****************************************************************************/


void SPI_isr_entry( void * p_channel, const eSPI_InterruptOperation type );
void SPI_isr_entry( void * p_channel, const eSPI_InterruptOperation type )
{
	DRIVER_ASSERT_NRET( NULL == p_channel );
	/* Check for SPI channel and type of ISR request */
	switch( type )
	{
	default:/* Considering all cases in default */
		case SPI_INTERRUPT_OPERATION_TX:
			SPI_tx_isr_entry( p_channel );
		break;
		case SPI_INTERRUPT_OPERATION_RX:
			SPI_rx_isr_entry( p_channel );
		break;
		#if (SPI_PROTOCOL_EVENTS_USED == 1U)
		case SPI_INTERRUPT_PROTOCOl_ERROR:
			SPI_err_isr_entry( p_channel );
		break;
		#endif
	}
}

/********************************** End of File *******************************/
