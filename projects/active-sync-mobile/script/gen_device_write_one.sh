#!/bin/bash

case $1 in
	WStr\*) 
		echo "		ret = asm_output_buffer_device_write_wstr(output, $2);"
	;;
	RKEY)
		echo "		ret = asm_output_buffer_write_uint32(output, $2);"
	;;
	void\*)
		echo "		ret = asm_output_buffer_write_data(output, $2, $2""_length);"
	;;
	unsigned)
	if [ "$2" = "int" ]
	then
		echo "		ret = asm_output_buffer_write_uint32(output, $3);"
	else
		echo "		ret = asm_output_buffer_write_uint16(output, $3);"
	fi
     ;;
    "")
    ;;
    *)
    	echo "		ret = asm_output_buffer_write_data(output, $2, sizeof(*$2));"
    ;;
esac

