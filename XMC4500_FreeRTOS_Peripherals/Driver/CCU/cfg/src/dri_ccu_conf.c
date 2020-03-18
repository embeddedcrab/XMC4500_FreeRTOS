/*****************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		CCU Configuration Source
* Filename:		dri_ccu_conf.c
* Author:		HS
* Origin Date:	02/14/2020
* Version:		1.0.0
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	dri_ccu_conf.c
 *  @brief:	This source file contains configuration function definitions for
 *  		CCU
 */


/******************************************************************************
* Includes
*******************************************************************************/
#include <dri_ccu.h>


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

/*
 * @brief	CCU4 API functions
 *
 * \par<b>Description:</b><br>
 * 			This is data structure for CCU4 API functions to be used by Application
 */
tStCCU4_Api CCU4_Api_Functions =
{
	.fp_module_init = &CCU4_module_init,
	.fp_compare_channel_init = &CCU4_compare_channel_init,
	.fp_capture_channel_init = &CCU4_capture_channel_init,
	.fp_channel_timer_control = &CCU4_channel_timer_control
};

/*
 * @brief	CCU8 API functions
 *
 * \par<b>Description:</b><br>
 * 			This is data structure for CCU8 API functions to be used by Application
 */
tStCCU8_Api CCU8_Api_Functions =
{
	.fp_module_init = &CCU8_module_init,
	.fp_compare_channel_init = &CCU8_compare_channel_init,
	.fp_channel_timer_control = &CCU8_channel_timer_control
};

/*****************************************************************************/

/* Callback handler for user */
#if (CCU4_CALLBACK_HANDLER_USED == 1U)
extern void CCU4_callback_handler( void * p_channel, unsigned long *p_data );
#endif


#if (CCU40_USED > 0)
/* CCU4 Module 0 configuration */
static tStCCU4_ModuleConfiguartion CCU40_Configuration =
{
	.p_module_context = CCU40,
	.module_transfer_request = XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR,
	.module_clock = XMC_CCU4_CLOCK_SCU
};
#endif	/* CCU40_USED */

#if (CCU42_USED > 0)
/* CCU4 Module 2 configuration */
static tStCCU4_ModuleConfiguartion CCU42_Configuration =
{
	.p_module_context = CCU42,
	.module_transfer_request = XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR,
	.module_clock = XMC_CCU4_CLOCK_SCU
};
#endif	/* CCU42_USED */


/* Module CCU40 Channel 0 Configurations */
#if( CCU40_CHANNEL0_USED > 0U )
static XMC_CCU4_SLICE_CAPTURE_CONFIG_t CCU40_Channel0_Capture_Configuration =
{
	.fifo_enable = 0,
	.timer_clear_mode = XMC_CCU4_SLICE_TIMER_CLEAR_MODE_CAP_LOW,/* Only C1V anc C0V */
	.same_event = 0,
	.ignore_full_flag = 0,
	.prescaler_mode = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
	.prescaler_initval = XMC_CCU4_SLICE_PRESCALER_128,	/* Fclk = FCCU/128 = 937500Hz => 1.066us
	 	 	 	 	 	 	 	 	 	 	 can read from 1us to 65535us or ~15Hz to ~1MHz */
	.float_limit = 0,
	.timer_concatenation = 0
};
static XMC_CCU4_SLICE_EVENT_CONFIG_t CCU40_Channel0_Event0_Configuration =
{
	.mapped_input = CCU40_IN0_P1_3,	/* Capture on P1.3 */
	.edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,
	.level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
	.duration = XMC_CCU4_SLICE_EVENT_FILTER_7_CYCLES
};
static XMC_CCU4_SLICE_EVENT_CONFIG_t CCU40_Channel0_Event1_Configuration =
{
	.mapped_input = CCU40_IN0_P1_3,
	.edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_FALLING_EDGE,
	.level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
	.duration = XMC_CCU4_SLICE_EVENT_FILTER_7_CYCLES
};
static tStCCU_InterruptConfiguartion CCU40_Channel0_Interrupt_Configuration =
{
	.irq =
	{
		.irq_num = CCU40_0_IRQn,
		.irq_priority = 52
	},
	.sr = XMC_CCU4_SLICE_SR_ID_0
};
static tStCCU4_SliceCaptureConfiguartion CCU40_Channel0_Configuration =
{
	.p_slice_context = CCU40_CC40,
	.p_config = &CCU40_Channel0_Capture_Configuration,
	.p_event_config_off = &CCU40_Channel0_Event0_Configuration,
	.p_event_config_on = &CCU40_Channel0_Event1_Configuration,
	.p_irq_config = &CCU40_Channel0_Interrupt_Configuration,
	.event0 = XMC_CCU4_SLICE_EVENT_0,
	.event1 = XMC_CCU4_SLICE_EVENT_1,
	.interrupt_event = XMC_CCU4_SLICE_IRQ_ID_EVENT1
};
static tStCCU4_Control CCU40_Channel0_Control;
#endif	/* CCU40_Channel0_USED */


