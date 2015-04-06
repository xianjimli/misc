#include <jmachine.h>
#include <jinstruction_arm7.h>

extern JRet arm7_08_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_08_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_08_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_08_test(void);

extern JRet arm7_28_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_28_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_28_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_28_test(void);

extern JRet arm7_00_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_00_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_00_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_00_test(void);

extern JRet arm7_20_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_20_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_20_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_20_test(void);

extern JRet arm7_3c_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_3c_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_3c_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_3c_test(void);

extern JRet arm7_a0_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_a0_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_a0_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_a0_test(void);

extern JRet arm7_af_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_af_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_af_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_af_test(void);

extern JRet arm7_b0_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_b0_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_b0_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_b0_test(void);

extern JRet arm7_bf_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_bf_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_bf_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_bf_test(void);

extern JRet arm7_ee_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_ee_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_ee_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_ee_test(void);

extern JRet arm7_15_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_15_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_15_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_15_test(void);

extern JRet arm7_35_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_35_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_35_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_35_test(void);

extern JRet arm7_91_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_91_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_91_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_91_test(void);

extern JRet arm7_89_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_89_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_89_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_89_test(void);

extern JRet arm7_8b_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_8b_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_8b_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_8b_test(void);

extern JRet arm7_8d_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_8d_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_8d_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_8d_test(void);

extern JRet arm7_8f_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_8f_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_8f_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_8f_test(void);

extern JRet arm7_99_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_99_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_99_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_99_test(void);

extern JRet arm7_49_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_49_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_49_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_49_test(void);

extern JRet arm7_51_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_51_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_51_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_51_test(void);

extern JRet arm7_59_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_59_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_59_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_59_test(void);

extern JRet arm7_79_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_79_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_79_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_79_test(void);

extern JRet arm7_45_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_45_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_45_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_45_test(void);

extern JRet arm7_4d_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_4d_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_4d_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_4d_test(void);

extern JRet arm7_5d_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_5d_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_5d_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_5d_test(void);

extern JRet arm7_5f_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_5f_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_5f_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_5f_test(void);

extern JRet arm7_7d_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_7d_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_7d_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_7d_test(void);

extern JRet arm7_1a_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_1a_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_1a_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_1a_test(void);

extern JRet arm7_3a_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_3a_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_3a_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_3a_test(void);

extern JRet arm7_1b_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_1b_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_1b_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_1b_test(void);

extern JRet arm7_10_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_10_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_10_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_10_test(void);

extern JRet arm7_14_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_14_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_14_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_14_test(void);

extern JRet arm7_12_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_12_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_12_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_12_test(void);

extern JRet arm7_16_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_16_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_16_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_16_test(void);

extern JRet arm7_32_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_32_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_32_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_32_test(void);

extern JRet arm7_1e_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_1e_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_1e_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_1e_test(void);

extern JRet arm7_3e_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_3e_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_3e_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_3e_test(void);

extern JRet arm7_3f_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_3f_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_3f_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_3f_test(void);

extern JRet arm7_18_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_18_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_18_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_18_test(void);

extern JRet arm7_38_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_38_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_38_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_38_test(void);

extern JRet arm7_06_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_06_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_06_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_06_test(void);

extern JRet arm7_26_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_26_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_26_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_26_test(void);

extern JRet arm7_cc_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_cc_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_cc_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_cc_test(void);

extern JRet arm7_90_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_90_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_90_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_90_test(void);

extern JRet arm7_92_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_92_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_92_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_92_test(void);

extern JRet arm7_88_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_88_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_88_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_88_test(void);

extern JRet arm7_8c_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_8c_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_8c_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_8c_test(void);

extern JRet arm7_48_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_48_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_48_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_48_test(void);

extern JRet arm7_50_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_50_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_50_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_50_test(void);

extern JRet arm7_58_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_58_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_58_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_58_test(void);

extern JRet arm7_4c_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_4c_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_4c_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_4c_test(void);

