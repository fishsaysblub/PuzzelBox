#!/bin/bash
if [ "$1" ]; then
    IFACE=$1  
else
    IFACE=eth0
fi

if { ip -f inet addr show $IFACE | sed -En -e 's/.*inet ([0-9.]+).*/\1/p'; } 2>/dev/null; then
    exit 0
else
    exit 1
fi
