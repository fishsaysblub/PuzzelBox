#!/bin/bash
if [ "$1" ]; then
    IFACE=$1  
else
    IFACE=eth0
fi

if { read -r MAC < /sys/class/net/$IFACE/address; } 2>/dev/null; then
    echo "$MAC"
    exit 0
else
    exit 1
fi
