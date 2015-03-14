/* Copyright 2012 lynix <lynix47@gmail.com>
 * Copyright 2013 JinTu <JinTu@praecogito.com>, lynix <lynix47@gmail.com>
 * Copyright 2014 barracks510 <barracks510@gmail.com>
 * COpyright 2015 barracks510 <barracks510@gmail.com>
 *
 * This file is part of Aquaeronix.
 *
 * Aquaeronix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Aquaeronix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Aquaeronix. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBAQUAERO5_H_
#define LIBAQUAERO5_H_

#include <stdint.h>
#include <time.h>

/* sensor quantity */
#define AQ5_NUM_TEMP					16
#define AQ5_NUM_FAN						12
#define AQ5_NUM_FLOW					14
#define AQ5_NUM_CPU						8
#define AQ5_NUM_LEVEL					4
#define AQ5_NUM_INFO_PAGE				32
#define AQ5_NUM_VIRT_SENSORS			4
#define AQ5_NUM_SOFT_SENSORS			8
#define AQ5_NUM_OTHER_SENSORS			16
#define AQ5_NUM_POWER_SENSORS			4
#define AQ5_NUM_CURVE_POINTS			16
#define AQ5_NUM_CURVE_CONTROLLERS		4
#define AQ5_NUM_TARGET_VAL_CONTROLLERS	8
#define AQ5_NUM_TWO_POINT_CONTROLLERS	16
#define AQ5_NUM_PRESET_VAL_CONTROLLERS	32
#define AQ5_NUM_DATA_LOG				16
#define AQ5_NUM_ALARM_AND_WARNING_LVLS	8
#define AQ5_NUM_TEMP_ALARMS				16
#define AQ5_NUM_FLOW_ALARMS				4
#define AQ5_NUM_PUMP_ALARMS				4
#define AQ5_NUM_FILL_ALARMS				4
#define AQ5_NUM_TIMERS					32
#define AQ5_NUM_IR_COMMANDS				16
#define AQ5_NUM_AQUASTREAM_XT		2
#define AQ5_NUM_NAME_TYPES		28

/* constant for unknown value */
#define AQ5_FLOAT_UNDEF			-99.0

/* The intrapage delay for name reports */
#define AQ5_NAME_REPORT_INTRAPAGE_DELAY 7


typedef enum { FALSE, TRUE } boolean_t;

typedef enum {
	NAME_BUTTON,
	NAME_SENSOR,
	NAME_POWERADJUST,
	NAME_SOFTWARE_SENSOR,
	NAME_VIRTUAL_SENSOR,
	NAME_MPS,
	NAME_AQUASTREAM,
	NAME_SENSOR_EXT1,
	NAME_FAN_AMPLIFIER,
	NAME_CPU,
	NAME_SENSOR_EXT2,
	NAME_FAN,
	NAME_FLOW,
	NAME_PROFILE,
	NAME_AQUASTREAM_XT,
	NAME_MULTISWITCH,
	NAME_TARGET_VALUE_CONT,
	NAME_CURVE_CONT,
	NAME_TWO_POINT_CONT,
	NAME_PRESET_VALUE_CONT,
	NAME_POWER_OUTPUT,
	NAME_ALERT_LEVEL,
	NAME_AQ5,
	NAME_FILL_LEVEL,
	NAME_PRESSURE,
	NAME_HUMIDITY,
	NAME_WATER_QUALITY,
	NAME_MPS_D5
} name_enum_t;

typedef struct {
	uint8_t	address;
	uint8_t	count;
} name_position_t;

static name_position_t name_positions[] = {
	[NAME_BUTTON] 		= { 0,	16 },
	[NAME_SENSOR] 		= { 16,	8 },
	[NAME_POWERADJUST] 	= { 24,	8 },
	[NAME_SOFTWARE_SENSOR] 	= { 32,	8 },
	[NAME_VIRTUAL_SENSOR] 	= { 40,	4 },
	[NAME_MPS] 		= { 44,	8 },
	[NAME_AQUASTREAM] 	= { 52,	2 },
	[NAME_SENSOR_EXT1] 	= { 54,	6 },
	[NAME_FAN_AMPLIFIER] 	= { 60,	12 },
	[NAME_CPU] 		= { 72,	1 },
	[NAME_SENSOR_EXT2] 	= { 73, 7 },
	[NAME_FAN] 		= { 80,	12 },
	[NAME_FLOW] 		= { 92,	14 },
	[NAME_PROFILE] 		= { 106,	4 },
	[NAME_AQUASTREAM_XT] 	= { 110,	2 },
	[NAME_MULTISWITCH] 	= { 112,	2 },
	[NAME_TARGET_VALUE_CONT] = { 114,	8 },
	[NAME_CURVE_CONT] 	= { 122,	4 },
	[NAME_TWO_POINT_CONT] 	= { 126,	16 },
	[NAME_PRESET_VALUE_CONT] = { 142,	8 },
	[NAME_POWER_OUTPUT]	= { 150,	2 },
	[NAME_ALERT_LEVEL] 	= { 152,	8 },
	[NAME_AQ5] 		= { 160,	1 },
	[NAME_FILL_LEVEL] 	= { 161,	4 },
	[NAME_PRESSURE] 	= { 165,	4 },
	[NAME_HUMIDITY] 	= { 169,	4 },
	[NAME_WATER_QUALITY] 	= { 173,	4 },
	[NAME_MPS_D5] 		= { 177,	4 }
};