/* Module CCU40 Channel 1 Configurations */
#if( CCU40_CHANNEL0_USED > 0U )
static XMC_CCU4_SLICE_CAPTURE_CONFIG_t CCU40_Channel1_Capture_Configuration =
{
	.fifo_enable = 0,
	.timer_clear_mode = XMC_CCU4_SLICE_TIMER_CLEAR_MODE_CAP_LOW,/* Only C1V anc C0V */
	.same_event = 0,
	.ignore_full_flag = 0,
	.prescaler_mode = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
	.prescaler_initval = XMC_CCU4_SLICE_PRESCALER_128,	/* Fclk = FCCU/128 = 937500Hz => 1.066us
	 	 	 	 	 	 	 	 	 	 	 can read from 1us to 65535us or ~15Hz to ~1MHz */
	.float_limit = 0,
	.timer_concatenation = 0
};
static XMC_CCU4_SLICE_EVENT_CONFIG_t CCU40_Channel1_Event0_Configuration =
{
	.mapped_input = CCU40_IN1_P1_2,	/* Capture on P1.2 */
	.edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,
	.level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
	.duration = XMC_CCU4_SLICE_EVENT_FILTER_7_CYCLES
};
static XMC_CCU4_SLICE_EVENT_CONFIG_t CCU40_Channel1_Event1_Configuration =
{
	.mapped_input = CCU40_IN1_P1_2,
	.edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_FALLING_EDGE,
	.level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
	.duration = XMC_CCU4_SLICE_EVENT_FILTER_7_CYCLES
};
static tStCCU_InterruptConfiguartion CCU40_Channel1_Interrupt_Configuration =
{
	.irq =
	{
		.irq_num = CCU40_1_IRQn,
		.irq_priority = 52
	},
	.sr = XMC_CCU4_SLICE_SR_ID_1
};
static tStCCU4_SliceCaptureConfiguartion CCU40_Channel1_Configuration =
{
	.p_slice_context = CCU40_CC41,
	.p_config = &CCU40_Channel1_Capture_Configuration,
	.p_event_config_off = &CCU40_Channel1_Event0_Configuration,
	.p_event_config_on = &CCU40_Channel1_Event1_Configuration,
	.p_irq_config = &CCU40_Channel1_Interrupt_Configuration,
	.event0 = XMC_CCU4_SLICE_EVENT_0,
	.event1 = XMC_CCU4_SLICE_EVENT_1,
	.interrupt_event = XMC_CCU4_SLICE_IRQ_ID_EVENT1
};
static tStCCU4_Control CCU40_Channel1_Control;
#endif	/* CCU40_Channel1_USED */


/* Module CCU40 Channel 3 Configurations */
#if( CCU40_CHANNEL3_USED > 0U )
static XMC_CCU4_SLICE_COMPARE_CONFIG_t CCU40_Channel3_Compare_Configuration =
{
	.timer_mode = XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
	.monoshot = XMC_CCU4_SLICE_TIMER_REPEAT_MODE_REPEAT,
	.shadow_xfer_clear = 0,
	.dither_timer_period = 0,
	.prescaler_mode = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
	.mcm_enable = 0,

	.prescaler_initval = XMC_CCU4_SLICE_PRESCALER_64,
	.float_limit = 0,
	.dither_limit = 0,
	.passive_level = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
	.timer_concatenation = 0
};
static XMC_CCU4_SLICE_EVENT_CONFIG_t CCU40_Channel3_Event_Configuration =
{
	.mapped_input = XMC_CCU4_SLICE_INPUT_I,	/* Connected to CCU40_IN0_SCU_GSC40 */
	.edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,
	.level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
	.duration = XMC_CCU4_SLICE_EVENT_FILTER_3_CYCLES
};
static tStCCU_InterruptConfiguartion CCU40_Channel3_Interrupt_Configuration =
{
	.irq =
	{
		.irq_num = CCU40_3_IRQn,
		.irq_priority = 52
	},
	.sr = XMC_CCU4_SLICE_SR_ID_3
};

static tStCCU4_SliceCompareConfiguartion CCU40_Channel3_Configuration =
{
	.p_slice_context = CCU40_CC43,
	.p_config = &CCU40_Channel3_Compare_Configuration,
	.p_event_config = &CCU40_Channel3_Event_Configuration,
	.p_irq_config = &CCU40_Channel3_Interrupt_Configuration,
	.period = 37499,	/* Used for Servo Motor control @50Hz/20ms, [Fclk/Fpwm - 1], Fclk = Fccu/prescale
	 	 	 	 	 	 	 Fclk = 120000000/64 = 1875000Hz, Fpwm = 50Hz
	 	 	 	 	 	 	 PR = (1875000/50) - 1 => 37499 */
	.compare = ( (1-(25/(float)100)) * (37499 + 1) ),	/* 50% duty cycle always, [(1-DC/100) * (PR+1)] */
	.event = XMC_CCU4_SLICE_EVENT_0,
	.start_mode = XMC_CCU4_SLICE_START_MODE_TIMER_START_CLEAR,
	.interrupt_event = XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH,
	.shadow_transfer = XMC_CCU4_SHADOW_TRANSFER_SLICE_3 |\
						XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_3
};
static tStCCU4_Control CCU40_Channel3_Control;
#endif	/* CCU40_Channel3_USED */


