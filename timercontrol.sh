#!/bin/sh

# Keep light awake
# Also adding time check and run certain times.

# Store PID
echo $$ >timercontrol.pid

# Run forever
while true
do
  ##
  ## Get time
  ##
  now=$(date +"%H%M") 
  date
  echo "Now = $now"

  ##
  ## Check file turn_on.txt.  If it contains 1 then we turn light on.
  ##
  turn_on = 0
  if [ -f "turn_on.txt" ]
  then
    turn_on = `cat turn_on.txt`;
  fi

  ##
  ## Decide if we shall run christmas light
  if [ $turn_on -eq "1" ]
  then
    sudo ./christmas_light
  elif [ $now -ge 1500 -a $now -le 2359 ]
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
