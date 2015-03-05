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

#ifndef AQUAERO5_USER_STRINGS_H_
#define AQUAERO5_USER_STRINGS_H_

typedef struct {
	int	val;
	char	*str;
} val_str_t;

/* Fan regulation mode strings */
val_str_t fan_regulation_mode_strings[] = {
	{ (fan_regulation_mode_t)M_OUTPUT, 	"Output" },
	{ (fan_regulation_mode_t)M_RPM, 	"RPM" },
	{ -1, 					"Unknown" }
};

/* Language setting strings */
val_str_t language_strings[] = {
	{ (language_t)ENGLISH,	"English" },
	{ (language_t)GERMAN,	"German" },
	{ -1,			"Unknown language"}
};

/* Temperature units strings */
val_str_t temp_units_strings[] = {
	{ (temp_units_t)CELSIUS,	"Celsius" },
	{ (temp_units_t)FAHRENHEIT,	"Fahrenheit" },
	{ (temp_units_t)KELVIN,		"Kelvin" },
	{ -1,				"Unknown temperature units"}
};

/* Flow units strings */
val_str_t flow_units_strings[] = {
	{ (flow_units_t)LPH,		"Liters per hour" },
	{ (flow_units_t)LPM,		"Liters per minute" },
	{ (flow_units_t)GPH_US,		"Gallons per hour (US)" },
	{ (flow_units_t)GPM_US,		"Gallons per minute (US)" },
	{ (flow_units_t)GPH_IMP,	"Gallons per hour (Imp)" },
	{ (flow_units_t)GPM_IMP,	"Gallons per minute (Imp)" },
	{ -1,				"Unknown flow units"}
};

/* Pressure units strings */
val_str_t pressure_units_strings[] = {
	{ (pressure_units_t)BAR,	"bar" },
	{ (pressure_units_t)PSI,	"PSI" },
	{ -1,				"Unknown pressure units"}
};

/* Decimal separator strings */
val_str_t decimal_separator_strings[] = {
	{ (decimal_separator_t)POINT,	"point" },
	{ (decimal_separator_t)COMMA,	"comma" },
	{ -1,				"Unknown decimal separator"}
};

/* Fan data source strings */
val_str_t controller_data_source_strings[] = {
	{ (controller_data_source_t)NONE,		"No data source" },
	{ (controller_data_source_t)TARGET_VAL_CONT_1,	"Target value controller 1" },
	{ (controller_data_source_t)TARGET_VAL_CONT_2,	"Target value controller 2" },
	{ (controller_data_source_t)TARGET_VAL_CONT_3,	"Target value controller 3" },
	{ (controller_data_source_t)TARGET_VAL_CONT_4,	"Target value controller 4" },
	{ (controller_data_source_t)TARGET_VAL_CONT_5,	"Target value controller 5" },
	{ (controller_data_source_t)TARGET_VAL_CONT_6,	"Target value controller 6" },
	{ (controller_data_source_t)TARGET_VAL_CONT_7,	"Target value controller 7" },
	{ (controller_data_source_t)TARGET_VAL_CONT_8,	"Target value controller 8" },
	{ (controller_data_source_t)TWO_POINT_CONT_1,	"Two point controller 1" },
	{ (controller_data_source_t)TWO_POINT_CONT_2,	"Two point controller 2" },
	{ (controller_data_source_t)TWO_POINT_CONT_3,	"Two point controller 3" },
	{ (controller_data_source_t)TWO_POINT_CONT_4,	"Two point controller 4" },
	{ (controller_data_source_t)TWO_POINT_CONT_5,	"Two point controller 5" },
	{ (controller_data_source_t)TWO_POINT_CONT_6,	"Two point controller 6" },
	{ (controller_data_source_t)TWO_POINT_CONT_7,	"Two point controller 7" },
	{ (controller_data_source_t)TWO_POINT_CONT_8,	"Two point controller 8" },
	{ (controller_data_source_t)TWO_POINT_CONT_9,	"Two point controller 9" },
	{ (controller_data_source_t)TWO_POINT_CONT_10,	"Two point controller 10" },
	{ (controller_data_source_t)TWO_POINT_CONT_11,	"Two point controller 11" },
	{ (controller_data_source_t)TWO_POINT_CONT_12,	"Two point controller 12" },
	{ (controller_data_source_t)TWO_POINT_CONT_13,	"Two point controller 13" },
	{ (controller_data_source_t)TWO_POINT_CONT_14,	"Two point controller 14" },
	{ (controller_data_source_t)TWO_POINT_CONT_15,	"Two point controller 15" },
	{ (controller_data_source_t)TWO_POINT_CONT_16,	"Two point controller 16" },
	{ (controller_data_source_t)CURVE_CTRLR_1,	"Curve controller 1" },
	{ (controller_data_source_t)CURVE_CTRLR_2,	"Curve controller 2" },
	{ (controller_data_source_t)CURVE_CTRLR_3,	"Curve controller 3" },
	{ (controller_data_source_t)CURVE_CTRLR_4,	"Curve controller 4" },
	{ (controller_data_source_t)RGB_LED_RED,	"RGB LED red" },
	{ (controller_data_source_t)RGB_LED_BLUE,	"RGB LED blue" },
	{ (controller_data_source_t)RGB_LED_GREEN,	"RGB LED green" },
	{ (controller_data_source_t)PRESET_VAL_1,	"Preset value 1" },
	{ (controller_data_source_t)PRESET_VAL_2,	"Preset value 2" },
	{ (controller_data_source_t)PRESET_VAL_3,	"Preset value 3" },
	{ (controller_data_source_t)PRESET_VAL_4,	"Preset value 4" },
	{ (controller_data_source_t)PRESET_VAL_5,	"Preset value 5" },
	{ (controller_data_source_t)PRESET_VAL_6,	"Preset value 6" },
	{ (controller_data_source_t)PRESET_VAL_7,	"Preset value 7" },
	{ (controller_data_source_t)PRESET_VAL_8,	"Preset value 8" },
	{ (controller_data_source_t)PRESET_VAL_9,	"Preset value 9" },
	{ (controller_data_source_t)PRESET_VAL_10,	"Preset value 10" },
	{ (controller_data_source_t)PRESET_VAL_11,	"Preset value 11" },
	{ (controller_data_source_t)PRESET_VAL_12,	"Preset value 12" },
	{ (controller_data_source_t)PRESET_VAL_13,	"Preset value 13" },
	{ (controller_data_source_t)PRESET_VAL_14,	"Preset value 14" },
	{ (controller_data_source_t)PRESET_VAL_15,	"Preset value 15" },
	{ (controller_data_source_t)PRESET_VAL_16,	"Preset value 16" },
	{ (controller_data_source_t)PRESET_VAL_17,	"Preset value 17" },
	{ (controller_data_source_t)PRESET_VAL_18,	"Preset value 18" },
	{ (controller_data_source_t)PRESET_VAL_19,	"Preset value 19" },
	{ (controller_data_source_t)PRESET_VAL_20,	"Preset value 20" },
	{ (controller_data_source_t)PRESET_VAL_21,	"Preset value 21" },
	{ (controller_data_source_t)PRESET_VAL_22,	"Preset value 22" },
	{ (controller_data_source_t)PRESET_VAL_23,	"Preset value 23" },
	{ (controller_data_source_t)PRESET_VAL_24,	"Preset value 24" },
	{ (controller_data_source_t)PRESET_VAL_25,	"Preset value 25" },
	{ (controller_data_source_t)PRESET_VAL_26,	"Preset value 26" },
	{ (controller_data_source_t)PRESET_VAL_27,	"Preset value 27" },
	{ (controller_data_source_t)PRESET_VAL_28,	"Preset value 28" },
	{ (controller_data_source_t)PRESET_VAL_29,	"Preset value 29" },
	{ (controller_data_source_t)PRESET_VAL_30,	"Preset value 30" },
	{ (controller_data_source_t)PRESET_VAL_31,	"Preset value 31" },
	{ (controller_data_source_t)PRESET_VAL_32,	"Preset value 32" },
	{ -1,					"Unknown data source" }
};