/* Module CCU42 Channel 0 Configurations */
#if( CCU42_CHANNEL0_USED > 0U )
static XMC_CCU4_SLICE_COMPARE_CONFIG_t CCU42_Channel0_Compare_Configuration =
{
	.timer_mode = XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
	.monoshot = XMC_CCU4_SLICE_TIMER_REPEAT_MODE_REPEAT,
	.shadow_xfer_clear = 0,
	.dither_timer_period = 0,
	.prescaler_mode = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
	.mcm_enable = 0,

	.prescaler_initval = XMC_CCU4_SLICE_PRESCALER_64,
	.float_limit = 0,
	.dither_limit = 0,
	.passive_level = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
	.timer_concatenation = 0
};
static XMC_CCU4_SLICE_EVENT_CONFIG_t CCU42_Channel0_Event_Configuration =
{
	.mapped_input = XMC_CCU4_SLICE_INPUT_I,	/* Connected to CCU40_IN0_SCU_GSC40 */
	.edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,
	.level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
	.duration = XMC_CCU4_SLICE_EVENT_FILTER_3_CYCLES
};
static tStCCU_InterruptConfiguartion CCU42_Channel0_Interrupt_Configuration =
{
	.irq =
	{
		.irq_num = CCU42_0_IRQn,
		.irq_priority = 52
	},
	.sr = XMC_CCU4_SLICE_SR_ID_0
};

static tStCCU4_SliceCompareConfiguartion CCU42_Channel0_Configuration =
{
	.p_slice_context = CCU42_CC40,
	.p_config = &CCU42_Channel0_Compare_Configuration,
	.p_event_config = &CCU42_Channel0_Event_Configuration,
	.p_irq_config = &CCU42_Channel0_Interrupt_Configuration,
	.period = 24999,	/* @75Hz/13.33ms, [Fclk/Fpwm - 1], Fclk = Fccu/prescale
	 	 	 	 	 	 	 Fclk = 120000000/64 = 1875000Hz, Fpwm = 75Hz
	 	 	 	 	 	 	 PR = (1875000/75) - 1 => 24999 */
	.compare = ( (1-(25/(float)100)) * (24999 + 1) ),	/* 50% duty cycle always, [(1-DC/100) * (PR+1)] */
	.event = XMC_CCU4_SLICE_EVENT_0,
	.start_mode = XMC_CCU4_SLICE_START_MODE_TIMER_START_CLEAR,
	.interrupt_event = XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH,
	.shadow_transfer = XMC_CCU4_SHADOW_TRANSFER_SLICE_0 |\
						XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_0
};
static tStCCU4_Control CCU42_Channel0_Control;
#endif	/* CCU42_CHANNEL0_USED */


/** CCU4 Modules **/
#if (CCU40_USED > 0)
/* CCU4 Module 0 configuration */
tStCCU4_Module CCU4_Module0 =
{
	.p_module_config = &CCU40_Configuration
};
#endif	/* CCU40_USED */
#if (CCU42_USED > 0)
/* CCU4 Module 2 configuration */
tStCCU4_Module CCU4_Module2 =
{
	.p_module_config = &CCU42_Configuration
};
#endif	/* CCU42_USED */


