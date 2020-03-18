/******************************************************************************
 * Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		GPIO API Source
* Filename:		dri_gpio_pins.cpp
* Author:		HS
* Origin Date:	10/01/2019
* Version:		1.0.0
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	dri_gpio_pins.cpp
 *  @brief:	This header file contains API function definitions for
 *  		GPIO pins information.
 */


/******************************************************************************
* Includes
*******************************************************************************/
#include <dri_gpio_pins.h>


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/

#define UART_USED
#define CAN_USED
#define ETHERNET_USED
#define DAC_USED

#define EXTERNAL_FLASH_USED


/******************************************************************************
* Macros
*******************************************************************************/


/******************************************************************************
* Typedefs
*******************************************************************************/


/******************************************************************************
* Variables
*******************************************************************************/

/*
 * @brief Array size used for Pin configuration
 */
static constexpr auto sg_pins_array_size (21);

/*
 * @brief Structure array used for Pin configuration
 */
static constexpr tStPinConfig sg_gpio_pins[::sg_pins_array_size] =
{
	/** GPIO LEDs **/
	{/**< Port information for LED GPIO Pin 0 on Port 1 */
		XMC_GPIO_PORT1,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
			XMC_GPIO_OUTPUT_LEVEL_LOW,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE
		},
		0
	},
	{/**< Port information for LED GPIO Pin 1 on Port 1 */
		XMC_GPIO_PORT1,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
			XMC_GPIO_OUTPUT_LEVEL_LOW,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE
		},
		1
	},
	/** UART over USIC pins **/
	{/**< Port information for UART RX0 Pin 4 on Port 1, U0C0 */
		XMC_GPIO_PORT1,
		{
			XMC_GPIO_MODE_INPUT_TRISTATE,
			XMC_GPIO_OUTPUT_LEVEL_HIGH,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
		},
		4
	},
	{/**< Port information for UART TX0 Pin 5 on Port 1, U0C0 */
		XMC_GPIO_PORT1,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
			XMC_GPIO_OUTPUT_LEVEL_HIGH,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
		},
		5
	},
	{/**< Port information for UART RX2 Pin 15 on Port 2, U1C0 */
		XMC_GPIO_PORT2,
		{
			XMC_GPIO_MODE_INPUT_TRISTATE,
			XMC_GPIO_OUTPUT_LEVEL_HIGH,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
		},
		15
	},
	{/**< Port information for UART TX2 Pin 14 on Port 2, U1C0 */
		XMC_GPIO_PORT2,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
			XMC_GPIO_OUTPUT_LEVEL_HIGH,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
		},
		14
	},
	/** SPI Master over USIC (U2C0) pins,
	 * Four Slave can be connected on U2C0.SEL0,1,2,3(P5.3/4/5/6) available **/
	{/**< Port information for SPI_MOSI Pin 0 on Port 5 */
		XMC_GPIO_PORT5,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
			XMC_GPIO_OUTPUT_LEVEL_HIGH,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
		},
		0
	},
	{/**< Port information for SPI_MISO Pin 1 on Port 5 */
		XMC_GPIO_PORT5,
		{
			XMC_GPIO_MODE_INPUT_TRISTATE,
			XMC_GPIO_OUTPUT_LEVEL_LOW,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
		},
		1
	},
	{/**< Port information for SPI_CLK Pin 2 on Port 5 */
		XMC_GPIO_PORT5,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
			XMC_GPIO_OUTPUT_LEVEL_LOW,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
		},
		2
	},
	{/**< Port information for SPI_SS0 Pin 3 on Port 5 */
		XMC_GPIO_PORT5,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
			XMC_GPIO_OUTPUT_LEVEL_HIGH,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
		},
		3
	},
	{/**< Port information for SPI_SS1 Pin 4 on Port 5 */
		XMC_GPIO_PORT5,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
			XMC_GPIO_OUTPUT_LEVEL_HIGH,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
		},
		4
	},
	{/**< Port information for SPI_SS2 Pin 5 on Port 5 */
		XMC_GPIO_PORT5,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
			XMC_GPIO_OUTPUT_LEVEL_HIGH,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
		},
		5
	},
	{/**< Port information for SPI_SS3 Pin 6 on Port 5 */
		XMC_GPIO_PORT5,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
			XMC_GPIO_OUTPUT_LEVEL_HIGH,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
		},
		6
	},
	/**< CCU4x Channel pins for PWM/OC generation and IC the same generated output,
	 * IC pins used are P1.2 and P1.3 for P0.12 and P3.0 respectively */
	{/**< Port information for CCU40.OUT3 Pin 12 on Port 0, CCU40 Slice 3 */
		XMC_GPIO_PORT0,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3,
			XMC_GPIO_OUTPUT_LEVEL_LOW,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
		},
		12
	},
	{/**< Port information for CCU42.OUT0 Pin 0 on Port3 , CCU42 Slice 0 */
		XMC_GPIO_PORT3,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3,
			XMC_GPIO_OUTPUT_LEVEL_LOW,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
		},
		0
	},
	/**< CCU8x Channel pins for PWMC generation
	 *  */
	{/**< Port information for CCU80.OUT00 Pin 5 on Port 0, CCU80 Slice 00 */
		XMC_GPIO_PORT0,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3,
			XMC_GPIO_OUTPUT_LEVEL_LOW,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE
		},
		5
	},
	{/**< Port information for CCU80.OUT01 Pin 2 on Port 0, CCU80 Slice 01 */
		XMC_GPIO_PORT0,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3,
			XMC_GPIO_OUTPUT_LEVEL_LOW,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE
		},
		2
	},
	{/**< Port information for CCU80.OUT10 Pin 4 on Port 0, CCU80 Slice 10 */
		XMC_GPIO_PORT0,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3,
			XMC_GPIO_OUTPUT_LEVEL_LOW,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE
		},
		4
	},
	{/**< Port information for CCU80.OUT11 Pin 1 on Port 0, CCU80 Slice 11 */
		XMC_GPIO_PORT0,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3,
			XMC_GPIO_OUTPUT_LEVEL_LOW,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE
		},
		1
	},
	{/**< Port information for CCU80.OUT20 Pin 3 on Port 0, CCU80 Slice 20 */
		XMC_GPIO_PORT0,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3,
			XMC_GPIO_OUTPUT_LEVEL_LOW,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE
		},
		3
	},
	{/**< Port information for CCU80.OUT21 Pin 0 on Port 0, CCU80 Slice 21 */
		XMC_GPIO_PORT0,
		{
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3,
			XMC_GPIO_OUTPUT_LEVEL_LOW,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE
		},
		0
	}
};


