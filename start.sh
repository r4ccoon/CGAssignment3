#!/bin/sh

# Gives the local IP address
local_ip=$(ifconfig | awk '/inet/{print $2}' | grep '192.168.*')

#  "$#" denotes the no. of command line arguments
# If no arguments means, this guy is the creator of the network
if test $# -eq 0
then
	# Get the default IP initially present in calendar/config.php
	calendar_ip=$(awk '/xmlrpc.php/{print $3}' ./calendar/config.php | grep -o '[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}')

	# MAC - Replace the initial IP with the local IP
	$(sed -i .bk 's/'$calendar_ip'/'$local_ip'/g' ./calendar/config.php)
	
	# In mac, we need to give ".bk" for 'sed'. This creates backup, which we don't need. So remove it.
	rm ./calendar/config.php.bk

	# Give this command in linux instead of the above two.
	#$(sed -i 's/'$calendar_ip'/'$local_ip'/g' ./calendar/config.php)
		
	# MAC - Open the link in browser
	open http://$local_ip/calendar
	
	#Linux
	#/usr/bin/firefox http://$local_ip/calendar
	
	# Get initial Client IP
	client_ip=$(awk '/xmlrpc.php/{print $3}' ./client/config.php | grep -o '[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}')

	# MAC - Replace the initial IP with the local IP
	$(sed -i .bk 's/'$client_ip'/'$local_ip'/g' ./client/config.php)
	rm ./client/config.php.bk

	# Give this command in linux instead of the above two.
	#$(sed -i 's/'$client_ip'/'$local_ip'/g' ./client/config.php)

	# MAC - Open link
	open http://$local_ip/client
	
	#Linux
	#/usr/bin/firefox http://$local_ip/client

# If args is given, then argv[1] = tracker_ip of the form "192.168.1.06"
elif test $# -eq 1
then
	# Same process as above but this time replace the calendar_ip with tracker_ip instead of local_ip to connect to the network
	tracker_ip=$1
	calendar_ip=$(awk '/xmlrpc.php/{print $3}' ./calendar/config.php | grep -o '[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}')

	$(sed -i .bk 's/'$calendar_ip'/'$tracker_ip'/g' ./calendar/config.php)
	rm ./calendar/config.php.bk

	# Give this command in linux instead of the above two.
	#$(sed -i 's/'$calendar_ip'/'$tracker_ip'/g' ./calendar/config.php)
	
	# MAC
	open http://$tracker_ip/calendar

	#Linux
	# /usr/bin/firefox http://$tacker_ip/calendar

	client_ip=$(awk '/xmlrpc.php/{print $3}' ./client/config.php | grep -o '[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}')

	$(sed -i .bk 's/'$client_ip'/'$local_ip'/g' ./client/config.php)
	rm ./client/config.php.bk
	
	# Give this command in linux instead of the above two.
	#$(sed -i 's/'$client_ip'/'$local_ip'/g' ./client/config.php)
	
	# MAC
	open http://$local_ip/client

	#Linux
	# /usr/bin/firefox http://$local_ip/client

fi