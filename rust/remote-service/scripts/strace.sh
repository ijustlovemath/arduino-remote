#!/bin/bash
if [ -z "$LOGNAME" ] ; then
    LOGNAME="/tmp/strace.log"
fi
sudo strace -o "$LOGNAME" -e openat,ioctl,fcntl,ppoll,write,read -ff "$@"