/* Info page strings */
val_str_t info_page_strings[] = {
	{ (info_page_type_t)LOG_DATA_1,		"Log data 1" },
	{ (info_page_type_t)LOG_DATA_2,		"Log data 2" },
	{ (info_page_type_t)LOG_DATA_3,		"Log data 3" },
	{ (info_page_type_t)LOG_DATA_4,		"Log data 4" },
	{ (info_page_type_t)LOG_DATA_5,		"Log data 5" },
	{ (info_page_type_t)LOG_DATA_6,		"Log data 6" },
	{ (info_page_type_t)LOG_DATA_7,		"Log data 7" },
	{ (info_page_type_t)LOG_DATA_8,		"Log data 8" },
	{ (info_page_type_t)LOG_DATA_9,		"Log data 9" },
	{ (info_page_type_t)LOG_DATA_10,	"Log data 10" },
	{ (info_page_type_t)LOG_DATA_11,	"Log data 11" },
	{ (info_page_type_t)LOG_DATA_12,	"Log data 12" },
	{ (info_page_type_t)LOG_DATA_13,	"Log data 13" },
	{ (info_page_type_t)LOG_DATA_14,	"Log data 14" },
	{ (info_page_type_t)LOG_DATA_15,	"Log data 15" },
	{ (info_page_type_t)LOG_DATA_16,	"Log data 16" },
	{ (info_page_type_t)SENSOR_1_2,		"Sensor 1+2" },
	{ (info_page_type_t)SENSOR_3_4,		"Sensor 3+4" },
	{ (info_page_type_t)SENSOR_5_6,		"Sensor 5+6" },
	{ (info_page_type_t)SENSOR_7_8,		"Sensor 7+8" },
	{ (info_page_type_t)POWERADJUST_1_2,	"Poweradjust 1+2" },
	{ (info_page_type_t)POWERADJUST_3_4,	"Poweradjust 3+4" },
	{ (info_page_type_t)POWERADJUST_5_6,	"Poweradjust 5+6" },
	{ (info_page_type_t)POWERADJUST_7_8,	"Poweradjust 7+8" },
	{ (info_page_type_t)SOFT_SENSOR_1_2,	"Software sensor 1+2" },
	{ (info_page_type_t)SOFT_SENSOR_3_4,	"Software sensor 3+4" },
	{ (info_page_type_t)SOFT_SENSOR_5_6,	"Software sensor 5+6" },
	{ (info_page_type_t)SOFT_SENSOR_7_8,	"Software sensor 7+8" },
	{ (info_page_type_t)VIRT_SENSOR_1_2,	"Virtual sensor 1+2" },
	{ (info_page_type_t)VIRT_SENSOR_3_4,	"Virtual sensor 3+4" },
	{ (info_page_type_t)MPS_1,		"MPS 1" },
	{ (info_page_type_t)MPS_2,		"MPS 2" },
	{ (info_page_type_t)MPS_3,		"MPS 3" },
	{ (info_page_type_t)MPS_4,		"MPS 4" },
	{ (info_page_type_t)AQUASTREAM_XT,	"Aquastream XT" },
	{ (info_page_type_t)SENSOR_39_40,	"Sensor 39+40" },
	{ (info_page_type_t)SENSOR_1_4,		"Sensor 1-4" },
	{ (info_page_type_t)SENSOR_5_8,		"Sensor 5-8" },
	{ (info_page_type_t)POWERADJUST_1_4,	"Poweradjust 1-4" },
	{ (info_page_type_t)POWERADJUST_5_8,	"Poweradjust 5-8" },
	{ (info_page_type_t)SOFT_SENSOR_1_4,	"Software sensor 1-4" },
	{ (info_page_type_t)SOFT_SENSOR_5_8,	"Software sensor 5-8" },
	{ (info_page_type_t)VIRT_SENSORS,	"Virtual sensors" },
	{ (info_page_type_t)MPS_1_2,		"MPS 1+2" },
	{ (info_page_type_t)MPS_3_4,		"MPS 3+4" },
	{ (info_page_type_t)AQUASTREAM,		"Aquastream" },
	{ (info_page_type_t)SENSOR_41_44,	"Sensor 41-44" },
	{ (info_page_type_t)FAN_AMP_1_4,	"Fan AMP 1-4" },
	{ (info_page_type_t)FAN_AMP_5_8,	"Fan AMP 5-8" },
	{ (info_page_type_t)FAN_AMP_9_12,	"Fan AMP 9-12" },
	{ (info_page_type_t)SENSOR_56_60,	"Sensor 56-60" },
	{ (info_page_type_t)SENSOR_61_64,	"Sensor 61-64" },
	{ (info_page_type_t)FAN_1_4_POWER,	"Fan 1-4 power" },
	{ (info_page_type_t)FAN_5_8_POWER,	"Fan 5-8 power" },
	{ (info_page_type_t)FAN_9_12_POWER,	"Fan 9-12 power" },
	{ (info_page_type_t)FAN_1_4_RPM,	"Fan 1-4 RPM" },
	{ (info_page_type_t)FAN_5_8_RPM,	"Fan 5-8 RPM" },
	{ (info_page_type_t)FAN_9_12_RPM,	"Fan 9-12 RPM" },
	{ (info_page_type_t)FAN_1,		"Fan 1" },
	{ (info_page_type_t)FAN_2,		"Fan 2" },
	{ (info_page_type_t)FAN_3,		"Fan 3" },
	{ (info_page_type_t)FAN_4,		"Fan 4" },
	{ (info_page_type_t)FAN_5,		"Fan 5" },
	{ (info_page_type_t)FAN_6,		"Fan 6" },
	{ (info_page_type_t)FAN_7,		"Fan 7" },
	{ (info_page_type_t)FAN_8,		"Fan 8" },
	{ (info_page_type_t)FAN_9,		"Fan 9" },
	{ (info_page_type_t)FAN_10,		"Fan 10" },
	{ (info_page_type_t)FAN_11,		"Fan 11" },
	{ (info_page_type_t)FAN_12,		"Fan 12" },
	{ (info_page_type_t)FLOW_1,		"Flow 1" },
	{ (info_page_type_t)FLOW_2,		"Flow 2" },
	{ (info_page_type_t)FLOW_3,		"Flow 3" },
	{ (info_page_type_t)FLOW_4,		"Flow 4" },
	{ (info_page_type_t)FLOW_5,		"Flow 5" },
	{ (info_page_type_t)FLOW_6,		"Flow 6" },
	{ (info_page_type_t)FLOW_7,		"Flow 7" },
	{ (info_page_type_t)FLOW_8,		"Flow 8" },
	{ (info_page_type_t)FLOW_9,		"Flow 9" },
	{ (info_page_type_t)FLOW_10,		"Flow 10" },
	{ (info_page_type_t)FLOW_11,		"Flow 11" },
	{ (info_page_type_t)FLOW_12,		"Flow 12" },
	{ (info_page_type_t)FLOW_13,		"Flow 13" },
	{ (info_page_type_t)FLOW_14,		"Flow 14" },
	{ (info_page_type_t)AQUASTREAM_XT_1,	"Aquastream XT 1" },
	{ (info_page_type_t)AQUASTREAM_XT_2,	"Aquastream XT 2" },
	{ (info_page_type_t)MULTISWITCH_1,	"Multiswitch 1" },
	{ (info_page_type_t)MULTISWITCH_2,	"Multiswitch 2" },
	{ (info_page_type_t)FILL_LEVEL_1,	"Fill level 1" },
	{ (info_page_type_t)FILL_LEVEL_2,	"Fill level 2" },
	{ (info_page_type_t)FILL_LEVEL_3,	"Fill level 3" },
	{ (info_page_type_t)FILL_LEVEL_4,	"Fill level 4" },
	{ (info_page_type_t)PWR_CONSUMPT_1,	"Power consumption 1" },
	{ (info_page_type_t)PWR_CONSUMPT_2,	"Power consumption 2" },
	{ (info_page_type_t)PWR_CONSUMPT_3,	"Power consumption 3" },
	{ (info_page_type_t)PWR_CONSUMPT_4,	"Power consumption 4" },
	{ (info_page_type_t)AQUAERO_INFO,	"Aquaero info" },
	{ (info_page_type_t)TIME,		"Time" },
	{ (info_page_type_t)USB_LCD_PAGE,	"USB LCD page" },
	{ (info_page_type_t)RELAY_AND_POWER,	"Relay and power outputs" },
	{ (info_page_type_t)USER_DEF_LOGO,	"User defined logo" },
	{ -1,					"Unknown info page"}
};