extern JRet arm7_5c_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_5c_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_5c_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_5c_test(void);

extern JRet arm7_7c_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_7c_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_7c_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_7c_test(void);

extern JRet arm7_04_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_04_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_04_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_04_test(void);

extern JRet arm7_24_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_24_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_24_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_24_test(void);

extern JRet arm7_25_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_25_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_25_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_25_test(void);

extern JRet arm7_f0_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_f0_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_f0_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_f0_test(void);

extern JRet arm7_11_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_11_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_11_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_11_test(void);

extern JRet arm7_31_execute(JInstruction* thiz, jinst_t instr);
extern JRet arm7_31_das(JInstruction* thiz, jinst_t instr, char* t);
extern JRet arm7_31_as(JInstruction* thiz, const char* t, jinst_t* i);
extern void arm7_31_test(void);

JRet arm7_instruction_init(JMachine* m)
{
	JInstruction* instr = NULL;
	instr = jinstruction_arm7_create(0x08,
		arm7_08_execute, arm7_08_das, arm7_08_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x08, instr);

	instr = jinstruction_arm7_create(0x28,
		arm7_28_execute, arm7_28_das, arm7_28_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x28, instr);

	instr = jinstruction_arm7_create(0x00,
		arm7_00_execute, arm7_00_das, arm7_00_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x00, instr);

	instr = jinstruction_arm7_create(0x20,
		arm7_20_execute, arm7_20_das, arm7_20_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x20, instr);

	instr = jinstruction_arm7_create(0x3c,
		arm7_3c_execute, arm7_3c_das, arm7_3c_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x3c, instr);

	instr = jinstruction_arm7_create(0xa0,
		arm7_a0_execute, arm7_a0_das, arm7_a0_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0xa0, instr);

	instr = jinstruction_arm7_create(0xaf,
		arm7_af_execute, arm7_af_das, arm7_af_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0xaf, instr);

	instr = jinstruction_arm7_create(0xb0,
		arm7_b0_execute, arm7_b0_das, arm7_b0_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0xb0, instr);

	instr = jinstruction_arm7_create(0xbf,
		arm7_bf_execute, arm7_bf_das, arm7_bf_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0xbf, instr);

	instr = jinstruction_arm7_create(0xee,
		arm7_ee_execute, arm7_ee_das, arm7_ee_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0xee, instr);

	instr = jinstruction_arm7_create(0x15,
		arm7_15_execute, arm7_15_das, arm7_15_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x15, instr);

	instr = jinstruction_arm7_create(0x35,
		arm7_35_execute, arm7_35_das, arm7_35_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x35, instr);

	instr = jinstruction_arm7_create(0x91,
		arm7_91_execute, arm7_91_das, arm7_91_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x91, instr);

	instr = jinstruction_arm7_create(0x89,
		arm7_89_execute, arm7_89_das, arm7_89_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x89, instr);

	instr = jinstruction_arm7_create(0x8b,
		arm7_8b_execute, arm7_8b_das, arm7_8b_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x8b, instr);

	instr = jinstruction_arm7_create(0x8d,
		arm7_8d_execute, arm7_8d_das, arm7_8d_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x8d, instr);

	instr = jinstruction_arm7_create(0x8f,
		arm7_8f_execute, arm7_8f_das, arm7_8f_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x8f, instr);

	instr = jinstruction_arm7_create(0x99,
		arm7_99_execute, arm7_99_das, arm7_99_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x99, instr);

	instr = jinstruction_arm7_create(0x49,
		arm7_49_execute, arm7_49_das, arm7_49_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x49, instr);

	instr = jinstruction_arm7_create(0x51,
		arm7_51_execute, arm7_51_das, arm7_51_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x51, instr);

	instr = jinstruction_arm7_create(0x59,
		arm7_59_execute, arm7_59_das, arm7_59_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x59, instr);

	instr = jinstruction_arm7_create(0x79,
		arm7_79_execute, arm7_79_das, arm7_79_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x79, instr);

	instr = jinstruction_arm7_create(0x45,
		arm7_45_execute, arm7_45_das, arm7_45_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x45, instr);

	instr = jinstruction_arm7_create(0x4d,
		arm7_4d_execute, arm7_4d_das, arm7_4d_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x4d, instr);

	instr = jinstruction_arm7_create(0x5d,
		arm7_5d_execute, arm7_5d_das, arm7_5d_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x5d, instr);

	instr = jinstruction_arm7_create(0x5f,
		arm7_5f_execute, arm7_5f_das, arm7_5f_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x5f, instr);

	instr = jinstruction_arm7_create(0x7d,
		arm7_7d_execute, arm7_7d_das, arm7_7d_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x7d, instr);

	instr = jinstruction_arm7_create(0x1a,
		arm7_1a_execute, arm7_1a_das, arm7_1a_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x1a, instr);

	instr = jinstruction_arm7_create(0x3a,
		arm7_3a_execute, arm7_3a_das, arm7_3a_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x3a, instr);

	instr = jinstruction_arm7_create(0x1b,
		arm7_1b_execute, arm7_1b_das, arm7_1b_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x1b, instr);

	instr = jinstruction_arm7_create(0x10,
		arm7_10_execute, arm7_10_das, arm7_10_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x10, instr);

	instr = jinstruction_arm7_create(0x14,
		arm7_14_execute, arm7_14_das, arm7_14_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x14, instr);

	instr = jinstruction_arm7_create(0x12,
		arm7_12_execute, arm7_12_das, arm7_12_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x12, instr);

	instr = jinstruction_arm7_create(0x16,
		arm7_16_execute, arm7_16_das, arm7_16_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x16, instr);

	instr = jinstruction_arm7_create(0x32,
		arm7_32_execute, arm7_32_das, arm7_32_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x32, instr);

	instr = jinstruction_arm7_create(0x1e,
		arm7_1e_execute, arm7_1e_das, arm7_1e_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x1e, instr);

	instr = jinstruction_arm7_create(0x3e,
		arm7_3e_execute, arm7_3e_das, arm7_3e_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x3e, instr);

	instr = jinstruction_arm7_create(0x3f,
		arm7_3f_execute, arm7_3f_das, arm7_3f_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x3f, instr);

	instr = jinstruction_arm7_create(0x18,
		arm7_18_execute, arm7_18_das, arm7_18_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x18, instr);

	instr = jinstruction_arm7_create(0x38,
		arm7_38_execute, arm7_38_das, arm7_38_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x38, instr);

	instr = jinstruction_arm7_create(0x06,
		arm7_06_execute, arm7_06_das, arm7_06_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x06, instr);

	instr = jinstruction_arm7_create(0x26,
		arm7_26_execute, arm7_26_das, arm7_26_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x26, instr);

	instr = jinstruction_arm7_create(0xcc,
		arm7_cc_execute, arm7_cc_das, arm7_cc_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0xcc, instr);

	instr = jinstruction_arm7_create(0x90,
		arm7_90_execute, arm7_90_das, arm7_90_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x90, instr);

	instr = jinstruction_arm7_create(0x92,
		arm7_92_execute, arm7_92_das, arm7_92_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x92, instr);

	instr = jinstruction_arm7_create(0x88,
		arm7_88_execute, arm7_88_das, arm7_88_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x88, instr);

	instr = jinstruction_arm7_create(0x8c,
		arm7_8c_execute, arm7_8c_das, arm7_8c_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x8c, instr);

	instr = jinstruction_arm7_create(0x48,
		arm7_48_execute, arm7_48_das, arm7_48_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x48, instr);

	instr = jinstruction_arm7_create(0x50,
		arm7_50_execute, arm7_50_das, arm7_50_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x50, instr);

	instr = jinstruction_arm7_create(0x58,
		arm7_58_execute, arm7_58_das, arm7_58_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x58, instr);

	instr = jinstruction_arm7_create(0x4c,
		arm7_4c_execute, arm7_4c_das, arm7_4c_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x4c, instr);

	instr = jinstruction_arm7_create(0x5c,
		arm7_5c_execute, arm7_5c_das, arm7_5c_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x5c, instr);

	instr = jinstruction_arm7_create(0x7c,
		arm7_7c_execute, arm7_7c_das, arm7_7c_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x7c, instr);

	instr = jinstruction_arm7_create(0x04,
		arm7_04_execute, arm7_04_das, arm7_04_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x04, instr);

	instr = jinstruction_arm7_create(0x24,
		arm7_24_execute, arm7_24_das, arm7_24_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x24, instr);

	instr = jinstruction_arm7_create(0x25,
		arm7_25_execute, arm7_25_das, arm7_25_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x25, instr);

	instr = jinstruction_arm7_create(0xf0,
		arm7_f0_execute, arm7_f0_das, arm7_f0_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0xf0, instr);

	instr = jinstruction_arm7_create(0x11,
		arm7_11_execute, arm7_11_das, arm7_11_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x11, instr);

	instr = jinstruction_arm7_create(0x31,
		arm7_31_execute, arm7_31_das, arm7_31_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0x31, instr);

	instr = jinstruction_arm7_create(0xbf,,
		arm7_bf,_execute, arm7_bf,_das, arm7_bf,_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0xb8, instr);

	instr = jinstruction_arm7_create(0xbf,,
		arm7_bf,_execute, arm7_bf,_das, arm7_bf,_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0xb9, instr);

	instr = jinstruction_arm7_create(0xbf,,
		arm7_bf,_execute, arm7_bf,_das, arm7_bf,_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0xba, instr);

	instr = jinstruction_arm7_create(0xbf,,
		arm7_bf,_execute, arm7_bf,_das, arm7_bf,_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0xbb, instr);

	instr = jinstruction_arm7_create(0xbf,,
		arm7_bf,_execute, arm7_bf,_das, arm7_bf,_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0xbc, instr);

	instr = jinstruction_arm7_create(0xbf,,
		arm7_bf,_execute, arm7_bf,_das, arm7_bf,_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0xbd, instr);

	instr = jinstruction_arm7_create(0xbf,,
		arm7_bf,_execute, arm7_bf,_das, arm7_bf,_as);
	jinstruction_init(instr, m);
	jmachine_reg_instruction(m, 0xbe, instr);

	return JRET_OK;
}
void arm7_test(void)
{
	arm7_08_test();
	arm7_28_test();
	arm7_00_test();
	arm7_20_test();
	arm7_3c_test();
	arm7_a0_test();
	arm7_af_test();
	arm7_b0_test();
	arm7_bf_test();
	arm7_ee_test();
	arm7_15_test();
	arm7_35_test();
	arm7_91_test();
	arm7_89_test();
	arm7_8b_test();
	arm7_8d_test();
	arm7_8f_test();
	arm7_99_test();
	arm7_49_test();
	arm7_51_test();
	arm7_59_test();
	arm7_79_test();
	arm7_45_test();
	arm7_4d_test();
	arm7_5d_test();
	arm7_5f_test();
	arm7_7d_test();
	arm7_1a_test();
	arm7_3a_test();
	arm7_1b_test();
	arm7_10_test();
	arm7_14_test();
	arm7_12_test();
	arm7_16_test();
	arm7_32_test();
	arm7_1e_test();
	arm7_3e_test();
	arm7_3f_test();
	arm7_18_test();
	arm7_38_test();
	arm7_06_test();
	arm7_26_test();
	arm7_cc_test();
	arm7_90_test();
	arm7_92_test();
	arm7_88_test();
	arm7_8c_test();
	arm7_48_test();
	arm7_50_test();
	arm7_58_test();
	arm7_4c_test();
	arm7_5c_test();
	arm7_7c_test();
	arm7_04_test();
	arm7_24_test();
	arm7_25_test();
	arm7_f0_test();
	arm7_11_test();
	arm7_31_test();

	return;
}
