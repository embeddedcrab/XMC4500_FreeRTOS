/******************************************************************************
* Title:		Boot Initialization Source
* Filename:		_boot_init.c
* Author:
* Origin Date:
* Version:
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	_boot_init.c
 *  @brief:	This source file contains Booting of system
 */


/******************************************************************************
* Includes
*******************************************************************************/

/* Include Master Headers */
#include <master_config.h>

/* Include Trace headers */
#include <trace.h>

/* Include peripheral device files */
#include <dri_uart_extern.h>
#include <dri_vadc_extern.h>
#include <dri_dac_extern.h>
#include <dri_spi_extern.h>
#include <dri_ccu_extern.h>
#include <dri_can_extern.h>
#include <dri_scu_extern.h>
#include <dri_rtc_extern.h>


/******************************************************************************
* Variables
*******************************************************************************/

/* Reset reason storing global variable */
volatile unsigned long gResetReason;
/* Boot mode storing global variable */
volatile unsigned long gBootMode;
/* System State Global Variable */
volatile unsigned char gSystemState = MASTER_APP_STATE_ACTIVE;
/* Sleep mode Clcok configurations */
const unsigned long gSleepMode_PeripheralsClockConfig =
		XMC_SCU_CLOCK_SLEEP_MODE_CONFIG_SYSCLK_FOFI |
		XMC_SCU_CLOCK_SLEEP_MODE_CONFIG_DISABLE_USB |
		XMC_SCU_CLOCK_SLEEP_MODE_CONFIG_DISABLE_SDMMC |
		XMC_SCU_CLOCK_SLEEP_MODE_CONFIG_DISABLE_ETH |
		XMC_SCU_CLOCK_SLEEP_MODE_CONFIG_DISABLE_EBU |
		XMC_SCU_CLOCK_SLEEP_MODE_CONFIG_DISABLED_CCU |
		XMC_SCU_CLOCK_SLEEP_MODE_CONFIG_ENABLE_WDT;
/* Deep Sleep mode Clcok configurations */
const unsigned long gDeepSleepMode_PeripheralsClockConfig =
		XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_SYSCLK_FOFI |
		XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_FLASH_POWERDOWN |
		XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_PLL_POWERDOWN |
		XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_VCO_POWERDOWN |
		XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_DISABLE_USB |
		XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_DISABLE_SDMMC |
		XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_DISABLE_ETH |
		XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_DISABLE_EBU |
		XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_DISABLE_CCU |
		XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_DISABLE_WDT;


/******************************************************************************
* Functions
*******************************************************************************/

/**
 * @function
 *
 * @brief		User defined Booting Initialization
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
void init_system_before_main( void );
void init_system_before_main( void )
{
	ITM_printf( (void *)"Boot Mode of System is : ", sizeof("Boot Mode of System is : ") );
	/* Get Boot mode of device */
	gBootMode = XMC_SCU_GetBootMode();
	/* Check specific mdoe */
	switch( gBootMode )
	{
	default:
		/**< Boot from start of flash. */
		case XMC_SCU_BOOTMODE_NORMAL:
		break;
		/**< UART bootstrap. */
		case XMC_SCU_BOOTMODE_ASC_BSL:
		break;
		/**< Boot Mode Index - Customized boot sequence. */
		case XMC_SCU_BOOTMODE_BMI:
		break;
		/**< CAN bootstrap. */
		case XMC_SCU_BOOTMODE_CAN_BSL:
		break;
		/**< Boot from PSRAM. */
		case XMC_SCU_BOOTMODE_PSRAM_BOOT:
		break;
		/**< Boot from flash - fixed alternative address 0. */
		case XMC_SCU_BOOTMODE_ABM0:
		break;
		/**< Boot from flash - fixed alternative address 1. */
		case XMC_SCU_BOOTMODE_ABM1:
		break;
		/**< fallback Alternate Boot Mode (ABM) - Try ABM-0 then try ABM-1. */
		case XMC_SCU_BOOTMODE_FABM:
		break;
	}
	/* Print current Boot mode of system */
//	ITM_printf( (void *)"", sizeof("") );


	ITM_printf( (void *)"Device Reset Reason is : ", sizeof("Device Reset Reason is : ") );
	/* Get the Reason for Reset */
	gResetReason = XMC_SCU_RESET_GetDeviceResetReason();
	/* Check specific reason */
	switch( gResetReason )
	{
	default:
		/**< Reset due to Power on reset. */
		case XMC_SCU_RESET_REASON_PORST:
			/* Perform some operation */
			XMC_SCU_RESET_ClearDeviceResetReason();
		break;
		/**< Reset due to Supply Watchdog reset. */
		case XMC_SCU_RESET_REASON_SWD:
			/* Perform some operation */
			XMC_SCU_RESET_ClearDeviceResetReason();
		break;
		/**< Reset due to Power Validation reset. */
		case XMC_SCU_RESET_REASON_PV:
			/* Perform some operation */
			XMC_SCU_RESET_ClearDeviceResetReason();
		break;
		/**< Reset due to Software reset. */
		case XMC_SCU_RESET_REASON_SW:
			/* Perform some operation */
			XMC_SCU_RESET_ClearDeviceResetReason();
		break;
		/**< Reset due to reset due to CPU lockup. */
		case XMC_SCU_RESET_REASON_LOCKUP:
			/* Perform some operation */
			XMC_SCU_RESET_ClearDeviceResetReason();
		break;
		/**< Reset due to Watchdog timer initiated  reset. */
		case XMC_SCU_RESET_REASON_WATCHDOG:
			/* Perform some operation */
			XMC_SCU_RESET_ClearDeviceResetReason();
		break;
		/**< Reset due to reset due to  memory parity  error. */
		case XMC_SCU_RESET_REASON_PARITY_ERROR:
			/* Perform some operation */
			XMC_SCU_RESET_ClearDeviceResetReason();
		break;
	}
	/* Print Device Reset Reason */
//	ITM_printf( (void *)"", sizeof("") );

	/* Configuration of Peripherals in Sleep Mode */
	ITM_printf( (void *)"Configuring Sleep Mode Peripherals", sizeof("Configuring Sleep Mode Peripherals") );
	XMC_SCU_CLOCK_SetSleepConfig( gSleepMode_PeripheralsClockConfig );

	/* Configurations for Deep Sleep */
	ITM_printf( (void *)"Configuring Deep Sleep Mode Peripherals", sizeof("Configuring Deep Sleep Mode Peripherals") );
	XMC_SCU_CLOCK_SetDeepSleepConfig( gDeepSleepMode_PeripheralsClockConfig );

	/* Update System State */
	gSystemState = MASTER_APP_STATE_NOT_STARTED;
	ITM_printf( (void *)"System State is: NOT STARTED", sizeof("System State is: NOT STARTED") );
}



/********************************** End of File *******************************/
