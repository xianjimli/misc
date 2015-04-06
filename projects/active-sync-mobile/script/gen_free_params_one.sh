#!/bin/bash

case $1 in
	*\*|\*\*)
		echo "	ASM_FREE("$2");";
	;;
	*)
	;;
esac