typedef enum {
	AQASTREAM_XT_MODE_AUTO		=	0x00,
	AQASTREAM_XT_MODE_MANUAL	=	0x01,
	AQASTREAM_XT_MODE_DEARATION	=	0x02,
	AQASTREAM_XT_MODE_OFFLINE	=	0xff
} aquastream_xt_freqmode_t;

typedef struct {
	boolean_t	available;
	boolean_t	alarm;
} aquastream_xt_status_t;	

typedef struct {
	aquastream_xt_status_t	status;
	aquastream_xt_freqmode_t	freqmode;
	uint16_t	frequency;
	double		voltage;
	uint16_t	current;
} aquastream_xt_data_t;

/* structures holding device data */
typedef struct {
	struct tm	time_utc;
	uint16_t	serial_major;
	uint16_t	serial_minor;
	uint16_t	firmware_version;
	uint16_t	bootloader_version;
	uint16_t	hardware_version;
	struct tm	uptime;
	struct tm	total_time;
	double		temp[AQ5_NUM_TEMP];
	double		vtemp[AQ5_NUM_VIRT_SENSORS];
	double		stemp[AQ5_NUM_SOFT_SENSORS];
	double		otemp[AQ5_NUM_OTHER_SENSORS];
	uint16_t	fan_current[AQ5_NUM_FAN];
	uint16_t	fan_rpm[AQ5_NUM_FAN];
	double		fan_duty[AQ5_NUM_FAN];
	double		fan_voltage[AQ5_NUM_FAN];
	double		fan_vrm_temp[AQ5_NUM_FAN];
	double		flow[AQ5_NUM_FLOW];
	double		cpu_temp[AQ5_NUM_CPU];
	double		level[AQ5_NUM_LEVEL];
	aquastream_xt_data_t	aquastream_xt[AQ5_NUM_AQUASTREAM_XT];
} aq5_data_t;

typedef enum { 
	M_OUTPUT 	= 0x0000, 
	M_RPM 		= 0x0001 
} fan_regulation_mode_t;

typedef enum {
	NONE		=	0xffff,
	/* Target value controllers */
	TARGET_VAL_CONT_1	=	0x0040,
	TARGET_VAL_CONT_2	=	0x0041,
	TARGET_VAL_CONT_3	=	0x0042,
	TARGET_VAL_CONT_4	=	0x0043,
	TARGET_VAL_CONT_5	=	0x0044,
	TARGET_VAL_CONT_6	=	0x0045,
	TARGET_VAL_CONT_7	=	0x0046,
	TARGET_VAL_CONT_8	=	0x0047,
	/* Two point controllers */
	TWO_POINT_CONT_1	=	0x0048,
	TWO_POINT_CONT_2	=	0x0049,
	TWO_POINT_CONT_3	=	0x004a,
	TWO_POINT_CONT_4	=	0x004b,
	TWO_POINT_CONT_5	=	0x004c,
	TWO_POINT_CONT_6	=	0x004d,
	TWO_POINT_CONT_7	=	0x004e,
	TWO_POINT_CONT_8	=	0x004f,
	TWO_POINT_CONT_9	=	0x0050,
	TWO_POINT_CONT_10	=	0x0051,
	TWO_POINT_CONT_11	=	0x0052,
	TWO_POINT_CONT_12	=	0x0053,
	TWO_POINT_CONT_13	=	0x0054,
	TWO_POINT_CONT_14	=	0x0055,
	TWO_POINT_CONT_15	=	0x0056,
	TWO_POINT_CONT_16	=	0x0057,
	/* Curve controllers */
	CURVE_CTRLR_1	=	0x0058,
	CURVE_CTRLR_2	=	0x0059,
	CURVE_CTRLR_3	=	0x005a,
	CURVE_CTRLR_4	=	0x005b,
	/* RGB LEDs */
	RGB_LED_RED	=	0x005c,
	RGB_LED_BLUE	=	0x005d,
	RGB_LED_GREEN	=	0x005e,
	/* Preset values */
	PRESET_VAL_1	=	0x0060,
	PRESET_VAL_2	=	0x0061,
	PRESET_VAL_3	=	0x0062,
	PRESET_VAL_4	=	0x0063,
	PRESET_VAL_5	=	0x0064,
	PRESET_VAL_6	=	0x0065,
	PRESET_VAL_7	=	0x0066,
	PRESET_VAL_8	=	0x0067,
	PRESET_VAL_9	=	0x0068,
	PRESET_VAL_10	=	0x0069,
	PRESET_VAL_11	=	0x006a,
	PRESET_VAL_12	=	0x006b,
	PRESET_VAL_13	=	0x006c,
	PRESET_VAL_14	=	0x006d,
	PRESET_VAL_15	=	0x006e,
	PRESET_VAL_16	=	0x006f,
	PRESET_VAL_17	=	0x0070,
	PRESET_VAL_18	=	0x0071,
	PRESET_VAL_19	=	0x0072,
	PRESET_VAL_20	=	0x0073,
	PRESET_VAL_21	=	0x0074,
	PRESET_VAL_22	=	0x0075,
	PRESET_VAL_23	=	0x0076,
	PRESET_VAL_24	=	0x0077,
	PRESET_VAL_25	=	0x0078,
	PRESET_VAL_26	=	0x0079,
	PRESET_VAL_27	=	0x007a,
	PRESET_VAL_28	=	0x007b,
	PRESET_VAL_29	=	0x007c,
	PRESET_VAL_30	=	0x007d,
	PRESET_VAL_31	=	0x007e,
	PRESET_VAL_32	=	0x007f
} controller_data_source_t;