/* Info page display mode strings */
val_str_t page_display_mode_strings[] = {
	{ (page_display_mode_t)HIDE_PAGE,	"Hide page" },
	{ (page_display_mode_t)SHOW_PAGE,	"Show page" },
	{ (page_display_mode_t)SHOW_PAGE_PERM,	"Show page permanently" },
	{ -1,					"Unknown display mode" }
};

/* disable keys strings */
val_str_t disable_keys_strings[] = {
	{ (disable_keys_t)ENABLED,	"Enabled" },
	{ (disable_keys_t)DISABLED,	"Disabled" },
	{ -1,				"Unknown disable keys state"}
};

/* Illumination mode strings */
val_str_t illumination_mode_strings[] = {
	{ (illumination_mode_t)AUTO_OFF,	"Automatic off" },
	{ (illumination_mode_t)ALWAYS_ON,	"Always on" },
	{ -1,					"Unknown illumination mode"}
};

/* Key tone strings */
val_str_t key_tone_strings[] = {
	{ (key_tone_t)OFF,	"Off" },
	{ (key_tone_t)QUIET,	"Quiet" },
	{ (key_tone_t)NORMAL,	"Normal" },
	{ (key_tone_t)LOUD,	"Loud" },
	{ -1,			"Unknown key tone mode" }
};

