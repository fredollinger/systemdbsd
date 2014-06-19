#!/usr/local/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )"/../ && pwd )"

if [[ -z "$1" ]]; then 
	echo "syntax: ./gen-dbus-interfaces <interface name>"
	exit 1
fi

gdbus-codegen \
--interface-prefix org.freedesktop. \
--generate-docbook doc/$1-docbook.xml \
--generate-c-code  src/interfaces/$1/$1-gen \
--c-namespace SystemdUtils \
conf/$1-ispect.xml

