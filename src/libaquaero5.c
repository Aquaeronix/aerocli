/* Copyright 2012 lynix <lynix47@gmail.com>
 * Copyright 2013 JinTu <JinTu@praecogito.com>, lynix <lynix47@gmail.com>
 *
 * This file is part of aerotools-ng.
 *
 * aerotools-ng is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * aerotools-ng is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with aerotools-ng. If not, see <http://www.gnu.org/licenses/>.
 */

#include "libaquaero5.h"
#include "aquaero5-user-strings.h"

/* libs */
#include <stdio.h>

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/ioctl.h>
#include <linux/hiddev.h>
#include <dirent.h>

/* usb communication related constants */
#define AQ5_USB_VID				0x0c70
#define AQ5_USB_PID				0xf001

/* device data and formatting constants */
#include "aquaero5-offsets.h"

/* Fan settings control mode masks */
#define AQ5_SETTINGS_CTRL_MODE_REG_MODE_OUTPUT	0x0000	
#define AQ5_SETTINGS_CTRL_MODE_REG_MODE_RPM	0x0001
#define AQ5_SETTINGS_CTRL_MODE_PROG_FUSE	0x0200
#define AQ5_SETTINGS_CTRL_MODE_STARTBOOST	0x0400
#define AQ5_SETTINGS_CTRL_MODE_HOLD_MIN_POWER	0x0100

/* Timer settings day of week masks */
#define AQ5_SETTINGS_TIMER_DAY_SUNDAY		0x01
#define AQ5_SETTINGS_TIMER_DAY_MONDAY		0x02
#define AQ5_SETTINGS_TIMER_DAY_TUESDAY		0x04
#define AQ5_SETTINGS_TIMER_DAY_WEDNESDAY	0x08
#define AQ5_SETTINGS_TIMER_DAY_THURSDAY		0x10
#define AQ5_SETTINGS_TIMER_DAY_FRIDAY		0x20
#define AQ5_SETTINGS_TIMER_DAY_SATURDAY		0x40

/* IR function setting masks */
#define AQ5_SETTINGS_IR_AQUAERO_CONTROL		0x01
#define AQ5_SETTINGS_IR_PC_MOUSE		0x02
#define AQ5_SETTINGS_IR_PC_KEYBOARD		0x04
#define AQ5_SETTINGS_IR_USB_FWDING_OF_UNKNOWN	0x08

/* device-specific globals */
/* TODO: vectorize to handle more than one device */
unsigned char aq5_buf_data[AQ5_DATA_LEN];
unsigned char aq5_buf_settings[AQ5_SETTINGS_LEN];
int aq5_fd = -1;

/* helper functions */

inline uint16_t aq5_get_int16(unsigned char *buffer, short offset)
{
	return (uint16_t)((buffer[offset] << 8) | buffer[offset + 1]);
}


inline uint32_t aq5_get_int32(unsigned char *buffer, short offset)
{
	return (buffer[offset] << 24) | (buffer[offset + 1] << 16) |
			(buffer[offset + 2] << 8) | buffer[offset + 3];
}


/* get the uptime for the given value in seconds */
inline void aq5_get_uptime(uint32_t timeval, struct tm *uptime)
{
	uptime->tm_sec = timeval;
	uptime->tm_min = uptime->tm_sec / 60;
	uptime->tm_hour = uptime->tm_min / 60;
	uptime->tm_mday = uptime->tm_hour / 24;
	if (uptime->tm_sec > 59)
		uptime->tm_sec -= 60 * uptime->tm_min;
	if (uptime->tm_min > 59)
		uptime->tm_min -= 60 * uptime->tm_hour;
	if (uptime->tm_hour > 23)
		uptime->tm_hour -= 24 * uptime->tm_mday;
}


inline void aq5_get_time(uint32_t timeval, struct tm *time)
{
	time->tm_min = 0;
	time->tm_hour = 0;
	time->tm_mday = 1;
	time->tm_mon = 0;
	time->tm_year = 109;
	time->tm_sec = timeval;
	time->tm_gmtoff = 0;
	mktime(time);
}


char *aq5_strcat(char *str1, char *str2)
{
	char *ret;

	if ((ret = malloc(strlen(str1) + strlen(str2) + 1)) == NULL)
		return NULL;
	strcpy(ret, str1);
	strcpy(ret + strlen(str1), str2);

	return ret;
}

int aq5_open(char *device, char **err_msg)
{
	struct hiddev_devinfo dinfo;

	/* Only open the device if we need to */
	if (fcntl(aq5_fd, F_GETFL) != -1)
		/* The file handle is already defined and open, just continue */
		return 0;

	/* no device given, search */
	if (device == NULL) {
		DIR *dp;
		struct dirent *ep;
		char *full_path = NULL;

		if ((dp = opendir("/dev/usb")) == NULL) {
			*err_msg = "failed to open directory '/dev/usb'";
			return -1;
		}

		while ((ep = readdir(dp)) != NULL) {
			/* search for files beginning with 'hiddev' */
			if (strncmp(ep->d_name, "hiddev", 6) != 0) {
				continue;
			}
			full_path = aq5_strcat("/dev/usb/", ep->d_name);
			if ((aq5_fd = open(full_path, O_RDONLY)) < 0) {
#ifdef DEBUG
				printf("failed to open '%s', skipping\n", full_path);
#endif
				continue;
			}
			ioctl(aq5_fd, HIDIOCGDEVINFO, &dinfo);
			if ((dinfo.vendor != AQ5_USB_VID) || ((dinfo.product & 0xffff) !=
					AQ5_USB_PID)) {
#ifdef DEBUG
				printf("no Aquaero 5 found on '%s'\n", full_path);
#endif
				close(aq5_fd);
				continue;
			} else {
				/* we found the first Aquaero 5 device */
#ifdef DEBUG
				printf("found Aquaero 5 device on '%s'!\n", full_path);
#endif
				break;
			}
		}
		closedir(dp);

		if (fcntl(aq5_fd, F_GETFL) == -1) {
			*err_msg = "failed to find an Aquaero 5 device";
			return -1;
		}

		return 0;
	}


	/* device name given, try using it */
	aq5_fd = open(device, O_RDONLY);
	if (fcntl(aq5_fd, F_GETFL) == -1) {
		/* We tried to open the device but failed */
		*err_msg = "failed to open device";
		return -1;
	}

#ifdef DEBUG
	u_int32_t version;
	ioctl(aq5_fd, HIDIOCGVERSION, &version);
	printf("hiddev driver version is %d.%d.%d\n", version >> 16,
			(version >> 8) & 0xff, version & 0xff);
#endif

	ioctl(aq5_fd, HIDIOCGDEVINFO, &dinfo);
	if ((dinfo.vendor != AQ5_USB_VID) ||
			((dinfo.product & 0xffff) != AQ5_USB_PID)) {
		printf("No Aquaero 5 found on %s. Found vendor:0x%x, product:0x%x(0x%x), version 0x%x instead\n",
				device, dinfo.vendor, dinfo.product & 0xffff, dinfo.product,
				dinfo.version);
		close(aq5_fd);
		return -1;
	}

	if (ioctl(aq5_fd, HIDIOCINITREPORT, 0) < 0) {
		*err_msg = "failed to init HID reports with HIDIOCINITREPORT";
		return -1;
	}

#ifdef DEBUG
	struct hiddev_string_descriptor hStr;
	hStr.index = 2; /* Vendor = 1, Product = 2 */
	hStr.value[0] = 0;
	ioctl(aq5_fd, HIDIOCGSTRING, &hStr);
	printf("Found '%s'\n", hStr.value);
#endif

	return 0;
}