/* Date formt strings */
val_str_t date_format_strings[] = {
	{ (date_format_t)YEAR_MONTH_DAY,	"Year.Month.Day" },
	{ (date_format_t)DAY_MONTH_YEAR,	"Day.Month.Year" },
	{ -1,					"Unknown date format"}
};

/* Time format strings */
val_str_t time_format_strings[] = {
	{ (time_format_t)TWELVE_HOUR,		"12 hour" },
	{ (time_format_t)TWENTY_FOUR_HOUR,	"24 hour" },
	{ -1,					"Unknown time format" }
};

/* State enable/disable strings */
val_str_t state_enable_disable_strings[] = {
	{ (state_enable_disable_t)STATE_DISABLED,	"Disabled" },
	{ (state_enable_disable_t)STATE_ENABLED,	"Enabled" },
	{ -1,						"Unknown" }
};

/* State enable/disable strings (inverted) */
val_str_t state_enable_disable_inv_strings[] = {
	{ (state_enable_disable_inv_t)STATE_DISABLED_INV,	"Disabled" },
	{ (state_enable_disable_inv_t)STATE_ENABLED_INV,	"Enabled" },
	{ -1,							"Unknown" }
};

/* Display mode strings */
val_str_t display_mode_strings[] = {
	{ (display_mode_t)DISP_NORMAL,		"Normal" },
	{ (display_mode_t)DISP_INVERTED,	"Inverted" },
	{ -1,					"Unknown display mode"}
};

/* Standby action strings */
val_str_t event_action_strings[] = {
	{ (event_action_t)NO_ACTION,			"No action" },
	{ (event_action_t)SPEED_SIG_GEN_ON,		"Speed signal generator on" },
	{ (event_action_t)SPEED_SIG_GEN_OFF,		"Speed signal generator off" },
	{ (event_action_t)ALARM_BUZZER_ON,		"Alarm buzzer on" },
	{ (event_action_t)ALARM_BUZZER_OFF,		"Alarm buzzer off" },
	{ (event_action_t)ALARM_BUZZER_CYCLE_ON_OFF,	"Alarm buzzer cycle on-off" },
	{ (event_action_t)ALARM_BUZZER_SINGLE_TONE,	"Alarm buzzer single tone" },
	{ (event_action_t)RELAY_ON,			"Relay on" },
	{ (event_action_t)RELAY_OFF,			"Relay off" },
	{ (event_action_t)SWITCH_RELAY_2_SEC,		"Switch relay for 2 s" },
	{ (event_action_t)SWITCH_RELAY_10_SEC,		"Switch relay for 10 s" },
	{ (event_action_t)LOAD_PROFILE_1,		"Load profile 1" },
	{ (event_action_t)LOAD_PROFILE_2,		"Load profile 2" },
	{ (event_action_t)LOAD_PROFILE_3,		"Load profile 3" },
	{ (event_action_t)LOAD_PROFILE_4,		"Load profile 4" },
	{ (event_action_t)USB_KEYBD_POWER_KEY,		"USB keyboard: power key" },
	{ (event_action_t)USB_KEYBD_SLEEP_KEY,		"USB keyboard: sleep key" },
	{ (event_action_t)USB_KEYBD_WAKEUP_KEY,		"USB keyboard: wakeup key" },
	{ (event_action_t)USB_MEDIA_KEYBD_PLAY_KEY,	"USB media keyboard: play" },
	{ (event_action_t)USB_MEDIA_KEYBD_VOL_UP_KEY,	"USB media keyboard: volume up" },
	{ (event_action_t)USB_MEDIA_KEYBD_VOL_DOWN_KEY,	"USB media keyboard: volume down" },
	{ (event_action_t)USB_MEDIA_KEYBD_MUTE_KEY,	"USB media keyboard: mute" },
	{ -1,						"Unknown standby action" }
};

