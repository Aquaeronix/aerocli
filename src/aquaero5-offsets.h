/* Copyright 2012 lynix <lynix47@gmail.com>
 * Copyright 2013 JinTu <JinTu@praecogito.com>, lynix <lynix47@gmail.com>
 * Copyright 2014 barracks510 <barracks510@gmail.com>
 * Copyright 2015 barracks510 <barracks510@gmail.com>
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

/* target firmware to build for */
#ifndef AQ5_FW_TARGET
	#define AQ5_FW_TARGET 1030
#endif

/* report lengths */
#if AQ5_FW_TARGET == 1027
	#define AQ5_TIME_LEN			4
	#define AQ5_SOFT_SENSORS_LEN		16
	#define AQ5_DATA_LEN			659
	#define AQ5_REPORT_NAME_LEN		523
	#define AQ5_CLEAN_NAME_LEN		4096
	#define AQ5_FW_MIN			1027
	#define AQ5_FW_MAX			1027
#elif ((AQ5_FW_TARGET <= 1030) && (AQ5_FW_TARGET >= 1028))
	#define AQ5_TIME_LEN			4
	#define AQ5_SOFT_SENSORS_LEN		16
	#define AQ5_DATA_LEN			661
	#define AQ5_REPORT_NAME_LEN		523
	#define AQ5_CLEAN_NAME_LEN		4096
	#define AQ5_FW_MIN			1028
	#define AQ5_FW_MAX			1030
#endif

/* data offsets for status report */
#if AQ5_FW_TARGET == 1027
	#define AQ5_CURRENT_TIME_OFFS		0x001
	#define AQ5_SERIAL_MAJ_OFFS			0x007
	#define AQ5_SERIAL_MIN_OFFS			0x009
	#define AQ5_FIRMWARE_VER_OFFS		0x00b
	#define AQ5_BOOTLOADER_VER_OFFS		0x00d
	#define AQ5_HARDWARE_VER_OFFS		0x00f
	#define AQ5_UPTIME_OFFS				0x011
	#define AQ5_TOTAL_TIME_OFFS			0x015
	#define AQ5_TEMP_OFFS				0x067
	#define AQ5_VTEMP_OFFS				0x097
	#define AQ5_STEMP_OFFS				0x087
	#define AQ5_OTEMP_OFFS				0x09f
	#define AQ5_FAN_VRM_OFFS			0x0bf
	#define AQ5_CPU_TEMP_OFFS			0x0d7
	#define AQ5_FLOW_OFFS				0x0fb
	#define AQ5_LEVEL_OFFS				0x147
	#define AQ5_FAN_OFFS				0x169
	#define AQ5_AQUASTREAM_XT_OFFS			0x1c9
#elif ((AQ5_FW_TARGET <= 1030) && (AQ5_FW_TARGET >= 1028))
	#define AQ5_CURRENT_TIME_OFFS		0x001
	#define AQ5_SERIAL_MAJ_OFFS			0x007
	#define AQ5_SERIAL_MIN_OFFS			0x009
	#define AQ5_FIRMWARE_VER_OFFS		0x00b
	#define AQ5_BOOTLOADER_VER_OFFS		0x00d
	#define AQ5_HARDWARE_VER_OFFS		0x00f
	#define AQ5_UPTIME_OFFS				0x011
	#define AQ5_TOTAL_TIME_OFFS			0x015
	#define AQ5_TEMP_OFFS				0x069
	#define AQ5_VTEMP_OFFS				0x099
	#define AQ5_STEMP_OFFS				0x089
	#define AQ5_OTEMP_OFFS				0x0a1
	#define AQ5_FAN_VRM_OFFS			0x0c1
	#define AQ5_CPU_TEMP_OFFS			0x0d9
	#define AQ5_FLOW_OFFS				0x0fd
	#define AQ5_LEVEL_OFFS				0x149
	#define AQ5_FAN_OFFS				0x16b
	#define AQ5_AQUASTREAM_XT_OFFS			0x1cb
#endif

#define AQ5_TEMP_DIST			2
#define AQ5_TEMP_UNDEF			0x7fff
#define AQ5_FAN_DIST			8
#define AQ5_FAN_VRM_DIST		2
#define AQ5_FAN_VRM_UNDEF		0x7fff
#define AQ5_FLOW_DIST			2
#define AQ5_CPU_TEMP_DIST		2
#define AQ5_LEVEL_DIST			2
#define AQ5_AQUASTREAM_XT_DIST		8

