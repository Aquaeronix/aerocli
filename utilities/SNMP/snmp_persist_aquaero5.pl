#!/usr/bin/perl -w
#
# snmp_persist_aquaero5.pl
#
# Export the Aquaero 5 sensor readings and settings provided ny Aquaeronix to net-snmp via 
# pass_persist for external consumption.
#
# Copyright 2013 JinTu <JinTu@praecogito.com>
# Copyright 2014 barracks510 <barracks510@gmail.com>
# Copyright 2015 barracks510 <barracks510@gmail.com>
#
#
# This file is a support utility of Aquaeronix.
#
# Copyright 2012 lynix <lynix47@gmail.com>
# Copyright 2013 JinTu <JinTu@praecogito.com>, lynix <lynix47@gmail.com>
# Copyright 2014 barracks510 <barracks510@gmail.com>
# Copyright 2015 barracks510 <barracks510@gmail.com>
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
#
####

# Sources:
#   snmp.pl     http://www.docum.org/stef.coene/qos/gui/
#   trafgraf.pl by Sébastien Cramatte <scramatte@zensoluciones.com> October 20006
#
#
####
## Installation instructions
####
#
# Add the following line to snmpd.conf
#
# pass_persist .1.3.6.1.4.1.2021.255.65.67 /usr/local/sbin/snmp_persist_aquaero5.pl
#
#
####
# Revision history
####
#
# v0.03 9/1/2013 JinTu <JinTu@praecogito.com>
# 	Added support for device names.
#
# v0.02 4/13/2013 JinTu <JinTu@praecogito.com>
# 	Adding support for virtual, software and other sensors.
#
# v0.01 1/29/2013 JinTu <JinTu@praecogito.com>
# 	First working version. Only supports sensor readings, not settings.
#
#
####
# Usage notes (this really belongs in a MIB)
####
#
# Sensor readings
#
# General device info
# .1.3.6.1.4.1.2021.255.65.67.1.1.1
#
# Temperature sensors
# .1.3.6.1.4.1.2021.255.65.67.1.1.2
#   Device
#   .1.3.6.1.4.1.2021.255.65.67.1.1.2.0
#   Name
#   .1.3.6.1.4.1.2021.255.65.67.1.1.2.1
#   Temp value
#   .1.3.6.1.4.1.2021.255.65.67.1.1.2.2
#
# Fans
# .1.3.6.1.4.1.2021.255.65.67.1.1.3
#   Device
#   .1.3.6.1.4.1.2021.255.65.67.1.1.3.0
#   Name
#   .1.3.6.1.4.1.2021.255.65.67.1.1.3.1
#   VRM temp
#   .1.3.6.1.4.1.2021.255.65.67.1.1.3.2
#   Current
#   .1.3.6.1.4.1.2021.255.65.67.1.1.3.3
#   RPM
#   .1.3.6.1.4.1.2021.255.65.67.1.1.3.4
#   Duty cycle
#   .1.3.6.1.4.1.2021.255.65.67.1.1.3.5
#   Voltage
#   .1.3.6.1.4.1.2021.255.65.67.1.1.3.6
#
# Flow sensors
# .1.3.6.1.4.1.2021.255.65.67.1.1.4
#   Device
#   .1.3.6.1.4.1.2021.255.65.67.1.1.4.0
#   Name
#   .1.3.6.1.4.1.2021.255.65.67.1.1.4.1
#   Flow value
#   .1.3.6.1.4.1.2021.255.65.67.1.1.4.2
#
# CPU temperatures
# .1.3.6.1.4.1.2021.255.65.67.1.1.5
#   Device
#   .1.3.6.1.4.1.2021.255.65.67.1.1.5.0
#   Name
#   .1.3.6.1.4.1.2021.255.65.67.1.1.5.1
#   CPU temp
#   .1.3.6.1.4.1.2021.255.65.67.1.1.5.2