/** CUU4 Module Channels **/
#if( CCU40_CHANNEL0_USED > 0U )
/* CCU40 Module Channel 0 Callback */
#if( CCU4_CALLBACK_HANDLER_USED == 1U )
tStCCU4_CaptureCallbacks CCU40_Channel0_Callback =
{
	.fp_callback = NULL
};
#endif
/* CCU40 Module Channel 0 Handle */
tStCCU4_Capture CCU40_Channel0_Handle =
{
	.p_config = &CCU40_Channel0_Configuration,
	.p_control = &CCU40_Channel0_Control
	#if( CCU4_CALLBACK_HANDLER_USED == 1U )
	,.p_callback = &CCU40_Channel0_Callback
	#endif
};
#endif	/* CCU40_CHANNEL0_USED */
#if( CCU40_CHANNEL1_USED > 0U )
/* CCU40 Module Channel 0 Callback */
#if( CCU4_CALLBACK_HANDLER_USED == 1U )
tStCCU4_CaptureCallbacks CCU40_Channel1_Callback =
{
	.fp_callback = NULL
};
#endif
/* CCU40 Module Channel 1 Handle */
tStCCU4_Capture CCU40_Channel1_Handle =
{
	.p_config = &CCU40_Channel1_Configuration,
	.p_control = &CCU40_Channel1_Control
	#if( CCU4_CALLBACK_HANDLER_USED == 1U )
	,.p_callback = &CCU40_Channel1_Callback
	#endif
};
#endif	/* CCU40_CHANNEL1_USED */
#if( CCU40_CHANNEL3_USED > 0U )
/* CCU42 Module Channel 0 Callback */
#if( CCU4_CALLBACK_HANDLER_USED == 1U )
tStCCU4_Callbacks CCU40_Channel3_Callback =
{
	.fp_callback = NULL
};
#endif
/* CCU40 Module Channel 3 Handle */
tStCCU4_Compare CCU40_Channel3_Handle =
{
	.p_config = &CCU40_Channel3_Configuration,
	.p_control = &CCU40_Channel3_Control
	#if( CCU4_CALLBACK_HANDLER_USED == 1U )
	,.p_callback = &CCU40_Channel3_Callback
	#endif
};
#endif	/* CCU40_CHANNEL3_USED */
#if( CCU42_CHANNEL0_USED > 0U )
/* CCU42 Module Channel 0 Callback */
#if( CCU4_CALLBACK_HANDLER_USED == 1U )
tStCCU4_Callbacks CCU42_Channel0_Callback =
{
	.fp_callback = NULL
};
#endif
/* CCU42 Module Channel 0 Handle */
tStCCU4_Compare CCU42_Channel0_Handle =
{
	.p_config = &CCU42_Channel0_Configuration,
	.p_control = &CCU42_Channel0_Control
	#if( CCU4_CALLBACK_HANDLER_USED == 1U )
	,.p_callback = &CCU42_Channel0_Callback
	#endif
};
#endif	/* CCU42_CHANNEL0_USED */


/************************************************************************************/


/************************************************************************************/

/* Callback handler for user */
#if (CCU8_CALLBACK_HANDLER_USED == 1U)
extern void CCU8_callback_handler( void * p_channel );
#endif

#if (CCU80_USED > 0)
/* CCU8 Module 0 configuration */
static tStCCU4_ModuleConfiguartion CCU80_Configuration =
{
	.p_module_context = CCU80,
	.module_transfer_request = XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR,
	.module_clock = XMC_CCU4_CLOCK_SCU
};
#endif	/* CCU80_USED */


/* CCU80 Channel 0 Configurations and Control
 *
 * <i>Imp Note:</i>
 * CCU80 Channel 0 and Channel 1 are being used in combination with Dead time control
 *  */
#if ( (CCU80_CHANNEL0_USED == 1U) && (CCU80_CHANNEL1_USED == 1U) )
static XMC_CCU8_SLICE_COMPARE_CONFIG_t CCU80_Channel0_Compare_Configuration =
{
	/** tc */
	.timer_mode = XMC_CCU8_SLICE_TIMER_COUNT_MODE_EA,
	.monoshot = XMC_CCU8_SLICE_TIMER_REPEAT_MODE_REPEAT,
	.shadow_xfer_clear = 0,
	.dither_timer_period = 0,
	.dither_duty_cycle = 0,
	.prescaler_mode = XMC_CCU8_SLICE_PRESCALER_MODE_NORMAL,
	.mcm_ch1_enable = 0,
	.mcm_ch2_enable = 0,
	.slice_status = XMC_CCU8_SLICE_STATUS_CHANNEL_1,

	/** psl */
	.passive_level_out0 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
	.passive_level_out1 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
	.passive_level_out2 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
	.passive_level_out3 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,

	/** chc */
	.asymmetric_pwm = 0,
	.invert_out0 = 0,
	.invert_out1 = 1,
	.invert_out2 = 0,
	.invert_out3 = 1,

	.prescaler_initval = XMC_CCU8_SLICE_PRESCALER_1,/* Fclk = Fccu = 120MHz */
	.float_limit = 0,
	.dither_limit = 0,
	.timer_concatenation = 0
};
static XMC_CCU8_SLICE_DEAD_TIME_CONFIG_t CCU80_Channel0_DeadTime_Configuration =
{
	/**< dtc */
	.enable_dead_time_channel1 = 1,
	.enable_dead_time_channel2 = 1,
	.channel1_st_path = 1,
	.channel1_inv_st_path = 1,
	.channel2_st_path = 0,
	.channel2_inv_st_path = 0,
	.div = XMC_CCU8_SLICE_DTC_DIV_1,

	/**< dc1r */
	.channel1_st_rising_edge_counter = 24,	/* 200ns @120MHz */
	.channel1_st_falling_edge_counter = 12,	/* 100ns @120MHz */

	/**< dc2r */
	.channel2_st_rising_edge_counter = 0,
	.channel2_st_falling_edge_counter = 0
};
static XMC_CCU8_SLICE_EVENT_CONFIG_t CCU80_Channel0_Event_Configuration =
{
	.mapped_input = CCU80_IN0_SCU_GSC80,
	.edge = XMC_CCU8_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,
	.level = XMC_CCU8_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
	.duration = XMC_CCU8_SLICE_EVENT_FILTER_DISABLED
};
static tStCCU_InterruptConfiguartion CCU80_Channel0_Interrupt_Configuration =
{
	.irq = { .irq_num = CCU80_0_IRQn, .irq_priority = 53 },
	.sr = XMC_CCU8_SLICE_SR_ID_0
};

