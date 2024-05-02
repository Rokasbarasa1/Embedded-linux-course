#Authors:
#Rokas Barasa
#Arturas Maziliauskas

#! /bin/bash

# ./LedSwitch.sh led0 blink 200
# ./LedSwitch.sh led0 heartbeat 

help="Set the state of beaglebone leds. \narg0 - which led to set status of (led0, led1, led2, led3, all)\narg1 - set mode of specified led('s)\narg2 - supply this argument if mode is set to (blink). Sets the refresh rate of led. Argument must be integer larger than 0"

if test $1 = "--help"
    then
        echo "$help"
        exit 1 
fi

# see if arg0 is valid 
if test $1 != "led0" && test $1 != "led1" && test $1 != "led2" && test $1 != "led3" && test $1 != "all"; 
    then
        echo "Failed check for argument 0"
        echo "$help"
        exit 1 
fi

# see if arg1 is valid 
if test $2 != "on" && test $2 != "off" && test $2 != "heartbeat" && test $2 != "blink" && test $2 != "default"; 
    then
        echo "Failed check for argument 1"
        echo "$help"
        exit 1 
fi

# see if arg1 is blink and if it is check arg2 to be 
# an integer more than 0 
if test $2 = "blink"
    then
        if test $3 -gt 0
            then
                echo "Blink at $3"
            else
                echo "Failed check for argument 0"
                echo "$help"
                exit 1 
        fi
fi

# usr0 = heartbeat
# usr1 = mmc0
# usr2 = cpu0
# usr3 = mmc1

# $1 is leds
# $2 is mode
# $3 is hz if mode blink

leds=$1
mode=$2

if test $mode = "blink"
then
    mode="timer"
elif test $mode = "on"
then
    mode="default-on"
elif test $mode = "off"
then
    mode="none"
fi

# change the trigger for all
if test $leds = "all"; 
then
    number=0
    while test "$number" -lt 4
    do
        # If mode not default use the mode in the variable $mode
        if test $mode != "default" 
        then
            echo $mode > "/sys/class/leds/beaglebone:green:usr$number/trigger"

        # Default modes require specific modes
        else
            if test $number -eq 0
            then    
                echo "heartbeat" > "/sys/class/leds/beaglebone:green:usr$number/trigger"
            elif test $number -eq 1
            then
                echo "mmc0" > "/sys/class/leds/beaglebone:green:usr$number/trigger"
            elif test $number -eq 2
            then
                echo "cpu0" > "/sys/class/leds/beaglebone:green:usr$number/trigger"
            else
                echo "mmc1" > "/sys/class/leds/beaglebone:green:usr$number/trigger"
            fi
        fi

        # increment number
        ((number=number+1))
    done

#Change trigger for one led 
else

    # If mode not default use the mode in the variable $mode
    if test $mode != "default" 
    then
        echo $mode > "/sys/class/leds/beaglebone:green:usr${leds: -1}/trigger"
    
    # Default modes require specific modes
    else
        if test ${leds: -1} -eq 0
        then    
            echo "heartbeat" > "/sys/class/leds/beaglebone:green:usr${leds: -1}/trigger"
        elif test ${leds: -1} -eq 1
        then
            echo "mmc0" > "/sys/class/leds/beaglebone:green:usr${leds: -1}/trigger"
        elif test ${leds: -1} -eq 2
        then
            echo "cpu0" > "/sys/class/leds/beaglebone:green:usr${leds: -1}/trigger"
        else
            echo "mmc1" > "/sys/class/leds/beaglebone:green:usr${leds: -1}/trigger"
        fi
    fi
fi

# if the mode is timer 2 files need to be set a delay in ms
if test $mode = "timer"
then

    # get frequency in ms halfed for led to turn off and on
    frequency=$(($3/2))

    # check if this is for all leds
    if test $leds = "all"
    then
        echo "do loop"
        number=0
        while test "$number" -lt 4
        do
            delay_on_string="/sys/class/leds/beaglebone\:green\:usr$number/delay_on"
            delay_off_string="/sys/class/leds/beaglebone\:green\:usr$number/delay_off"
            
            sudo sh -c "echo $frequency > $delay_on_string"
            sudo sh -c "echo $frequency > $delay_off_string"

            # increment number
            ((number=number+1))
        done
    else 
        delay_on_string="/sys/class/leds/beaglebone\:green\:usr${leds: -1}/delay_on"
        delay_off_string="/sys/class/leds/beaglebone\:green\:usr${leds: -1}/delay_off"
        
        sudo sh -c "echo $frequency > $delay_on_string"
        sudo sh -c "echo $frequency > $delay_off_string"
    fi
fi

# delay_on
# delay_off
# beaglebone:green:usr0
# beaglebone:green:usr1
# beaglebone:green:usr2
# beaglebone:green:usr3

if test $2 -le 20
then 