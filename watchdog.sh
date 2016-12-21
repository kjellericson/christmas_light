#!/bin/sh

# Keep light awake

while true
do
  sudo ./clear_leds 
  ./timercontrol.pl

# Wait between run
  sleep 5
done
