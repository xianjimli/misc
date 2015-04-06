INCLUDES=-I$(top_srcdir)/common -I$(top_srcdir)/vm

noinst_PROGRAMS=arm7_test arm7_nv_test

arm7_test_SOURCES=jinstruction_arm7.c
arm7_test_CFLAGS=-DARM7_TEST

arm7_nv_test_SOURCES=arm7_nv.c
arm7_nv_test_CFLAGS=-DARM7_NV_TEST

lib_LTLIBRARIES=libvm-arm7.la
libvm_arm7_la_SOURCES=arm7_nv.c arm7_memory.c\
	arm7_cond.c arm7i_and_00.c \
	arm7i_mov_1a.c\
	arm7i_stmdb_92.c \
	arm7i_sub_04.c \
	arm7i_sub_24.c \
	arm7i_str_50.c \
	arm7i_ldr_51.c \
	arm7i_add_08.c \
	arm7i_ldmia_89.c \
	arm7i_rsb_06.c \
	arm7i_rsb_26.c \
	arm7i_ldr_59.c \
	arm7i_ldr_49.c \
	arm7i_bl_b0.c \
	arm7i_bl_bf.c \
	arm7i_mov_3a.c \
	arm7i_msr_32.c \
	arm7i_add_28.c \
	arm7i_cmp_35.c \
	arm7i_mrs_14.c \
	arm7i_mrs_10.c \
	arm7i_bic_3c.c \
	arm7i_orr_38.c \
	arm7i_msr_12.c \
	arm7i_mvn_3e.c \
	arm7i_str_58.c \
	arm7i_bl_a0.c \
	arm7i_bl_af.c \
	arm7i_svc_f0.c \
	arm7i_stmia_88.c \
	arm7i_ldmia_8f.c \
	arm7i_ldmia_8b.c \
	arm7i_msr_16.c \
	arm7i_ldr_79.c \
	arm7i_stmia_8c.c \
	arm7i_stmdb_90.c \
	arm7i_ldmdb_91.c \
	arm7i_ldmia_8d.c \
	arm7i_movs_1b.c \
	arm7i_cmp_15.c \
	arm7i_ldmib_99.c \
	arm7i_ldrb_5d.c \
	arm7i_mvn_3f.c \
	arm7i_tst_11.c \
	arm7i_tst_31.c \
	arm7i_orr_18.c \
	arm7i_mvn_1e.c \
	arm7i_and_20.c \
	arm7i_subs_25.c \
	arm7i_strb_5c.c \
	arm7i_strb_7c.c \
	arm7i_ldrb_7d.c \
	arm7i_strb_4c.c \
	arm7i_stc_cc.c \
	arm7i_ldrb_4d.c \
	arm7i_ldrb_45.c \
	arm7i_str_48.c \
	arm7i_ldrb_5f.c \
	arm7i_cdp_ee.c \
	arm7i_mull_0c.c \
	arm7i_strb_54.c \
	jinstruction_arm7.c

EXTRA_DIST=arm7_macro.h  arm7_memory.h  arm7_nv.h  jinstruction_arm7.h
