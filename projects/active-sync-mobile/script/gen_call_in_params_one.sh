#!/bin/bash

case $1 in
	"unsigned")
		echo -n ", "$3
	;;
	"")
	;;
	*)
		echo -n ", "$2
	;;
esac

