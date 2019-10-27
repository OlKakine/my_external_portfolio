/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0xfbc00daa */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "/user/1/.base/checchio/home/Documents/tp_archi/TP2/src_etd/vhd/tb_auto.vhd";
extern char *IEEE_P_2592010699;

unsigned char ieee_p_2592010699_sub_374109322130769762_503743352(char *, unsigned char );


static void work_a_1694615067_3212880686_p_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    int t5;
    int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned char t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    char *t15;
    int64 t16;
    int64 t17;
    unsigned char t18;
    unsigned char t19;

LAB0:    t1 = (t0 + 3144U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(44, ng0);
    t2 = (t0 + 1928U);
    t3 = *((char **)t2);
    t2 = (t0 + 2168U);
    t4 = *((char **)t2);
    t5 = *((int *)t4);
    t6 = (t5 - 0);
    t7 = (t6 * 1);
    xsi_vhdl_check_range_of_index(0, 31, 1, t5);
    t8 = (1U * t7);
    t9 = (0 + t8);
    t2 = (t3 + t9);
    t10 = *((unsigned char *)t2);
    t11 = (t0 + 3776);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    *((unsigned char *)t15) = t10;
    xsi_driver_first_trans_fast(t11);
    xsi_set_current_line(45, ng0);
    t2 = (t0 + 1808U);
    t3 = *((char **)t2);
    t16 = *((int64 *)t3);
    t17 = (t16 / 2);
    t2 = (t0 + 2952);
    xsi_process_wait(t2, t17);

LAB6:    *((char **)t1) = &&LAB7;

LAB1:    return;
LAB4:    xsi_set_current_line(46, ng0);
    t2 = (t0 + 1032U);
    t3 = *((char **)t2);
    t10 = *((unsigned char *)t3);
    t18 = ieee_p_2592010699_sub_374109322130769762_503743352(IEEE_P_2592010699, t10);
    t2 = (t0 + 3840);
    t4 = (t2 + 56U);
    t11 = *((char **)t4);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    *((unsigned char *)t13) = t18;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(47, ng0);
    t2 = (t0 + 1808U);
    t3 = *((char **)t2);
    t16 = *((int64 *)t3);
    t17 = (t16 / 2);
    t2 = (t0 + 2952);
    xsi_process_wait(t2, t17);

LAB10:    *((char **)t1) = &&LAB11;
    goto LAB1;

LAB5:    goto LAB4;

LAB7:    goto LAB5;

LAB8:    xsi_set_current_line(48, ng0);
    t2 = (t0 + 1032U);
    t3 = *((char **)t2);
    t10 = *((unsigned char *)t3);
    t18 = ieee_p_2592010699_sub_374109322130769762_503743352(IEEE_P_2592010699, t10);
    t2 = (t0 + 3840);
    t4 = (t2 + 56U);
    t11 = *((char **)t4);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    *((unsigned char *)t13) = t18;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(50, ng0);
    t2 = (t0 + 1512U);
    t3 = *((char **)t2);
    t10 = *((unsigned char *)t3);
    t2 = (t0 + 2048U);
    t4 = *((char **)t2);
    t2 = (t0 + 2168U);
    t11 = *((char **)t2);
    t5 = *((int *)t11);
    t6 = (t5 - 0);
    t7 = (t6 * 1);
    xsi_vhdl_check_range_of_index(0, 31, 1, t5);
    t8 = (1U * t7);
    t9 = (0 + t8);
    t2 = (t4 + t9);
    t18 = *((unsigned char *)t2);
    t19 = (t10 == t18);
    if (t19 == 0)
        goto LAB12;

LAB13:    xsi_set_current_line(51, ng0);
    t2 = (t0 + 2168U);
    t3 = *((char **)t2);
    t5 = *((int *)t3);
    t6 = (t5 + 1);
    t2 = (t0 + 2168U);
    t4 = *((char **)t2);
    t2 = (t4 + 0);
    *((int *)t2) = t6;
    xsi_set_current_line(52, ng0);
    t2 = (t0 + 2168U);
    t3 = *((char **)t2);
    t5 = *((int *)t3);
    t10 = (t5 < 32);
    if (t10 == 0)
        goto LAB14;

LAB15:    goto LAB2;

LAB9:    goto LAB8;

LAB11:    goto LAB9;

LAB12:    t12 = (t0 + 6720);
    xsi_report(t12, 49U, (unsigned char)2);
    goto LAB13;

LAB14:    t2 = (t0 + 6769);
    xsi_report(t2, 20U, (unsigned char)3);
    goto LAB15;

}

static void work_a_1694615067_3212880686_p_1(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    int64 t7;

LAB0:    t1 = (t0 + 3392U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(57, ng0);
    t2 = (t0 + 3904);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(58, ng0);
    t2 = (t0 + 1808U);
    t3 = *((char **)t2);
    t7 = *((int64 *)t3);
    t2 = (t0 + 3200);
    xsi_process_wait(t2, t7);

LAB6:    *((char **)t1) = &&LAB7;

LAB1:    return;
LAB4:    xsi_set_current_line(59, ng0);
    t2 = (t0 + 3904);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(60, ng0);

LAB10:    *((char **)t1) = &&LAB11;
    goto LAB1;

LAB5:    goto LAB4;

LAB7:    goto LAB5;

LAB8:    goto LAB2;

LAB9:    goto LAB8;

LAB11:    goto LAB9;

}


extern void work_a_1694615067_3212880686_init()
{
	static char *pe[] = {(void *)work_a_1694615067_3212880686_p_0,(void *)work_a_1694615067_3212880686_p_1};
	xsi_register_didat("work_a_1694615067_3212880686", "isim/tb_auto_isim_beh.exe.sim/work/a_1694615067_3212880686.didat");
	xsi_register_executes(pe);
}
