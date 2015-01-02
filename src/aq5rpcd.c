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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#include <jsonrpc-c.h>
#include "libaquaero5.h"

#define DEFAULT_PORT 9090

aq5_data_t *aquaero_data;
struct jrpc_server rpc_server;
int port = DEFAULT_PORT;


int query_aquaero()
{
	char *err_msg;
	if (libaquaero5_poll(NULL, aquaero_data, &err_msg) < 0) {
		fprintf(stderr, "failed to query device: %s (%s)\n", err_msg,
				strerror(errno));
		return -1;
	}

	return 0;
}

cJSON *exit_server(jrpc_context *ctx, cJSON *params, cJSON *id)
{
	jrpc_server_stop(&rpc_server);

	return cJSON_CreateString("Bye!");
}

cJSON *get_fans(jrpc_context *ctx, cJSON *params, cJSON *id)
{
	if (query_aquaero() < 0)
		return cJSON_CreateNull();

	cJSON *res = cJSON_CreateArray();
	char fan_name[6];

	for (int i=0; i<AQ5_NUM_FAN; i++) {
		sprintf(fan_name, "fan%d", i+1);
		cJSON *fan = cJSON_CreateObject();
		cJSON_AddItemToObject(fan, "name", cJSON_CreateString(fan_name));
		cJSON_AddItemToObject(fan, "rpm",
				cJSON_CreateNumber(aquaero_data->fan_rpm[i]));
		cJSON_AddItemToObject(fan, "current",
				cJSON_CreateNumber(aquaero_data->fan_current[i]));
		cJSON_AddItemToObject(fan, "duty",
				cJSON_CreateNumber(aquaero_data->fan_duty[i]));
		cJSON_AddItemToObject(fan, "voltage",
				cJSON_CreateNumber(aquaero_data->fan_voltage[i]));
		cJSON_AddItemToObject(fan, "vrm_temp",
				cJSON_CreateNumber(aquaero_data->fan_vrm_temp[i]));
		cJSON_AddItemToArray(res, fan);
	}

	return res;
}

cJSON *get_sensors(jrpc_context *ctx, cJSON *params, cJSON *id)
{
	if (query_aquaero() < 0)
		return cJSON_CreateNull();

	cJSON *res = cJSON_CreateArray();
	char sensor_name[8];

	/* real temperature sensors */
	for (int i=0; i<AQ5_NUM_TEMP; i++) {
		sprintf(sensor_name, "temp%d", i+1);
		cJSON *temp = cJSON_CreateObject();
		cJSON_AddItemToObject(temp, "name", cJSON_CreateString(sensor_name));
		cJSON_AddItemToObject(temp, "value",
				cJSON_CreateNumber(aquaero_data->temp[i]));
		cJSON_AddItemToArray(res, temp);
	}

	/* virtual temperature sensors */
	for (int i=0; i<AQ5_NUM_VIRT_SENSORS; i++) {
		sprintf(sensor_name, "vtemp%d", i+1);
		cJSON *temp = cJSON_CreateObject();
		cJSON_AddItemToObject(temp, "name", cJSON_CreateString(sensor_name));
		cJSON_AddItemToObject(temp, "value",
				cJSON_CreateNumber(aquaero_data->vtemp[i]));
		cJSON_AddItemToArray(res, temp);
	}

	/* software temperature sensors */
	for (int i=0; i<AQ5_NUM_SOFT_SENSORS; i++) {
		sprintf(sensor_name, "stemp%d", i+1);
		cJSON *temp = cJSON_CreateObject();
		cJSON_AddItemToObject(temp, "name", cJSON_CreateString(sensor_name));
		cJSON_AddItemToObject(temp, "value",
				cJSON_CreateNumber(aquaero_data->stemp[i]));
		cJSON_AddItemToArray(res, temp);
	}

	/* other temperature sensors */
	for (int i=0; i<AQ5_NUM_OTHER_SENSORS; i++) {
		sprintf(sensor_name, "otemp%d", i+1);
		cJSON *temp = cJSON_CreateObject();
		cJSON_AddItemToObject(temp, "name", cJSON_CreateString(sensor_name));
		cJSON_AddItemToObject(temp, "value",
				cJSON_CreateNumber(aquaero_data->otemp[i]));
		cJSON_AddItemToArray(res, temp);
	}

	/* cpu temperature sensors */
	for (int i=0; i<AQ5_NUM_CPU; i++) {
		sprintf(sensor_name, "cpu%d", i+1);
		cJSON *temp = cJSON_CreateObject();
		cJSON_AddItemToObject(temp, "name", cJSON_CreateString(sensor_name));
		cJSON_AddItemToObject(temp, "value",
				cJSON_CreateNumber(aquaero_data->cpu_temp[i]));
		cJSON_AddItemToArray(res, temp);
	}

	return res;
}