/* data offsets for HID feature report 0xB */
#define AQ5_SETTINGS_FAN_OFFS					0x20d
#define AQ5_SETTINGS_TEMP_OFFS_OFFS				0x0dc
#define AQ5_SETTINGS_VTEMP_OFFS_OFFS				0x10c
#define AQ5_SETTINGS_STEMP_OFFS_OFFS				0x0fc
#define AQ5_SETTINGS_OTEMP_OFFS_OFFS				0x114
#define AQ5_SETTINGS_VRM_TEMP_OFFS_OFFS			0x134
#define AQ5_SETTINGS_CPU_TEMP_OFFS_OFFS			0x14c
#define AQ5_SETTINGS_LANGUAGE_OFFS				0x01a
#define AQ5_SETTINGS_TEMP_UNITS_OFFS			0x0c5
#define AQ5_SETTINGS_FLOW_UNITS_OFFS			0x0c6
#define AQ5_SETTINGS_PRESSURE_UNITS_OFFS		0x0c7
#define AQ5_SETTINGS_DECIMAL_SEPARATOR_OFFS		0x0c8
#define AQ5_SETTINGS_INFO_PAGE_OFFS				0x031
#define AQ5_SETTINGS_KEY_DOWN_SENS_OFFS			0x009
#define AQ5_SETTINGS_KEY_ENTER_SENS_OFFS		0x00b
#define AQ5_SETTINGS_KEY_UP_SENS_OFFS			0x00d
#define AQ5_SETTINGS_KEY_PROG4_SENS_OFFS		0x011
#define AQ5_SETTINGS_KEY_PROG3_SENS_OFFS		0x013
#define AQ5_SETTINGS_KEY_PROG2_SENS_OFFS		0x015
#define AQ5_SETTINGS_KEY_PROG1_SENS_OFFS		0x017
#define AQ5_SETTINGS_DISABLE_KEYS_OFFS			0x00f
#define AQ5_SETTINGS_BRT_WHILE_IN_USE_OFFS		0x027
#define AQ5_SETTINGS_BRT_WHILE_IDLE_OFFS		0x029
#define AQ5_SETTINGS_ILLUM_MODE_OFFS			0x02b
#define AQ5_SETTINGS_KEY_TONE_OFFS				0x0c9
#define AQ5_SETTINGS_DISP_CONTRAST_OFFS			0x01b
#define AQ5_SETTINGS_DISP_BRT_WHILE_IN_USE_OFFS	0x01f
#define AQ5_SETTINGS_DISP_BRT_WHILE_IDLE_OFFS	0x021
#define AQ5_SETTINGS_DISP_ILLUM_TIME_OFFS		0x023
#define AQ5_SETTINGS_DISP_ILLUM_MODE_OFFS		0x025
#define AQ5_SETTINGS_DISP_MODE_OFFS				0x026
#define AQ5_SETTINGS_MENU_DISP_DURATION_OFFS	0x02c
#define AQ5_SETTINGS_DISP_DURATION_APS_OFFS		0x0d4
#define AQ5_SETTINGS_TIME_ZONE_OFFS				0x02f
#define AQ5_SETTINGS_DATE_SETTINGS_OFFS			0x030
#define AQ5_SETTINGS_STNDBY_DISP_CONTRAST_OFFS	0x01d
#define AQ5_SETTINGS_STNDBY_LCD_BL_BRT_OFFS		0x0ca
#define AQ5_SETTINGS_STNDBY_KEY_BL_BRT_OFFS		0x0ce
#define AQ5_SETTINGS_STNDBY_TMO_KAD_BRT_OFFS	0x0cc
#define AQ5_SETTINGS_STNDBY_ACT_PWR_DOWN_OFFS	0x0d2
#define AQ5_SETTINGS_STNDBY_ACT_PWR_ON_OFFS		0x0d0
#define AQ5_SETTINGS_VIRT_SENSOR_CONFIG_OFFS	0x15c
#define AQ5_SETTINGS_SOFT_SENSOR_OFFS			0x178
#define AQ5_SETTINGS_FLOW_SENSOR_OFFS			0x1a0
#define AQ5_SETTINGS_POWER_SENSOR_OFFS			0x1f4
#define AQ5_SETTINGS_AQUASTREAM_XT_OFFS			0x2fd
#define AQ5_SETTINGS_CURVE_CONTROLLER_OFFS		0x4f8
#define AQ5_SETTINGS_TARGET_VAL_CONTRLR_OFFS	0x488
#define AQ5_SETTINGS_TWO_POINT_CONTRLR_OFFS		0x3e8
#define AQ5_SETTINGS_PRESET_VAL_CONTRLR_OFFS	0x448
#define AQ5_SETTINGS_RGB_LED_CONTRLR_OFFS		0x608
#define AQ5_SETTINGS_POWER_OUTPUT_OFFS			0x30c
#define AQ5_SETTINGS_DATA_LOG_OFFS				0x623
#define AQ5_SETTINGS_SUPP_ALRM_AT_PWRON_OFFS	0x683
#define AQ5_SETTINGS_ALARM_WARN_OFFS			0x653
#define AQ5_SETTINGS_TEMP_ALARM_OFFS			0x685
#define AQ5_SETTINGS_FAN_ALARM_OFFS				0x715
#define AQ5_SETTINGS_FLOW_ALARM_OFFS			0x745
#define AQ5_SETTINGS_PUMP_ALARM_OFFS			0x769
#define AQ5_SETTINGS_FILL_ALARM_OFFS			0x779
#define AQ5_SETTINGS_TIMER_OFFS					0x7c1
#define AQ5_SETTINGS_INFRARED_OFFS				0x8a1
#define AQ5_SETTINGS_ALLOW_OUTPUT_OVERRIDE_OFFS	0x973
#define AQ5_SETTINGS_FAN_DIST					20