static tStCCU8_SliceCompareConfiguartion CCU80_Channel0_Configuration =
{
	.p_slice_context = CCU80_CC80,
	.p_config = &CCU80_Channel0_Compare_Configuration,
	.p_dead_time_config = &CCU80_Channel0_DeadTime_Configuration,
	.p_event_config = &CCU80_Channel0_Event_Configuration,
	.p_irq_config = &CCU80_Channel0_Interrupt_Configuration,
	.period = 7499,	/* @16KHz, [Fclk/Fpwm - 1], Fclk = Fccu/prescale
		 	 	 	 	 	 	 Fclk = 120000000, Fpwm = 16KHz
		 	 	 	 	 	 	 PR = (120000000/16000) - 1 => 7499 */
	.compare = ( (1-(0/(float)100)) * (7499 + 1) ),/* 0% duty cycle initially, [(1-DC/100) * (PR+1)] */
	.compare_channel = XMC_CCU8_SLICE_COMPARE_CHANNEL_1,
	.event = XMC_CCU8_SLICE_EVENT_0,
	.start_mode = XMC_CCU8_SLICE_START_MODE_TIMER_START_CLEAR,
	.interrupt_event = XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH,
	.shadow_transfer = XMC_CCU8_SHADOW_TRANSFER_SLICE_0
};
static tStCCU8_Control CCU80_Channel0_Control;
/* CCU80 Module Channel 0 Callback */
#if( CCU8_CALLBACK_HANDLER_USED == 1U )
tStCCU4_Callbacks CCU80_Channel0_Callback =
{
	.fp_callback = NULL
};
#endif

/* CCU80 Channel 1 Configurations and Control */
static tStCCU8_SliceCompareConfiguartion CCU80_Channel1_Configuration =
{
	.p_slice_context = CCU80_CC81,
	.p_config = &CCU80_Channel0_Compare_Configuration,
	.p_dead_time_config = &CCU80_Channel0_DeadTime_Configuration,
	.p_event_config = &CCU80_Channel0_Event_Configuration,
	.p_irq_config = &CCU80_Channel0_Interrupt_Configuration,
	.period = 7499,	/* @16KHz, [Fclk/Fpwm - 1], Fclk = Fccu/prescale
		 	 	 	 	 	 	 Fclk = 120000000, Fpwm = 16KHz
		 	 	 	 	 	 	 PR = (120000000/16000) - 1 => 7499 */
	.compare = ( (1-(0/(float)100)) * (7499 + 1) ),/* 0% duty cycle initially, [(1-DC/100) * (PR+1)] */
	.compare_channel = XMC_CCU8_SLICE_COMPARE_CHANNEL_1,
	.event = XMC_CCU8_SLICE_EVENT_0,
	.start_mode = XMC_CCU8_SLICE_START_MODE_TIMER_START_CLEAR,
	.interrupt_event = XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH,
	.shadow_transfer = XMC_CCU8_SHADOW_TRANSFER_SLICE_1
};
static tStCCU8_Control CCU80_Channel1_Control;
#endif	/* CCU80_CHANNEL0_USED && CCU80_CHANNEL1_USED */