#ifdef EXTERNAL_FLASH_USED
/*
 * @brief Array size used for External Flash Pin configuration
 */
static constexpr auto sg_external_flash_gpio_pins_size (2);
/*
 * @brief Structure array used for External Flash over SPI Channel Pin configuration
 */
static constexpr tStPinConfig sg_external_flash_gpio_pins[sg_external_flash_gpio_pins_size] =
{
    {/**< Port information for SPI_WP/IO2, Pin 3 on Port 1 */
        XMC_GPIO_PORT1,
        {
        	XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
			XMC_GPIO_OUTPUT_LEVEL_HIGH,
            XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE
        },
        3
    },
    {/**< Port information for SPI_HOLD/IO3, Pin 2 on Port 1 */
        XMC_GPIO_PORT1,
        {
        	XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
			XMC_GPIO_OUTPUT_LEVEL_HIGH,
            XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE
        },
        2
    }
};
#endif


#ifdef CAN_USED
/*
 * @brief Array size used for CAN Pin configuration
 */
static constexpr auto sg_can_gpio_pins_size (4);

/*
 * @brief Structure array used for CAN Pin configuration
 */
static constexpr tStPinConfig sg_can_gpio_pins[::sg_can_gpio_pins_size] =
{
	{/**< CAN Node 1 Tx pin, Pin 12 on Port 1 */
		XMC_GPIO_PORT1,
		{
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_MEDIUM_EDGE
		},
		12
	},
	{/**< CAN Node 1 Rx pin, Pin 13 on Port 1 */
		XMC_GPIO_PORT1,
		{
			.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_MEDIUM_EDGE
		},
		13
	},
	{/**< CAN Node 2 Tx pin, Pin 9 on Port 1 */
		XMC_GPIO_PORT1,
		{
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_MEDIUM_EDGE
		},
		9
	},
	{/**< CAN Node 2 Rx pin, Pin 8 on Port 1 */
		XMC_GPIO_PORT1,
		{
			.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_MEDIUM_EDGE
		},
		8
	}
};
#endif