typedef struct {
	fan_regulation_mode_t	fan_regulation_mode;
	boolean_t		use_startboost;
	boolean_t		hold_minimum_power;
	boolean_t		use_programmable_fuse;
} aq5_fan_control_mode_t;

typedef enum { 
	ENGLISH		= 0x00, 
	GERMAN		= 0x01 
} language_t;

typedef enum { 
	CELSIUS		= 0x00, 
	FAHRENHEIT	= 0x01, 
	KELVIN		= 0x02 
} temp_units_t;

typedef enum { 
	LPH		= 0x00, 
	LPM		= 0x01, 
	GPH_US		= 0x02, 
	GPM_US		= 0x03,
	GPH_IMP		= 0x04,
	GPM_IMP		= 0x05
} flow_units_t;

typedef enum { 
	BAR		= 0x00, 
	PSI		= 0x01 
} pressure_units_t;

typedef enum { 
	POINT		= 0x00, 
	COMMA		= 0x01 
} decimal_separator_t;

typedef enum {
	LOG_DATA_1	= 0x00,
	LOG_DATA_2	= 0x01,
	LOG_DATA_3	= 0x02,
	LOG_DATA_4	= 0x03,
	LOG_DATA_5	= 0x04,
	LOG_DATA_6	= 0x05,
	LOG_DATA_7	= 0x06,
	LOG_DATA_8	= 0x07,
	LOG_DATA_9	= 0x08,
	LOG_DATA_10	= 0x09,
	LOG_DATA_11	= 0x0a,
	LOG_DATA_12	= 0x0b,
	LOG_DATA_13	= 0x0c,
	LOG_DATA_14	= 0x0d,
	LOG_DATA_15	= 0x0e,
	LOG_DATA_16	= 0x0f,
	SENSOR_1_2	= 0x10,
	SENSOR_3_4	= 0x11,
	SENSOR_5_6	= 0x12,
	SENSOR_7_8	= 0x13,
	POWERADJUST_1_2	= 0x14,
	POWERADJUST_3_4	= 0x15,
	POWERADJUST_5_6	= 0x16,
	POWERADJUST_7_8	= 0x17,
	SOFT_SENSOR_1_2	= 0x18,
	SOFT_SENSOR_3_4	= 0x19,
	SOFT_SENSOR_5_6	= 0x1a,
	SOFT_SENSOR_7_8	= 0x1b,
	VIRT_SENSOR_1_2	= 0x1c,
	VIRT_SENSOR_3_4	= 0x1d,
	MPS_1		= 0x1e,
	MPS_2		= 0x1f,
	MPS_3		= 0x20,
	MPS_4		= 0x21,
	AQUASTREAM_XT	= 0x22,
	SENSOR_39_40	= 0x23,
	SENSOR_1_4	= 0x24,
	SENSOR_5_8	= 0x25,
	POWERADJUST_1_4	= 0x26,
	POWERADJUST_5_8 = 0x27,
	SOFT_SENSOR_1_4	= 0x28,
	SOFT_SENSOR_5_8	= 0x29,
	VIRT_SENSORS	= 0x2a,
	MPS_1_2		= 0x2b,
	MPS_3_4		= 0x2c,
	AQUASTREAM	= 0x2d,
	SENSOR_41_44	= 0x2e,
	FAN_AMP_1_4	= 0x2f,
	FAN_AMP_5_8	= 0x30,
	FAN_AMP_9_12	= 0x31,
	SENSOR_56_60	= 0x32,
	SENSOR_61_64	= 0x33,
	FAN_1_4_POWER	= 0x34,
	FAN_5_8_POWER	= 0x35,
	FAN_9_12_POWER	= 0x36,
	FAN_1_4_RPM	= 0x37,
	FAN_5_8_RPM	= 0x38,
	FAN_9_12_RPM	= 0x39,
	FAN_1		= 0x3a,
	FAN_2		= 0x3b,
	FAN_3		= 0x3c,
	FAN_4		= 0x3d,
	FAN_5		= 0x3e,
	FAN_6		= 0x3f,
	FAN_7		= 0x40,
	FAN_8		= 0x41,
	FAN_9		= 0x42,
	FAN_10		= 0x43,
	FAN_11		= 0x44,
	FAN_12		= 0x45,
	FLOW_1		= 0x46,
	FLOW_2		= 0x47,
	FLOW_3		= 0x48,
	FLOW_4		= 0x49,
	FLOW_5		= 0x4a,
	FLOW_6		= 0x4b,
	FLOW_7		= 0x4c,
	FLOW_8		= 0x4d,
	FLOW_9		= 0x4e,
	FLOW_10		= 0x4f,
	FLOW_11		= 0x50,
	FLOW_12		= 0x51,
	FLOW_13		= 0x52,
	FLOW_14		= 0x53,
	AQUASTREAM_XT_1	= 0x54,
	AQUASTREAM_XT_2	= 0x55,
	MULTISWITCH_1	= 0x56,
	MULTISWITCH_2	= 0x57,
	FILL_LEVEL_1	= 0x58,
	FILL_LEVEL_2	= 0x59,
	FILL_LEVEL_3	= 0x5a,
	FILL_LEVEL_4	= 0x5b,
	PWR_CONSUMPT_1	= 0x5c,
	PWR_CONSUMPT_2	= 0x5d,
	PWR_CONSUMPT_3	= 0x5e,
	PWR_CONSUMPT_4	= 0x5f,
	AQUAERO_INFO	= 0x60,
	TIME		= 0x61,
	USB_LCD_PAGE	= 0x62,
	RELAY_AND_POWER	= 0x63,
	USER_DEF_LOGO	= 0x64
} info_page_type_t;

