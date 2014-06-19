#!/usr/local/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )"/../ && pwd )"

if [[ -z "$1" ]]; then 
	echo "syntax: ./gen-dbus-interfaces <interface name>"
	exit 1
elif [[ "$1" != "hostnamed" && "$1" != "localed" && "$1" != "timedated" && "$1" != "logind" ]]; then 
	echo "<interface name> must be 'hostnamed', 'localed', 'timedated', or 'logind'"
	exit 1
fi

gdbus-codegen \
--interface-prefix org.freedesktop. \
--generate-docbook doc/$1-docbook.xml \
--generate-c-code  src/interfaces/$1/$1-gen \
conf/$1-ispect.xml

echo "success"
exit 0
