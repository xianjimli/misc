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
export INTF_H="asm_"$FILENAME".h"
export DEFAULT_H="asm_"$FILENAME"_default.h"
export DEFAULT_C="asm_"$FILENAME"_default.c"
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

function gen_intf_h()
{
	echo "#include <asm-common.h>"
	echo "#include <rapi_lib.h>"
	gen_include_once_begin $INTF_H

	echo ""
	echo "struct _Asm$STRUCT_NAME;"
	echo "typedef struct _Asm$STRUCT_NAME Asm$STRUCT_NAME;"
	echo ""

	awk -F: '{name=$3; 
	gsub(/_/, "", name); 
	params_types=$4" "$5;
	gsub(/, $/, "", params_types);
	if(length($4$5) > 0)
	{
		params_types=", "params_types;
	}
	print "typedef AsmRet (*Asm" $2 name"Func)(" "Asm"$2 "* thiz"params_types");" }' $CMD_DEF

	echo ""
	echo "typedef void (*Asm"$STRUCT_NAME"DestroyFunc)(Asm"$STRUCT_NAME"* thiz);"

	echo ""
	echo "struct _Asm$STRUCT_NAME"
	echo "{"
	awk -F: '{name=$3; gsub(/_/, "", name); print "\tAsm"$2 name"Func " tolower($3) ";" }' $CMD_DEF

	echo "	Asm"$STRUCT_NAME"DestroyFunc destroy;"
	echo "	char priv[0];"
	echo "};"
	echo ""
	awk -F: '{name=$3; gsub(/_/, "", name); \
	params=$4$5; \
	gsub(/WStr\*|RKEY\*|RKEY|unsigned int\*|unsigned int|void\*|RapiProcessInfo\*|RapiStoreInfo\*|RapiSystemInfo\*|RapiSystemPowerStatus\*|RapiVersionInfo\*|WStr\*\*|void\*\*|RapiProcessInfo\*\*|RapiStoreInfo\*\*|RapiSystemInfo\*\*|RapiSystemPowerStatus\*\*|RapiVersionInfo\*\*|RapiFileTime\*|RapiFileTime\*\*|HookProgressFunc/, "", params);\
	gsub(/,$/, "", params);\
	params_types=$4" "$5;
	gsub(/, $/, "", params_types);\
	if(length($4$5) > 0)
	{
		params_types=", "params_types;
		params=", "params;
	}
	print "static inline AsmRet asm_" tolower($2)"_"tolower($3) "(Asm"$2 "* thiz" params_types ")\n{\n\tasm_return_val_if_fail(thiz != NULL && thiz->" tolower($3) " != NULL, ASM_RET_FAIL);\n\n\treturn thiz->" tolower($3) "(thiz"params");\n}\n"}' $CMD_DEF

	echo -n "static inline void asm_"
	echo -n $STRUCT_NAME|tr A-Z a-z
	echo "_destroy(Asm"$STRUCT_NAME"* thiz)"
	echo "{"
	echo "	asm_return_if_fail(thiz != NULL && thiz->destroy != NULL);"
	echo "	thiz->destroy(thiz);"
	echo ""
	echo "	return;"
	echo "}"
	gen_include_once_end $INTF_H
	
	return;
}

function gen_default_h()
{
	echo "#include <$INTF_H>"
	echo ""
	gen_include_once_begin $DEFAULT_H
	echo ""
	echo -n "Asm"$STRUCT_NAME"* asm_"
	echo -n $STRUCT_NAME|tr A-Z a-z
	echo "_default_create(void);"
	echo ""

	gen_include_once_end $DEFAULT_H
	
	return;
}

function gen_default_c()
{
	echo "#include <$DEFAULT_H>"
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
	print "static AsmRet asm_" tolower($2)"_default_"tolower($3) "(Asm"$2 "* thiz" params_types ")\n{\n\tasm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);\n\tPrivInfo* priv = (PrivInfo*)thiz->priv;\n\n\treturn ASM_RET_OK;\n}\n"}' $CMD_DEF

	echo "void asm_$LOWER_STURCT_NAME""_default_destroy(Asm$STRUCT_NAME* thiz)"
	echo "{"
	echo "	ASM_FREE(thiz);"
	echo ""
	echo "	return;"
	echo "}"
	echo ""
	echo -n "Asm"$STRUCT_NAME"* asm_"
	echo -n $STRUCT_NAME|tr A-Z a-z
	echo "_default_create(void)"
	echo "{"
	echo "	Asm"$STRUCT_NAME"* thiz = (Asm"$STRUCT_NAME"*)ASM_ALLOC(Asm"$STRUCT_NAME", sizeof(PrivInfo));"

	awk -F: '{name=$3; gsub(/_/, "", name); \
	print "	thiz->"tolower($3)" = asm_" tolower($2)"_default_"tolower($3)";";}' $CMD_DEF
	echo "	thiz->destroy = asm_$LOWER_STURCT_NAME""_default_destroy;";
	echo ""
	echo "	return thiz;"
	echo "}"
	echo ""
}
gen_intf_h >$INTF_H
gen_default_h>$DEFAULT_H
gen_default_c>$DEFAULT_C

