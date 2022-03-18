#!/bin/bash
sudo strace -o /tmp/strace.log -e openat,ioctl,fcntl,ppoll,write,read -f "$@"