#define AQ5_SETTINGS_LEN		2428
#define AQ5_SETTINGS_INFO_PAGE_DIST				4
#define AQ5_SETTINGS_VIRT_SENSOR_DIST			7
#define AQ5_SETTINGS_SOFT_SENSOR_DIST			5
#define AQ5_SETTINGS_FLOW_SENSOR_DIST			6
#define AQ5_SETTINGS_POWER_SENSOR_DIST			6
#define AQ5_SETTINGS_CURVE_CONTROLLER_DIST		68
#define AQ5_SETTINGS_TARGET_VAL_CONTRLR_DIST	14
#define AQ5_SETTINGS_TWO_POINT_CONTRLR_DIST		6
#define AQ5_SETTINGS_DATA_LOG_DIST				3
#define AQ5_SETTINGS_ALARM_WARN_DIST			6
#define AQ5_SETTINGS_TEMP_ALARM_DIST			9
#define AQ5_SETTINGS_FAN_ALARM_DIST				4
#define AQ5_SETTINGS_FLOW_ALARM_DIST			9
#define AQ5_SETTINGS_PUMP_ALARM_DIST			4
#define AQ5_SETTINGS_FILL_ALARM_DIST			9
#define AQ5_SETTINGS_TIMER_DIST					7
#define AQ5_SETTINGS_INFRARED_DIST				12
#define AQ5_SETTINGS_AQUASTREAM_XT_DIST			3

#define AQ5_NAME_LEN			24

/* Definitions for name reports */
typedef struct {
	uint16_t offset;
	uint16_t value;
} name_report_watermark;

name_report_watermark name_report_watermarks[] = {
	/* 1 
	 * start 0x0000: 01 00 09 c0 00 00 00 02 00
 	 * end 0x0209: DD 83
	 */
	{ 0x0000,	0x0100 },
	{ 0x0002,	0x09c0 },
	{ 0x0004,	0x0000 },
	{ 0x0006,	0x0002 },
	{ 0x0007,	0x0200 },
	{ 0x0209,	0xdd83 },
	/* 2
	 * start 0x020b: 01 00 09 C2 00 00 00 02 00
	 * end 0x0414: DD 84
	 */
	{ 0x020b,	0x0100 },
	{ 0x020d,	0x09c2 },
	{ 0x020f,	0x0000 },
	{ 0x0211,	0x0002 },
	{ 0x0212,	0x0200 },
	{ 0x0414,	0xdd84 },
	/* 3
	 * start 0x0416: 01 00 09 C4 00 00 00 02 00
 	 * end 0x061f: DD 85
 	 */
	{ 0x0416,	0x0100 },
	{ 0x0418,	0x09c4 },
	{ 0x041a,	0x0000 },
	{ 0x041c,	0x0002 },
	{ 0x041d,	0x0200 },
	{ 0x061f,	0xdd85 },
	/* 4
	 * start 0x0621: 01 00 09 C6 00 00 00 02 00
	 * end 0x082a: DD 86
	 */
	{ 0x0621,	0x0100 },
	{ 0x0623,	0x09c6 },
	{ 0x0625,	0x0000 },
	{ 0x0627,	0x0002 },
	{ 0x0628,	0x0200 },
	{ 0x082a,	0xdd86 },
	/* 5
	 * start 0x082c: 01 00 09 C8 00 00 00 02 00
	 * end 0x0a35: DD 87
	 */
	{ 0x082c,	0x0100 },
	{ 0x082e,	0x09c8 },
	{ 0x0830,	0x0000 },
	{ 0x0832,	0x0002 },
	{ 0x0833,	0x0200 },
	{ 0x0a35,	0xdd87 },
	/* 6
  	 * start 0x0a37: 01 00 09 CA 00 00 00 02 00
	 * end 0x0c40: DD 88
	 */
	{ 0x0a37,	0x0100 },
	{ 0x0a39,	0x09ca },
	{ 0x0a3b,	0x0000 },
	{ 0x0a3d,	0x0002 },
	{ 0x0a3e,	0x0200 },
	{ 0x0c40,	0xdd88 },
	/* 7
	 * start 0x0c42: 01 00 09 CC 00 00 00 02 00
	 * end 0x0e4b: DD 89
	 */
	{ 0x0c42,	0x0100 },
	{ 0x0c44,	0x09cc },
	{ 0x0c46,	0x0000 },
	{ 0x0c48,	0x0002 },
	{ 0x0c49,	0x0200 },
	{ 0x0e4b,	0xdd89 },
	/* 8
   	 * start 0x0e4d: 01 00 09 CE 00 00 00 02 00
   	 * end 0x1056 : DD 8A
	 */
	{ 0x0e4d,	0x0100 },
	{ 0x0e4f,	0x09ce },
	{ 0x0e51,	0x0000 },
	{ 0x0e53,	0x0002 },
	{ 0x0e54,	0x0200 },
	{ 0x1056,	0xdd8a }
};

