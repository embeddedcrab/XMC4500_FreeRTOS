#ifndef TRACE_H_
#define TRACE_H_


/* include Headers */
#include <core_cm4.h>

/* Debug Exception Monitor and Control register */
#define DEMCR   									(*((unsigned long *) 0xE000EDFC))
/* Enable Trace */
#define TRCENA  									0x01000000

/* Stimulus Port registers */
#define ITM_STIM0									(*((unsigned long *) 0xE0000000))
#define ITM_STIM1									(*((unsigned long *) 0xE0000004))
#define ITM_STIM2									(*((unsigned long *) 0xE0000008))
#define ITM_STIM3									(*((unsigned long *) 0xE000000c))
/* Trace enable registers */
#define ITM_TER										(*((unsigned long *) 0xE0000E00))
/* Privilege register: registers that can be accessed by unprivileged code */
#define ITM_TPR										(*((unsigned long *) 0xE0000E40))
/* Trace Control register */
#define ITM_TCR										(*((unsigned long *) 0xE0000E80))
/* Lock Access register */
#define ITM_LAR										(*((unsigned long *) 0xE0000FB0))
/* Unlock value */
#define ITM_LAR_ACCESS								0xC5ACCE55


#ifdef __cplusplus
extern "C"{
#endif


/* Check Trace data present or not? */
static inline int32_t ITM_isAvailable( void ){
	return (int32_t) ITM_CheckChar();
}

/*------- Function Declarations -------*/


/* Initialize ITM trace port */
void ITM_init( void );

/* Write to Host for Trace output */
long ITM_printf( void *src, uint32_t len );

/* Read from Host for Debugging */
long ITM_scanf( void *dst, uint32_t len );


#ifdef __cplusplus
}
#endif

#endif	/* TRACE_H_ */
