/*
 * File:    arm7_test.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   arm7 tester entry.
 *
 * Copyright (c) 2009  Li XianJing
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2009-1-25 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include <stdio.h>

extern void arm7_test(void);

int main(int argc, char* argv[])
{
	arm7_init(NULL);

	arm7_bf_test();
	arm7_b0_test();
	arm7_af_test();
	arm7_a0_test();
	arm7_51_test();
	arm7_49_test();
	arm7_59_test();
	arm7_79_test();
	arm7_45_test();
	arm7_4d_test();
	arm7_5d_test();
	arm7_5f_test();
	arm7_7d_test();
	arm7_48_test();
	arm7_4c_test();
	arm7_50_test();
	arm7_58_test();
	arm7_7c_test();
	arm7_test();

	return 0;


	arm7_test();
	arm7_79_test();
	arm7_51_test();
	arm7_59_test();
	arm7_5d_test();
	arm7_4d_test();
	arm7_5f_test();
	arm7_48_test();
	arm7_50_test();
	arm7_58_test();
	arm7_4c_test();
	arm7_5c_test();
	arm7_7c_test();
	arm7_7d_test();
	arm7_91_test();
	arm7_99_test();
	arm7_8b_test();
	arm7_89_test();
	arm7_8d_test();
	arm7_90_test();
	arm7_92_test();
	arm7_88_test();
	arm7_8c_test();
	arm7_8f_test();
	arm7_31_test();
	arm7_1e_test();
	arm7_3e_test();
	arm7_3f_test();
	arm7_1a_test();
	arm7_3a_test();
	arm7_1b_test();
	arm7_test();
	arm7_14_test();
	arm7_10_test();
	arm7_12_test();
	arm7_16_test();
	arm7_32_test();
	
	return 0;
}