typedef enum {
	FAN_REGULATION_MODE,
	BOOLEAN,
	STATE_ENABLE_DISABLE,
	STATE_ENABLE_DISABLE_INV,
	FLOW_CONFIG,
	FAN_LIMITS,
	ALARM_WARNING_LEVELS,
	TEMP_ALARM_CONFIG,
	DATA_LOG_INTERVAL,
	AQ_RELAY_CONFIG,
	LED_PB_MODE,
	SENSOR_DATA_SOURCE,
	VIRT_SENSOR_MODE,
	EVENT_ACTION,
	DATE_FORMAT,
	TIME_FORMAT,
	DISPLAY_MODE,
	CONTROLLER_DATA_SRC, 
	LANGUAGE, 
	TEMP_UNITS, 
	FLOW_UNITS, 
	PRESSURE_UNITS, 
	DECIMAL_SEPARATOR,
	INFO_SCREEN, 
	PAGE_DISPLAY_MODE,
	DISABLE_KEYS,
	ILLUM_MODE,
	KEY_TONE,
	AQUASTREAM_XT_FREQMODE
} val_str_opt_t;

typedef enum {
	HIDE_PAGE	= 0x00,
	SHOW_PAGE	= 0x01,
	SHOW_PAGE_PERM	= 0x02
} page_display_mode_t;

typedef enum {
	ENABLED		= 0x00,
	DISABLED	= 0xFF
} disable_keys_t;

typedef enum {
	AUTO_OFF	= 0x00,
	ALWAYS_ON	= 0x01
} illumination_mode_t;

typedef enum {
	OFF		= 0x00,
	QUIET		= 0x01,
	NORMAL		= 0x02,
	LOUD		= 0x03
} key_tone_t;

typedef struct {
	page_display_mode_t	page_display_mode;
	uint16_t		display_time;
	info_page_type_t	info_page_type;
} info_page_t;

typedef struct {
	uint16_t	enter_key;
	uint16_t	up_key;
	uint16_t	down_key;
	uint16_t	programmable_key_1;
	uint16_t	programmable_key_2;
	uint16_t	programmable_key_3;
	uint16_t	programmable_key_4;
} key_sensitivity_t;	

typedef enum {
	YEAR_MONTH_DAY	= 0x00,
	DAY_MONTH_YEAR	= 0x04
} date_format_t;

typedef enum {
	TWELVE_HOUR		= 0x00,
	TWENTY_FOUR_HOUR	= 0x02
} time_format_t;

typedef enum {
	STATE_DISABLED	= 0x00,
	STATE_ENABLED	= 0x01
} state_enable_disable_t;

typedef enum {
	STATE_ENABLED_INV	= 0x00,
	STATE_DISABLED_INV	= 0x01
} state_enable_disable_inv_t;

typedef enum {
	DISP_NORMAL	= 0x00,
	DISP_INVERTED	= 0x01
} display_mode_t;	

