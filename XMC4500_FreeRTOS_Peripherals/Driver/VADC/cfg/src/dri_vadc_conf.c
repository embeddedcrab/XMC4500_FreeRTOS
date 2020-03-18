/*****************************************************************************
* Copyright (c) 2019 - Hemant Sharma - All Rights Reserved
*
* Feel free to use this Code at your own risk for your own purposes.
*
*******************************************************************************/
/******************************************************************************
* Title:		UART Configuration Source
* Filename:		dri_vadc_conf.c
* Author:		HS
* Origin Date:	01/29/2020
* Version:		1.0.0
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	dri_vadc_conf.c
 *  @brief:	This source file contains configuration function definitions for
 *  		VADC
 */


/******************************************************************************
* Includes
*******************************************************************************/
#include <dri_vadc.h>


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
 * @brief	VADC API functions
 *
 * \par<b>Description:</b><br>
 * 			This is data structure for UART API functions to be used by Application
 */
tStVADC_BackgroundScan_Api VADC_BackgroundScan_Api_Functions =
{
	.fp_global_init = &VADC_global_init,
	.fp_init = &VADC_background_request_init,
	.fp_start = &VADC_background_scan_start_conversion,
	.fp_get_group = &VADC_get_group
};


/* Callback handler for user */
#if (VADC_CALLBACK_HANDLER_USED == 1U)
extern void VADC_callback_handler( void * p_channel, unsigned short *p_data );
#endif


#if( VADC_BACKGROUND_REQUEST_SOURCE == 1U )
static XMC_VADC_BACKGROUND_CONFIG_t VADC_Background_Scan_Configuration =
{
	.conv_start_mode = XMC_VADC_STARTMODE_WFS,
	.req_src_priority = XMC_VADC_GROUP_RS_PRIORITY_0,
	/**< asctrl */
#if(XMC_VADC_GROUP_SRCREG_AVAILABLE == (1U))
	.src_specific_result_reg = 0,
#endif
	.trigger_signal = XMC_VADC_REQ_TR_A,
	.trigger_edge = XMC_VADC_TRIGGER_EDGE_NONE,
	.gate_signal = XMC_VADC_REQ_GT_A,
	.timer_mode = 0,
	/**< asmr */
	.external_trigger = 0,
	.req_src_interrupt = 1,
	.enable_auto_scan = 0,
	.load_mode = XMC_VADC_SCAN_LOAD_OVERWRITE
};
#endif


/* VADC Global configuration */
tStVADC_GlobalConfiguartion VADC_Global_Configuration =
{
	.p_channel_context = (XMC_VADC_GLOBAL_t *) VADC,
	#if( VADC_BACKGROUND_REQUEST_SOURCE == 1U )
	.p_background_config = &VADC_Background_Scan_Configuration,
	#endif
	.global_config =
	{
		.boundary0 = 0,	/**< Lower boundary value for Normal comparison mode */
		.boundary1 = 0,	/**< Upper boundary value for Normal comparison mode */
		/**< Clock divider = 3, Fadci = Fadc/clk_div */
		.clock_config =
		{
			.analog_clock_divider = 3,
			.msb_conversion_clock = 0,
			.arbiter_clock_divider = 0
		},
		/**< Standard values considered, 66.7ns Sampling time and 12-bit conversion */
		.class0 =
		{
			.sample_time_std_conv = 0,
			.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT
			#if(XMC_VADC_EMUX_AVAILABLE == 1U)
			,.sampling_phase_emux_channel = 0,
			.conversion_mode_emux = XMC_VADC_CONVMODE_12BIT
			#endif
		},
		.class1 =
		{
			.sample_time_std_conv = 0,
			.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT
			#if(XMC_VADC_EMUX_AVAILABLE == 1U)
			,.sampling_phase_emux_channel = 0,
			.conversion_mode_emux = XMC_VADC_CONVMODE_12BIT
			#endif
		},

		.data_reduction_control = 3,/**< Accumulate 4 values for Result */
		.wait_for_read_mode = 0,
	#if(VADC_INTERRUPT_USED == 1U)
		.event_gen_enable = 1,
	#else
		.event_gen_enable = 0,
	#endif
		.module_disable = 0,
		.disable_sleep_mode_control = 0
	}
};


