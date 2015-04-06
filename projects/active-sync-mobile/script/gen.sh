#!/bin/bash
CMD_DEF=$1

if [ "$CMD_DEF" = "" ]
then
	echo "usage: $0 xxx.def"
	exit 0;
fi

export STRUCT_NAME=${CMD_DEF/.def/}
export LOWER_STURCT_NAME=`echo -n $STRUCT_NAME | tr A-Z a-z`
export FILENAME=`echo ${CMD_DEF/.def/}|tr A-Z a-z`
export INTF_H="rapi_device_"$FILENAME".h"
export DEVICE_DEFAULT_H="rapi_device_"$FILENAME"_default.h"
export DEVICE_DEFAULT_C="rapi_device_"$FILENAME"_default.c"
export DEVICE_READ_H="rapi_device_"$FILENAME"_read.h"
export DEVICE_READ_C="rapi_device_"$FILENAME"_read.c"
export DEVICE_WRITE_H="rapi_device_"$FILENAME"_write.h"
export DEVICE_WRITE_C="rapi_device_"$FILENAME"_write.c"
export HOST_READ_H="rapi_host_"$FILENAME"_read.h"
export HOST_READ_C="rapi_host_"$FILENAME"_read.c"
export HOST_WRITE_H="rapi_host_"$FILENAME"_write.h"
export HOST_WRITE_C="rapi_host_"$FILENAME"_write.c"
export HOST_H="rapi_host_"$FILENAME".h"
export HOST_C="rapi_host_"$FILENAME".c"
export COMMON_DEF="rapi_"$FILENAME".h"
export DEVICE_DISPATCH_H="rapi_device_"$FILENAME"_dispatch.h"
export DEVICE_DISPATCH_C="rapi_device_"$FILENAME"_dispatch.c"
echo $LOWER_STURCT_NAME

function gen_include_once_begin()
{
	FN=$1
	echo -n "#ifndef "
	echo $FN | sed -e "s/\./_/g"|tr a-z A-Z
	echo -n "#define "
	echo $FN | sed -e "s/\./_/g"|tr a-z A-Z

	return;
}

function gen_include_once_end()
{
	FN=$1
	echo -n "#endif/*"
	echo -n $FN | sed -e "s/\./_/g"|tr a-z A-Z
	echo "*/"
	echo ""

	return;
}

function gen_device_intf_h()
{
	echo "#include <asm-common.h>"
	gen_include_once_begin $INTF_H

	echo ""
	echo "struct _RapiDevice$STRUCT_NAME;"
	echo "typedef struct _RapiDevice$STRUCT_NAME RapiDevice$STRUCT_NAME;"
	echo ""

	awk -F: '{name=$3; 
	gsub(/_/, "", name); 
	params_types=$4" "$5;
	gsub(/, $/, "", params_types);
	if(length($4$5) > 0)
	{
		params_types=", "params_types;
	}
	print "typedef AsmRet (*RapiDevice" $2 name"Func)\n\t(" "RapiDevice"$2 "* thiz, unsigned int* return_value"params_types");" }' $CMD_DEF

	echo ""
	echo "typedef void (*RapiDevice"$STRUCT_NAME"DestroyFunc)(RapiDevice"$STRUCT_NAME"* thiz);"

	echo ""
	echo "struct _RapiDevice$STRUCT_NAME"
	echo "{"
	awk -F: '{name=$3; gsub(/_/, "", name); print "\tRapiDevice"$2 name"Func " tolower($3) ";" }' $CMD_DEF

	echo "	RapiDevice"$STRUCT_NAME"DestroyFunc destroy;"
	echo "	char priv[0];"
	echo "};"
	echo ""
	awk -F: '{name=$3; gsub(/_/, "", name); \
	params=$4$5; \
	gsub(/WStr\*|RKEY\*|RKEY|unsigned int\*|unsigned int|void\*|RapiProcessInfo\*|RapiStoreInfo\*|RapiSystemInfo\*|RapiSystemPowerStatus\*|RapiVersionInfo\*|WStr\*\*|void\*\*|RapiProcessInfo\*\*|RapiStoreInfo\*\*|RapiSystemInfo\*\*|RapiSystemPowerStatus\*\*|RapiVersionInfo\*\*|RapiFileTime\*|RapiFileTime\*\*|RapiFindData\*\*:RapiFindData\* /, "", params);\
	gsub(/,$/, "", params);\
	params_types=$4" "$5;
	gsub(/, $/, "", params_types);\
	if(length($4$5) > 0)
	{
		params_types=", "params_types;
		params=", "params;
	}
	print "static inline AsmRet rapi_device_" tolower($2)"_"tolower($3) "\n\t(RapiDevice"$2 "* thiz, unsigned int* return_value" params_types ")\n{\n\tasm_return_val_if_fail(thiz != NULL && thiz->" tolower($3) " != NULL, ASM_RET_FAIL);\n\n\treturn thiz->" tolower($3) "(thiz, return_value"params");\n}\n"}' $CMD_DEF

	echo -n "static inline void rapi_device_"
	echo -n $STRUCT_NAME|tr A-Z a-z
	echo "_destroy(RapiDevice"$STRUCT_NAME"* thiz)"
	echo "{"
	echo "	asm_return_if_fail(thiz != NULL && thiz->destroy != NULL);"
	echo "	thiz->destroy(thiz);"
	echo ""
	echo "	return;"
	echo "}"
	gen_include_once_end $INTF_H
	
	return;
}