typedef enum {
	NO_ACTION		= 0xffff,
	SPEED_SIG_GEN_ON	= 0x0000,
	SPEED_SIG_GEN_OFF	= 0x0001,
	ALARM_BUZZER_ON		= 0x0002,
	ALARM_BUZZER_OFF	= 0x0003,
	ALARM_BUZZER_CYCLE_ON_OFF	= 0x0004,
	ALARM_BUZZER_SINGLE_TONE	= 0x0005,
	RELAY_ON		= 0x0006,
	RELAY_OFF		= 0x0007,
	SWITCH_RELAY_2_SEC	= 0x0008,
	SWITCH_RELAY_10_SEC	= 0x0009,
	LOAD_PROFILE_1		= 0x000a,
	LOAD_PROFILE_2		= 0x000b,
	LOAD_PROFILE_3		= 0x000c,
	LOAD_PROFILE_4		= 0x000d,
	USB_KEYBD_POWER_KEY	= 0x000e,
	USB_KEYBD_SLEEP_KEY	= 0x000f,
	USB_KEYBD_WAKEUP_KEY	= 0x0010,
	USB_MEDIA_KEYBD_PLAY_KEY	= 0x0011,
	USB_MEDIA_KEYBD_VOL_UP_KEY	= 0x0012,
	USB_MEDIA_KEYBD_VOL_DOWN_KEY	= 0x0013,
	USB_MEDIA_KEYBD_MUTE_KEY	= 0x0014
} event_action_t;

typedef enum {
	NO_DATA_SOURCE		= 0xffff,
	SENSOR_1		= 0x0000,
	SENSOR_2		= 0x0001,
	SENSOR_3		= 0x0002,
	SENSOR_4		= 0x0003,
	SENSOR_5		= 0x0004,
	SENSOR_6		= 0x0005,
	SENSOR_7		= 0x0006,
	SENSOR_8		= 0x0007,
	SENSOR_9		= 0x0008,
	SENSOR_10		= 0x0009,
	SENSOR_11		= 0x000a,
	SENSOR_12		= 0x000b,
	SENSOR_13		= 0x000c,
	SENSOR_14		= 0x000d,
	SENSOR_15		= 0x000e,
	SENSOR_16		= 0x000f,
	SOFT_SENSOR_1		= 0x0010,
	SOFT_SENSOR_2		= 0x0011,
	SOFT_SENSOR_3		= 0x0012,
	SOFT_SENSOR_4		= 0x0013,
	SOFT_SENSOR_5		= 0x0014,
	SOFT_SENSOR_6		= 0x0015,
	SOFT_SENSOR_7		= 0x0016,
	SOFT_SENSOR_8		= 0x0017,
	VIRT_SENSOR_1		= 0x0018,
	VIRT_SENSOR_2		= 0x0019,
	VIRT_SENSOR_3		= 0x001a,
	VIRT_SENSOR_4		= 0x001b,
	/* Unknown */
	FAN_AMP_1		= 0x002c,
	FAN_AMP_2		= 0x002d,
	FAN_AMP_3		= 0x002e,
	FAN_AMP_4		= 0x002f,
	FAN_AMP_5		= 0x0030,
	FAN_AMP_6		= 0x0031,
	FAN_AMP_7		= 0x0032,
	FAN_AMP_8		= 0x0033,
	FAN_AMP_9		= 0x0034,
	FAN_AMP_10		= 0x0035,
	FAN_AMP_11		= 0x0036,
	FAN_AMP_12		= 0x0037,
	AQUAERO_CPU		= 0x0038,
	/* Unknown */
	FLOW_SENSOR_1		= 0x0080,
	FLOW_SENSOR_2		= 0x0081,
	FLOW_SENSOR_3		= 0x0082,
	FLOW_SENSOR_4		= 0x0083,
	FLOW_SENSOR_5		= 0x0084,
	FLOW_SENSOR_6		= 0x0085,
	FLOW_SENSOR_7		= 0x0086,
	FLOW_SENSOR_8		= 0x0087,
	FLOW_SENSOR_9		= 0x0088,
	FLOW_SENSOR_10		= 0x0089,
	FLOW_SENSOR_11		= 0x008a,
	FLOW_SENSOR_12		= 0x008b,
	FLOW_SENSOR_13		= 0x008c,
	FLOW_SENSOR_14		= 0x008d,
	FAN_RPM_1		= 0x008e,
	FAN_RPM_2		= 0x008f,
	FAN_RPM_3		= 0x0090,
	FAN_RPM_4		= 0x0091,
	FAN_RPM_5		= 0x0092,
	FAN_RPM_6		= 0x0093,
	FAN_RPM_7		= 0x0094,
	FAN_RPM_8		= 0x0095,
	FAN_RPM_9		= 0x0096,
	FAN_RPM_10		= 0x0097,
	FAN_RPM_11		= 0x0098,
	FAN_RPM_12		= 0x0099,
	/* Unknown */
	FAN_VOLTAGE_1		= 0x00a6,
	FAN_VOLTAGE_2		= 0x00a7,
	FAN_VOLTAGE_3		= 0x00a8,
	FAN_VOLTAGE_4		= 0x00a9,
	FAN_VOLTAGE_5		= 0x00aa,
	FAN_VOLTAGE_6		= 0x00ab,
	FAN_VOLTAGE_7		= 0x00ac,
	FAN_VOLTAGE_8		= 0x00ad,
	FAN_VOLTAGE_9		= 0x00ae,
	FAN_VOLTAGE_10		= 0x00af,
	FAN_VOLTAGE_11		= 0x00b0,
	FAN_VOLTAGE_12		= 0x00b1,
	FAN_CURRENT_1		= 0x00b2,
	FAN_CURRENT_2		= 0x00b3,
	FAN_CURRENT_3		= 0x00b4,
	FAN_CURRENT_4		= 0x00b5,
	FAN_CURRENT_5		= 0x00b6,
	FAN_CURRENT_6		= 0x00b7,
	FAN_CURRENT_7		= 0x00b8,
	FAN_CURRENT_8		= 0x00b9,
	FAN_CURRENT_9		= 0x00ba,
	FAN_CURRENT_10		= 0x00bb,
	FAN_CURRENT_11		= 0x00bc,
	FAN_CURRENT_12		= 0x00bd,
	/* Unknown */
	SENS_FILL_LEVEL_1	= 0x00c6,
	SENS_FILL_LEVEL_2	= 0x00c7,
	SENS_FILL_LEVEL_3	= 0x00c8,
	SENS_FILL_LEVEL_4	= 0x00c9,
	POWER_CONSUMPTION_1	= 0x00ca,
	POWER_CONSUMPTION_2	= 0x00cb,
	POWER_CONSUMPTION_3	= 0x00cc,
	POWER_CONSUMPTION_4	= 0x00cd
} sensor_data_source_t;