/* VADC Group Configurations */
#if (VADC_GROUPS_USED > 0)
static tStVADC_BackgroundScan_GroupConfiguartion VADC_Group0_Scan_Configuration =
{
	.p_group_context = (XMC_VADC_GROUP_t *)VADC_G0,
	.group_config =
	{
		.emux_config =
		{
			.starting_external_channel = 0,
			#if (XMC_VADC_EMUX_CH_SEL_STYLE == 1U)
			.connected_channel = 0
			#else
			.connected_channel = 0,
			#endif
			.emux_mode = 0,
			.emux_coding = 0,
			.stce_usage = 0
			#if (XMC_VADC_EMUX_CH_SEL_STYLE == 1U)
			,.emux_channel_select_style = 0;
			#endif
		},
		.class0 =
		{
			.sample_time_std_conv = 0,
			.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT
			#if(XMC_VADC_EMUX_AVAILABLE == 1U)
			,.sampling_phase_emux_channel = 0,
			.conversion_mode_emux = XMC_VADC_CONVMODE_12BIT
			#endif
		},
		.class1 =
		{
			.sample_time_std_conv = 0,
			.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT
			#if(XMC_VADC_EMUX_AVAILABLE == 1U)
			,.sampling_phase_emux_channel = 0,
			.conversion_mode_emux = XMC_VADC_CONVMODE_12BIT
			#endif
		},
		.boundary0 = 0,
		.boundary1 = 0,
		.arbitration_round_length = 0,
		.arbiter_mode = XMC_VADC_GROUP_ARBMODE_ALWAYS
	}
	#if( VADC_INTERRUPT_USED == 1U )
	,.group_isr_config =
	{
		.irq.irq_num = VADC0_C0_0_IRQn,
		.irq.irq_priority = 45,
		.sr = XMC_VADC_SR_SHARED_SR0
	}
	#endif
};
#endif	/* (VADC_GROUPS_USED > 0) */


