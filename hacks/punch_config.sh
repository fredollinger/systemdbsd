#!/bin/sh

# sticks our config for hostnamed (which needs to use the system bus)
# in place. and restarts dbus-daemon will be replaced by a more elegant,
# not-hack in the future

cp $(dirname "$(readlink -f "$0")")/hostnamed-dbus.conf /etc/dbus-1/system.d/hostnamed-dbus.conf
/etc/rc.d/dbus_daemon reload >> /dev/null
