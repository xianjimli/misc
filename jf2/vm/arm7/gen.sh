#!/bin/bash
for f in arm7i*.c;do echo $f;done|awk -F_ '{print $3}'|sed -e 's/\.c//'>t.list

echo "#include <jmachine.h>"
echo "#include <jinstruction_arm7.h>"

echo ""
awk '{
	print "extern JRet arm7_"$1"_execute(JInstruction* thiz, jinst_t instr);"
	print "extern JRet arm7_"$1"_das(JInstruction* thiz, jinst_t instr, char* t);"
	print "extern JRet arm7_"$1"_as(JInstruction* thiz, const char* t, jinst_t* i);"
	print "extern void arm7_"$1"_test(void);\n"
}' t.list
echo 'JRet arm7_instruction_init(JMachine* m)'
echo '{'
echo '	JInstruction* instr = NULL;'
awk '{
	print "	instr = jinstruction_arm7_create(0x"$1"," 
	print "		arm7_"$1"_execute, arm7_"$1"_das, arm7_"$1"_as);"
	print "	jinstruction_init(instr, m);"
	print "	jmachine_reg_instruction(m, 0x"$1", instr);\n"
}' t.list

function gen_repeat()
{
	code=$1
	repeat_codes=$2

	for repeat_code in $repeat_codes
	do
		echo "	instr = jinstruction_arm7_create(0x$code," 
		echo "		arm7_"$code"_execute, arm7_"$code"_das, arm7_"$code"_as);"
		echo "	jinstruction_init(instr, m);"
		echo "	jmachine_reg_instruction(m, 0x$repeat_code, instr);"
		echo ""
	done
}

gen_repeat "bf" "b8 b9 ba bb bc bd be"
gen_repeat "b0" "b1 b2 b3 b4 b5 b6 b7"
gen_repeat "af" "a8 a9 aa ab ac ad ae"
gen_repeat "a0" "a1 a2 a3 a4 a4 a6 a7"

echo "	return JRET_OK;"
echo '}'

echo "void arm7_test(void)"
echo "{"
awk '{
	print "	arm7_"$1"_test();"
}' t.list
echo ""
echo "	return;"
echo "}"
