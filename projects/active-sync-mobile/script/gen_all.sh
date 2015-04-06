#!/bin/bash

DEF_FILES="Fileman.def  Procman.def  Registry.def  System.def"

function gen_host_wrapper_h()
{
	awk -F: '{
	params_types=$4" "$5;
	gsub(/, $/, "", params_types);
	if(length($4$5) > 0)
	{
		params_types=",\n\t"params_types;
	}
	print "AsmRet rapi_host_"tolower($3)"(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value"params_types");" 
	}' $1
}

function gen_host_wrapper_c()
{
	awk -F: '{
	params_types=$4" "$5;
	gsub(/, $/, "", params_types);
	if(length($4$5) > 0)
	{
		params_types=",\n\t"params_types;
	}
	print "AsmRet rapi_host_"tolower($3)"(RapiHost* thiz, unsigned int* last_error, unsigned int* return_value"params_types")";
	print "{";
	print "	asm_return_val_if_fail(thiz != NULL && thiz->"tolower($2)"!= NULL, ASM_RET_FAIL);"
	printf "	return rapi_host_"tolower($2)"_"tolower($3)"(thiz->"tolower($2)", last_error, return_value";
	system("./gen_call_in_params.sh " $4);
	system("./gen_call_in_params.sh " $5);
	print ");";
	print "}";
	print ""
	}' $1
}

rm -f *.h *.c

for f in $DEF_FILES
do
	gen_host_wrapper_h $f >>rapi_host_wrapper.h
	gen_host_wrapper_c $f >>rapi_host_wrapper.c
	./gen.sh "$f"
done

#rm -fv *default*

