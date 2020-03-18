/******************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		Data types Header
* Filename:		dri_types.h
* Author:		HS
* Origin Date:
* Version:
* Notes:
*******************************************************************************/

/** @file:	dri_types.h
 *  @brief:	This file contains data types definitions and macros for drivers
 */
#ifndef DRI_TYPES_H_
#define DRI_TYPES_H_


/******************************************************************************
* Includes
*******************************************************************************/

/* Include XMC Headers */
#include <xmc_gpio.h>


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/
#define MAX_IRQ_NUMBER					110
#define USING_DRIVER_ASSERT				1


/******************************************************************************
* Macros
*******************************************************************************/

#if (1U == USING_DRIVER_ASSERT)
/* Assert statements */
#define DRIVER_ASSERT( cond, ret )	\
	if( 0 == (cond) ){				\
		(void) 0;					\
	}								\
	else{							\
		return ret;					\
	}
#define DRIVER_ASSERT_NRET( cond )	\
	if( 0 == (cond) ){				\
		(void) 0;					\
	}								\
	else{							\
		for( ; ; );					\
	}
#else
/* Assert statements */
#define DRIVER_ASSERT( cond, ret )
#define DRIVER_ASSERT_NRET( cond )
#endif


/******************************************************************************
* Typedefs
*******************************************************************************/


/*
 * @brief Structure used for Pin configuration,
 * 			use it in common header for types
 */
typedef struct tStPinConfig_
{
	/**< Pointer to the GPIO port base address */
	XMC_GPIO_PORT_t * p_port;
	/**< Pin configuration structure */
	XMC_GPIO_CONFIG_t config;
	/**< Pin number in the port*/
	unsigned char pin;
} tStPinConfig;


/*
 * @brief Structure used for Pin configuration,
 * 			use it in common header for types
 */
typedef struct tStPinHWConfig_
{
	/**< Pointer to the GPIO port base address */
	XMC_GPIO_PORT_t * p_port;
	/**< Pin configuration structure */
	XMC_GPIO_CONFIG_t config;
	XMC_GPIO_HWCTRL_t hw_config;
	/**< Pin number in the port*/
	unsigned char pin;
} tStPinHWConfig;



/*
 * @brief Structure used for Interrupt configuration for XMC
 */
typedef struct tStInterruptConfig_
{
	unsigned char irq_num;
	unsigned char irq_priority	: 7;	/**< restricting till 63 */
	unsigned char irq_res		: 1;
} tStInterruptConfig;


#endif /* DRI_TYPES_H_ */

/********************************** End of File *******************************/
