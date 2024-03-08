#!/bin/env bash

battery(){
	if [ $bat_status == "Discharging" ];then
		if [ $bat_int -ge "80"  ];then
			echo 
		elif [ $bat_int -ge "65"  ];then
			echo 
		elif [ $bat_int -ge "50"  ];then
			echo 
		elif [ $bat_int -ge "20"  ];then
			echo 
		elif [ $bat_int -lt "20"  ];then
			echo 
		fi
	elif [ $bat_status == "Full" ];then
		echo 
	else echo 
	fi
}

while true; do
	bat_status=$(acpitool -b | awk {'print $4'} | sed 's/,//') 
	bat_int=$(acpitool -b | awk {'print $5'} | sed 's/\.[0-9].*//') 
	bat_percent=$(acpitool -b | awk {'print $5'} | sed 's/\.[0-9].*/%/') 
	date=$(date +%I:%M' '%p' '''' '%m-%d)
	xsetroot -name "[ $(battery)  $bat_percent ] $date"
	#xsetroot -name " [ $(battery)  $bat_percent ] $(date +%I:%M" "%p)"
	sleep 5;
done
