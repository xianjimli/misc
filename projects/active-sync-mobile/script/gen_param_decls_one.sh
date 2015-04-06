#!/bin/bash

case $1 in
	WStr\*|void\*)
		echo "	$* = NULL;"
	;;
	"")
	;;
	*)
		echo "	$* = 0;"
	;;
esac

