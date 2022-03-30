#!/bin/bash
sudo strace -o django-strace-verbose.log -t -f --verbose=all --abbrev=none su jer ./run