/* VADC Channel Configurations */
#if( VADC_GROUP0_CHANNELS_USED > 0 )
static tStVADC_ChannelConfiguartion VADC_Group0_Channel_Configurarion[VADC_GROUP0_CHANNELS_USED] =
{
{/* Channel 0 Configuration */
	.channel_config =
	{
		.input_class = XMC_VADC_CHANNEL_CONV_GROUP_CLASS0,
		.lower_boundary_select = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.upper_boundary_select = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.event_gen_criteria = XMC_VADC_CHANNEL_EVGEN_NEVER,
		.sync_conversion = 0,
		.alternate_reference = XMC_VADC_CHANNEL_REF_INTREF,
		/* VADC Channel result number */
		.result_reg_number = 0,

		.use_global_result = 0,
		.result_alignment = XMC_VADC_RESULT_ALIGN_RIGHT,
		.broken_wire_detect_channel = XMC_VADC_CHANNEL_BWDCH_VAGND,
		.broken_wire_detect = 0,

		/**< bfl */
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.flag_output_condition_ch0 = 0,
		.flag_output_condition_ch1 = 0,
		.flag_output_condition_ch2 = 0,
		.flag_output_condition_ch3 = 0,
		#endif
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.invert_boundary_flag_ch0 = 0,
		.invert_boundary_flag_ch1 = 0,
		.invert_boundary_flag_ch2 = 0,
		.invert_boundary_flag_ch3 = 0,
		#else
		.boundary_flag_output_ch0 = 0,
		.boundary_flag_output_ch1 = 0,
		.boundary_flag_output_ch2 = 0,
		.boundary_flag_output_ch3 = 0,
		#endif

		/**< bflc */
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.boundary_flag_mode_ch0 = 0,
		.boundary_flag_mode_ch1 = 0,
		.boundary_flag_mode_ch2 = 0,
		.boundary_flag_mode_ch3 = 0,
		#endif

		.channel_priority = 0,
		.alias_channel = XMC_VADC_CHANNEL_ALIAS_DISABLED
	},
	.result_config =
	{
		.data_reduction_control = 3,
		.post_processing_mode = XMC_VADC_DMM_REDUCTION_MODE,
		.wait_for_read_mode = 0,
		.part_of_fifo = 0,
		.event_gen_enable = 1
	}
},
{/* Channel 1 Configuration */
	.channel_config =
	{
		.input_class = XMC_VADC_CHANNEL_CONV_GROUP_CLASS0,
		.lower_boundary_select = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.upper_boundary_select = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.event_gen_criteria = XMC_VADC_CHANNEL_EVGEN_NEVER,
		.sync_conversion = 0,
		.alternate_reference = XMC_VADC_CHANNEL_REF_INTREF,
		/* VADC Channel result number */
		.result_reg_number = 1,

		.use_global_result = 0,
		.result_alignment = XMC_VADC_RESULT_ALIGN_RIGHT,
		.broken_wire_detect_channel = XMC_VADC_CHANNEL_BWDCH_VAGND,
		.broken_wire_detect = 0,

		/**< bfl */
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.flag_output_condition_ch0 = 0,
		.flag_output_condition_ch1 = 0,
		.flag_output_condition_ch2 = 0,
		.flag_output_condition_ch3 = 0,
		#endif
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.invert_boundary_flag_ch0 = 0,
		.invert_boundary_flag_ch1 = 0,
		.invert_boundary_flag_ch2 = 0,
		.invert_boundary_flag_ch3 = 0,
		#else
		.boundary_flag_output_ch0 = 0,
		.boundary_flag_output_ch1 = 0,
		.boundary_flag_output_ch2 = 0,
		.boundary_flag_output_ch3 = 0,
		#endif

		/**< bflc */
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.boundary_flag_mode_ch0 = 0,
		.boundary_flag_mode_ch1 = 0,
		.boundary_flag_mode_ch2 = 0,
		.boundary_flag_mode_ch3 = 0,
		#endif

		.channel_priority = 0,
		.alias_channel = XMC_VADC_CHANNEL_ALIAS_DISABLED
	},
	.result_config =
	{
		.data_reduction_control = 3,
		.post_processing_mode = XMC_VADC_DMM_REDUCTION_MODE,
		.wait_for_read_mode = 0,
		.part_of_fifo = 0,
		.event_gen_enable = 1
	}
},
{/* Channel 2 Configuration */
	.channel_config =
	{
		.input_class = XMC_VADC_CHANNEL_CONV_GROUP_CLASS0,
		.lower_boundary_select = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.upper_boundary_select = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.event_gen_criteria = XMC_VADC_CHANNEL_EVGEN_NEVER,
		.sync_conversion = 0,
		.alternate_reference = XMC_VADC_CHANNEL_REF_INTREF,
		/* VADC Channel result number */
		.result_reg_number = 2,

		.use_global_result = 0,
		.result_alignment = XMC_VADC_RESULT_ALIGN_RIGHT,
		.broken_wire_detect_channel = XMC_VADC_CHANNEL_BWDCH_VAGND,
		.broken_wire_detect = 0,

		/**< bfl */
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.flag_output_condition_ch0 = 0,
		.flag_output_condition_ch1 = 0,
		.flag_output_condition_ch2 = 0,
		.flag_output_condition_ch3 = 0,
		#endif
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.invert_boundary_flag_ch0 = 0,
		.invert_boundary_flag_ch1 = 0,
		.invert_boundary_flag_ch2 = 0,
		.invert_boundary_flag_ch3 = 0,
		#else
		.boundary_flag_output_ch0 = 0,
		.boundary_flag_output_ch1 = 0,
		.boundary_flag_output_ch2 = 0,
		.boundary_flag_output_ch3 = 0,
		#endif

		/**< bflc */
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.boundary_flag_mode_ch0 = 0,
		.boundary_flag_mode_ch1 = 0,
		.boundary_flag_mode_ch2 = 0,
		.boundary_flag_mode_ch3 = 0,
		#endif

		.channel_priority = 0,
		.alias_channel = XMC_VADC_CHANNEL_ALIAS_DISABLED
	},
	.result_config =
	{
		.data_reduction_control = 3,
		.post_processing_mode = XMC_VADC_DMM_REDUCTION_MODE,
		.wait_for_read_mode = 0,
		.part_of_fifo = 0,
		.event_gen_enable = 1
	}
},
{/* Channel 3 Configuration */
	.channel_config =
	{
		.input_class = XMC_VADC_CHANNEL_CONV_GROUP_CLASS0,
		.lower_boundary_select = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.upper_boundary_select = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.event_gen_criteria = XMC_VADC_CHANNEL_EVGEN_NEVER,
		.sync_conversion = 0,
		.alternate_reference = XMC_VADC_CHANNEL_REF_INTREF,
		/* VADC Channel result number */
		.result_reg_number = 3,

		.use_global_result = 0,
		.result_alignment = XMC_VADC_RESULT_ALIGN_RIGHT,
		.broken_wire_detect_channel = XMC_VADC_CHANNEL_BWDCH_VAGND,
		.broken_wire_detect = 0,

		/**< bfl */
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.flag_output_condition_ch0 = 0,
		.flag_output_condition_ch1 = 0,
		.flag_output_condition_ch2 = 0,
		.flag_output_condition_ch3 = 0,
		#endif
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.invert_boundary_flag_ch0 = 0,
		.invert_boundary_flag_ch1 = 0,
		.invert_boundary_flag_ch2 = 0,
		.invert_boundary_flag_ch3 = 0,
		#else
		.boundary_flag_output_ch0 = 0,
		.boundary_flag_output_ch1 = 0,
		.boundary_flag_output_ch2 = 0,
		.boundary_flag_output_ch3 = 0,
		#endif

		/**< bflc */
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.boundary_flag_mode_ch0 = 0,
		.boundary_flag_mode_ch1 = 0,
		.boundary_flag_mode_ch2 = 0,
		.boundary_flag_mode_ch3 = 0,
		#endif

		.channel_priority = 0,
		.alias_channel = XMC_VADC_CHANNEL_ALIAS_DISABLED
	},
	.result_config =
	{
		.data_reduction_control = 3,
		.post_processing_mode = XMC_VADC_DMM_REDUCTION_MODE,
		.wait_for_read_mode = 0,
		.part_of_fifo = 0,
		.event_gen_enable = 1
	}
},
{/* Channel 4 Configuration */
	.channel_config =
	{
		.input_class = XMC_VADC_CHANNEL_CONV_GROUP_CLASS0,
		.lower_boundary_select = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.upper_boundary_select = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.event_gen_criteria = XMC_VADC_CHANNEL_EVGEN_NEVER,
		.sync_conversion = 0,
		.alternate_reference = XMC_VADC_CHANNEL_REF_INTREF,
		/* VADC Channel result number */
		.result_reg_number = 4,

		.use_global_result = 0,
		.result_alignment = XMC_VADC_RESULT_ALIGN_RIGHT,
		.broken_wire_detect_channel = XMC_VADC_CHANNEL_BWDCH_VAGND,
		.broken_wire_detect = 0,

		/**< bfl */
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.flag_output_condition_ch0 = 0,
		.flag_output_condition_ch1 = 0,
		.flag_output_condition_ch2 = 0,
		.flag_output_condition_ch3 = 0,
		#endif
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.invert_boundary_flag_ch0 = 0,
		.invert_boundary_flag_ch1 = 0,
		.invert_boundary_flag_ch2 = 0,
		.invert_boundary_flag_ch3 = 0,
		#else
		.boundary_flag_output_ch0 = 0,
		.boundary_flag_output_ch1 = 0,
		.boundary_flag_output_ch2 = 0,
		.boundary_flag_output_ch3 = 0,
		#endif

		/**< bflc */
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.boundary_flag_mode_ch0 = 0,
		.boundary_flag_mode_ch1 = 0,
		.boundary_flag_mode_ch2 = 0,
		.boundary_flag_mode_ch3 = 0,
		#endif

		.channel_priority = 0,
		.alias_channel = XMC_VADC_CHANNEL_ALIAS_DISABLED
	},
	.result_config =
	{
		.data_reduction_control = 3,
		.post_processing_mode = XMC_VADC_DMM_REDUCTION_MODE,
		.wait_for_read_mode = 0,
		.part_of_fifo = 0,
		.event_gen_enable = 1
	}
},
{/* Channel 5 Configuration */
	.channel_config =
	{
		.input_class = XMC_VADC_CHANNEL_CONV_GROUP_CLASS0,
		.lower_boundary_select = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.upper_boundary_select = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.event_gen_criteria = XMC_VADC_CHANNEL_EVGEN_NEVER,
		.sync_conversion = 0,
		.alternate_reference = XMC_VADC_CHANNEL_REF_INTREF,
		/* VADC Channel result number */
		.result_reg_number = 5,

		.use_global_result = 0,
		.result_alignment = XMC_VADC_RESULT_ALIGN_RIGHT,
		.broken_wire_detect_channel = XMC_VADC_CHANNEL_BWDCH_VAGND,
		.broken_wire_detect = 0,

		/**< bfl */
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.flag_output_condition_ch0 = 0,
		.flag_output_condition_ch1 = 0,
		.flag_output_condition_ch2 = 0,
		.flag_output_condition_ch3 = 0,
		#endif
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.invert_boundary_flag_ch0 = 0,
		.invert_boundary_flag_ch1 = 0,
		.invert_boundary_flag_ch2 = 0,
		.invert_boundary_flag_ch3 = 0,
		#else
		.boundary_flag_output_ch0 = 0,
		.boundary_flag_output_ch1 = 0,
		.boundary_flag_output_ch2 = 0,
		.boundary_flag_output_ch3 = 0,
		#endif

		/**< bflc */
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.boundary_flag_mode_ch0 = 0,
		.boundary_flag_mode_ch1 = 0,
		.boundary_flag_mode_ch2 = 0,
		.boundary_flag_mode_ch3 = 0,
		#endif

		.channel_priority = 0,
		.alias_channel = XMC_VADC_CHANNEL_ALIAS_DISABLED
	},
	.result_config =
	{
		.data_reduction_control = 3,
		.post_processing_mode = XMC_VADC_DMM_REDUCTION_MODE,
		.wait_for_read_mode = 0,
		.part_of_fifo = 0,
		.event_gen_enable = 1
	}
},
{/* Channel 6 Configuration */
	.channel_config =
	{
		.input_class = XMC_VADC_CHANNEL_CONV_GROUP_CLASS0,
		.lower_boundary_select = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.upper_boundary_select = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.event_gen_criteria = XMC_VADC_CHANNEL_EVGEN_NEVER,
		.sync_conversion = 0,
		.alternate_reference = XMC_VADC_CHANNEL_REF_INTREF,
		/* VADC Channel result number */
		.result_reg_number = 6,

		.use_global_result = 0,
		.result_alignment = XMC_VADC_RESULT_ALIGN_RIGHT,
		.broken_wire_detect_channel = XMC_VADC_CHANNEL_BWDCH_VAGND,
		.broken_wire_detect = 0,

		/**< bfl */
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.flag_output_condition_ch0 = 0,
		.flag_output_condition_ch1 = 0,
		.flag_output_condition_ch2 = 0,
		.flag_output_condition_ch3 = 0,
		#endif
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.invert_boundary_flag_ch0 = 0,
		.invert_boundary_flag_ch1 = 0,
		.invert_boundary_flag_ch2 = 0,
		.invert_boundary_flag_ch3 = 0,
		#else
		.boundary_flag_output_ch0 = 0,
		.boundary_flag_output_ch1 = 0,
		.boundary_flag_output_ch2 = 0,
		.boundary_flag_output_ch3 = 0,
		#endif

		/**< bflc */
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.boundary_flag_mode_ch0 = 0,
		.boundary_flag_mode_ch1 = 0,
		.boundary_flag_mode_ch2 = 0,
		.boundary_flag_mode_ch3 = 0,
		#endif

		.channel_priority = 0,
		.alias_channel = XMC_VADC_CHANNEL_ALIAS_DISABLED
	},
	.result_config =
	{
		.data_reduction_control = 3,
		.post_processing_mode = XMC_VADC_DMM_REDUCTION_MODE,
		.wait_for_read_mode = 0,
		.part_of_fifo = 0,
		.event_gen_enable = 1
	}
},
{/* Channel 7 Configuration */
	.channel_config =
	{
		.input_class = XMC_VADC_CHANNEL_CONV_GROUP_CLASS0,
		.lower_boundary_select = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.upper_boundary_select = XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.event_gen_criteria = XMC_VADC_CHANNEL_EVGEN_NEVER,
		.sync_conversion = 0,
		.alternate_reference = XMC_VADC_CHANNEL_REF_INTREF,
		/* VADC Channel result number */
		.result_reg_number = 7,

		.use_global_result = 0,
		.result_alignment = XMC_VADC_RESULT_ALIGN_RIGHT,
		.broken_wire_detect_channel = XMC_VADC_CHANNEL_BWDCH_VAGND,
		.broken_wire_detect = 0,

		/**< bfl */
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.flag_output_condition_ch0 = 0,
		.flag_output_condition_ch1 = 0,
		.flag_output_condition_ch2 = 0,
		.flag_output_condition_ch3 = 0,
		#endif
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.invert_boundary_flag_ch0 = 0,
		.invert_boundary_flag_ch1 = 0,
		.invert_boundary_flag_ch2 = 0,
		.invert_boundary_flag_ch3 = 0,
		#else
		.boundary_flag_output_ch0 = 0,
		.boundary_flag_output_ch1 = 0,
		.boundary_flag_output_ch2 = 0,
		.boundary_flag_output_ch3 = 0,
		#endif

		/**< bflc */
		#if (XMC_VADC_BOUNDARY_FLAG_SELECT == 1U)
		/* Need to set values, dummy provided */
		.boundary_flag_mode_ch0 = 0,
		.boundary_flag_mode_ch1 = 0,
		.boundary_flag_mode_ch2 = 0,
		.boundary_flag_mode_ch3 = 0,
		#endif

		.channel_priority = 0,
		.alias_channel = XMC_VADC_CHANNEL_ALIAS_DISABLED
	},
	.result_config =
	{
		.data_reduction_control = 3,
		.post_processing_mode = XMC_VADC_DMM_REDUCTION_MODE,
		.wait_for_read_mode = 0,
		.part_of_fifo = 0,
		.event_gen_enable = 1
	}
}
};
#endif

