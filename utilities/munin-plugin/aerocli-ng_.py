#!/usr/bin/python
# -*- coding: utf-8 -*-
#
# Munin Plugin to read values from aerocli (Aquaeronix version)
#
# Copyright 2012 lynix <lynix47@gmail.com>
# Copyright 2013 JinTu <JinTu@praecogito.com>, lynix <lynix47@gmail.com>
# Copyright 2014 barracks510 <barracks510@gmail.com>
# Copyright 2015 barracks510 <barracks510@gmail.com>
#
# This file is part of Aquaeronix.
#
# Aquaeronix is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Aquaeronix is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Aquaeronix. If not, see <http://www.gnu.org/licenses/>.


# Configuration:
#
#  [aerocli-ng_*]
#  user YOURUSER
#  group AQUAEROGROUP
#  env.DEVICE /dev/usb/hiddevX
#  env.AEROCLI /path/to/aerocli
#  env.TEMP1_NAME Your-Caption-Here
#  ...
#  env.FAN1_NAME Your-Caption-Here
#  ...


# Magic markers - optional - used by installation scripts and
# munin-config:
#
#%# family=manual
#%# capabilities=autoconf
import os,subprocess,re,sys
import chardet
from subprocess import call
import sys
import codecs
sys.stdout = codecs.getwriter('iso-8859-1')(sys.stdout)
pattern_lookup_name = "%s_NAME='(.*)'";

pattern_temp_alarm = "TEMP_ALARM(\d+)_DATA_SOURCE='%s'"
pattern_temp_alarm_warn = "TEMP_ALARM%s_LIMIT_FOR_WARNING=(\d{1,2}\.\d{2})"
pattern_temp_alarm_crit = "TEMP_ALARM%s_LIMIT_FOR_ALARM=(\d{1,2}\.\d{2})"

pattern_fan_rpmLine = "%s_RPM=(\d{1,4})";
pattern_fan_loadLine = "%s_DUTY_CYCLE=(\d{1,3}\.\d{2})";

regex_sensorLine = re.compile("^(((VIRT|SYS)_){0,1}TEMP(\d+){0,1}(_CPU\d){0,1})=(\d{1,2}\.\d{2})$");
regex_detect_temp_unit = re.compile("SYS_UNIT_TEMP='.{0,1}(.{1,2})'");
regex_detectActiveFan = re.compile("^((FAN(\d+))_DATA_SRC)='(.*)'$");


if os.getenv("CATEGORY") is not None:
  category = os.getenv("CATEGORY");
else:
  category = "Aquaero5";


if os.getenv("AEROCLI") is not None:
  aerocli = os.getenv("AEROCLI");
else:
  aerocli = "/usr/local/bin/aerocli";

device = os.getenv("DEVICE");


def AeroCli(listAll):
  parameters = [];
  parameters.append(aerocli)
  if device is not None:
    parameters.append("-d");
    parameters.append(device);
  if listAll:
    parameters.append("-a");
  parameters.append("-o");
  parameters.append("export");

  p = subprocess.Popen(parameters, stdout=subprocess.PIPE);
  (output, err) = p.communicate();
  return output.decode('iso-8859-1');

class SensorConfig:
  def __init__(self, sensorId, internalName, output):
    self.sensorId = sensorId
    if os.getenv("%s_NAME"%sensorId) is not None:
      self.name = os.getenv("%s_NAME"%sensorId)
    else:
      match = re.search(pattern_lookup_name%sensorId,output);
      if(match is not None):
        self.name = match.group(1);
      else:
        self.name = sensorId;

    self.warnLevel = None;
    self.critLevel = None;
    if(internalName is not None):
      match = re.search(pattern_temp_alarm%internalName,output);
      if(match is not None):
        alarmNumber = match.group(1);
        match = re.search(pattern_temp_alarm_warn%alarmNumber,output);
        self.warnLevel = match.group(1);
        match = re.search(pattern_temp_alarm_crit%alarmNumber,output);
        self.critLevel = match.group(1);

class FanConfig:
  def __init__(self, fanId, output):
    self.fanId = fanId
    if os.getenv("%s_NAME"%fanId) is not None:
      self.name = os.getenv("%s_NAME"%fanId)
    else:
      match = re.search(pattern_lookup_name%fanId,output);
      if(match is not None):
        self.name = match.group(1);
      else:
        self.name = fanId;