function gen_device_default_h()
{
	echo "#include <$INTF_H>"
	echo ""
	gen_include_once_begin $DEVICE_DEFAULT_H
	echo ""
	echo -n "RapiDevice"$STRUCT_NAME"* rapi_device_"
	echo -n $STRUCT_NAME|tr A-Z a-z
	echo "_default_create(void);"
	echo ""

	gen_include_once_end $DEVICE_DEFAULT_H
	
	return;
}

function gen_device_default_c()
{
	echo "#include <$DEVICE_DEFAULT_H>"
	echo ""
	echo "typedef struct _PrivInfo"
	echo "{"
	echo "	int dummy;"
	echo "}PrivInfo;"
	echo ""

	awk -F: '{name=$3; gsub(/_/, "", name); \
	params_types=$4" "$5;
	gsub(/, $/, "", params_types);\
	if(length($4$5) > 0)
	{
		params_types=", "params_types;
	}
	print "static AsmRet rapi_device_" tolower($2)"_default_"tolower($3) "\n\t(RapiDevice"$2 "* thiz, unsigned int* return_value" params_types ")\n{\n\tasm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);\n\tPrivInfo* priv = (PrivInfo*)thiz->priv;\n\n\treturn ASM_RET_OK;\n}\n"}' $CMD_DEF

	echo "void rapi_device_$LOWER_STURCT_NAME""_default_destroy(RapiDevice$STRUCT_NAME* thiz)"
	echo "{"
	echo "	ASM_FREE(thiz);"
	echo ""
	echo "	return;"
	echo "}"
	echo ""
	echo -n "RapiDevice"$STRUCT_NAME"* rapi_device_"
	echo -n $STRUCT_NAME|tr A-Z a-z
	echo "_default_create(void)"
	echo "{"
	echo "	RapiDevice"$STRUCT_NAME"* thiz = (RapiDevice"$STRUCT_NAME"*)ASM_ALLOC(RapiDevice"$STRUCT_NAME", sizeof(PrivInfo));"

	awk -F: '{name=$3; gsub(/_/, "", name); \
	print "	thiz->"tolower($3)" = rapi_device_" tolower($2)"_default_"tolower($3)";";}' $CMD_DEF
	echo "	thiz->destroy = rapi_device_$LOWER_STURCT_NAME""_default_destroy;";
	echo ""
	echo "	return thiz;"
	echo "}"
	echo ""
}

function gen_device_write_h()
{
	echo "#include <asm-output-buffer.h>"
	echo "#include <rapi_device_lib.h>"
	echo ""
	gen_include_once_begin $DEVICE_WRITE_H
	echo ""
	awk -F: '{params=$5; gsub(/\* /, " ", params); \
	printf "AsmRet rapi_device_write_" tolower($2)"_"tolower($3) "(\n\tAsmOutputBuffer* output, unsigned int last_error, unsigned int return_value";\
	if(length(params) > 0){printf ",\n\t" params;};\
	print ");"}' $CMD_DEF
	echo ""
	gen_include_once_end $DEVICE_WRITE_H

	return;
}
function gen_device_write_c()
{
	echo "#include <$DEVICE_WRITE_H>"
	echo ""
	echo ""
	awk -F: '{params=$5; gsub(/\* /, " ", params); \
	printf "AsmRet rapi_device_write_" tolower($2)"_"tolower($3) "(\n\tAsmOutputBuffer* output, unsigned int last_error, unsigned int return_value";\
	if(length(params) > 0){printf ",\n\t" params;};\
	print ")\n{\t";\
	print "	AsmRet ret = ASM_RET_FAIL;"; \
	print "	asm_return_val_if_fail(output != NULL, ret);\n";\
	print "	ret = asm_output_buffer_write_uint32(output, last_error);"; \
	print "	ret = asm_output_buffer_write_uint32(output, return_value);"; \
	if($2 ~ /Registry/)
	{
		print "	if(return_value == RAPI_SUCCESS)\n\t{";
		system("./gen_device_write.sh " params); 
		print "\n\t}";
	}
	else
	{
		system("./gen_device_write.sh " params); 
	}
	print "\n\treturn ret;\n}\n"
	}' $CMD_DEF
	echo ""

	return;
}