/* Get the specified HID report */
int aq5_get_report(int fd, int report_id, unsigned report_type, unsigned char *report_data)
{
	struct hiddev_report_info rinfo;
	struct hiddev_field_info finfo;
	struct hiddev_usage_ref uref;
	int j;

	rinfo.report_type = report_type;
	rinfo.report_id = report_id;
	rinfo.num_fields = 1;
	if (ioctl(fd, HIDIOCGREPORTINFO, &rinfo) != 0) {
		fprintf(stderr, "failed to fetch input report id %d\n", report_id);
		return -1;
	}
	/* printf("HIDIOCGREPORTINFO: report_id=0x%X (%u fields)\n", rinfo.report_id, rinfo.num_fields); */
	finfo.report_type = rinfo.report_type;
	finfo.report_id   = rinfo.report_id;
	finfo.field_index = 0; /* There is only one field for the Aquaero reports */
	if (ioctl(fd, HIDIOCGFIELDINFO, &finfo) != 0) {
		fprintf(stderr, "failed to fetch field info, report %d\n", report_id);
		return -1;
	}

	/* Put the report ID into the first byte to be consistant with hidraw */
	report_data[0] = report_id;
	/* printf("Max usage is %d\n", finfo.maxusage); */
	if(ioctl(fd, HIDIOCGREPORT, &rinfo) != 0) {
		fprintf(stderr, "Failed to HIDIOCGREPORT for report %d\n", finfo.report_id);
		return -1;
	}
	for (j = 0; j < finfo.maxusage; j++) {
		uref.report_type = finfo.report_type;
		uref.report_id   = finfo.report_id;
		uref.field_index = 0;
		uref.usage_index = j;
		/* fetch the usage code for given indexes */
		ioctl(fd, HIDIOCGUCODE, &uref);
		/* fetch the value from report */
		ioctl(fd, HIDIOCGUSAGE, &uref);
		report_data[j+1] = uref.value;
	}

	return 0;
}


/* Close the file handle and shut down */
void libaquaero5_exit()
{
	close(aq5_fd);
}