# Level sensors
# .1.3.6.1.4.1.2021.255.65.67.1.1.6
#   Device
#   .1.3.6.1.4.1.2021.255.65.67.1.1.6.0
#   Name
#   .1.3.6.1.4.1.2021.255.65.67.1.1.6.1
#   Level value
#   .1.3.6.1.4.1.2021.255.65.67.1.1.6.2
#
# Virtual sensors
# .1.3.6.1.4.1.2021.255.65.67.1.1.7
#   Device
#   .1.3.6.1.4.1.2021.255.65.67.1.1.7.0
#   Name
#   .1.3.6.1.4.1.2021.255.65.67.1.1.7.1
#   Virtual sensor value
#   .1.3.6.1.4.1.2021.255.65.67.1.1.7.2
#
# Software sensors
# .1.3.6.1.4.1.2021.255.65.67.1.1.8
#   Device
#   .1.3.6.1.4.1.2021.255.65.67.1.1.8.0
#   Name
#   .1.3.6.1.4.1.2021.255.65.67.1.1.8.1
#   Software sensor value
#   .1.3.6.1.4.1.2021.255.65.67.1.1.8.2
#
# Other sensors
# .1.3.6.1.4.1.2021.255.65.67.1.1.9
#   Device
#   .1.3.6.1.4.1.2021.255.65.67.1.1.9.0
#   Name
#   .1.3.6.1.4.1.2021.255.65.67.1.1.9.1
#   Other sensor value
#   .1.3.6.1.4.1.2021.255.65.67.1.1.9.2

###
#
# Settings
#
# Fan settings
# .1.3.6.1.4.1.2021.255.65.67.1.2.3
#   Minimum RPM
#   .1.3.6.1.4.1.2021.255.65.67.1.2.3.1
#   Maximum RPM
#   .1.3.6.1.4.1.2021.255.65.67.1.2.3.2
#   Minimum duty cycle
#   .1.3.6.1.4.1.2021.255.65.67.1.2.3.3
#   Maximum duty cycle
#   .1.3.6.1.4.1.2021.255.65.67.1.2.3.4
#   Startboost duty cycle
#   .1.3.6.1.4.1.2021.255.65.67.1.2.3.5
#   Startboost duration
#   .1.3.6.1.4.1.2021.255.65.67.1.2.3.6
#   Pulses per revolution
#   .1.3.6.1.4.1.2021.255.65.67.1.2.3.7
#   Programmable fuse
#   .1.3.6.1.4.1.2021.255.65.67.1.2.3.8
#
#


use strict;


#------------------------------------------------------------#
my $aeroclipath = "/usr/local/sbin/";
my $aeroclicmd = $aeroclipath . "aerocli -a -o export";

#my $debug = 1;
my $debug = 0;
my $cache_secs = 60;
my $mibtime = 0;

my ($mib,$oid_in,$oid,$found);

#------------------------------------------------------------#
# figure out what to send back

# Switch on autoflush
$| = 1;

my $baseoid = '.1.3.6.1.4.1.2021.255.65.67';


# Main loop
while (my $cmd = <STDIN>) {
	chomp $cmd;

	if ($cmd eq "PING") {
		print "PONG\n";
	} elsif ($cmd eq "get") {
		$oid_in = <STDIN>;

		$oid = get_oid($oid_in);
		$mib = create_mib(); 
 
 		if (defined($mib->{$oid})) {
			print "$baseoid.$oid\n";
			print $mib->{$oid}[0]."\n";
			print $mib->{$oid}[1]."\n";
		} else {
			print "NONE\n";
		}
	} elsif ($cmd eq "getnext") {
		$oid_in = <STDIN>;

		$oid = get_oid($oid_in);
		$mib = create_mib(); 
		$found = 0;

		my @s = sort { oidcmp($a, $b) } keys %{ $mib };
		for (my $i = 0; $i < @s; $i++) {
			if (oidcmp($oid, $s[$i]) == -1) {
				print "$baseoid.".$s[$i]."\n";
				print $mib->{$s[$i]}[0]."\n";
				print $mib->{$s[$i]}[1]."\n";
				$found = 1;
				last;
     			}
    		}
    
		if (!$found) {
			print "NONE\n";
		}
	} else {
  	# Unknown command
  	}
}