function gen_device_read_h()
{
	echo "#include <asm-input-buffer.h>"
	echo "#include <rapi_device_lib.h>"
	echo ""
	gen_include_once_begin $DEVICE_READ_H
	echo ""
	awk -F: '{params=$4; gsub(/ /, "* ", params); \
	gsub(/,\*/, ",", params); \
	gsub(/unsigned\*/, "unsigned", params); \
	gsub(/,$/, "", params); \
	if(length($4) > 0)
	{
		params=", "params;
		print "AsmRet rapi_device_read_" tolower($2)"_"tolower($3) "(AsmInputBuffer* input\n\t"params");"
	}
	}' $CMD_DEF
	echo ""
	gen_include_once_end $DEVICE_READ_H

	return;
}

function gen_device_read_c()
{
	echo "#include <$DEVICE_READ_H>"
	echo ""
	awk -F: '{params=$4; gsub(/ /, "* ", params); \
	gsub(/,\*/, ",", params); \
	gsub(/unsigned\*/, "unsigned", params); \
	gsub(/,$/, "", params); \
	if(length($4) > 0)
	{
		params=", "params;
		print "AsmRet rapi_device_read_" tolower($2)"_"tolower($3) "(AsmInputBuffer* input\n\t"params")\n{"; \
		print "	AsmRet ret = ASM_RET_FAIL;";\
		print "	asm_return_val_if_fail(input != NULL, ret);\n";\
		system("./gen_device_read.sh " params); \
		print "\n\treturn ret;\n}\n"
	}
	}' $CMD_DEF
	echo ""

	return;
}

function gen_common_def()
{
	gen_include_once_begin $COMMON_DEF

	echo ""
	echo "typedef enum _Rapi"$STRUCT_NAME"Command"
	echo "{"
	awk -F: '{print "	RAPI_COMMAND_" toupper($2) "_"toupper($3)"="$1","}' $CMD_DEF
	echo "}Rapi"$STRUCT_NAME"Command;"

	gen_include_once_end $COMMON_DEF

	return;
}

function gen_device_dispatch_c()
{
	echo "#include <$DEVICE_DISPATCH_H>"
	echo ""
	awk -F: '{ 
	out_params_decl=$5;
	gsub(/\* /, " ", out_params_decl);
	
	print "static AsmRet rapi_device_connection_session_handle_"tolower($3)"(AsmConnection* thiz)";
	print "{";
	print "	AsmRet ret = ASM_RET_FAIL;";
	print "	PrivInfo* priv = (PrivInfo*)thiz->priv;";
	print "";
	system("./gen_param_decls.sh " $4);
	system("./gen_param_decls.sh " out_params_decl);
	print "";
	print "	unsigned int return_value = RAPI_SUCCESS;";
	print "";
	print "	do";
	print "	{";
	if(length($4) > 0)
	{
		printf "		ret = rapi_device_read_"tolower($2)"_"tolower($3)"(priv->input";
		system("./gen_read_params.sh " $4);
		print ");";
		print "		if(ret != ASM_RET_OK) break;";
	}
	printf "		ret = rapi_device_"tolower($2)"_"tolower($3)"(priv->"tolower($2)", &return_value";
	system("./gen_call_in_params.sh " $4);
	system("./gen_call_out_params.sh " $5);
	print ");";
	print "		if(ret != ASM_RET_OK) break;"
	if($2 ~ /Registry/)
	{
		printf "		ret = rapi_device_write_"tolower($2)"_"tolower($3)"(priv->output, RAPI_SUCCESS, return_value";
	}
	else
	{
		printf "		ret = rapi_device_write_"tolower($2)"_"tolower($3)"(priv->output, RAPI_SUCCESS, return_value";
	}
	system("./gen_call_in_params.sh " $5);
	print ");";
	print "	}while(0);";
	print "";
	system("./gen_free_params.sh " $4);
	system("./gen_free_out_params.sh " $5);
	print "	return ret;";
	print "}"
	}' $CMD_DEF
	
	echo "AsmRet rapi_device_connection_session_"$LOWER_STURCT_NAME"_command_dispatch(AsmConnection* thiz, unsigned int cmd)"
	echo "{"
	echo "	AsmRet ret = ASM_RET_FAIL;";
	echo "	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);"
	echo ""
	echo "	switch(cmd)"
	echo "	{"
	awk -F: '{print "		case RAPI_COMMAND_" toupper($2) "_"toupper($3)":";
	print "		{";
	print "			ret = rapi_device_connection_session_handle_"tolower($3)"(thiz);";
	print "			break;"
	print "		}";
	}' $CMD_DEF
	echo "		default: ret = ASM_RET_UNHANDLED;break;"
	echo "	}"
	echo "	return ret;"
	echo "}"

	return;
}