/* VADC Background Scan Group Configuration for Global Access */
static tStVADC_BackgroundScanConfiguartion VADC_BackgroundScan_GroupConfiguration =
{
	.p_background_scan_group_config = &VADC_Group0_Scan_Configuration,
	.p_channel_config = VADC_Group0_Channel_Configurarion,
	.group_channels = VADC_GROUP0_CHANNELS_USED
};

/* VADC Control for Global Access */
static tStVADC_Control VADC_Group0_Scan_Control;

static tStVADC_Callbacks VADC_Callbacks =
{
	.fp_callback = &VADC_callback_handler
};


/** VADC Instance **/
static tStVADC_BackgroundScan VADC_BackgroundScan[VADC_GROUPS_USED] =
{
	{/* Instance for VADC Background Scan Group 0 */
		.p_config = &VADC_BackgroundScan_GroupConfiguration,
		.p_control = &VADC_Group0_Scan_Control,
		#if( VADC_CALLBACK_HANDLER_USED == 1U )
		.p_callback = &VADC_Callbacks
		#endif
	}
};


/** VADC Instance Global Access **/
tStVADC_Background VADC_BackgroundScan_Handle =
{
	.p_instance = {VADC_BackgroundScan}
};


/******************************************************************************
* Function Definitions
*******************************************************************************/