/* Get the settings feature report ID 0xB (11) */
int libaquaero5_getsettings(char *device, aq5_settings_t *settings_dest, char **err_msg)
{
	int res;

	/* Allow the device to be disconnected and open only if the fd is undefined */
	if (aq5_open(device, err_msg) != 0) {
		return -1;
	}

	res = aq5_get_report(aq5_fd, 0xB, HID_REPORT_TYPE_FEATURE, aq5_buf_settings);
	if (res != 0) {
		libaquaero5_exit();
		printf("failed to get report!");
		return -1;	
	}

	/* User interface settings */
	settings_dest->disable_keys = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_DISABLE_KEYS_OFFS);
	settings_dest->brightness_while_in_use = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_BRT_WHILE_IN_USE_OFFS) /100;
	settings_dest->brightness_while_idle = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_BRT_WHILE_IDLE_OFFS) /100;
	settings_dest->illumination_mode = aq5_buf_settings[AQ5_SETTINGS_ILLUM_MODE_OFFS];
	settings_dest->key_tone = aq5_buf_settings[AQ5_SETTINGS_KEY_TONE_OFFS];
	settings_dest->key_sensitivity.down_key = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_KEY_DOWN_SENS_OFFS);	
	settings_dest->key_sensitivity.enter_key = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_KEY_ENTER_SENS_OFFS);	
	settings_dest->key_sensitivity.up_key = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_KEY_UP_SENS_OFFS);	
	settings_dest->key_sensitivity.programmable_key_4 = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_KEY_PROG4_SENS_OFFS);	
	settings_dest->key_sensitivity.programmable_key_3 = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_KEY_PROG3_SENS_OFFS);	
	settings_dest->key_sensitivity.programmable_key_2 = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_KEY_PROG2_SENS_OFFS);	
	settings_dest->key_sensitivity.programmable_key_1 = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_KEY_PROG1_SENS_OFFS);	

	settings_dest->language = aq5_buf_settings[AQ5_SETTINGS_LANGUAGE_OFFS];

	settings_dest->time_zone = aq5_buf_settings[AQ5_SETTINGS_TIME_ZONE_OFFS];
	settings_dest->display_contrast = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_DISP_CONTRAST_OFFS) /100;
	settings_dest->display_brightness_while_in_use = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_DISP_BRT_WHILE_IN_USE_OFFS) /100;
	settings_dest->display_brightness_while_idle = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_DISP_BRT_WHILE_IDLE_OFFS) /100;
	settings_dest->display_illumination_time = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_DISP_ILLUM_TIME_OFFS);
	settings_dest->display_illumination_mode = aq5_buf_settings[AQ5_SETTINGS_DISP_ILLUM_MODE_OFFS];
	settings_dest->display_mode = aq5_buf_settings[AQ5_SETTINGS_DISP_MODE_OFFS];
	settings_dest->menu_display_duration = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_MENU_DISP_DURATION_OFFS);
	settings_dest->display_duration_after_page_selection = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_DISP_DURATION_APS_OFFS);

	for (int i=0; i<AQ5_NUM_INFO_PAGE; i++) {
		settings_dest->info_page[i].page_display_mode = aq5_buf_settings[AQ5_SETTINGS_INFO_PAGE_OFFS + i * AQ5_SETTINGS_INFO_PAGE_DIST];
		settings_dest->info_page[i].display_time = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_INFO_PAGE_OFFS + 1 + i * AQ5_SETTINGS_INFO_PAGE_DIST);
		settings_dest->info_page[i].info_page_type = aq5_buf_settings[AQ5_SETTINGS_INFO_PAGE_OFFS + 3 + i * AQ5_SETTINGS_INFO_PAGE_DIST];
	}

	settings_dest->temp_units = aq5_buf_settings[AQ5_SETTINGS_TEMP_UNITS_OFFS];
	settings_dest->flow_units = aq5_buf_settings[AQ5_SETTINGS_FLOW_UNITS_OFFS];
	settings_dest->pressure_units = aq5_buf_settings[AQ5_SETTINGS_PRESSURE_UNITS_OFFS];
	settings_dest->decimal_separator = aq5_buf_settings[AQ5_SETTINGS_DECIMAL_SEPARATOR_OFFS];

	/* System settings */
	int m;
	settings_dest->time_zone = aq5_buf_settings[AQ5_SETTINGS_TIME_ZONE_OFFS];

	m = aq5_buf_settings[AQ5_SETTINGS_DATE_SETTINGS_OFFS];
	if ((m & (date_format_t)DAY_MONTH_YEAR) == (date_format_t)DAY_MONTH_YEAR) {
		settings_dest->date_format = DAY_MONTH_YEAR;
	} else {
		settings_dest->date_format = YEAR_MONTH_DAY;
	}
	
	if ((m & (time_format_t)TWENTY_FOUR_HOUR) == (time_format_t)TWENTY_FOUR_HOUR) {
		settings_dest->time_format = TWENTY_FOUR_HOUR;
	} else {
		settings_dest->time_format = TWELVE_HOUR;
	}

	if ((m & (state_enable_disable_t)STATE_ENABLED) == (state_enable_disable_t)STATE_ENABLED) {
		settings_dest->auto_dst = STATE_ENABLED;
	} else {
		settings_dest->auto_dst = STATE_DISABLED;
	}

	/* System - standby config */
	settings_dest->standby_display_contrast = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_STNDBY_DISP_CONTRAST_OFFS) /100;
	settings_dest->standby_lcd_backlight_brightness = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_STNDBY_LCD_BL_BRT_OFFS) /100;
	settings_dest->standby_key_backlight_brightness = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_STNDBY_KEY_BL_BRT_OFFS) /100;
	settings_dest->standby_timeout_key_and_display_brightness = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_STNDBY_TMO_KAD_BRT_OFFS);
	settings_dest->standby_action_at_power_down = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_STNDBY_ACT_PWR_DOWN_OFFS);
	settings_dest->standby_action_at_power_up = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_STNDBY_ACT_PWR_ON_OFFS);

	/* temperature offset setting */
	for (int i=0; i<AQ5_NUM_TEMP; i++) {
		settings_dest->temp_offset[i] = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_TEMP_OFFS_OFFS + i * AQ5_TEMP_DIST) /100.0;
	}
	
	/* temperature offset setting */
	for (int i=0; i<AQ5_NUM_VIRT_SENSORS; i++) {
		settings_dest->vtemp_offset[i] = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_VTEMP_OFFS_OFFS + i * AQ5_TEMP_DIST) /100.0;
	}
	
	/* temperature offset setting */
	for (int i=0; i<AQ5_NUM_SOFT_SENSORS; i++) {
		settings_dest->stemp_offset[i] = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_STEMP_OFFS_OFFS + i * AQ5_TEMP_DIST) /100.0;
	}

	/* temperature offset setting */
	for (int i=0; i<AQ5_NUM_OTHER_SENSORS; i++) {
		settings_dest->otemp_offset[i] = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_OTEMP_OFFS_OFFS + i * AQ5_TEMP_DIST) /100.0;
	}
	
	/* Fan VRM temperature offset setting */
	for (int i=0; i<AQ5_NUM_FAN; i++) {
		settings_dest->fan_vrm_temp_offset[i] = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_VRM_TEMP_OFFS_OFFS + i * AQ5_TEMP_DIST) /100.0;
	}

	/* CPU temperature offset setting */
	for (int i=0; i<AQ5_NUM_CPU; i++) {
		settings_dest->cpu_temp_offset[i] = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_CPU_TEMP_OFFS_OFFS + i * AQ5_TEMP_DIST) /100.0;
	}

	/* Virtual sensor settings */
	for (int i=0; i<AQ5_NUM_VIRT_SENSORS; i++) {
		settings_dest->virt_sensor_config[i].data_source_1 = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_VIRT_SENSOR_CONFIG_OFFS + i * AQ5_SETTINGS_VIRT_SENSOR_DIST);
		settings_dest->virt_sensor_config[i].data_source_2 = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_VIRT_SENSOR_CONFIG_OFFS + 2 + i * AQ5_SETTINGS_VIRT_SENSOR_DIST);
		settings_dest->virt_sensor_config[i].data_source_3 = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_VIRT_SENSOR_CONFIG_OFFS + 4 + i * AQ5_SETTINGS_VIRT_SENSOR_DIST);
		settings_dest->virt_sensor_config[i].mode = aq5_buf_settings[AQ5_SETTINGS_VIRT_SENSOR_CONFIG_OFFS + 6 + i * AQ5_SETTINGS_VIRT_SENSOR_DIST];
	}

	/* Software sensor settings */
	for (int i=0; i<AQ5_NUM_SOFT_SENSORS; i++) {
		settings_dest->soft_sensor_state[i] = aq5_buf_settings[AQ5_SETTINGS_SOFT_SENSOR_OFFS + i * AQ5_SETTINGS_SOFT_SENSOR_DIST];
		settings_dest->soft_sensor_fallback_value[i] = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_SOFT_SENSOR_OFFS + 1 + i * AQ5_SETTINGS_SOFT_SENSOR_DIST) /100.0;
		settings_dest->soft_sensor_timeout[i] = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_SOFT_SENSOR_OFFS + 3 + i * AQ5_SETTINGS_SOFT_SENSOR_DIST);
	}

	/* Flow sensor settings */
	for (int i=0; i<AQ5_NUM_FLOW; i++) {
		settings_dest->flow_sensor_calibration_value[i] = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FLOW_SENSOR_OFFS + i * AQ5_SETTINGS_FLOW_SENSOR_DIST);
		settings_dest->flow_sensor_lower_limit[i] = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FLOW_SENSOR_OFFS + 2 + i * AQ5_SETTINGS_FLOW_SENSOR_DIST) /10.0;
		settings_dest->flow_sensor_upper_limit[i] = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FLOW_SENSOR_OFFS + 4 + i * AQ5_SETTINGS_FLOW_SENSOR_DIST) /10.0;
	}

	/* Power consumption sensors */
	for (int i=0; i<AQ5_NUM_POWER_SENSORS; i++) {
		settings_dest->power_consumption_config[i].flow_sensor_data_source = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_POWER_SENSOR_OFFS + i * AQ5_SETTINGS_POWER_SENSOR_DIST);
		settings_dest->power_consumption_config[i].temp_sensor_1 = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_POWER_SENSOR_OFFS + 2 + i * AQ5_SETTINGS_POWER_SENSOR_DIST);
		settings_dest->power_consumption_config[i].temp_sensor_2 = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_POWER_SENSOR_OFFS + 4 + i * AQ5_SETTINGS_POWER_SENSOR_DIST);
	};

	/* fan settings */
	int n;
	for (int i=0; i<AQ5_NUM_FAN; i++) {
		settings_dest->fan_min_rpm[i] = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FAN_OFFS + i * AQ5_SETTINGS_FAN_DIST);
		settings_dest->fan_max_rpm[i] = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FAN_OFFS + 2 + i * AQ5_SETTINGS_FAN_DIST);
		settings_dest->fan_min_duty[i] = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FAN_OFFS + 4 + i * AQ5_SETTINGS_FAN_DIST) / 100;
		settings_dest->fan_max_duty[i] = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FAN_OFFS + 6 + i * AQ5_SETTINGS_FAN_DIST) / 100;
		settings_dest->fan_startboost_duty[i] = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FAN_OFFS + 8 + i * AQ5_SETTINGS_FAN_DIST) / 100;
		settings_dest->fan_startboost_duration[i] = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FAN_OFFS + 10 + i * AQ5_SETTINGS_FAN_DIST);
		settings_dest->fan_pulses_per_revolution[i] = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FAN_OFFS + 12 + i * AQ5_SETTINGS_FAN_DIST);
		n = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FAN_OFFS + 14 + i * AQ5_SETTINGS_FAN_DIST);
		settings_dest->fan_control_mode[i].fan_regulation_mode = n & AQ5_SETTINGS_CTRL_MODE_REG_MODE_RPM;
		if ((n & AQ5_SETTINGS_CTRL_MODE_PROG_FUSE) == AQ5_SETTINGS_CTRL_MODE_PROG_FUSE) {
			settings_dest->fan_control_mode[i].use_programmable_fuse = TRUE; 
		} else {
			settings_dest->fan_control_mode[i].use_programmable_fuse = FALSE;
		}
		if ((n & AQ5_SETTINGS_CTRL_MODE_STARTBOOST) == AQ5_SETTINGS_CTRL_MODE_STARTBOOST) {
			settings_dest->fan_control_mode[i].use_startboost = TRUE;
		} else {
			settings_dest->fan_control_mode[i].use_startboost = FALSE;
		}
		if ((n & AQ5_SETTINGS_CTRL_MODE_HOLD_MIN_POWER) == AQ5_SETTINGS_CTRL_MODE_HOLD_MIN_POWER) {
			settings_dest->fan_control_mode[i].hold_minimum_power = TRUE;
		} else {
			settings_dest->fan_control_mode[i].hold_minimum_power = FALSE;
		}
		settings_dest->fan_data_source[i] = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FAN_OFFS + 16 + i * AQ5_SETTINGS_FAN_DIST);
		settings_dest->fan_programmable_fuse[i] = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FAN_OFFS + 18 + i * AQ5_SETTINGS_FAN_DIST);
	}

	/* Power and relay output settings  */
	settings_dest->power_output_1_config.min_power = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_POWER_OUTPUT_OFFS) /100;
	settings_dest->power_output_1_config.max_power = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_POWER_OUTPUT_OFFS + 2) /100;
	settings_dest->power_output_1_config.data_source = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_POWER_OUTPUT_OFFS + 4);
	settings_dest->power_output_1_config.mode = aq5_buf_settings[AQ5_SETTINGS_POWER_OUTPUT_OFFS + 6];

	settings_dest->power_output_2_config.min_power = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_POWER_OUTPUT_OFFS + 7) /100;
	settings_dest->power_output_2_config.max_power = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_POWER_OUTPUT_OFFS + 9) /100;
	settings_dest->power_output_2_config.data_source = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_POWER_OUTPUT_OFFS + 11);
	settings_dest->power_output_2_config.mode = aq5_buf_settings[AQ5_SETTINGS_POWER_OUTPUT_OFFS + 13];

	settings_dest->aquaero_relay_data_source = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_POWER_OUTPUT_OFFS + 14); 	
	settings_dest->aquaero_relay_configuration = aq5_buf_settings[AQ5_SETTINGS_POWER_OUTPUT_OFFS + 16]; 	
	settings_dest->aquaero_relay_switch_threshold = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_POWER_OUTPUT_OFFS + 17) /100; 	

	/* RGB LED controller settings */
	settings_dest->rgb_led_controller_config.data_source = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_RGB_LED_CONTRLR_OFFS);
	settings_dest->rgb_led_controller_config.pulsating_brightness = aq5_buf_settings[AQ5_SETTINGS_RGB_LED_CONTRLR_OFFS + 2];

	settings_dest->rgb_led_controller_config.low_temp.temp = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_RGB_LED_CONTRLR_OFFS + 3) /100.0;
	settings_dest->rgb_led_controller_config.low_temp.red_led = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_RGB_LED_CONTRLR_OFFS + 5) /100;
	settings_dest->rgb_led_controller_config.low_temp.green_led = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_RGB_LED_CONTRLR_OFFS + 7) /100;
	settings_dest->rgb_led_controller_config.low_temp.blue_led = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_RGB_LED_CONTRLR_OFFS + 9) /100;
	
	settings_dest->rgb_led_controller_config.optimum_temp.temp = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_RGB_LED_CONTRLR_OFFS + 11) /100.0;
	settings_dest->rgb_led_controller_config.optimum_temp.red_led = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_RGB_LED_CONTRLR_OFFS + 13) /100;
	settings_dest->rgb_led_controller_config.optimum_temp.green_led = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_RGB_LED_CONTRLR_OFFS + 15) /100;
	settings_dest->rgb_led_controller_config.optimum_temp.blue_led = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_RGB_LED_CONTRLR_OFFS + 17) /100;
	
	settings_dest->rgb_led_controller_config.high_temp.temp = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_RGB_LED_CONTRLR_OFFS + 19) /100.0;
	settings_dest->rgb_led_controller_config.high_temp.red_led = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_RGB_LED_CONTRLR_OFFS + 21) /100;
	settings_dest->rgb_led_controller_config.high_temp.green_led = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_RGB_LED_CONTRLR_OFFS + 23) /100;
	settings_dest->rgb_led_controller_config.high_temp.blue_led = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_RGB_LED_CONTRLR_OFFS + 25) /100;

	/* Two point controller settings */
	for (int i=0; i<AQ5_NUM_TWO_POINT_CONTROLLERS; i++) {
		settings_dest->two_point_controller_config[i].data_source = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_TWO_POINT_CONTRLR_OFFS + i * AQ5_SETTINGS_TWO_POINT_CONTRLR_DIST);
		settings_dest->two_point_controller_config[i].upper_limit = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_TWO_POINT_CONTRLR_OFFS + 2 + i * AQ5_SETTINGS_TWO_POINT_CONTRLR_DIST) /100.0;
		settings_dest->two_point_controller_config[i].lower_limit = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_TWO_POINT_CONTRLR_OFFS + 4 + i * AQ5_SETTINGS_TWO_POINT_CONTRLR_DIST) /100.0;
	}

	/* Preset value controller settings  */
	for (int i=0; i<AQ5_NUM_PRESET_VAL_CONTROLLERS; i++) {
		settings_dest->preset_value_controller[i] = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_PRESET_VAL_CONTRLR_OFFS + i * 2) /100;
	}

	/* Target value controller settings */
	for (int i=0; i<AQ5_NUM_TARGET_VAL_CONTROLLERS; i++) {
		settings_dest->target_value_controller_config[i].data_source = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_TARGET_VAL_CONTRLR_OFFS + i * AQ5_SETTINGS_TARGET_VAL_CONTRLR_DIST);
		settings_dest->target_value_controller_config[i].target_val = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_TARGET_VAL_CONTRLR_OFFS + 2 + i * AQ5_SETTINGS_TARGET_VAL_CONTRLR_DIST) /100.0;
		settings_dest->target_value_controller_config[i].factor_p = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_TARGET_VAL_CONTRLR_OFFS + 4 + i * AQ5_SETTINGS_TARGET_VAL_CONTRLR_DIST);
		settings_dest->target_value_controller_config[i].factor_i = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_TARGET_VAL_CONTRLR_OFFS + 6 + i * AQ5_SETTINGS_TARGET_VAL_CONTRLR_DIST) /10.0;
		settings_dest->target_value_controller_config[i].factor_d = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_TARGET_VAL_CONTRLR_OFFS + 8 + i * AQ5_SETTINGS_TARGET_VAL_CONTRLR_DIST);
		settings_dest->target_value_controller_config[i].reset_time = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_TARGET_VAL_CONTRLR_OFFS + 10 + i * AQ5_SETTINGS_TARGET_VAL_CONTRLR_DIST) /10.0;
		settings_dest->target_value_controller_config[i].hysteresis = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_TARGET_VAL_CONTRLR_OFFS + 12 + i * AQ5_SETTINGS_TARGET_VAL_CONTRLR_DIST) /100.0;
	}

	/* Curve controller settings */
	for (int i=0; i<AQ5_NUM_CURVE_CONTROLLERS; i++) {
		settings_dest->curve_controller_config[i].data_source = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_CURVE_CONTROLLER_OFFS + i * AQ5_SETTINGS_CURVE_CONTROLLER_DIST);
		settings_dest->curve_controller_config[i].startup_temp = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_CURVE_CONTROLLER_OFFS + 2 + i * AQ5_SETTINGS_CURVE_CONTROLLER_DIST) /100.0;
		for (int j=0; j<AQ5_NUM_CURVE_POINTS; j++) {
			settings_dest->curve_controller_config[i].curve_point[j].temp = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_CURVE_CONTROLLER_OFFS + 4 + (i * AQ5_SETTINGS_CURVE_CONTROLLER_DIST) + (j * 2)) /100.0; 
			settings_dest->curve_controller_config[i].curve_point[j].percent = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_CURVE_CONTROLLER_OFFS + 36 + (i * AQ5_SETTINGS_CURVE_CONTROLLER_DIST) + (j * 2)) /100; 
		}
	}

	/* Data log settings */
	for (int i=0; i<AQ5_NUM_DATA_LOG; i++) {
		settings_dest->data_log_config[i].interval = aq5_buf_settings[AQ5_SETTINGS_DATA_LOG_OFFS + i * AQ5_SETTINGS_DATA_LOG_DIST];
		settings_dest->data_log_config[i].data_source = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_DATA_LOG_OFFS + 1 + i * AQ5_SETTINGS_DATA_LOG_DIST);
	}

	/* Alarm and warning settings */
	for (int i=0; i<AQ5_NUM_ALARM_AND_WARNING_LVLS; i++) {
		for (int j=0; j<3; j++) {
			settings_dest->alarm_and_warning_level[i].action[j] = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_ALARM_WARN_OFFS + (j * 2) + i * AQ5_SETTINGS_ALARM_WARN_DIST);
		}
	}
	settings_dest->suppress_alarm_at_poweron = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_SUPP_ALRM_AT_PWRON_OFFS);

	/* Temperature alarm settings */
	for (int i=0; i<AQ5_NUM_TEMP_ALARMS; i++) {
		settings_dest->temp_alarm[i].data_source = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_TEMP_ALARM_OFFS + i * AQ5_SETTINGS_TEMP_ALARM_DIST);
		settings_dest->temp_alarm[i].config = aq5_buf_settings[AQ5_SETTINGS_TEMP_ALARM_OFFS + 2 + i * AQ5_SETTINGS_TEMP_ALARM_DIST];
		settings_dest->temp_alarm[i].limit_for_warning = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_TEMP_ALARM_OFFS + 3 + i * AQ5_SETTINGS_TEMP_ALARM_DIST) /100.0;
		settings_dest->temp_alarm[i].set_warning_level = aq5_buf_settings[AQ5_SETTINGS_TEMP_ALARM_OFFS + 5 + i * AQ5_SETTINGS_TEMP_ALARM_DIST];
		settings_dest->temp_alarm[i].limit_for_alarm = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_TEMP_ALARM_OFFS + 6 + i * AQ5_SETTINGS_TEMP_ALARM_DIST) /100.0;
		settings_dest->temp_alarm[i].set_alarm_level = aq5_buf_settings[AQ5_SETTINGS_TEMP_ALARM_OFFS + 8 + i * AQ5_SETTINGS_TEMP_ALARM_DIST];
	}

	/* Fan alarm settings */
	for (int i=0; i<AQ5_NUM_FAN; i++) {
		settings_dest->fan_alarm[i].limit_for_warning = aq5_buf_settings[AQ5_SETTINGS_FAN_ALARM_OFFS + i * AQ5_SETTINGS_FAN_ALARM_DIST];
		settings_dest->fan_alarm[i].set_warning_level = aq5_buf_settings[AQ5_SETTINGS_FAN_ALARM_OFFS + 1 + i * AQ5_SETTINGS_FAN_ALARM_DIST];
		settings_dest->fan_alarm[i].limit_for_alarm = aq5_buf_settings[AQ5_SETTINGS_FAN_ALARM_OFFS + 2 + i * AQ5_SETTINGS_FAN_ALARM_DIST];
		settings_dest->fan_alarm[i].set_alarm_level = aq5_buf_settings[AQ5_SETTINGS_FAN_ALARM_OFFS + 3 + i * AQ5_SETTINGS_FAN_ALARM_DIST];
	}

	/* Flow alarm settings */
	for (int i=0; i<AQ5_NUM_FLOW_ALARMS; i++) {
		settings_dest->flow_alarm[i].data_source = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FLOW_ALARM_OFFS + i * AQ5_SETTINGS_FLOW_ALARM_DIST);
		settings_dest->flow_alarm[i].config = aq5_buf_settings[AQ5_SETTINGS_FLOW_ALARM_OFFS + 2 + i * AQ5_SETTINGS_FLOW_ALARM_DIST];
		settings_dest->flow_alarm[i].limit_for_warning = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FLOW_ALARM_OFFS + 3 + i * AQ5_SETTINGS_FLOW_ALARM_DIST) /10.0;
		settings_dest->flow_alarm[i].set_warning_level = aq5_buf_settings[AQ5_SETTINGS_FLOW_ALARM_OFFS + 5 + i * AQ5_SETTINGS_FLOW_ALARM_DIST];
		settings_dest->flow_alarm[i].limit_for_alarm = (double)aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FLOW_ALARM_OFFS + 6 + i * AQ5_SETTINGS_FLOW_ALARM_DIST) /10.0;
		settings_dest->flow_alarm[i].set_alarm_level = aq5_buf_settings[AQ5_SETTINGS_FLOW_ALARM_OFFS + 8 + i * AQ5_SETTINGS_FLOW_ALARM_DIST];
	}
	
	/* Pump alarm settings */
	for (int i=0; i<AQ5_NUM_PUMP_ALARMS; i++) {
		settings_dest->pump_alarm[i].data_source = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_PUMP_ALARM_OFFS + i * AQ5_SETTINGS_PUMP_ALARM_DIST);
		settings_dest->pump_alarm[i].config = aq5_buf_settings[AQ5_SETTINGS_PUMP_ALARM_OFFS + 2 + i * AQ5_SETTINGS_PUMP_ALARM_DIST];
		settings_dest->pump_alarm[i].set_alarm_level = aq5_buf_settings[AQ5_SETTINGS_PUMP_ALARM_OFFS + 3 + i * AQ5_SETTINGS_PUMP_ALARM_DIST];
	}

	/* Fill level alarm settings */
	for (int i=0; i<AQ5_NUM_FILL_ALARMS; i++) {
		settings_dest->fill_alarm[i].data_source = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FILL_ALARM_OFFS + i * AQ5_SETTINGS_FILL_ALARM_DIST);
		settings_dest->fill_alarm[i].config = aq5_buf_settings[AQ5_SETTINGS_FILL_ALARM_OFFS + 2 + i * AQ5_SETTINGS_FILL_ALARM_DIST];
		settings_dest->fill_alarm[i].limit_for_warning = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FILL_ALARM_OFFS + 3 + i * AQ5_SETTINGS_FILL_ALARM_DIST) /100;
		settings_dest->fill_alarm[i].set_warning_level = aq5_buf_settings[AQ5_SETTINGS_FILL_ALARM_OFFS + 5 + i * AQ5_SETTINGS_FILL_ALARM_DIST];
		settings_dest->fill_alarm[i].limit_for_alarm = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_FILL_ALARM_OFFS + 6 + i * AQ5_SETTINGS_FILL_ALARM_DIST) /100;
		settings_dest->fill_alarm[i].set_alarm_level = aq5_buf_settings[AQ5_SETTINGS_FILL_ALARM_OFFS + 8 + i * AQ5_SETTINGS_FILL_ALARM_DIST];
	}

	/* Timer settings */
	for (int i=0; i<AQ5_NUM_TIMERS; i++) {
		int j;
		j = aq5_buf_settings[AQ5_SETTINGS_TIMER_OFFS + i * AQ5_SETTINGS_TIMER_DIST];
		if ((j & AQ5_SETTINGS_TIMER_DAY_SUNDAY) == AQ5_SETTINGS_TIMER_DAY_SUNDAY) {
			settings_dest->timer[i].active_days.sunday = TRUE;
		} else {
			settings_dest->timer[i].active_days.sunday = FALSE;
		}
		if ((j & AQ5_SETTINGS_TIMER_DAY_MONDAY) == AQ5_SETTINGS_TIMER_DAY_MONDAY) {
			settings_dest->timer[i].active_days.monday = TRUE;
		} else {
			settings_dest->timer[i].active_days.monday = FALSE;
		}
		if ((j & AQ5_SETTINGS_TIMER_DAY_TUESDAY) == AQ5_SETTINGS_TIMER_DAY_TUESDAY) {
			settings_dest->timer[i].active_days.tuesday = TRUE;
		} else {
			settings_dest->timer[i].active_days.tuesday = FALSE;
		}
		if ((j & AQ5_SETTINGS_TIMER_DAY_WEDNESDAY) == AQ5_SETTINGS_TIMER_DAY_WEDNESDAY) {
			settings_dest->timer[i].active_days.wednesday = TRUE;
		} else {
			settings_dest->timer[i].active_days.wednesday = FALSE;
		}
		if ((j & AQ5_SETTINGS_TIMER_DAY_THURSDAY) == AQ5_SETTINGS_TIMER_DAY_THURSDAY) {
			settings_dest->timer[i].active_days.thursday = TRUE;
		} else {
			settings_dest->timer[i].active_days.thursday = FALSE;
		}
		if ((j & AQ5_SETTINGS_TIMER_DAY_FRIDAY) == AQ5_SETTINGS_TIMER_DAY_FRIDAY) {
			settings_dest->timer[i].active_days.friday = TRUE;
		} else {
			settings_dest->timer[i].active_days.friday = FALSE;
		}
		if ((j & AQ5_SETTINGS_TIMER_DAY_SATURDAY) == AQ5_SETTINGS_TIMER_DAY_SATURDAY) {
			settings_dest->timer[i].active_days.saturday = TRUE;
		} else {
			settings_dest->timer[i].active_days.saturday = FALSE;
		}

		aq5_get_uptime(aq5_get_int32(aq5_buf_settings, AQ5_SETTINGS_TIMER_OFFS + 1 + i * AQ5_SETTINGS_TIMER_DIST), &settings_dest->timer[i].switching_time);
		settings_dest->timer[i].action = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_TIMER_OFFS + 5 + i * AQ5_SETTINGS_TIMER_DIST);
	}

	/* IR function settings */
	int j;
	j = aq5_buf_settings[AQ5_SETTINGS_INFRARED_OFFS];
	if ((j & AQ5_SETTINGS_IR_AQUAERO_CONTROL) == AQ5_SETTINGS_IR_AQUAERO_CONTROL) {
		settings_dest->infrared_functions.aquaero_control = TRUE;
	} else {
		settings_dest->infrared_functions.aquaero_control = FALSE;
	}
	if ((j & AQ5_SETTINGS_IR_PC_MOUSE) == AQ5_SETTINGS_IR_PC_MOUSE) {
		settings_dest->infrared_functions.pc_mouse = TRUE;
	} else {
		settings_dest->infrared_functions.pc_mouse = FALSE;
	}
	if ((j & AQ5_SETTINGS_IR_PC_KEYBOARD) == AQ5_SETTINGS_IR_PC_KEYBOARD) {
		settings_dest->infrared_functions.pc_keyboard = TRUE;
	} else {
		settings_dest->infrared_functions.pc_keyboard = FALSE;
	}
	if ((j & AQ5_SETTINGS_IR_USB_FWDING_OF_UNKNOWN) == AQ5_SETTINGS_IR_USB_FWDING_OF_UNKNOWN) {
		settings_dest->infrared_functions.usb_forwarding_of_unknown = TRUE;
	} else {
		settings_dest->infrared_functions.usb_forwarding_of_unknown = FALSE;
	}
	settings_dest->infrared_keyboard_layout = aq5_buf_settings[AQ5_SETTINGS_INFRARED_OFFS + 1];

	for (int i=0; i<AQ5_NUM_IR_COMMANDS; i++) {
		settings_dest->trained_ir_commands[i].config = aq5_buf_settings[AQ5_SETTINGS_INFRARED_OFFS + 2 + i * AQ5_SETTINGS_INFRARED_DIST];
		settings_dest->trained_ir_commands[i].action = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_INFRARED_OFFS + 4 + i * AQ5_SETTINGS_INFRARED_DIST);
		settings_dest->trained_ir_commands[i].refresh_rate = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_INFRARED_OFFS + 6 + i * AQ5_SETTINGS_INFRARED_DIST);
		for (int r=0; r<3; r++) {
			settings_dest->trained_ir_commands[i].learned_ir_signal[r] = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_INFRARED_OFFS + 8 + (r * 2) + i * AQ5_SETTINGS_INFRARED_DIST);
		}
	}
	settings_dest->switch_pc_via_ir.config = aq5_buf_settings[AQ5_SETTINGS_INFRARED_OFFS + 195];
	settings_dest->switch_pc_via_ir.refresh_rate = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_INFRARED_OFFS + 198);
	for (int r=0; r<3; r++) {
		settings_dest->switch_pc_via_ir.learned_ir_signal[r] = aq5_get_int16(aq5_buf_settings, AQ5_SETTINGS_INFRARED_OFFS + 200 + (r * 2));
	}
	settings_dest->switch_pc_via_ir.action_on = aq5_get_int16(aq5_buf_settings,  AQ5_SETTINGS_INFRARED_OFFS + 206);
	settings_dest->switch_pc_via_ir.action_off = aq5_get_int16(aq5_buf_settings,  AQ5_SETTINGS_INFRARED_OFFS + 208);

	/* Output override setting */
	settings_dest->allow_output_override = aq5_buf_settings[AQ5_SETTINGS_ALLOW_OUTPUT_OVERRIDE_OFFS];

	return 0;
}