function gen_device_dispatch_h()
{
	echo "#include <rapi_device_"$LOWER_STURCT_NAME".h>"
	echo "#include <rapi_device_connection_session.h>"
	echo ""
	gen_include_once_begin $DEVICE_DISPATCH_H
	echo ""
	echo "AsmRet rapi_device_connection_session_"$LOWER_STURCT_NAME"_command_dispatch(AsmConnection* thiz, unsigned int cmd);"
	echo ""
	gen_include_once_end $DEVICE_DISPATCH_H
}


function gen_device_files()
{
	gen_device_intf_h >$INTF_H
	gen_device_default_h >$DEVICE_DEFAULT_H
	gen_device_default_c >$DEVICE_DEFAULT_C

	gen_device_write_h >$DEVICE_WRITE_H
	gen_device_write_c >$DEVICE_WRITE_C

	gen_device_read_h >$DEVICE_READ_H
	gen_device_read_c >$DEVICE_READ_C

	gen_device_dispatch_h >$DEVICE_DISPATCH_H
	gen_device_dispatch_c >$DEVICE_DISPATCH_C
}

function gen_host_h()
{
	echo "#include <asm-common.h>"
	echo "#include <rapi_lib.h>"
	gen_include_once_begin $HOST_H

	echo ""
	echo "struct _RapiHost$STRUCT_NAME;"
	echo "typedef struct _RapiHost$STRUCT_NAME RapiHost$STRUCT_NAME;"
	echo ""
	
	echo "RapiHost$STRUCT_NAME""* rapi_host_"$LOWER_STURCT_NAME"_create(AsmStream* stream);"
	awk -F: '{
	params_types=$4" "$5;
	gsub(/, $/, "", params_types);
	if(length($4$5) > 0)
	{
		params_types=",\n\t"params_types;
	}
	print "AsmRet rapi_host_"tolower($2)"_"tolower($3)"(RapiHost"$2 "* thiz, unsigned int* last_error, unsigned int* return_value"params_types");" 
	}' $CMD_DEF
	echo "void rapi_host_"$LOWER_STURCT_NAME"_destroy(RapiHost$STRUCT_NAME""* thiz);"

	echo ""
	gen_include_once_end $HOST_H
	
	return;
}

function gen_host_c()
{
	echo "#include <$HOST_H>"

	echo struct _RapiHost$STRUCT_NAME
	echo {
	echo "	AsmStream* stream;"
	echo "	AsmInputBuffer* input;"
	echo "	AsmOutputBuffer* output;"
	echo "};"
	echo ""
	echo RapiHost$STRUCT_NAME* rapi_host_$LOWER_STURCT_NAME"_create(AsmStream* stream)"
	echo "{"
	echo "	RapiHost$STRUCT_NAME* thiz = (RapiHost$STRUCT_NAME*)ASM_ALLOC(RapiHost$STRUCT_NAME, 0);"
	echo "	thiz->stream = stream;"
	echo "	thiz->input = asm_input_buffer_create(NULL, 0, ASM_ENDIAN_LITTLE, NULL);"
	echo "	thiz->output = asm_output_buffer_create(1024, ASM_ENDIAN_LITTLE);"
	echo ""
	echo "	return thiz;"
	echo "}"
	echo ""
	awk -F: '{
	params_types=$4" "$5;
	gsub(/, $/, "", params_types);
	if(length($4$5) > 0)
	{
		params_types=",\n\t"params_types;
	}
	print "AsmRet rapi_host_"tolower($2)"_"tolower($3)"(RapiHost"$2 "* thiz, unsigned int* last_error, unsigned int* return_value"params_types")";
	print "{";
	print "	AsmRet ret = ASM_RET_FAIL;";
	print "	asm_return_val_if_fail(thiz != NULL, ret);";
	print "";
	print "	asm_output_buffer_reset(thiz->output);";
	print "";
	print "	do";
	print "	{";
	printf "		ret = rapi_host_write_"tolower($2)"_"tolower($3)"(thiz->output";
	system("./gen_call_in_params.sh " $4);
	print ");";
	print "		if(ret != ASM_RET_OK) break;";
	print "		ret = rapi_stream_write(thiz->stream, thiz->output);";
	print "		if(ret != ASM_RET_OK) break;";
	print "		ret = rapi_stream_read(thiz->stream, thiz->input);";
	print "		if(ret != ASM_RET_OK) break;";
	printf "		ret = rapi_host_read_"tolower($2)"_"tolower($3)"(thiz->input, last_error, return_value";
	system("./gen_call_in_params.sh " $5);
	print ");";
	print "	}while(0);";
	print "";
	print "	return ret;";
	print "}";
	print ""
	}' $CMD_DEF
	echo "void rapi_host_"$LOWER_STURCT_NAME"_destroy(RapiHost$STRUCT_NAME""* thiz)"
	echo "{"
	echo "	asm_input_buffer_destroy(thiz->input);"
	echo "	asm_output_buffer_destroy(thiz->output);"
	echo "	ASM_FREE(thiz);"
	echo ""
	echo "	return;"
	echo "}"
	echo ""
	
	return;
}