/******* ISR Handlers for VADC channel *******/

/* Channels ISR Entries */
/* Background Group ISR Entries */
#if( VADC_BACKGROUND_REQUEST_SOURCE == 1U )
extern void VADC_isr_entry( void * p_group, const unsigned char group );
	/* Group 0 ISR Entry */
	#if( VADC_GROUP0_USED == 1U )
	void VADC_Group0_Handler( void )
	{
		VADC_isr_entry( VADC_BackgroundScan_Handle.p_instance[0], 0 );
	}
	#endif
	/* Group 1 ISR Entry */
	#if( VADC_GROUP1_USED == 1U )
	void VADC_Group1_Handler( void )
	{
		VADC_isr_entry( VADC_BackgroundScan_Handle.p_instance[1], 0 );
	}
	#endif
	/* Group 2 ISR Entry */
	#if( VADC_GROUP2_USED == 1U )
	void VADC_Group2_Handler( void )
	{
		VADC_isr_entry( VADC_BackgroundScan_Handle.p_instance[2], 0 );
	}
	#endif
	/* Group 3 ISR Entry */
	#if( VADC_GROUP3_USED == 1U )
	void VADC_Group3_Handler( void )
	{
		VADC_isr_entry( VADC_BackgroundScan_Handle.p_instance[3], 0 );
	}
	#endif
#endif


/*********************************** End of File ******************************/