/* CCU80 Channel 2 Data variables  */
#if (CCU80_CHANNEL2_USED == 1U )
static XMC_CCU8_SLICE_COMPARE_CONFIG_t CCU80_Channel2_Compare_Configuration =
{
	/** tc */
	.timer_mode = XMC_CCU8_SLICE_TIMER_COUNT_MODE_EA,
	.monoshot = XMC_CCU8_SLICE_TIMER_REPEAT_MODE_REPEAT,
	.shadow_xfer_clear = 0,
	.dither_timer_period = 0,
	.dither_duty_cycle = 0,
	.prescaler_mode = XMC_CCU8_SLICE_PRESCALER_MODE_NORMAL,
	.mcm_ch1_enable = 0,
	.mcm_ch2_enable = 0,
	.slice_status = XMC_CCU8_SLICE_STATUS_CHANNEL_1,

	/** psl */
	.passive_level_out0 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
	.passive_level_out1 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
	.passive_level_out2 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
	.passive_level_out3 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,

	/** chc */
	.asymmetric_pwm = 0,
	.invert_out0 = 0,
	.invert_out1 = 1,
	.invert_out2 = 0,
	.invert_out3 = 0,

	.prescaler_initval = XMC_CCU8_SLICE_PRESCALER_1,/* Fclk = Fccu = 120MHz */
	.float_limit = 0,
	.dither_limit = 0,
	.timer_concatenation = 0
};
static XMC_CCU8_SLICE_DEAD_TIME_CONFIG_t CCU80_Channel2_DeadTime_Configuration =
{
	/**< dtc */
	.enable_dead_time_channel1 = 1,
	.enable_dead_time_channel2 = 1,
	.channel1_st_path = 1,
	.channel1_inv_st_path = 1,
	.channel2_st_path = 0,
	.channel2_inv_st_path = 0,
	.div = XMC_CCU8_SLICE_DTC_DIV_1,

	/**< dc1r */
	.channel1_st_rising_edge_counter = 24,	/* 200ns @120MHz */
	.channel1_st_falling_edge_counter = 12,	/* 100ns @120MHz */

	/**< dc2r */
	.channel2_st_rising_edge_counter = 0,
	.channel2_st_falling_edge_counter = 0
};
static XMC_CCU8_SLICE_EVENT_CONFIG_t CCU80_Channel2_Event_Configuration =
{
	.mapped_input = CCU80_IN0_SCU_GSC80,
	.edge = XMC_CCU8_SLICE_EVENT_EDGE_SENSITIVITY_RISING_EDGE,
	.level = XMC_CCU8_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
	.duration = XMC_CCU8_SLICE_EVENT_FILTER_DISABLED
};
static tStCCU_InterruptConfiguartion CCU80_Channel2_Interrupt_Configuration =
{
	.irq = { .irq_num = CCU80_2_IRQn, .irq_priority = 54 },
	.sr = XMC_CCU8_SLICE_SR_ID_2
};

/* CCU80 Channel 2 Configurations and Control */
static tStCCU8_SliceCompareConfiguartion CCU80_Channel2_Configuration =
{
	.p_slice_context = CCU80_CC82,
	.p_config = &CCU80_Channel2_Compare_Configuration,
	.p_dead_time_config = &CCU80_Channel2_DeadTime_Configuration,
	.p_event_config = &CCU80_Channel2_Event_Configuration,
	.p_irq_config = &CCU80_Channel2_Interrupt_Configuration,
	.period = 7499,	/* @16KHz, [Fclk/Fpwm - 1], Fclk = Fccu/prescale
		 	 	 	 	 	 	 Fclk = 120000000, Fpwm = 16KHz
		 	 	 	 	 	 	 PR = (120000000/16000) - 1 => 7499 */
	.compare = ( (1-(0/(float)100)) * (7499 + 1) ),/* 0% duty cycle initially, [(1-DC/100) * (PR+1)] */
	.compare_channel = XMC_CCU8_SLICE_COMPARE_CHANNEL_1,
	.event = XMC_CCU8_SLICE_EVENT_0,
	.start_mode = XMC_CCU8_SLICE_START_MODE_TIMER_START_CLEAR,
	.interrupt_event = XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH,
	.shadow_transfer = XMC_CCU8_SHADOW_TRANSFER_SLICE_2
};

static tStCCU8_Control CCU80_Channel2_Control;

#if( CCU8_CALLBACK_HANDLER_USED == 1U )
tStCCU4_Callbacks CCU80_Channel2_Callback =
{
	.fp_callback = NULL
};
#endif
#endif	/* CCU80_CHANNEL2_USED */


/** CCU8 Modules **/
#if (CCU80_USED > 0)
/* CCU8 Module 0 configuration */
tStCCU8_Module CCU8_Module0 =
{
	.p_module_config = &CCU80_Configuration
};
#endif	/* CCU80_USED */

/** CCU80 Channel 0 **/
#if (CCU80_CHANNEL0_USED == 1U)
tStCCU8_Compare CCU80_Channel0_Handle =
{
	.p_config = &CCU80_Channel0_Configuration,
	.p_control = &CCU80_Channel0_Control
	#if( CCU8_CALLBACK_HANDLER_USED == 1U )
	,.p_callback = &CCU80_Channel0_Callback
	#endif
};
#endif
/** CCU80 Channel 1 **/
#if (CCU80_CHANNEL1_USED == 1U)
tStCCU8_Compare CCU80_Channel1_Handle =
{
	.p_config = &CCU80_Channel1_Configuration,
	.p_control = &CCU80_Channel1_Control
	#if( CCU8_CALLBACK_HANDLER_USED == 1U )
	,.p_callback = &CCU80_Channel0_Callback
	#endif
};
#endif