typedef enum {
	HIGHEST_TEMP		= 0x00,
	LOWEST_TEMP		= 0x01,
	AVERAGE_TEMP		= 0x02,
	DIFFERENCE		= 0x03,
	DIFFERENCE_ABS		= 0x04
} virt_sensor_mode_t;

typedef struct {
	sensor_data_source_t		data_source_1;
	sensor_data_source_t		data_source_2;
	sensor_data_source_t		data_source_3;
	virt_sensor_mode_t		mode;
} virt_sensor_config_t;

typedef struct {
	sensor_data_source_t		flow_sensor_data_source;
	sensor_data_source_t		temp_sensor_1;
	sensor_data_source_t		temp_sensor_2;
} power_consumption_config_t;

typedef struct {
	double		temp;
	uint8_t		percent;
} curve_point_t;

typedef struct {
	uint16_t	data_source;
	double		startup_temp;
	curve_point_t	curve_point[AQ5_NUM_CURVE_POINTS];
} curve_controller_config_t;

typedef struct {
	uint16_t	data_source;
	double		target_val;
	uint16_t	factor_p;
	double		factor_i;
	uint16_t	factor_d;
	double		reset_time;
	double		hysteresis;
} target_value_controller_config_t;

typedef struct {
	uint16_t	data_source;
	double		upper_limit;
	double		lower_limit;
} two_point_controller_config_t;

typedef struct {
	double		temp;
	uint8_t		red_led;
	uint8_t		green_led;
	uint8_t		blue_led;
} led_config_t;

typedef enum {
	PB_OFF		= 0x00,
	PB_VARIANT_1	= 0x01,
	PB_VARIANT_2	= 0x02,
	PB_VARIANT_3	= 0x03,
} rgb_led_pulsating_brightness_t;

typedef struct {
	sensor_data_source_t	data_source;
	rgb_led_pulsating_brightness_t	pulsating_brightness;
	led_config_t	low_temp;
	led_config_t	optimum_temp;
	led_config_t	high_temp;
} rgb_led_controller_config_t;

typedef struct {
	uint8_t		min_power;
	uint8_t		max_power;
	controller_data_source_t	data_source;
	state_enable_disable_t	mode;
} power_output_config_t;

typedef enum {
	CONTROLLED_FROM_DS		= 0x00,
	AQ_RELAY_ON			= 0x01,
	AQ_RELAY_OFF			= 0x02,
	CONTROLLED_FROM_EVENT_SYS	= 0x03
} aquaero_relay_configuration_t;

typedef enum {
	INT_OFF				= 0x00,
	INT_EVERY_2_SEC			= 0x01,
	INT_EVERY_10_SEC		= 0x02,
	INT_EVERY_30_SEC		= 0x03,
	INT_EVERY_MIN			= 0x04,
	INT_EVERY_5_MIN			= 0x05,
	INT_EVERY_10_MIN		= 0x06,
	INT_EVERY_30_MIN		= 0x07,
	INT_EVERY_HOUR			= 0x08
} data_log_interval_t;

typedef struct {
	data_log_interval_t	interval;
	sensor_data_source_t	data_source;
} data_log_config_t;

typedef struct {
	event_action_t	action[3];
} alarm_and_warning_level_t;

typedef enum {
	TEMP_EXCEEDS_LIMIT		= 0x00,
	TEMP_DROPS_BELOW_LIMIT		= 0x01,
	TEMP_ALARM_OFF			= 0x02
} temp_alarm_config_t;