#------------------------------------------------------------#
# get all the sensor readings and settings
sub create_mib {
	my %tmpmib;

	if (time - $mibtime < $cache_secs) {
		# Just return the cached value
    		return $mib;
  	}
	my @aerocliout = `$aeroclicmd`;
 
	foreach my $line (@aerocliout) {
		chomp($line);
	
		# Sensor readings
		if ($line =~ /^TEMP\d+=/) {
			my ($tempnum,$tempval) = $line =~ /^TEMP(\d+)=(-?\d+\.\d+)/i;
			print "Line->$line<-\n" if $debug;
			$tempval = 0 if ($tempval < 0);
			print "Temp $tempnum = $tempval (" . strip_decimal($tempval) . ")\n" if $debug;
			$tmpmib{"1.1.2.0.0.$tempnum"} = [ "string", "Temp$tempnum" ];
			$tmpmib{"1.1.2.2.0.$tempnum"} = [ "gauge", adjust_to_32bit(strip_decimal($tempval)) ];
		} elsif ($line =~ /^TEMP\d+_NAME=/) {
			my ($tempnum,$tempname) = $line =~ /^TEMP(\d+)_NAME='(.*)'$/i;
			print "Line->$line<-\n" if $debug;
			print "Temp $tempnum name = \"$tempname\"\n" if $debug;
			$tmpmib{"1.1.2.1.0.$tempnum"} = [ "string", "$tempname" ];
		} elsif ($line =~ /^FAN\d+_VRM_TEMP=/) {
			my ($fannum,$tempval) = $line =~ /^FAN(\d+)_VRM_TEMP=(-?\d+\.\d+)/i;
			print "Line->$line<-\n" if $debug;
			$tempval = 0 if ($tempval < 0);
			print "Fan $fannum VRM temp = $tempval (" . strip_decimal($tempval) . ")\n" if $debug;
			$tmpmib{"1.1.3.0.0.$fannum"} = [ "string", "Fan$fannum" ];
			$tmpmib{"1.1.3.2.0.$fannum"} = [ "gauge", adjust_to_32bit(strip_decimal($tempval)) ];
		} elsif ($line =~ /^FAN\d+_CURRENT=/) {
			my ($fannum,$currentval) = $line =~ /^FAN(\d+)_CURRENT=(\d+)/i;
			print "Line->$line<-\n" if $debug;
			print "Fan $fannum current = $currentval\n" if $debug;
			$tmpmib{"1.1.3.3.0.$fannum"} = [ "gauge", adjust_to_32bit($currentval) ];
		} elsif ($line =~ /^FAN\d+_RPM=/) {
			my ($fannum,$rpmval) = $line =~ /^FAN(\d+)_RPM=(\d+)/i;
			print "Line->$line<-\n" if $debug;
			print "Fan $fannum RPM = $rpmval\n" if $debug;
			$tmpmib{"1.1.3.4.0.$fannum"} = [ "gauge", adjust_to_32bit($rpmval) ];
		} elsif ($line =~ /^FAN\d+_DUTY_CYCLE=/) {
			my ($fannum,$dutycycleval) = $line =~ /^FAN(\d+)_DUTY_CYCLE=(\d+\.\d+)/i;
			print "Line->$line<-\n" if $debug;
			print "Fan $fannum duty cycle = $dutycycleval (" . strip_decimal($dutycycleval) . ")\n" if $debug;
			$tmpmib{"1.1.3.5.0.$fannum"} = [ "gauge", adjust_to_32bit(strip_decimal($dutycycleval)) ];
		} elsif ($line =~ /^FAN\d+_VOLTAGE=/) {
			my ($fannum,$voltageval) = $line =~ /^FAN(\d+)_VOLTAGE=(\d+\.\d+)/i;
			print "Line->$line<-\n" if $debug;
			print "Fan $fannum duty cycle = $voltageval (" . strip_decimal($voltageval) . ")\n" if $debug;
			$tmpmib{"1.1.3.6.0.$fannum"} = [ "gauge", adjust_to_32bit(strip_decimal($voltageval)) ];
		} elsif ($line =~ /^FAN\d+_NAME=/) {
			my ($fannum,$fanname) = $line =~ /^FAN(\d+)_NAME='(.*)'$/i;
			print "Line->$line<-\n" if $debug;
			print "Fan $fannum name = \"$fanname\"\n" if $debug;
			$tmpmib{"1.1.3.1.0.$fannum"} = [ "string", "$fanname" ];
		} elsif ($line =~ /^FLOW\d+=/) {
			my ($flownum,$flowval) = $line =~ /^FLOW(\d+)=(\d+\.\d+)/i;
			print "Line->$line<-\n" if $debug;
			print "Flow sensor $flownum = $flowval (" . strip_decimal($flowval) . ")\n" if $debug;
			$tmpmib{"1.1.4.0.0.$flownum"} = [ "string", "Flow$flownum" ];
			$tmpmib{"1.1.4.2.0.$flownum"} = [ "gauge", adjust_to_32bit(strip_decimal($flowval)) ];
		} elsif ($line =~ /^FLOW\d+_NAME=/) {
			my ($flownum,$flowname) = $line =~ /^FLOW(\d+)_NAME='(.*)'$/i;
			print "Line->$line<-\n" if $debug;
			print "Flow sensor $flownum name = \"$flowname\"\n" if $debug;
			$tmpmib{"1.1.4.1.0.$flownum"} = [ "string", "$flowname" ];
		} elsif ($line =~ /^SYS_TEMP_CPU\d+=/) {
			my ($cpunum,$tempval) = $line =~ /^SYS_TEMP_CPU(\d+)=(\d+\.\d+)/i;
			print "Line->$line<-\n" if $debug;
			print "CPU $cpunum = $tempval (" . strip_decimal($tempval) . ")\n" if $debug;
			$tmpmib{"1.1.5.0.0.$cpunum"} = [ "string", "CPUTemp$cpunum" ];
			$tmpmib{"1.1.5.2.0.$cpunum"} = [ "gauge", adjust_to_32bit(strip_decimal($tempval)) ];
		} elsif ($line =~ /^SYS_TEMP_CPU\d+_NAME=/) {
			my ($cpunum,$cpuname) = $line =~ /^SYS_TEMP_CPU(\d+)_NAME='(.*)'$/i;
			print "Line->$line<-\n" if $debug;
			print "CPU $cpunum name = \"$cpuname\"\n" if $debug;
			$tmpmib{"1.1.5.1.0.$cpunum"} = [ "string", "$cpuname" ];
		} elsif ($line =~ /^LEVEL\d+=/) {
			my ($levelnum,$levelval) = $line =~ /^LEVEL(\d+)=(\d+\.\d+)/i;
			print "Line->$line<-\n" if $debug;
			print "Level sensor $levelnum = $levelval (" . strip_decimal($levelval) . ")\n" if $debug;
			$tmpmib{"1.1.6.0.0.$levelnum"} = [ "string", "Level$levelnum" ];
			$tmpmib{"1.1.6.2.0.$levelnum"} = [ "gauge", adjust_to_32bit(strip_decimal($levelval)) ];
		} elsif ($line =~ /^LEVEL\d+_NAME=/) {
			my ($levelnum,$levelname) = $line =~ /^LEVEL(\d+)_NAME='(.*)'$/i;
			print "Line->$line<-\n" if $debug;
			print "Level $levelnum name = \"$levelname\"\n" if $debug;
			$tmpmib{"1.1.6.1.0.$levelnum"} = [ "string", "$levelname" ];
		} elsif ($line =~ /^VIRT_TEMP\d+=/) {
			my ($tempnum,$tempval) = $line =~ /^VIRT_TEMP(\d+)=(-?\d+\.\d+)/i;
			print "Line->$line<-\n" if $debug;
			$tempval = 0 if ($tempval < 0);
			print "Virtual sensor temp $tempnum = $tempval (" . strip_decimal($tempval) . ")\n" if $debug;
			$tmpmib{"1.1.7.0.0.$tempnum"} = [ "string", "VirtualTemp$tempnum" ];
			$tmpmib{"1.1.7.2.0.$tempnum"} = [ "gauge", adjust_to_32bit(strip_decimal($tempval)) ];
		} elsif ($line =~ /^VIRT_TEMP\d+_NAME=/) {
			my ($tempnum,$tempname) = $line =~ /^VIRT_TEMP(\d+)_NAME='(.*)'$/i;
			print "Line->$line<-\n" if $debug;
			print "Virtual sensor temp $tempnum name = \"$tempname\"\n" if $debug;
			$tmpmib{"1.1.7.1.0.$tempnum"} = [ "string", "$tempname" ];
		} elsif ($line =~ /^SOFT_TEMP\d+=/) {
			my ($tempnum,$tempval) = $line =~ /^SOFT_TEMP(\d+)=(-?\d+\.\d+)/i;
			print "Line->$line<-\n" if $debug;
			$tempval = 0 if ($tempval < 0);
			print "Software sensor temp $tempnum = $tempval (" . strip_decimal($tempval) . ")\n" if $debug;
			$tmpmib{"1.1.8.0.0.$tempnum"} = [ "string", "SoftwareTemp$tempnum" ];
			$tmpmib{"1.1.8.2.0.$tempnum"} = [ "gauge", adjust_to_32bit(strip_decimal($tempval)) ];
		} elsif ($line =~ /^SOFT_TEMP\d+_NAME=/) {
			my ($tempnum,$tempname) = $line =~ /^SOFT_TEMP(\d+)_NAME='(.*)'$/i;
			print "Line->$line<-\n" if $debug;
			print "Software sensor temp $tempnum name = \"$tempname\"\n" if $debug;
			$tmpmib{"1.1.8.1.0.$tempnum"} = [ "string", "$tempname" ];
		} elsif ($line =~ /^OTHER_TEMP\d+=/) {
			my ($tempnum,$tempval) = $line =~ /^OTHER_TEMP(\d+)=(-?\d+\.\d+)/i;
			print "Line->$line<-\n" if $debug;
			$tempval = 0 if ($tempval < 0);
			print "Other sensor temp $tempnum = $tempval (" . strip_decimal($tempval) . ")\n" if $debug;
			$tmpmib{"1.1.9.1.0.$tempnum"} = [ "string", "OtherTemp$tempnum" ];
			$tmpmib{"1.1.9.2.0.$tempnum"} = [ "gauge", adjust_to_32bit(strip_decimal($tempval)) ];
		} elsif ($line =~ /^OTHER_TEMP\d+_NAME=/) {
			my ($tempnum,$tempname) = $line =~ /^OTHER_TEMP(\d+)_NAME='(.*)'$/i;
			print "Line->$line<-\n" if $debug;
			print "Other sensor temp $tempnum name = \"$tempname\"\n" if $debug;
			$tmpmib{"1.1.9.1.0.$tempnum"} = [ "string", "$tempname" ];
		}
	}
	$mib = \%tmpmib;
	$mibtime = time;
	return $mib;
} 

