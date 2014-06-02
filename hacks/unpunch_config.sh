#!/bin/sh

# unsticks our config for hostnamed (which needs to use the system bus)
# and restarts dbus

rm /etc/dbus-1/system.d/hostnamed-dbus.conf
/etc/rc.d/dbus_daemon reload >> /dev/null