cJSON *get_flow(jrpc_context *ctx, cJSON *params, cJSON *id)
{
	if (query_aquaero() < 0)
		return cJSON_CreateNull();

	cJSON *res = cJSON_CreateArray();
	char sensor_name[6];

	for (int i=0; i<AQ5_NUM_FLOW; i++) {
		sprintf(sensor_name, "flow%d", i+1);
		cJSON *flow = cJSON_CreateObject();
		cJSON_AddItemToObject(flow, "name", cJSON_CreateString(sensor_name));
		cJSON_AddItemToObject(flow, "value",
				cJSON_CreateNumber(aquaero_data->flow[i]));
		cJSON_AddItemToArray(res, flow);
	}

	return res;
}

cJSON *get_device(jrpc_context *ctx, cJSON *params, cJSON *id)
{
	if (query_aquaero() < 0)
		return cJSON_CreateNull();

	cJSON *res = cJSON_CreateObject();

	char time_utc[21];
	strftime(time_utc, 20, "%Y-%m-%d %H:%M:%S", &aquaero_data->time_utc);
	char uptime[51];
	strftime(uptime, 50, "%dd %H:%M:%S", &aquaero_data->uptime);
	char uptime_total[51];
	strftime(uptime_total, 50, "%yy %dd %H:%M:%S", &aquaero_data->total_time);
	char serial[11];
	snprintf(serial, 11, "%d-%d", aquaero_data->serial_major,
			aquaero_data->serial_minor);

	cJSON_AddItemToObject(res, "time_utc",
			cJSON_CreateString(time_utc));
	cJSON_AddItemToObject(res, "serial",
			cJSON_CreateString(serial));
	cJSON_AddItemToObject(res, "firmware",
			cJSON_CreateNumber(aquaero_data->firmware_version));
	cJSON_AddItemToObject(res, "bootloader",
			cJSON_CreateNumber(aquaero_data->bootloader_version));
	cJSON_AddItemToObject(res, "hardware",
			cJSON_CreateNumber(aquaero_data->hardware_version));
	cJSON_AddItemToObject(res, "uptime",
			cJSON_CreateString(uptime));
	cJSON_AddItemToObject(res, "uptime_total",
			cJSON_CreateString(uptime_total));

	return res;
}

void print_help()
{
	puts("Usage: aq5rpcd [OPTIONS]\n\n");
	puts("OPTIONS:\n");
	printf("  -p  PORT    listen on TCP port PORT (default: %d)\n",
			DEFAULT_PORT);
	puts("  -h          display this usage information\n\n");
	printf("This version of aq5rpcd was built on %s %s.\n", __DATE__, __TIME__);
}

void parse_cmdline(int argc, char *argv[])
{
	extern int optind, optopt, opterr;
	int n;
	char c;

	while ((c = getopt(argc, argv, "p:h")) != -1) {
		switch (c) {
			case 'h':
				print_help();
				exit(EXIT_SUCCESS);
				break;
			case 'p':
				n = atoi(optarg);
				if (n < 1 || n > 65535) {
					fprintf(stderr, "invalid port: %d", n);
					exit(EXIT_FAILURE);
				}
				port = n;
				break;
			case '?':
				if (optopt == 'p')
					fprintf(stderr, "option -%c requires an argument\n",
							optopt);
				exit(EXIT_FAILURE);
				break;
			default:
				fputs("invalid arguments. Try -h for help.", stderr);
				exit(EXIT_FAILURE);
		}
	}
}

int main(int argc, char *argv[])
{
	parse_cmdline(argc, argv);
	if ((aquaero_data = (aq5_data_t*)malloc(sizeof(aq5_data_t))) == NULL) {
		fputs("out of memory allocating aquaero data buffer.\n", stderr);
		exit(EXIT_FAILURE);
	}

	jrpc_server_init(&rpc_server, port);

	jrpc_register_procedure(&rpc_server, get_fans, "getFans", NULL);
	jrpc_register_procedure(&rpc_server, get_sensors, "getSensors", NULL);
	jrpc_register_procedure(&rpc_server, get_flow, "getFlow", NULL);
	jrpc_register_procedure(&rpc_server, get_device, "getDeviceInfo", NULL);
	jrpc_register_procedure(&rpc_server, exit_server, "exit", NULL);

	jrpc_server_run(&rpc_server);

	jrpc_server_destroy(&rpc_server);
	exit(EXIT_SUCCESS);
}