#ifdef ETHERNET_USED
/*
 * @brief Array size used for Ethernet RMII Pin configuration
 */
static constexpr auto sg_eth_gpio_pins_size (10);
/*
 * @brief Structure array used for Ethernet Pin configuration
 */
static constexpr tStPinConfig sg_eth_gpio_pins[sg_eth_gpio_pins_size] =
{
    {/**< Port information for ETH_MDIO, Ethernet Channel 0 Pin 0 on Port 2 */
        XMC_GPIO_PORT2,
        {
            XMC_GPIO_MODE_INPUT_TRISTATE,
            XMC_GPIO_OUTPUT_LEVEL_LOW,
            XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE  /* Default Value */
        },
        0
    },
    {/**< Port information for ETH_RXD0, Ethernet Channel 0 Pin 2 on Port 2 */
        XMC_GPIO_PORT2,
        {
            XMC_GPIO_MODE_INPUT_TRISTATE,
            XMC_GPIO_OUTPUT_LEVEL_LOW,
            XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE  /* Default Value */
        },
        2
    },
    {/**< Port information for ETH_RXD1, Ethernet Channel 0 Pin 3 on Port 2 */
        XMC_GPIO_PORT2,
        {
            XMC_GPIO_MODE_INPUT_TRISTATE,
            XMC_GPIO_OUTPUT_LEVEL_LOW,
            XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE  /* Default Value */
        },
        3
    },
    {/**< Port information for ETH_RXER, Ethernet Channel 0 Pin 4 on Port 2 */
        XMC_GPIO_PORT2,
        {
            XMC_GPIO_MODE_INPUT_TRISTATE,
            XMC_GPIO_OUTPUT_LEVEL_LOW,
            XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE  /* Default Value */
        },
        4
    },
    {/**< Port information for ETH_CLK, Ethernet Channel 0 Pin 8 on Port 15 */
        XMC_GPIO_PORT15,
        {
            XMC_GPIO_MODE_INPUT_TRISTATE,
            XMC_GPIO_OUTPUT_LEVEL_LOW,
            XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE  /* Default Value */
        },
        8
    },
    {/**< Port information for ETH_CRS_DV, Ethernet Channel 0 Pin 9 on Port 15 */
        XMC_GPIO_PORT15,
        {
            XMC_GPIO_MODE_INPUT_TRISTATE,
            XMC_GPIO_OUTPUT_LEVEL_LOW,
            XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE  /* Default Value */
        },
        9
    },
    {/**< Port information ETH_MDC for Ethernet Channel 0 Pin 7 on Port 2 */
        XMC_GPIO_PORT2,
        {
            XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
            XMC_GPIO_OUTPUT_LEVEL_LOW,
            XMC_GPIO_OUTPUT_STRENGTH_STRONG_MEDIUM_EDGE
        },
        7
    },
    {/**< Port information for ETH_TXEN Ethernet Channel 0 Pin 5 on Port 2 */
        XMC_GPIO_PORT2,
        {
            XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
            XMC_GPIO_OUTPUT_LEVEL_LOW,
            XMC_GPIO_OUTPUT_STRENGTH_STRONG_MEDIUM_EDGE
        },
        5
    },
    {/**< Port information for ETH_TXD0 Ethernet Channel 0 Pin 8 on Port 2 */
        XMC_GPIO_PORT2,
        {
        	XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
            XMC_GPIO_OUTPUT_LEVEL_LOW,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_MEDIUM_EDGE
        },
        8
    },
    {/**< Port information for ETH_TXD1 Ethernet Channel 0 Pin 9 on Port 2 */
        XMC_GPIO_PORT2,
        {
        	XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
            XMC_GPIO_OUTPUT_LEVEL_LOW,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_MEDIUM_EDGE
        },
        9
    }
};
#endif


