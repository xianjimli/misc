#!/bin/bash

case $1 in
	WStr\*\*) 
		echo "	ret = asm_input_buffer_read_wstr_dup(input, $2);"
	;;
	RKEY*)
		echo "	ret = asm_input_buffer_read_uint32(input, $2);"
	;;
	unsigned)
	if [ "$2" = "int*" ]
	then
		echo "	ret = asm_input_buffer_read_uint32(input, $3);"
	else
		echo "	ret = asm_input_buffer_read_uint16(input, $3);"
	fi
     ;;
    void\*\*)
    	echo "	ret = asm_input_buffer_read_data(input, $2, *$2""_length);"
    ;;
    "")
    ;;
    *)
    	echo "	*$2=ASM_ALLOC(${1/\*\*/}, 0);"
    	echo "	ret = asm_input_buffer_read_data(input, *$2, sizeof(*(*$2)));"
    ;;
esac

