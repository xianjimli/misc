#!/bin/bash
find  -name \*.c | awk -F/ '{str=$3; sub(/\.c/, ".o", str);print str ":"$0;print "\t$(CC) $(CFLAGS) -o $@ $<" }' >c.mk
find  -name \*.c | awk -F/ 'BEGIN{printf "\nC_OBJS="}{str=$3; sub(/\.c/, ".o", str);printf str" "}END{print ""}' >>c.mk
