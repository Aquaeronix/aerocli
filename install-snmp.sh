make aerocli

cp ./utilities/SNMP/snmp_persist_aquaero5.pl /usr/local/sbin
chmod +x /usr/local/sbin/snmp_persist_aquaero5.pl

echo "pass_persist .1.3.6.1.4.1.2021.255.65.67 /usr/local/sbin/snmp_persist_aquaero5.pl" > /etc/snmp/snmpd.conf