/* Data source strings */
val_str_t sensor_data_source_strings[] = {
	{ (sensor_data_source_t)NO_DATA_SOURCE,		"No data source selected" },
	{ (sensor_data_source_t)SENSOR_1,		"Sensor 1" },
	{ (sensor_data_source_t)SENSOR_2,		"Sensor 2" },
	{ (sensor_data_source_t)SENSOR_3,		"Sensor 3" },
	{ (sensor_data_source_t)SENSOR_4,		"Sensor 4" },
	{ (sensor_data_source_t)SENSOR_5,		"Sensor 5" },
	{ (sensor_data_source_t)SENSOR_6,		"Sensor 6" },
	{ (sensor_data_source_t)SENSOR_7,		"Sensor 7" },
	{ (sensor_data_source_t)SENSOR_8,		"Sensor 8" },
	{ (sensor_data_source_t)SENSOR_9,		"Sensor 9" },
	{ (sensor_data_source_t)SENSOR_10,		"Sensor 10" },
	{ (sensor_data_source_t)SENSOR_11,		"Sensor 11" },
	{ (sensor_data_source_t)SENSOR_12,		"Sensor 12" },
	{ (sensor_data_source_t)SENSOR_13,		"Sensor 13" },
	{ (sensor_data_source_t)SENSOR_14,		"Sensor 14" },
	{ (sensor_data_source_t)SENSOR_15,		"Sensor 15" },
	{ (sensor_data_source_t)SENSOR_16,		"Sensor 16" },
	{ (sensor_data_source_t)SOFT_SENSOR_1,		"Software sensor 1"},
	{ (sensor_data_source_t)SOFT_SENSOR_2,		"Software sensor 2"},
	{ (sensor_data_source_t)SOFT_SENSOR_3,		"Software sensor 3"},
	{ (sensor_data_source_t)SOFT_SENSOR_4,		"Software sensor 4"},
	{ (sensor_data_source_t)SOFT_SENSOR_5,		"Software sensor 5"},
	{ (sensor_data_source_t)SOFT_SENSOR_6,		"Software sensor 6"},
	{ (sensor_data_source_t)SOFT_SENSOR_7,		"Software sensor 7"},
	{ (sensor_data_source_t)SOFT_SENSOR_8,		"Software sensor 8"},
	{ (sensor_data_source_t)VIRT_SENSOR_1,		"Virtual sensor 1"},
	{ (sensor_data_source_t)VIRT_SENSOR_2,		"Virtual sensor 2"},
	{ (sensor_data_source_t)VIRT_SENSOR_3,		"Virtual sensor 3"},
	{ (sensor_data_source_t)VIRT_SENSOR_4,		"Virtual sensor 4"},
	/* Unknown */
	{ (sensor_data_source_t)FAN_AMP_1,		"Fan amplifier 1" },
	{ (sensor_data_source_t)FAN_AMP_2,		"Fan amplifier 2" },
	{ (sensor_data_source_t)FAN_AMP_3,		"Fan amplifier 3" },
	{ (sensor_data_source_t)FAN_AMP_4,		"Fan amplifier 4" },
	{ (sensor_data_source_t)FAN_AMP_5,		"Fan amplifier 5" },
	{ (sensor_data_source_t)FAN_AMP_6,		"Fan amplifier 6" },
	{ (sensor_data_source_t)FAN_AMP_7,		"Fan amplifier 7" },
	{ (sensor_data_source_t)FAN_AMP_8,		"Fan amplifier 8" },
	{ (sensor_data_source_t)FAN_AMP_9,		"Fan amplifier 9" },
	{ (sensor_data_source_t)FAN_AMP_10,		"Fan amplifier 10" },
	{ (sensor_data_source_t)FAN_AMP_11,		"Fan amplifier 11" },
	{ (sensor_data_source_t)FAN_AMP_12,		"Fan amplifier 12" },
	{ (sensor_data_source_t)AQUAERO_CPU,		"Aquaero CPU" },
	/* Unknown */
	{ (sensor_data_source_t)FLOW_SENSOR_1,		"Flow sensor 1" },
	{ (sensor_data_source_t)FLOW_SENSOR_2,		"Flow sensor 2" },
	{ (sensor_data_source_t)FLOW_SENSOR_3,		"Flow sensor 3" },
	{ (sensor_data_source_t)FLOW_SENSOR_4,		"Flow sensor 4" },
	{ (sensor_data_source_t)FLOW_SENSOR_5,		"Flow sensor 5" },
	{ (sensor_data_source_t)FLOW_SENSOR_6,		"Flow sensor 6" },
	{ (sensor_data_source_t)FLOW_SENSOR_7,		"Flow sensor 7" },
	{ (sensor_data_source_t)FLOW_SENSOR_8,		"Flow sensor 8" },
	{ (sensor_data_source_t)FLOW_SENSOR_9,		"Flow sensor 9" },
	{ (sensor_data_source_t)FLOW_SENSOR_10,		"Flow sensor 10" },
	{ (sensor_data_source_t)FLOW_SENSOR_11,		"Flow sensor 11" },
	{ (sensor_data_source_t)FLOW_SENSOR_12,		"Flow sensor 12" },
	{ (sensor_data_source_t)FLOW_SENSOR_13,		"Flow sensor 13" },
	{ (sensor_data_source_t)FLOW_SENSOR_14,		"Flow sensor 14" },
	{ (sensor_data_source_t)FAN_RPM_1,		"Fan RPM 1" },
	{ (sensor_data_source_t)FAN_RPM_2,		"Fan RPM 2" },
	{ (sensor_data_source_t)FAN_RPM_3,		"Fan RPM 3" },
	{ (sensor_data_source_t)FAN_RPM_4,		"Fan RPM 4" },
	{ (sensor_data_source_t)FAN_RPM_5,		"Fan RPM 5" },
	{ (sensor_data_source_t)FAN_RPM_6,		"Fan RPM 6" },
	{ (sensor_data_source_t)FAN_RPM_7,		"Fan RPM 7" },
	{ (sensor_data_source_t)FAN_RPM_8,		"Fan RPM 8" },
	{ (sensor_data_source_t)FAN_RPM_9,		"Fan RPM 9" },
	{ (sensor_data_source_t)FAN_RPM_10,		"Fan RPM 10" },
	{ (sensor_data_source_t)FAN_RPM_11,		"Fan RPM 11" },
	{ (sensor_data_source_t)FAN_RPM_12,		"Fan RPM 12" },
	/* Unknown */
	{ (sensor_data_source_t)FAN_VOLTAGE_1,		"Fan voltage 1" },
	{ (sensor_data_source_t)FAN_VOLTAGE_2,		"Fan voltage 2" },
	{ (sensor_data_source_t)FAN_VOLTAGE_3,		"Fan voltage 3" },
	{ (sensor_data_source_t)FAN_VOLTAGE_4,		"Fan voltage 4" },
	{ (sensor_data_source_t)FAN_VOLTAGE_5,		"Fan voltage 5" },
	{ (sensor_data_source_t)FAN_VOLTAGE_6,		"Fan voltage 6" },
	{ (sensor_data_source_t)FAN_VOLTAGE_7,		"Fan voltage 7" },
	{ (sensor_data_source_t)FAN_VOLTAGE_8,		"Fan voltage 8" },
	{ (sensor_data_source_t)FAN_VOLTAGE_9,		"Fan voltage 9" },
	{ (sensor_data_source_t)FAN_VOLTAGE_10,		"Fan voltage 10" },
	{ (sensor_data_source_t)FAN_VOLTAGE_11,		"Fan voltage 11" },
	{ (sensor_data_source_t)FAN_VOLTAGE_12,		"Fan voltage 12" },
	{ (sensor_data_source_t)FAN_CURRENT_1,		"Fan current 1" },
	{ (sensor_data_source_t)FAN_CURRENT_2,		"Fan current 2" },
	{ (sensor_data_source_t)FAN_CURRENT_3,		"Fan current 3" },
	{ (sensor_data_source_t)FAN_CURRENT_4,		"Fan current 4" },
	{ (sensor_data_source_t)FAN_CURRENT_5,		"Fan current 5" },
	{ (sensor_data_source_t)FAN_CURRENT_6,		"Fan current 6" },
	{ (sensor_data_source_t)FAN_CURRENT_7,		"Fan current 7" },
	{ (sensor_data_source_t)FAN_CURRENT_8,		"Fan current 8" },
	{ (sensor_data_source_t)FAN_CURRENT_9,		"Fan current 9" },
	{ (sensor_data_source_t)FAN_CURRENT_10,		"Fan current 10" },
	{ (sensor_data_source_t)FAN_CURRENT_11,		"Fan current 11" },
	{ (sensor_data_source_t)FAN_CURRENT_12,		"Fan current 12" },
	/* Unknown */
	{ (sensor_data_source_t)SENS_FILL_LEVEL_1,	"Fill level 1" },
	{ (sensor_data_source_t)SENS_FILL_LEVEL_2,	"Fill level 2" },
	{ (sensor_data_source_t)SENS_FILL_LEVEL_3,	"Fill level 3" },
	{ (sensor_data_source_t)SENS_FILL_LEVEL_4,	"Fill level 4" },
	{ (sensor_data_source_t)POWER_CONSUMPTION_1,	"Power consumption 1" },
	{ (sensor_data_source_t)POWER_CONSUMPTION_2,	"Power consumption 2" },
	{ (sensor_data_source_t)POWER_CONSUMPTION_3,	"Power consumption 3" },
	{ (sensor_data_source_t)POWER_CONSUMPTION_4,	"Power consumption 4" },
	{ -1,						"Unknown data source" }
};