function gen_host_write_h()
{
	echo "#include <asm-output-buffer.h>"
	echo "#include <rapi_host_lib.h>"
	echo ""
	gen_include_once_begin $HOST_WRITE_H
	echo ""
	awk -F: '{
	params=$4; 
	gsub(/,$/, "", params); 
	printf "AsmRet rapi_host_write_" tolower($2)"_"tolower($3) "(AsmOutputBuffer* output";
	if(length(params) > 0)
	{
		printf ",\n\t" params;
	};
	print ");"
	}' $CMD_DEF
	echo ""
	gen_include_once_end $HOST_WRITE_H

	return;
}

function gen_host_write_c()
{
	echo "#include <$HOST_WRITE_H>"
	echo ""
	echo ""
	awk -F: '{
	params=$4; 
	gsub(/,$/, "", params); 
	printf "AsmRet rapi_host_write_" tolower($2)"_"tolower($3) "(AsmOutputBuffer* output";
	if(length(params) > 0)
	{
		printf ",\n\t" params;
	};
	print ")\n{\t";
	print "	AsmRet ret = ASM_RET_FAIL;"; 
	print "	asm_return_val_if_fail(output != NULL, ret);\n";
	print "	ret = asm_output_buffer_write_uint32(output, RAPI_COMMAND_" toupper($2) "_"toupper($3)");";
	system("./gen_host_write.sh " params);
	print "\n\treturn ret;\n}\n"
	}' $CMD_DEF
	echo ""

	return;
}

function gen_host_read_h()
{
	echo "#include <asm-input-buffer.h>"
	echo "#include <rapi_host_lib.h>"
	echo ""
	gen_include_once_begin $HOST_READ_H
	echo ""
	awk -F: '{
	params=$5;
	if(length($5) > 0)
	{
		params=", "params;
	}
	print "AsmRet rapi_host_read_" tolower($2)"_"tolower($3) "(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value";
	print "\t"params");";
	}' $CMD_DEF
	echo ""
	gen_include_once_end $HOST_READ_H

	return;
}

function gen_host_read_c()
{
	echo "#include <$HOST_READ_H>"
	echo ""
	awk -F: '{
	params=$5;
	if(length($5) > 0)
	{
		params=", "params;
	}
	print "AsmRet rapi_host_read_" tolower($2)"_"tolower($3) "(AsmInputBuffer* input, unsigned int* last_error, unsigned int* return_value";
	print "\t"params")";
	print "{"; \
	print "	AsmRet ret = ASM_RET_FAIL;";\
	print "	asm_return_val_if_fail(input != NULL, ret);\n";\
	print "	ret = asm_input_buffer_read_uint32(input, last_error);";
	print "	ret = asm_input_buffer_read_uint32(input, return_value);";
	system("./gen_host_read.sh " params); \
	print "\n\treturn ret;\n}\n"
	}' $CMD_DEF
	echo ""

	return;
}

function gen_host_files()
{
	gen_host_h >$HOST_H
	gen_host_c >$HOST_C
	gen_host_write_h>$HOST_WRITE_H
	gen_host_write_c>$HOST_WRITE_C

	gen_host_read_h>$HOST_READ_H
	gen_host_read_c>$HOST_READ_C

	return;
}


gen_common_def>$COMMON_DEF

gen_host_files
gen_device_files