/* Get the current sensor data from input report 1 */
int libaquaero5_poll(char *device, aq5_data_t *data_dest, char **err_msg)
{
	int res;

	/* Allow the device to be disconnected and open only if the fd is undefined */
	if (aq5_open(device, err_msg) != 0) {
		return -1;
	}

	res = aq5_get_report(aq5_fd, 0x1, HID_REPORT_TYPE_INPUT, aq5_buf_data);
	if (res != 0) {
		libaquaero5_exit();
		printf("failed to get report!\n");
		return -1;	
	}

	/* current time */
	aq5_get_time(aq5_get_int32(aq5_buf_data, AQ5_CURRENT_TIME_OFFS), &data_dest->time_utc);

	/* device info */
	data_dest->serial_major = aq5_get_int16(aq5_buf_data, AQ5_SERIAL_MAJ_OFFS);
	data_dest->serial_minor = aq5_get_int16(aq5_buf_data, AQ5_SERIAL_MIN_OFFS);
	data_dest->firmware_version = aq5_get_int16(aq5_buf_data, AQ5_FIRMWARE_VER_OFFS);
	data_dest->bootloader_version = aq5_get_int16(aq5_buf_data, AQ5_BOOTLOADER_VER_OFFS);
	data_dest->hardware_version = aq5_get_int16(aq5_buf_data, AQ5_HARDWARE_VER_OFFS);

	/* operating times */
	aq5_get_uptime(aq5_get_int32(aq5_buf_data, AQ5_UPTIME_OFFS), &data_dest->uptime);
	aq5_get_uptime(aq5_get_int32(aq5_buf_data, AQ5_TOTAL_TIME_OFFS), &data_dest->total_time);

	/* temperature sensors */
	int n;
	for (int i=0; i<AQ5_NUM_TEMP; i++) {
		n = aq5_get_int16(aq5_buf_data, AQ5_TEMP_OFFS  + i * AQ5_TEMP_DIST);
		data_dest->temp[i] = n!=AQ5_TEMP_UNDEF ? (double)n/100.0 : AQ5_FLOAT_UNDEF;
	}

	/* virtual temperature sensors */
	for (int i=0; i<AQ5_NUM_VIRT_SENSORS; i++) {
		n = aq5_get_int16(aq5_buf_data, AQ5_VTEMP_OFFS  + i * AQ5_TEMP_DIST);
		data_dest->vtemp[i] = n!=AQ5_TEMP_UNDEF ? (double)n/100.0 : AQ5_FLOAT_UNDEF;
	}

	/* software temperature sensors */
	for (int i=0; i<AQ5_NUM_SOFT_SENSORS; i++) {
		n = aq5_get_int16(aq5_buf_data, AQ5_STEMP_OFFS  + i * AQ5_TEMP_DIST);
		data_dest->stemp[i] = n!=AQ5_TEMP_UNDEF ? (double)n/100.0 : AQ5_FLOAT_UNDEF;
	}

	/* other temperature sensors */
	for (int i=0; i<AQ5_NUM_OTHER_SENSORS; i++) {
		n = aq5_get_int16(aq5_buf_data, AQ5_OTEMP_OFFS  + i * AQ5_TEMP_DIST);
		data_dest->otemp[i] = n!=AQ5_TEMP_UNDEF ? (double)n/100.0 : AQ5_FLOAT_UNDEF;
	}

	/* fans */
	for (int i=0; i<AQ5_NUM_FAN; i++) {
		n = aq5_get_int16(aq5_buf_data, AQ5_FAN_VRM_OFFS + i * AQ5_FAN_VRM_DIST);
		data_dest->fan_vrm_temp[i] = n!=AQ5_FAN_VRM_UNDEF ? (double)n/100.0 : AQ5_FLOAT_UNDEF;
		data_dest->fan_rpm[i] = aq5_get_int16(aq5_buf_data, AQ5_FAN_OFFS + i * AQ5_FAN_DIST);
		data_dest->fan_duty[i] = (double)aq5_get_int16(aq5_buf_data, AQ5_FAN_OFFS + 2 + i * AQ5_FAN_DIST) / 100.0;
		data_dest->fan_voltage[i] = (double)aq5_get_int16(aq5_buf_data, AQ5_FAN_OFFS + 4 + i * AQ5_FAN_DIST) / 100.0;
		data_dest->fan_current[i] = aq5_get_int16(aq5_buf_data, AQ5_FAN_OFFS + 6 + i * AQ5_FAN_DIST);
	}

	/* flow sensors */
	for (int i=0; i<AQ5_NUM_FLOW; i++) {
		data_dest->flow[i] = (double)aq5_get_int16(aq5_buf_data, AQ5_FLOW_OFFS + i * AQ5_FLOW_DIST) / 10.0;
	}

	/* CPU temp */
	for (int i=0; i<AQ5_NUM_CPU; i++) {
		n = (double)aq5_get_int16(aq5_buf_data, AQ5_CPU_TEMP_OFFS + i * AQ5_CPU_TEMP_DIST);
		data_dest->cpu_temp[i] = n!=AQ5_TEMP_UNDEF ? (double)n/100.0 : AQ5_FLOAT_UNDEF;
	}

	/* Liquid level sensors */
	for (int i=0; i<AQ5_NUM_LEVEL; i++) {
		data_dest->level[i] = (double)aq5_get_int16(aq5_buf_data, AQ5_LEVEL_OFFS + i * AQ5_LEVEL_DIST) / 100.0;
	}

	/* firmware compatibility check */
	if ((data_dest->firmware_version < AQ5_FW_MIN) || (data_dest->firmware_version > AQ5_FW_MAX))
		*err_msg = "unsupported firmware version";

	return 0;
}