/* Virtual sensor mode strings */
val_str_t virt_sensor_mode_strings[] = {
	{ (virt_sensor_mode_t)HIGHEST_TEMP,	"Highest temperature" },
	{ (virt_sensor_mode_t)LOWEST_TEMP,	"Lowest temperature" },
	{ (virt_sensor_mode_t)AVERAGE_TEMP,	"Average temperature" },
	{ (virt_sensor_mode_t)DIFFERENCE,	"Difference (Sensor 1 - Sensor 2)" },
	{ (virt_sensor_mode_t)DIFFERENCE_ABS,	"Difference absolute (Sen.1 - Sen.2)" },
	{ -1,					"Unknown mode" }
};

/* RGB LED pulsating brightness strings */
val_str_t rgb_led_pulsating_brightness_strings[] = {
	{ (rgb_led_pulsating_brightness_t)PB_OFF,	"Off" },
	{ (rgb_led_pulsating_brightness_t)PB_VARIANT_1,	"Variant 1" },
	{ (rgb_led_pulsating_brightness_t)PB_VARIANT_2,	"Variant 2" },
	{ (rgb_led_pulsating_brightness_t)PB_VARIANT_3,	"Variant 3" },
	{ -1,						"Unknown mode" }
};

/* aquaero relay configuration user strings */
val_str_t aquaero_relay_configuration_strings[] = {
	{ (aquaero_relay_configuration_t)CONTROLLED_FROM_DS,	"Controlled from data source" },
	{ (aquaero_relay_configuration_t)AQ_RELAY_ON,		"Relay on" },	
	{ (aquaero_relay_configuration_t)AQ_RELAY_OFF,		"Relay off" },	
	{ (aquaero_relay_configuration_t)CONTROLLED_FROM_EVENT_SYS,	"Controlled from event system" },
	{ -1,							"Unknown"}	
};