typedef enum {
	NORMAL_OPERATION		= 0x00,
	WARNING				= 0x01,
	ALARM				= 0x02,
	ALARM_WARNING_4			= 0x03,
	ALARM_WARNING_5			= 0x04,
	ALARM_WARNING_6			= 0x05,
	ALARM_WARNING_7			= 0x06,
	ALARM_WARNING_8			= 0x07
} alarm_warning_levels_t;

typedef struct {
	sensor_data_source_t	data_source;
	temp_alarm_config_t	config;
	double			limit_for_warning;
	alarm_warning_levels_t	set_warning_level;
	double			limit_for_alarm;
	alarm_warning_levels_t	set_alarm_level;
} temp_alarm_t;

typedef enum {
	NO_RPM_SIG_AFTER_6S		= 0x00,
	NO_RPM_SIG_AFTER_12S		= 0x01,
	NO_RPM_SIG_AFTER_24S		= 0x02,
	RPM_OFF				= 0x03
} fan_limit_t;

typedef struct {
	fan_limit_t		limit_for_warning;
	alarm_warning_levels_t	set_warning_level;
	fan_limit_t		limit_for_alarm;
	alarm_warning_levels_t	set_alarm_level;
} fan_alarm_t;

typedef enum {
	FLOW_FALLS_BELOW_LIMIT		= 0x00,
	FLOW_EXCEEDS_LIMIT		= 0x01,
	FLOW_OFF			= 0x02
} flow_config_t;

typedef struct {
	sensor_data_source_t	data_source;
	flow_config_t		config;
	double			limit_for_warning;
	alarm_warning_levels_t	set_warning_level;
	double			limit_for_alarm;
	alarm_warning_levels_t	set_alarm_level;
} flow_alarm_t;

typedef struct {
	sensor_data_source_t	data_source;
	state_enable_disable_inv_t	config;
	alarm_warning_levels_t	set_alarm_level;
} pump_alarm_t;

typedef struct {
	sensor_data_source_t		data_source;
	state_enable_disable_inv_t	config;
	uint8_t				limit_for_warning;
	alarm_warning_levels_t		set_warning_level;
	uint8_t				limit_for_alarm;
	alarm_warning_levels_t		set_alarm_level;
} fill_alarm_t;

typedef struct {
	boolean_t	sunday;
	boolean_t	monday;
	boolean_t	tuesday;
	boolean_t	wednesday;
	boolean_t	thursday;
	boolean_t	friday;
	boolean_t	saturday;
} active_days_t;

typedef struct {
	active_days_t	active_days;
	struct tm		switching_time;
	event_action_t	action;
} aq_timer_t;

typedef struct {
	boolean_t	aquaero_control;
	boolean_t	pc_mouse;
	boolean_t	pc_keyboard;
	boolean_t	usb_forwarding_of_unknown;
} infrared_functions_t;

typedef struct {
	state_enable_disable_t	config;
	event_action_t		action;
	uint16_t		refresh_rate;
	uint16_t		learned_ir_signal[3];
} trained_ir_commands_t;

typedef struct {
	state_enable_disable_t	config;
	event_action_t		action_on;
	event_action_t		action_off;
	uint16_t		refresh_rate;
	uint16_t		learned_ir_signal[3];
} switch_pc_via_ir_t;

typedef struct {
	aquastream_xt_freqmode_t	freqmode;
	uint16_t			frequency;
} aquastream_xt_settings_t;

