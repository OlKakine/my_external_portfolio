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
static const char *ng0 = "/user/1/.base/checchio/home/Documents/tp_archi/TP3/src_etd/vhd/lecture_memoire.vhd";
extern char *IEEE_P_1242562249;

char *ieee_p_1242562249_sub_3299428170688237929_1035706684(char *, char *, char *, char *, int );
char *ieee_p_1242562249_sub_3299657338228113225_1035706684(char *, char *, char *, char *, int );
unsigned char ieee_p_1242562249_sub_3307759752501503797_1035706684(char *, char *, char *, int );


static void work_a_0871606977_3271922888_p_0(char *t0)
{
    char t1[16];
    char t2[16];
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    unsigned char t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;

LAB0:    xsi_set_current_line(51, ng0);
    t3 = (t0 + 1512U);
    t4 = *((char **)t3);
    t3 = (t0 + 6064U);
    t5 = ieee_p_1242562249_sub_3299428170688237929_1035706684(IEEE_P_1242562249, t2, t4, t3, 3);
    t6 = ieee_p_1242562249_sub_3299657338228113225_1035706684(IEEE_P_1242562249, t1, t5, t2, 16);
    t7 = ieee_p_1242562249_sub_3307759752501503797_1035706684(IEEE_P_1242562249, t6, t1, 0);
    if (t7 != 0)
        goto LAB3;

LAB4:
LAB2:    t14 = (t0 + 3464);
    *((int *)t14) = 1;

LAB1:    return;
LAB3:    t8 = (t0 + 1672U);
    t9 = *((char **)t8);
    t8 = (t0 + 3544);
    t10 = (t8 + 56U);
    t11 = *((char **)t10);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    memcpy(t13, t9, 24U);
    xsi_driver_first_trans_fast_port(t8);
    goto LAB2;

}


extern void work_a_0871606977_3271922888_init()
{
	static char *pe[] = {(void *)work_a_0871606977_3271922888_p_0};
	xsi_register_didat("work_a_0871606977_3271922888", "isim/tb_lecture_memoire_isim_beh.exe.sim/work/a_0871606977_3271922888.didat");
	xsi_register_executes(pe);
}
