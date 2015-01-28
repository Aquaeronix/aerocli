#!/bin/bash
# Note: 
#   - this script is just a dirty hack to keep us going until I can hack together 
#     a proper daemon to do the work
#   - bash arithmetic evaluation does not support floating point, so bc is needed 
#   - this script conks out if you have less than 10 or more than 99 degrees celsius,
#     but at least in latter case your least concern will probably be to write 
#     the temperature value to the aquaero. Sorry to you guys at Admundsen Station,
#	  you'll have to sit out a spell if the heating goes spare ;)
if [ $# -le 1 ]; then
	OFFSET=0.00
else
	OFFSET=$2
fi

while true; do 
	TEMP=$(echo scale=2\;$(cat $1 |sed -r 's/([0-9]{2})([0-9]{3})/\1.\2/') +$OFFSET|bc)
	sudo aerocli -q -s 1:$TEMP
	sleep 1; 
done