typedef struct {
	aquastream_xt_settings_t	aquastream_xt[AQ5_NUM_AQUASTREAM_XT];
	disable_keys_t		allow_output_override;
	infrared_functions_t	infrared_functions;
	language_t		infrared_keyboard_layout;
	trained_ir_commands_t	trained_ir_commands[AQ5_NUM_IR_COMMANDS];
	switch_pc_via_ir_t	switch_pc_via_ir;
	aq_timer_t		timer[AQ5_NUM_TIMERS];
	fill_alarm_t		fill_alarm[AQ5_NUM_FILL_ALARMS];
	pump_alarm_t		pump_alarm[AQ5_NUM_PUMP_ALARMS];
	flow_alarm_t		flow_alarm[AQ5_NUM_FLOW_ALARMS];
	fan_alarm_t		fan_alarm[AQ5_NUM_FAN];
	temp_alarm_t		temp_alarm[AQ5_NUM_TEMP_ALARMS];
	uint16_t		suppress_alarm_at_poweron;
	alarm_and_warning_level_t	alarm_and_warning_level[AQ5_NUM_ALARM_AND_WARNING_LVLS];
	data_log_config_t	data_log_config[AQ5_NUM_DATA_LOG];
	power_output_config_t	power_output_1_config;
	power_output_config_t	power_output_2_config;
	aquaero_relay_configuration_t	aquaero_relay_configuration;
	controller_data_source_t	aquaero_relay_data_source;
	uint8_t			aquaero_relay_switch_threshold;
	rgb_led_controller_config_t	rgb_led_controller_config;
	uint8_t			preset_value_controller[AQ5_NUM_PRESET_VAL_CONTROLLERS];
	two_point_controller_config_t	two_point_controller_config[AQ5_NUM_TWO_POINT_CONTROLLERS];
	target_value_controller_config_t	target_value_controller_config[AQ5_NUM_TARGET_VAL_CONTROLLERS];
	curve_controller_config_t	curve_controller_config[AQ5_NUM_CURVE_CONTROLLERS];
	power_consumption_config_t	power_consumption_config[AQ5_NUM_POWER_SENSORS];
	state_enable_disable_t	soft_sensor_state[AQ5_NUM_SOFT_SENSORS];
	double			soft_sensor_fallback_value[AQ5_NUM_SOFT_SENSORS];
	uint16_t		soft_sensor_timeout[AQ5_NUM_SOFT_SENSORS];
	uint16_t		flow_sensor_calibration_value[AQ5_NUM_FLOW];
	double			flow_sensor_lower_limit[AQ5_NUM_FLOW];
	double			flow_sensor_upper_limit[AQ5_NUM_FLOW];
	virt_sensor_config_t	virt_sensor_config[AQ5_NUM_VIRT_SENSORS];
	uint8_t			standby_display_contrast;
	uint8_t			standby_lcd_backlight_brightness;
	uint8_t			standby_key_backlight_brightness;
	uint16_t		standby_timeout_key_and_display_brightness;
	event_action_t		standby_action_at_power_down;
	event_action_t		standby_action_at_power_up;
	time_format_t		time_format;
	date_format_t		date_format;
	state_enable_disable_t	auto_dst;
	int8_t			time_zone;
	uint8_t			display_contrast;
	uint8_t			display_brightness_while_in_use;
	uint8_t			display_brightness_while_idle;
	uint16_t		display_illumination_time;
	illumination_mode_t	display_illumination_mode;
	display_mode_t		display_mode;
	uint16_t		menu_display_duration;
	uint16_t		display_duration_after_page_selection;
	disable_keys_t		disable_keys;
	uint8_t			brightness_while_in_use;
	uint8_t			brightness_while_idle;
	illumination_mode_t	illumination_mode;
	key_tone_t		key_tone;
	key_sensitivity_t	key_sensitivity;
	temp_units_t		temp_units;
	flow_units_t		flow_units;
	pressure_units_t	pressure_units;
	decimal_separator_t	decimal_separator;
	language_t		language;
	info_page_t		info_page[AQ5_NUM_INFO_PAGE];	
	double			temp_offset[AQ5_NUM_TEMP];
	double			vtemp_offset[AQ5_NUM_VIRT_SENSORS];
	double			stemp_offset[AQ5_NUM_SOFT_SENSORS];
	double			otemp_offset[AQ5_NUM_OTHER_SENSORS];
	double			fan_vrm_temp_offset[AQ5_NUM_TEMP];
	double			cpu_temp_offset[AQ5_NUM_TEMP];
	uint16_t		fan_min_rpm[AQ5_NUM_FAN];
	uint16_t		fan_max_rpm[AQ5_NUM_FAN];
	uint8_t			fan_max_duty[AQ5_NUM_FAN];
	uint8_t			fan_min_duty[AQ5_NUM_FAN];
	uint8_t			fan_startboost_duty[AQ5_NUM_FAN];
	uint16_t		fan_startboost_duration[AQ5_NUM_FAN];
	uint16_t		fan_pulses_per_revolution[AQ5_NUM_FAN];
	aq5_fan_control_mode_t	fan_control_mode[AQ5_NUM_FAN];
	controller_data_source_t	fan_data_source[AQ5_NUM_FAN];
	uint16_t		fan_programmable_fuse[AQ5_NUM_FAN];
} aq5_settings_t;


/* functions to be called from application */
int	libaquaero5_poll(char *device, aq5_data_t *data_dest, char **err_msg);
int	libaquaero5_getsettings(char *device, aq5_settings_t *settings_dest, char **err_msg);
void	libaquaero5_exit();
char	*libaquaero5_get_string(int id, val_str_opt_t opt);
void 	libaquaero5_init_soft_sensors();
int	libaquaero5_set_soft_sensor(int sensor_id, double value);
int 	libaquaero5_commit_soft_sensors(char *device, char **err_msg);
int	libaquaero5_set_time(char *device, time_t time, char **err_msg);
int	libaquaero5_get_all_names(char *device, int max_attempts, char **err_msg);
char	*libaquaero5_get_name(name_enum_t type, uint8_t index);
char	*libaquaero5_get_default_name_by_ref(char *reference, uint8_t index);
char	*libaquaero5_get_default_name_by_type(name_enum_t type, uint8_t index);
char	*libaquaero5_get_name_ref_by_type(name_enum_t type);
int 	libaquaero5_set_name_by_ref(char *device, char *reference, uint8_t index, char *name, char **err_msg);

/* helpful for debugging */
int 	libaquaero5_dump_data(char *file);
int	libaquaero5_dump_settings(char *file);

#endif /* LIBAQUAERO5_H_ */
