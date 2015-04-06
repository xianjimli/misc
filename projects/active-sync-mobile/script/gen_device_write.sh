#!/bin/bash

echo $* | awk -F, '{for(i = 1; i <= NF; i++) {field=$i; sub(/^ /, "", field); system("./gen_device_write_one.sh " field );}; }'

