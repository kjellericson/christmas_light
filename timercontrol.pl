#!/usr/bin/perl

# Keep light awake
# Also adding time check and run certain times.

my %sunrise;
my %sunset;

@{$sunrise{"stockholm"}} = ("08:44", # jan
			    "07:59", # feb
			    "06:41", # mar
			    "06:12", # apr
			    "04:45", # may
			    "03:42", # jun
			    "03:39", # jul
			    "04:35", # aug
			    "05:46", # sep
			    "06:55", # oct
			    "07:08", # nov
			    "08:19");# dec
@{$sunset{"stockholm"}} = ("14:57", # jan
			   "16:02", # feb
			   "17:16", # mar
			   "19:29", # apr
			   "20:42", # may
			   "21:47", # jun
			   "22:03", # jul
			   "21:11", # aug
			   "19:48", # sep
			   "18:17", # oct
			   "15:52", # nov
			   "14:53");# dec

my $location = $ARGV[1];

if ($location eq "") {
    $location = "stockholm";
}

##
## Run forever
##
while (1) {
    ##
    ## Store PID
    ##
    `echo $$ >timercontrol.pid`;

    ##
    ## Get time
    ##
    $now=time();

    ##
    ## Check file turn_on.txt.  If it contains 1 then we turn light on.
    ##
    my $turn_on=0;
    if (-f "turn_on.txt") {
	$turn_on = `/bin/cat turn_on.txt`;
    }

    # Turn on one hour before sunset
    {
	my ($sec, $min, $hour, $mday, $mon, $year, $wday, $yday, $isdst) = 
	    localtime($now - 3600);
	my $t = sprintf("%02d:%02d", $hour, $min);
	if ($sunset{$location}[$mon] gt $t) {
	    print "Sunset mode\n";
	    $turn_on = 1;
	}
    }

    # Keep turned on until one hour after sunrise
    {
	my ($sec, $min, $hour, $mday, $mon, $year, $wday, $yday, $isdst) = 
	    localtime($now + 3600);
	my $t = sprintf("%02d:%02d", $hour, $min);
	if ($sunrise{$location}[$mon] gt $t) {
	    print "Sunrise mode\n";
	    $turn_on = 1;
	}
    }

    ##
    ## Decide if we shall run christmas light
    ##
    if ($turn_on) {
	`sudo ./christmas_light`;
    }
    `sudo ./clear_leds`;
    sleep(10);
}

##
## Sleep a while for not exhausting the system
##
sleep(2);

