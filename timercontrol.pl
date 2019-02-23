#!/usr/bin/perl

# Keep light awake
# Also adding time check and run certain times.

my %sunrise;
my %sunset;

my $location = $ARGV[1];


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

    my $turn_on=0;
    my $arg;

    ##
    ## Check file turn_on2.txt.  If it contains 1 then we turn light on.
    ##
    if (-f "turn_on2.txt") {
	$tmp = `/bin/cat turn_on2.txt`;
	if ($tmp eq "1") {
	    $turn_on = $tmp;
	}
    }

    ##
    ## Check file turn_on.txt.  If it contains 1 then we turn light on.
    ## This overrides turn_on2.txt (but only in a positive way)
    ##
    if (-f "turn_on.txt") {
	$tmp = `/bin/cat turn_on.txt`;
	if ($tmp eq "1") {
	    $turn_on = $tmp;
	    $arg = "whiteoverlay";
	}
    }

    ##
    ## Decide if we shall run christmas light
    ##
    print "turn_on = $turn_on\n";
    if ($turn_on) {
	`sudo ./christmas_light $arg`;
    }
    `sudo ./clear_leds`;
    sleep(10);
}

##
## Sleep a while for not exhausting the system
##
sleep(2);

