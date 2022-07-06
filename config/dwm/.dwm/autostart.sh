#!/bin/bash

wmname compiz

#if [[ ! $(pgrep "xob") ]]; then
#exec sxob
#fi

start() {
	if ! pgrep -f $1; then
		exec $@ &
	fi
}

nitrogen --restore
start dunst

# start copyq

start xrdb "$HOME/.Xresources"
start /usr/lib/polkit-kde-authentication-agent-1

dex --autostart --environment autostart
# dex --autostart --environment awesome
