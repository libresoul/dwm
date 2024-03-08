#!/bin/bash

OPTIONS="Cancel;Lock;Logout;Suspend;Shutdown;Reboot"
OPTION=$(echo "$OPTIONS" | tr ';' '\n' | dmenu -i -p "Powermenu")
	
case $OPTION in
	"Lock") $(slock) ;;
	"Logout") $(pkill -u $USER) ;;
	"Suspend") $(systemctl suspend) ;;
	"Shutdown") $(sudo shutdown now) ;;
	"Reboot") $(sudo reboot now) ;;
	*) exit 0 ;;
esac

