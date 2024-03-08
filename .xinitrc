#feh --bg-fill --randomize --recursive ~/Pictures/backgrounds/ &
~/.scripts/panelfilling.sh &
~/.scripts/xinput.sh &
#~/.scripts/background.sh &
systemctl --user import-environment DISPLAY XAUTHORITY
dbus-update-activation-environment DISPLAY XAUTHORITY
#dbus-update-activation-environment --systemd --all

#nm-applet &
#copyq &
xfce4-clipman &

picom &

exec dwm