# Strip the decimal place from floating point values
sub strip_decimal {
	my ($inval) = @_;
	if ($inval == 0.0) {
		return 0;
	} else {
		$inval =~ s/\.//;
 		return $inval;
	}
}

sub create_coid {
	my ($k, %p, %oids) = @_;
	my ($ifoid,$val) = split /\s/, $k;

	my $id = $p{$val};
	my $oid= "";

	while (defined($id)) {
		$oid = $oids{$id}?$oids{$id}++:1;
		print "$oid\n";
		$id = $p{$id};
	}
	
	return "";
}


sub adjust_to_32bit {
	my ($val) = @_;
	if ($val > 4294967295) {
		$val = $val % 4294967295;
	}
	return $val;
}

sub get_oid {
	my ($oid) = @_;
	chomp $oid;

	my $base = $baseoid;
	$base =~ s/\./\\./g;

	if ($oid !~ /^$base(\.|$)/) {
		# Requested oid doesn't match base oid
		return 0;
	}

	$oid =~ s/^$base\.?//;
	return $oid;
}


sub oidcmp {
	my ($x, $y) = @_;

	my @a = split /\./, $x;
	my @b = split /\./, $y;

	my $i = 0;

	while (1) {

		if ($i > $#a) {
			if ($i > $#b) {
				return 0;
      			} else {
				return -1;
      			}
		} elsif ($i > $#b) {
			return 1;
		}

		if ($a[$i] < $b[$i]) {
			return -1;
		} elsif ($a[$i] > $b[$i]) {
			return 1;
		}
		$i++;
	}
}


