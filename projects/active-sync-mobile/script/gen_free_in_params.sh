#!/bin/bash

echo $* | awk -F, '{for(i = 1; i <= NF; i++) {field=$i; sub(/^ /, "", field); system("./gen_free_in_params_one.sh " field );}; }'