/* data log interval user strings */
val_str_t data_log_interval_strings[] = {
	{ (data_log_interval_t)INT_OFF,			"Off" },
	{ (data_log_interval_t)INT_EVERY_2_SEC, 	"Every 2 seconds" },
	{ (data_log_interval_t)INT_EVERY_10_SEC, 	"Every 10 seconds" },
	{ (data_log_interval_t)INT_EVERY_30_SEC,	"Every 30 seconds" },
	{ (data_log_interval_t)INT_EVERY_MIN, 		"Every minute" },
	{ (data_log_interval_t)INT_EVERY_5_MIN, 	"Every 5 minutes" },
	{ (data_log_interval_t)INT_EVERY_10_MIN,	"Every 10 minutes" },
	{ (data_log_interval_t)INT_EVERY_30_MIN,	"Every 30 minutes" },
	{ (data_log_interval_t)INT_EVERY_HOUR, 		"Every hour" },
	{ -1,						"Unknown"}
};

/* temperature alarm configuration user strings */
val_str_t temp_alarm_config_strings[] = {
	{ (temp_alarm_config_t)TEMP_EXCEEDS_LIMIT,	"Temperature exceeds limit" },
	{ (temp_alarm_config_t)TEMP_DROPS_BELOW_LIMIT,	"Temperature drops below limit" },
	{ (temp_alarm_config_t)TEMP_ALARM_OFF,		"Alarm off" },
	{ -1,						"Unknown" }
};

/* Alarm and warning level strings */
val_str_t alarm_warning_levels_strings[] = {
	{ (alarm_warning_levels_t)NORMAL_OPERATION,	"Normal operation" },
	{ (alarm_warning_levels_t)WARNING, 		"Warning" },
	{ (alarm_warning_levels_t)ALARM, 		"Alarm" },
	{ (alarm_warning_levels_t)ALARM_WARNING_4,	"Alarm/warning 4" },
	{ (alarm_warning_levels_t)ALARM_WARNING_5,	"Alarm/warning 5" },
	{ (alarm_warning_levels_t)ALARM_WARNING_6,	"Alarm/warning 6" },
	{ (alarm_warning_levels_t)ALARM_WARNING_7,	"Alarm/warning 7" },
	{ (alarm_warning_levels_t)ALARM_WARNING_8,	"Alarm/warning 8" },
	{ -1, 						"Unknown" }
};

/* Fan limit strings */
val_str_t fan_limit_strings[] = {
	{ (fan_limit_t)NO_RPM_SIG_AFTER_6S,		"No RPM signal after 6 seconds" },
	{ (fan_limit_t)NO_RPM_SIG_AFTER_12S,		"No RPM signal after 12 seconds" },
	{ (fan_limit_t)NO_RPM_SIG_AFTER_24S,		"No RPM signal after 24 seconds" },
	{ (fan_limit_t)RPM_OFF,				"Off" },
	{ -1,						"Unknown" }
};

/* Flow sensor configuration strings */
val_str_t flow_config_strings[] = {
	{ (flow_config_t)FLOW_FALLS_BELOW_LIMIT,	"Flow falls below limit" },
	{ (flow_config_t)FLOW_EXCEEDS_LIMIT,		"Flow exceeds limit" },
	{ (flow_config_t)FLOW_OFF,			"Off" },
	{ -1,						"Unknown" }
};

/* Boolean strings */
val_str_t boolean_strings[] = {
	{ (boolean_t)FALSE,				"False" }, 
	{ (boolean_t)TRUE,				"True" },
	{ -1,						"Unknown" }
};

/* Aquastream frequency mode strings */
val_str_t aquastream_xt_freqmode_strings[] = {
	{ (aquastream_xt_freqmode_t)AQASTREAM_XT_MODE_AUTO,		"Auto" },
	{ (aquastream_xt_freqmode_t)AQASTREAM_XT_MODE_MANUAL,		"Manual" },
	{ (aquastream_xt_freqmode_t)AQASTREAM_XT_MODE_DEARATION,	"Dearation" },
	{ (aquastream_xt_freqmode_t)AQASTREAM_XT_MODE_OFFLINE,		"Offline" },
	{ -1,								"Unknown" }
};


/* Definitions for device name defaults */
typedef struct {
	int	name_type;
	char	*ref;
	char	*name_string[16];
} default_name_str_t;