int	libaquaero5_dump_data(char *file)
{
	FILE *outf = fopen(file, "w");
	if (outf == NULL)
		return -1;

	if (fwrite(aq5_buf_data, 1, AQ5_DATA_LEN, outf) != AQ5_DATA_LEN) {
		fclose(outf);
		return -1;
	}
	fclose(outf);

	return 0;
}


int	libaquaero5_dump_settings(char *file)
{
	FILE *outf = fopen(file, "w");
	if (outf == NULL)
		return -1;

	if (fwrite(aq5_buf_settings, 1, AQ5_SETTINGS_LEN, outf) !=
			AQ5_SETTINGS_LEN) {
		fclose(outf);
		return -1;
	}
	fclose(outf);

	return 0;
}

/* Return the human readable string for the given enum */
char *libaquaero5_get_string(int id, val_str_opt_t opt) 
{
	int i;
	val_str_t *val_str;
	switch (opt) {
		case FAN_REGULATION_MODE:
			val_str = fan_regulation_mode_strings;
			break;
		case BOOLEAN:
			val_str = boolean_strings;
			break;
		case FLOW_CONFIG:
			val_str = flow_config_strings;
			break;
		case FAN_LIMITS:
			val_str = fan_limit_strings;
			break;
		case TEMP_ALARM_CONFIG:
			val_str = temp_alarm_config_strings;
			break;
		case ALARM_WARNING_LEVELS:
			val_str = alarm_warning_levels_strings;
			break;
		case DATA_LOG_INTERVAL:
			val_str = data_log_interval_strings;
			break;
		case AQ_RELAY_CONFIG:
			val_str = aquaero_relay_configuration_strings;
			break;
		case LED_PB_MODE:
			val_str = rgb_led_pulsating_brightness_strings;
			break;
		case SENSOR_DATA_SOURCE:
			val_str = sensor_data_source_strings;
			break;
		case VIRT_SENSOR_MODE:
			val_str = virt_sensor_mode_strings;
			break;
		case EVENT_ACTION:
			val_str = event_action_strings;
			break;
		case DATE_FORMAT:
			val_str = date_format_strings;
			break;
		case TIME_FORMAT:
			val_str = time_format_strings;
			break;
		case STATE_ENABLE_DISABLE:
			val_str = state_enable_disable_strings;
			break;
		case STATE_ENABLE_DISABLE_INV:
			val_str = state_enable_disable_inv_strings;
			break;
		case DISPLAY_MODE:
			val_str = display_mode_strings;
			break;
		case CONTROLLER_DATA_SRC:
			val_str = controller_data_source_strings;
			break;
		case LANGUAGE:
			val_str = language_strings;
			break;
		case TEMP_UNITS:
			val_str = temp_units_strings;
			break;
		case FLOW_UNITS:
			val_str = flow_units_strings;
			break;
		case PRESSURE_UNITS:
			val_str = pressure_units_strings;
			break;
		case DECIMAL_SEPARATOR:
			val_str = decimal_separator_strings;
			break; 
		case INFO_SCREEN:
			val_str = info_page_strings;
			break;
		case PAGE_DISPLAY_MODE:
			val_str = page_display_mode_strings;
			break;
		case DISABLE_KEYS:
			val_str = disable_keys_strings;
			break;
		case ILLUM_MODE:
			val_str = illumination_mode_strings;
			break;
		case KEY_TONE:
		default:
			val_str = key_tone_strings;
	}
	/* We have to search for it */
	for (i=0; val_str[i].val != -1; i++) {
		if (id == val_str[i].val) {
			break;
		}
	}
	return (val_str[i].str);
}
