#!/bin/sh

# Keep light awake

while true
do
  sudo ./clear_leds 
  ./timercontrol.sh

# Wait between run
  sleep 5
done
