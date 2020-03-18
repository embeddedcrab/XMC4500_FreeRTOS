/* Include Headers */
#include "trace.h"


/* ITM Variables */
volatile int32_t ITM_RxBuffer;		/*!< External variable to receive characters. */


/* Initialize ITM Trace */
void ITM_init( void )
{
	/* Enable ITM */
    ITM_LAR = ITM_LAR_ACCESS; 			/**< Unlock */
    ITM_TCR = 0x1;            			/**< Global enable for ITM */
    ITM_TPR = 0x1;            			/**< First 8 stim registers have unpriv access */
    ITM_TER = 0xf;            			/**< Enable 4 stim ports */
    DEMCR = TRCENA;           			/**< Global enable DWT and ITM */
}


/* Write to Host for Trace output */
long ITM_printf( void *src, uint32_t len )
{
	/* Local Variables */
	uint8_t *xdata = (uint8_t *) src;
	uint32_t xlen = len;
	uint32_t xcount = 0;

	/* Print Data for debugging */
	for ( xcount = 0; xcount < xlen; ++xcount )
	{
		ITM_SendChar( xdata[xcount] );
	}
	/* Return length of data received */
	return ((long) xcount);
}


/* Read from Host for Debugging */
long ITM_scanf( void *dst, uint32_t len )
{
	/* Local Variables */
	uint8_t *xdata = (uint8_t *)dst;
	uint32_t xlen = len;
	uint32_t xcount = 0;

	for( xcount = 0; xcount < xlen; )
	{
		/* Update buffer until a valid character is received */
		if( ( xdata[xcount] = (uint8_t)ITM_ReceiveChar() ) != -1 )
		{
			++xcount;
		}
	}
	/* Return length of data received */
	return ((long) xcount);
}