default_name_str_t default_name_strings[] = {
	{ NAME_BUTTON,	"buttons", 
		{ 
			"F1",
			"F2",
			"F3",
			"F4",
			"exit",
			"Menu",
			"back",
			"cancel",
			"learn",
			"dummy",
			"dummy",
			"dummy",
			"dummy",
			"dummy",
			"dummy",
			"dummy"
		}
	},
	{ NAME_SENSOR,	"sensors",
		{
			"Sensor 1",
			"Sensor 2",
			"Sensor 3",
			"Sensor 4",
			"Sensor 5",
			"Sensor 6",
			"Sensor 7",
			"Sensor 8"
		}
	},
	{ NAME_POWERADJUST,	"poweradjust",
		{
			"poweradjust 1",
			"poweradjust 2",
			"poweradjust 3",
			"poweradjust 4",
			"poweradjust 5",
			"poweradjust 6",
			"poweradjust 7",
			"poweradjust 8"
		}
	},
	{ NAME_SOFTWARE_SENSOR,	"software sensor",
		{
			"Software sensor 1",
			"Software sensor 2",
			"Software sensor 3",
			"Software sensor 4",
			"Software sensor 5",
			"Software sensor 6",
			"Software sensor 7",
			"Software sensor 8"
		}
	},
	{ NAME_VIRTUAL_SENSOR,	"virtual sensor",
		{
			"Virtual sensor 1",
			"Virtual sensor 2",
			"Virtual sensor 3",
			"Virtual sensor 4"
		}
	},
	{ NAME_MPS,	"MPS",
		{
			"MPS 1 external",
			"MPS 1 internal",
			"MPS 2 external",
			"MPS 2 internal",
			"MPS 3 external",
			"MPS 3 internal",
			"MPS 4 external",
			"MPS 4 internal"
		}
	},
	{ NAME_AQUASTREAM,	"aquastream",
		{
			"aquastream 1",
			"aquastream 2"
		}
	},
	{ NAME_SENSOR_EXT1,	"external sensors 1",
		{
			"Sensor 39",
			"Sensor 40",
			"Sensor 41",
			"Sensor 42",
			"Sensor 43",
			"Sensor 44"
		}
	},
	{ NAME_FAN_AMPLIFIER,	"fan amplifier",
		{
			"Fan amplifier 1",
			"Fan amplifier 2",
			"Fan amplifier 3",
			"Fan amplifier 4",
			"Fan amplifier 5",
			"Fan amplifier 6",
			"Fan amplifier 7",
			"Fan amplifier 8",
			"Fan amplifier 9",
			"Fan amplifier 10",
			"Fan amplifier 11",
			"Fan amplifier 12"
		}
	},
	{ NAME_CPU,	"CPU",
		{
			"aquaero CPU"
		}
	},
	{ NAME_SENSOR_EXT2,	"external sensors 2",
		{
			"Sensor 58",
			"Sensor 59",
			"Sensor 60",
			"Sensor 61",
			"Sensor 62",
			"Sensor 63",
			"Sensor 64"
		}
	},
	{ NAME_FAN,	"fan",
		{
			"Fan 1",
			"Fan 2",
			"Fan 3",
			"Fan 4",
			"Fan 5",
			"Fan 6",
			"Fan 7",
			"Fan 8",
			"Fan 9",
			"Fan 10",
			"Fan 11",
			"Fan 12"
		}
	},
	{ NAME_FLOW,	"flow sensor",
		{
			"Flow 1",
			"Flow 2",
			"Flow 3",
			"Flow 4",
			"Flow 5",
			"Flow 6",
			"Flow 7",
			"Flow 8",
			"Flow 9",
			"Flow 10",
			"Flow 11",
			"Flow 12",
			"Flow 13",
			"Flow 14"
		}
	},
	{ NAME_PROFILE,	"profile",
		{
			"Profile 1",
			"Profile 2",
			"Profile 3",
			"Profile 4"
		}
	},
	{ NAME_AQUASTREAM_XT, "aquastream XT",
		{
			"aquastream xt 1",
			"aquastream xt 2"
		}
	},
	{ NAME_MULTISWITCH, "multiswitch",
		{
			"multiswitch 1",
			"multiswitch 2"
		}
	},
	{ NAME_TARGET_VALUE_CONT, "target value controller",
		{
			"Target value 1",
			"Target value 2",
			"Target value 3",
			"Target value 4",
			"Target value 5",
			"Target value 6",
			"Target value 7",
			"Target value 8"
		}
	},
	{ NAME_CURVE_CONT, "curve controller",
		{
			"Curve controller 1",
			"Curve controller 2",
			"Curve controller 3",
			"Curve controller 4"
		}
	},
	{ NAME_TWO_POINT_CONT, "two point controller",
		{
			"Two point 1",
			"Two point 2",
			"Two point 3",
			"Two point 4",
			"Two point 5",
			"Two point 6",
			"Two point 7",
			"Two point 8",
			"Two point 9",
			"Two point 10",
			"Two point 11",
			"Two point 12",
			"Two point 13",
			"Two point 14",
			"Two point 15",
			"Two point 16"
		}
	},
	{ NAME_PRESET_VALUE_CONT, "preset value controller",
		{
			"Preset value 1",
			"Preset value 2",
			"Preset value 3",
			"Preset value 4",
			"Preset value 5",
			"Preset value 6",
			"Preset value 7",
			"Preset value 8"
		}
	},
	{ NAME_POWER_OUTPUT, "power output",
		{
			"Power output 1",
			"Power output 2"
		}
	},
	{ NAME_ALERT_LEVEL, "alert level",
		{
			"Normal operation",
			"Warning",
			"Alarm",
			"Alarm/Warning 4",
			"Alarm/Warning 5",
			"Alarm/Warning 6",
			"Alarm/Warning 7",
			"Alarm/Warning 8"
		}
	},
	{ NAME_AQ5, "aq5",
		{
			"aquaero 5"
		}
	},
	{ NAME_FILL_LEVEL, "fill level",
		{
			"Fill level 1",
			"Fill level 2",
			"Fill level 3",
			"Fill level 4"
		}
	},
	{ NAME_PRESSURE, "pressure",
		{
			"Pressure 1",
			"Pressure 2",
			"Pressure 3",
			"Pressure 4"
		}
	},
	{ NAME_HUMIDITY, "humidity",
		{
			"Humidity 1",
			"Humidity 2",
			"Humidity 3",
			"Humidity 4"
		}
	},
	{ NAME_WATER_QUALITY, "water quality",
		{
			"Water quality 1",
			"Water quality 2",
			"Water quality 3",
			"Water quality 4"
		}
	},
	{ NAME_MPS_D5, "mps D5",
		{
			"mps D5 - 1",
			"mps D5 - 2",
			"mps D5 - 3",
			"mps D5 - 4"
		}
	}
};

#endif /* AQUAERO5_USER_STRINGS_H_ */