#ifdef DAC_USED
/*
 * @brief Array size used for DAC Pin configuration
 */
static constexpr auto sg_dac_gpio_pins_size (2);

/*
 * @brief Structure array used for SDMMC Pin configuration
 */
static constexpr tStPinHWConfig sg_dac_gpio_pins[::sg_dac_gpio_pins_size] =
{
	{/**< DAC 0 OUT pin, Port 14 pin 8 */
		XMC_GPIO_PORT14,
		{
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE
		},
		XMC_GPIO_HWCTRL_PERIPHERAL1,
		8
	}
	,{/**< DAC 1 OUT pin, Port 14 pin 9 */
		XMC_GPIO_PORT14,
		{
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
			.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE
		},
		XMC_GPIO_HWCTRL_PERIPHERAL1,
		9
	}
};

#endif


/******************************************************************************
* Function Definitions
*******************************************************************************/

/**
 * @function	init
 *
 * @brief		Pins initialization function
 *
 * <i>Imp Note:</i>
 * 				This function has to be called first in main or before main!
 *
 * 	Tasks:
 * 	1. CAN pins needs to be initialized if not working in Loopback mode
 *
 */
void GPIO_Pins__::init( void )
{
	/* Local Variables */
	unsigned char pins = 0;

	/* Initialize Peripherals Pins */
	for( pins = 0; pins < ::sg_pins_array_size; ++pins )
	{
		XMC_GPIO_Init( ::sg_gpio_pins[pins].p_port,
						::sg_gpio_pins[pins].pin,
						 &::sg_gpio_pins[pins].config
		);
	}

	#ifdef EXTERNAL_FLASH_USED
	for( pins = 0; pins < ::sg_external_flash_gpio_pins_size; ++pins )
	{
		XMC_GPIO_Init( ::sg_external_flash_gpio_pins[pins].p_port,
						::sg_external_flash_gpio_pins[pins].pin,
						 &::sg_external_flash_gpio_pins[pins].config
		);
	}
	#endif

	#ifdef ETHERNET_USED
    /* Initialize Ethernet pins */
    for( pins = 0; pins < ::sg_eth_gpio_pins_size; ++pins )
    {
        XMC_GPIO_Init( ::sg_eth_gpio_pins[pins].p_port,
                        ::sg_eth_gpio_pins[pins].pin,
                        &::sg_eth_gpio_pins[pins].config
                        );
    }
    /* Initialize HW functionality for Ethernet pins */
    XMC_GPIO_SetHardwareControl( ::sg_eth_gpio_pins[0].p_port, ::sg_eth_gpio_pins[0].pin,
                            XMC_GPIO_HWCTRL_PERIPHERAL1
                            );
    #endif

	#ifdef DAC_USED
	/* Initialize SDMMC Pins */
	for( pins = 0; pins < ::sg_dac_gpio_pins_size; ++pins )
	{
		XMC_GPIO_Init( ::sg_dac_gpio_pins[pins].p_port,
				::sg_dac_gpio_pins[pins].pin,
				 &::sg_dac_gpio_pins[pins].config
		);
		XMC_GPIO_SetHardwareControl( ::sg_dac_gpio_pins[pins].p_port,
				::sg_dac_gpio_pins[pins].pin,
				 ::sg_dac_gpio_pins[pins].hw_config
		);
	}
	#endif
}


/* Providing call to pins initialization for C */
extern "C"
{

void gpio_init_c( void );
void gpio_init_c( void )
{
	/* Initialize Hardware pins functionality options */
	GPIO_Pins__::init();
}

}

/********************************** End of File *******************************/
