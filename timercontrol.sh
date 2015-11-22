#!/bin/sh

# Keep light awake
# Also adding time check and run certain times.

# Store PID
echo $$ >timercontrol.pid

# Run forever
while true
do
  now=$(date +"%H%M") 
  date
  echo "Now = $now"
  if [ $now -ge 1500 -a $now -le 2359 ]
  then 
    sudo ./christmas_light
  elif [ $now -ge 0400 -a $now -le 0830 ]
  then 
    sudo ./christmas_light
  else
    sleep 10
  fi

  sleep 2
done