/** CCU80 Channel 2 **/
#if (CCU80_CHANNEL2_USED == 1U)
tStCCU8_Compare CCU80_Channel2_Handle =
{
	.p_config = &CCU80_Channel2_Configuration,
	.p_control = &CCU80_Channel2_Control
	#if( CCU8_CALLBACK_HANDLER_USED == 1U )
	,.p_callback = &CCU80_Channel2_Callback
	#endif
};
#endif





/******************************************************************************
* Function Definitions
*******************************************************************************/

/******* ISR Handlers for CCU4 channel *******/

/* Channels ISR Entries */
#if( CCU40_CHANNEL0_USED > 0U )
void CCU40_Channel0_Handler( void )
{
	/* Local permanent variables */
	unsigned long capture_value_1 = 0;
	unsigned long capture_value_3 = 0;
	unsigned short result_l;

	/* Test only */
	float dc_l = 0.0f;

	/* Clear Event */
	XMC_CCU4_SLICE_ClearEvent( (XMC_CCU4_SLICE_t *const) CCU40_Channel0_Handle.p_config->p_slice_context,
									CCU40_Channel0_Handle.p_config->interrupt_event );

	capture_value_1 = XMC_CCU4_SLICE_GetCaptureRegisterValue((const XMC_CCU4_SLICE_t *const) CCU40_Channel0_Handle.p_config->p_slice_context, 1);
	capture_value_3 = XMC_CCU4_SLICE_GetCaptureRegisterValue((const XMC_CCU4_SLICE_t *const) CCU40_Channel0_Handle.p_config->p_slice_context, 3);

	/* Update period and duty cycle values */
	result_l = (unsigned short) (capture_value_1 & CCU4_CC4_CV_CAPTV_Msk);
	CCU40_Channel1_Handle.p_config->period = (unsigned short) (result_l << 1);
	CCU40_Channel0_Handle.p_config->duty_cycle = (unsigned short) (capture_value_3 & CCU4_CC4_CV_CAPTV_Msk);

	dc_l = ( (capture_value_3&CCU4_CC4_CV_CAPTV_Msk) / (float)result_l ) * (100);

	#if( CCU4_CALLBACK_HANDLER_USED == 1U )
	if( CCU40_Channel0_Handle.p_callback->fp_callback != NULL )
	{
		CCU40_Channel0_Handle.p_callback->fp_callback( (XMC_CCU4_SLICE_t *const) CCU40_Channel0_Handle.p_config->p_slice_context, NULL );
	}
	#endif

	__asm("NOP");
}
#endif	/* CCU40_CHANNEL0_USED */


#if( CCU40_CHANNEL1_USED > 0U )
void CCU40_Channel1_Handler( void )
{
	/* Local permanent variables */
	unsigned long capture_value_1 = 0;
	unsigned long capture_value_3 = 0;
	unsigned short result_l;

	/* Test only */
	float dc_l = 0.0f;

	/* Clear Event */
	XMC_CCU4_SLICE_ClearEvent( (XMC_CCU4_SLICE_t *const) CCU40_Channel1_Handle.p_config->p_slice_context,
									CCU40_Channel1_Handle.p_config->interrupt_event );

	capture_value_1 = XMC_CCU4_SLICE_GetCaptureRegisterValue((const XMC_CCU4_SLICE_t *const) CCU40_Channel1_Handle.p_config->p_slice_context, 1);
	capture_value_3 = XMC_CCU4_SLICE_GetCaptureRegisterValue((const XMC_CCU4_SLICE_t *const) CCU40_Channel1_Handle.p_config->p_slice_context, 3);

	/* Update period and duty cycle values */
	result_l = (unsigned short) (capture_value_1 & CCU4_CC4_CV_CAPTV_Msk);
	CCU40_Channel1_Handle.p_config->period = (unsigned short) (result_l << 1);
	CCU40_Channel1_Handle.p_config->duty_cycle = (unsigned short) (capture_value_3 & CCU4_CC4_CV_CAPTV_Msk);

	dc_l = ( (capture_value_3&CCU4_CC4_CV_CAPTV_Msk) / (float)result_l ) * (100);

	#if( CCU4_CALLBACK_HANDLER_USED == 1U )
	if( CCU40_Channel1_Handle.p_callback->fp_callback != NULL )
	{
		CCU40_Channel1_Handle.p_callback->fp_callback( (XMC_CCU4_SLICE_t *const) CCU40_Channel1_Handle.p_config->p_slice_context, NULL );
	}
	#endif

	__asm("NOP");
}
#endif	/* CCU40_CHANNEL1_USED */