def DecodeTempConfig():
  output=AeroCli(True);

  print "graph_title Aquaero Temperatures";
  print "graph_args --base 1000";

  match = regex_detect_temp_unit.search(output);
  if (match is not None):
    print "graph_vlabel Temp in %s"%match.group(1)
  print "graph_scale yes";
  print "graph_category %s"%(category);



  for line in output.splitlines():
    match = regex_sensorLine.search(line);
    if(match is not None):
      sensorId = match.group(1);
      if match.group(4) is not None:
        if match.group(3) == "VIRT":
          internalName = "Virtual sensor %s"%(match.group(4));
        else:
          internalName = "Sensor %s"%(match.group(4));
      else:
        internalName = None;

      config = SensorConfig(sensorId, internalName, output);
      print "%s.label %s"%(config.sensorId,config.name);
      print "%s.type GAUGE"%(config.sensorId);
      if config.warnLevel is not None:
        print "%s.warning %s"%(config.sensorId,config.warnLevel);
      if config.critLevel is not None:
        print "%s.critical %s"%(config.sensorId,config.critLevel);

def DecodeTempValues():
  for line in AeroCli(False).splitlines():
    match = regex_sensorLine.search(line);
    if(match is not None):
      sensorId = match.group(1);
      value = match.group(6);
      print "%s.value %s"%(sensorId,value);


def DecodeFanRpmConfig():

  print "graph_title Aquaero Fan RPM";
  print "graph_args --base 1000";
  print "graph_vlabel RPM";
  print "graph_scale no";
  print "graph_category %s"%(category);

  output = AeroCli(True);

  for line in output.splitlines():
    match = regex_detectActiveFan.search(line);
    if(match is not None):
      if match.group(4) != "No data source":
        fanId = match.group(2);
        config = FanConfig(fanId, output);
        print "%s.label %s"%(config.fanId,config.name);
        print "%s.type GAUGE"%(config.fanId);

def DecodeFanRpmValues():
  output = AeroCli(True)
  for line in output.splitlines():
    match = regex_detectActiveFan.search(line);
    if(match is not None):
      if match.group(4) != "No data source":
        fanId = match.group(2);
        pattern = pattern_fan_rpmLine%fanId;
        value = re.search(pattern,output).group(1);
        print "%s.value %s"%(fanId,value);

def DecodeFanLoadConfig():
  print "graph_title Aquaero FAN Load";
  print "graph_args --base 1000";
  print "graph_vlabel Load in %";
  print "graph_scale no";
  print "graph_category %s"%(category);

  output = AeroCli(True)

  for line in output.splitlines():
    match = regex_detectActiveFan.search(line);
    if(match is not None):
      if match.group(4) != "No data source":
        fanId = match.group(2);
        config = FanConfig(fanId, output);
        print "%s.label %s"%(config.fanId,config.name);
        print "%s.type GAUGE"%(config.fanId);


def DecodeFanLoadValues():
  output = AeroCli(True)
  for line in output.splitlines():
    match = regex_detectActiveFan.search(line);
    if(match is not None):
      if match.group(4) != "No data source":
        fanId = match.group(2);
        pattern = pattern_fan_loadLine%fanId;
        value = re.search(pattern,output).group(1);
        print "%s.value %s"%(fanId,value);


plugin_name=list(os.path.split(sys.argv[0]))[1];
splittet_name = plugin_name.split("_");
target=splittet_name[1];
if(len(splittet_name)>2):
  subtarget = splittet_name[2];
else:
  subtarget = None;

config = len(sys.argv)>1 and sys.argv[1]=="config";

if (len(sys.argv) > 1 and sys.argv[1] == "autoconf"):
  if os.path.exists(aerocli):
    print "yes";
    sys.exit(0);
  else:
    print "no";
    sys.exit(1);

if target == "temp":
  if config:
    DecodeTempConfig();
  else:
    DecodeTempValues();
elif target == "fan":
  if subtarget is None or subtarget == "rpm":
    if config:
      DecodeFanRpmConfig();
    else:
      DecodeFanRpmValues();
  else:
    if config:
      DecodeFanLoadConfig();
    else:
      DecodeFanLoadValues();
