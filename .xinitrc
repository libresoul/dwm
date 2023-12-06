#picom -CG --no-fading-openclose &
feh --bg-fill ~/Pictures/wallpapers/daniel-leone-v7daTKlZzaw-unsplash.jpg &
~/.scripts/panelfilling.sh &

systemctl --user import-environment DISPLAY XAUTHORITY
dbus-update-activation-environment DISPLAY XAUTHORITY

#nm-applet &
#xfce4-clipman &

exec dwm