#if( CCU40_CHANNEL3_USED > 0U )
void CCU40_Channel3_Handler( void )
{
	/* Clear Period Match event */
	XMC_CCU4_SLICE_ClearEvent( (XMC_CCU4_SLICE_t *const) CCU40_Channel3_Handle.p_config->p_slice_context,
								CCU40_Channel3_Handle.p_config->interrupt_event );

	/* Can set new Compare Match value or any other processing */
	#if( CCU4_CALLBACK_HANDLER_USED == 1U )
	if( CCU40_Channel3_Handle.p_callback->fp_callback != NULL )
	{
		CCU40_Channel3_Handle.p_callback->fp_callback( (XMC_CCU4_SLICE_t *const) CCU40_Channel3_Handle.p_config->p_slice_context );
	}
	#endif

	/* Enable shadow transfer for new PWM value update */
	XMC_CCU4_EnableShadowTransfer( (XMC_CCU4_MODULE_t *const) CCU4_Module0.p_module_config->p_module_context,
									XMC_CCU4_SHADOW_TRANSFER_SLICE_3 );
}
#endif	/* CCU40_CHANNEL3_USED */


#if( CCU42_CHANNEL0_USED > 0U )
void CCU42_Channel0_Handler( void )
{
	/* Clear Period Match event */
	XMC_CCU4_SLICE_ClearEvent( (XMC_CCU4_SLICE_t *const) CCU42_Channel0_Handle.p_config->p_slice_context,
								CCU42_Channel0_Handle.p_config->interrupt_event );

	/* Can set new Compare Match value or any other processing */
	#if( CCU4_CALLBACK_HANDLER_USED == 1U )
	if( CCU42_Channel0_Handle.p_callback->fp_callback != NULL )
	{
		CCU42_Channel0_Handle.p_callback->fp_callback( (XMC_CCU4_SLICE_t *const) CCU42_Channel0_Handle.p_config->p_slice_context );
	}
	#endif

	/* Enable shadow transfer for new PWM value update */
	XMC_CCU4_EnableShadowTransfer( (XMC_CCU4_MODULE_t *const) CCU4_Module2.p_module_config->p_module_context,
									XMC_CCU4_SHADOW_TRANSFER_SLICE_0 );
}
#endif	/* CCU40_CHANNEL3_USED */


/*****************************************************************************/


#if ( (CCU80_CHANNEL0_USED == 1U) && (CCU80_CHANNEL1_USED == 1U) )
__attribute__((section(".ram_code"))) void CCU80_Ch0_Ch1_Handler( void )
{
	if( XMC_CCU8_SLICE_GetEvent( (XMC_CCU8_SLICE_t *const) CCU80_Channel0_Handle.p_config->p_slice_context,
									XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH)
			)
	{
		/* Clear Period Match event */
		XMC_CCU8_SLICE_ClearEvent( (XMC_CCU8_SLICE_t *const) CCU80_Channel0_Handle.p_config->p_slice_context,
									CCU80_Channel0_Handle.p_config->interrupt_event );

		/* Can set new Compare Match value or any other processing */
		#if( CCU8_CALLBACK_HANDLER_USED == 1U )
		if( CCU80_Channel0_Handle.p_callback->fp_callback != NULL )
		{
			CCU80_Channel0_Handle.p_callback->fp_callback( (XMC_CCU8_SLICE_t *const) CCU80_Channel0_Handle.p_config->p_slice_context );
		}
		#endif

		/* Enable shadow transfer for new PWM value update */
		XMC_CCU8_EnableShadowTransfer( (XMC_CCU8_MODULE_t *const) CCU8_Module0.p_module_config->p_module_context,
										XMC_CCU4_SHADOW_TRANSFER_SLICE_0 );
	}
}
#endif	/* CCU80_CHANNEL0_USED && CCU80_CHANNEL1_USED */


#if (CCU80_CHANNEL2_USED == 1U )
__attribute__((section(".ram_code"))) void CCU80_Channel2_Handler( void )
{
	if( XMC_CCU8_SLICE_GetEvent( (XMC_CCU8_SLICE_t *const) CCU80_Channel2_Handle.p_config->p_slice_context,
									XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH)
			)
	{
		/* Clear Period Match event */
		XMC_CCU8_SLICE_ClearEvent( (XMC_CCU8_SLICE_t *const) CCU80_Channel2_Handle.p_config->p_slice_context,
									CCU80_Channel2_Handle.p_config->interrupt_event );

		/* Can set new Compare Match value or any other processing */
		#if( CCU8_CALLBACK_HANDLER_USED == 1U )
		if( CCU80_Channel2_Handle.p_callback->fp_callback != NULL )
		{
			CCU80_Channel2_Handle.p_callback->fp_callback( (XMC_CCU8_SLICE_t *const) CCU80_Channel2_Handle.p_config->p_slice_context );
		}
		#endif

		/* Enable shadow transfer for new PWM value update */
		XMC_CCU8_EnableShadowTransfer( (XMC_CCU8_MODULE_t *const) CCU8_Module0.p_module_config->p_module_context,
										XMC_CCU4_SHADOW_TRANSFER_SLICE_2 );
	}
}
#endif	/* CCU80_CHANNEL2_USED */


/*********************************** End of File ******************************/
