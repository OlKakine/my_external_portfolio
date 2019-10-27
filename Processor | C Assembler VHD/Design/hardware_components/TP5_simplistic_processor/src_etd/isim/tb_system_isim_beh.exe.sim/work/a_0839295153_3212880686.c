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
static const char *ng0 = "/user/1/.base/checchio/home/Documents/tp_archi/TP5/src_etd/vhd/periph.vhd";
extern char *IEEE_P_2592010699;
extern char *IEEE_P_1242562249;

char *ieee_p_1242562249_sub_1006216973935652998_1035706684(char *, char *, char *, char *, int );
unsigned char ieee_p_1242562249_sub_1434214030532753770_1035706684(char *, char *, char *, char *, char *);
unsigned char ieee_p_1242562249_sub_1434214030532789707_1035706684(char *, char *, char *, char *, char *);
unsigned char ieee_p_2592010699_sub_3488546069778340532_503743352(char *, unsigned char , unsigned char );
unsigned char ieee_p_2592010699_sub_3488768496604610246_503743352(char *, unsigned char , unsigned char );
unsigned char ieee_p_2592010699_sub_3488768497115059394_503743352(char *, unsigned char , unsigned char );
unsigned char ieee_p_2592010699_sub_3496108598716332692_503743352(char *, unsigned char , unsigned char );
unsigned char ieee_p_2592010699_sub_374109322130769762_503743352(char *, unsigned char );


static void work_a_0839295153_3212880686_p_0(char *t0)
{
    char t72[16];
    char t73[16];
    char *t1;
    char *t2;
    unsigned char t3;
    unsigned char t4;
    char *t5;
    unsigned char t6;
    unsigned char t7;
    char *t8;
    int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned char t13;
    char *t14;
    char *t15;
    int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned char t20;
    unsigned char t21;
    unsigned char t22;
    char *t23;
    char *t24;
    int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned char t29;
    char *t30;
    char *t31;
    int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned char t36;
    unsigned char t37;
    unsigned char t38;
    unsigned char t39;
    char *t40;
    char *t41;
    int t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    unsigned char t46;
    char *t47;
    char *t48;
    int t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    unsigned char t53;
    unsigned char t54;
    unsigned char t55;
    char *t56;
    char *t57;
    int t59;
    char *t60;
    int t62;
    char *t63;
    int t65;
    char *t66;
    char *t67;
    char *t68;
    char *t69;
    char *t70;
    char *t71;

LAB0:    xsi_set_current_line(42, ng0);
    t1 = (t0 + 1352U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = ieee_p_2592010699_sub_374109322130769762_503743352(IEEE_P_2592010699, t3);
    t1 = (t0 + 1192U);
    t5 = *((char **)t1);
    t6 = *((unsigned char *)t5);
    t7 = ieee_p_2592010699_sub_3488768496604610246_503743352(IEEE_P_2592010699, t4, t6);
    t1 = (t0 + 1672U);
    t8 = *((char **)t1);
    t9 = (15 - 15);
    t10 = (t9 * -1);
    t11 = (1U * t10);
    t12 = (0 + t11);
    t1 = (t8 + t12);
    t13 = *((unsigned char *)t1);
    t14 = (t0 + 1672U);
    t15 = *((char **)t14);
    t16 = (13 - 15);
    t17 = (t16 * -1);
    t18 = (1U * t17);
    t19 = (0 + t18);
    t14 = (t15 + t19);
    t20 = *((unsigned char *)t14);
    t21 = ieee_p_2592010699_sub_3488768497115059394_503743352(IEEE_P_2592010699, t13, t20);
    t22 = ieee_p_2592010699_sub_3488768496604610246_503743352(IEEE_P_2592010699, t7, t21);
    t23 = (t0 + 1672U);
    t24 = *((char **)t23);
    t25 = (14 - 15);
    t26 = (t25 * -1);
    t27 = (1U * t26);
    t28 = (0 + t27);
    t23 = (t24 + t28);
    t29 = *((unsigned char *)t23);
    t30 = (t0 + 1672U);
    t31 = *((char **)t30);
    t32 = (12 - 15);
    t33 = (t32 * -1);
    t34 = (1U * t33);
    t35 = (0 + t34);
    t30 = (t31 + t35);
    t36 = *((unsigned char *)t30);
    t37 = ieee_p_2592010699_sub_3496108598716332692_503743352(IEEE_P_2592010699, t29, t36);
    t38 = ieee_p_2592010699_sub_3488768496604610246_503743352(IEEE_P_2592010699, t22, t37);
    t39 = (t38 == (unsigned char)3);
    if (t39 != 0)
        goto LAB2;

LAB4:    xsi_set_current_line(54, ng0);
    t1 = xsi_get_transient_memory(8U);
    memset(t1, 0, 8U);
    t2 = t1;
    memset(t2, (unsigned char)2, 8U);
    t5 = (t0 + 6888);
    t8 = (t5 + 56U);
    t14 = *((char **)t8);
    t15 = (t14 + 56U);
    t23 = *((char **)t15);
    memcpy(t23, t1, 8U);
    xsi_driver_first_trans_fast_port(t5);

LAB3:    t1 = (t0 + 6712);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(43, ng0);
    t40 = (t0 + 1672U);
    t41 = *((char **)t40);
    t42 = (14 - 15);
    t43 = (t42 * -1);
    t44 = (1U * t43);
    t45 = (0 + t44);
    t40 = (t41 + t45);
    t46 = *((unsigned char *)t40);
    t47 = (t0 + 1672U);
    t48 = *((char **)t47);
    t49 = (12 - 15);
    t50 = (t49 * -1);
    t51 = (1U * t50);
    t52 = (0 + t51);
    t47 = (t48 + t52);
    t53 = *((unsigned char *)t47);
    t54 = ieee_p_2592010699_sub_3488546069778340532_503743352(IEEE_P_2592010699, t46, t53);
    t55 = (t54 == (unsigned char)2);
    if (t55 != 0)
        goto LAB5;

LAB7:    xsi_set_current_line(51, ng0);
    t1 = (t0 + 3272U);
    t2 = *((char **)t1);
    t1 = (t0 + 6888);
    t5 = (t1 + 56U);
    t8 = *((char **)t5);
    t14 = (t8 + 56U);
    t15 = *((char **)t14);
    memcpy(t15, t2, 8U);
    xsi_driver_first_trans_fast_port(t1);

LAB6:    goto LAB3;

LAB5:    xsi_set_current_line(44, ng0);
    t56 = (t0 + 1672U);
    t57 = *((char **)t56);
    t56 = (t0 + 11439);
    t59 = xsi_mem_cmp(t56, t57, 16U);
    if (t59 == 1)
        goto LAB9;

LAB13:    t60 = (t0 + 11455);
    t62 = xsi_mem_cmp(t60, t57, 16U);
    if (t62 == 1)
        goto LAB10;

LAB14:    t63 = (t0 + 11471);
    t65 = xsi_mem_cmp(t63, t57, 16U);
    if (t65 == 1)
        goto LAB11;

LAB15:
LAB12:    xsi_set_current_line(48, ng0);
    t1 = xsi_get_transient_memory(8U);
    memset(t1, 0, 8U);
    t2 = t1;
    memset(t2, (unsigned char)2, 8U);
    t5 = (t0 + 6888);
    t8 = (t5 + 56U);
    t14 = *((char **)t8);
    t15 = (t14 + 56U);
    t23 = *((char **)t15);
    memcpy(t23, t1, 8U);
    xsi_driver_first_trans_fast_port(t5);

LAB8:    goto LAB6;

LAB9:    xsi_set_current_line(45, ng0);
    t66 = (t0 + 2792U);
    t67 = *((char **)t66);
    t66 = (t0 + 6888);
    t68 = (t66 + 56U);
    t69 = *((char **)t68);
    t70 = (t69 + 56U);
    t71 = *((char **)t70);
    memcpy(t71, t67, 8U);
    xsi_driver_first_trans_fast_port(t66);
    goto LAB8;

LAB10:    xsi_set_current_line(46, ng0);
    t1 = (t0 + 11487);
    t5 = (t0 + 1992U);
    t8 = *((char **)t5);
    t14 = ((IEEE_P_1242562249) + 2976);
    t15 = (t73 + 0U);
    t23 = (t15 + 0U);
    *((int *)t23) = 0;
    t23 = (t15 + 4U);
    *((int *)t23) = 3;
    t23 = (t15 + 8U);
    *((int *)t23) = 1;
    t9 = (3 - 0);
    t10 = (t9 * 1);
    t10 = (t10 + 1);
    t23 = (t15 + 12U);
    *((unsigned int *)t23) = t10;
    t23 = (t0 + 11176U);
    t5 = xsi_base_array_concat(t5, t72, t14, (char)97, t1, t73, (char)97, t8, t23, (char)101);
    t10 = (4U + 4U);
    t3 = (8U != t10);
    if (t3 == 1)
        goto LAB17;

LAB18:    t24 = (t0 + 6888);
    t30 = (t24 + 56U);
    t31 = *((char **)t30);
    t40 = (t31 + 56U);
    t41 = *((char **)t40);
    memcpy(t41, t5, 8U);
    xsi_driver_first_trans_fast_port(t24);
    goto LAB8;

LAB11:    xsi_set_current_line(47, ng0);
    t1 = (t0 + 11491);
    t5 = (t0 + 2152U);
    t8 = *((char **)t5);
    t14 = ((IEEE_P_1242562249) + 2976);
    t15 = (t73 + 0U);
    t23 = (t15 + 0U);
    *((int *)t23) = 0;
    t23 = (t15 + 4U);
    *((int *)t23) = 4;
    t23 = (t15 + 8U);
    *((int *)t23) = 1;
    t9 = (4 - 0);
    t10 = (t9 * 1);
    t10 = (t10 + 1);
    t23 = (t15 + 12U);
    *((unsigned int *)t23) = t10;
    t23 = (t0 + 11192U);
    t5 = xsi_base_array_concat(t5, t72, t14, (char)97, t1, t73, (char)97, t8, t23, (char)101);
    t10 = (5U + 3U);
    t3 = (8U != t10);
    if (t3 == 1)
        goto LAB19;

LAB20:    t24 = (t0 + 6888);
    t30 = (t24 + 56U);
    t31 = *((char **)t30);
    t40 = (t31 + 56U);
    t41 = *((char **)t40);
    memcpy(t41, t5, 8U);
    xsi_driver_first_trans_fast_port(t24);
    goto LAB8;

LAB16:;
LAB17:    xsi_size_not_matching(8U, t10, 0);
    goto LAB18;

LAB19:    xsi_size_not_matching(8U, t10, 0);
    goto LAB20;

}

static void work_a_0839295153_3212880686_p_1(char *t0)
{
    char t25[16];
    unsigned char t1;
    char *t2;
    unsigned char t3;
    char *t4;
    char *t5;
    unsigned char t6;
    unsigned char t7;
    char *t8;
    unsigned char t9;
    unsigned char t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    char *t15;
    char *t16;
    int t17;
    int t18;
    int t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    unsigned int t26;

LAB0:    xsi_set_current_line(62, ng0);
    t2 = (t0 + 992U);
    t3 = xsi_signal_has_event(t2);
    if (t3 == 1)
        goto LAB5;

LAB6:    t1 = (unsigned char)0;

LAB7:    if (t1 != 0)
        goto LAB2;

LAB4:
LAB3:    t2 = (t0 + 6728);
    *((int *)t2) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(63, ng0);
    t4 = (t0 + 1512U);
    t8 = *((char **)t4);
    t9 = *((unsigned char *)t8);
    t10 = (t9 == (unsigned char)3);
    if (t10 != 0)
        goto LAB8;

LAB10:    t2 = (t0 + 1352U);
    t4 = *((char **)t2);
    t3 = *((unsigned char *)t4);
    t6 = (t3 == (unsigned char)2);
    if (t6 == 1)
        goto LAB13;

LAB14:    t1 = (unsigned char)0;

LAB15:    if (t1 != 0)
        goto LAB11;

LAB12:
LAB9:    goto LAB3;

LAB5:    t4 = (t0 + 1032U);
    t5 = *((char **)t4);
    t6 = *((unsigned char *)t5);
    t7 = (t6 == (unsigned char)3);
    t1 = t7;
    goto LAB7;

LAB8:    xsi_set_current_line(64, ng0);
    t4 = xsi_get_transient_memory(8U);
    memset(t4, 0, 8U);
    t11 = t4;
    memset(t11, (unsigned char)2, 8U);
    t12 = (t0 + 6952);
    t13 = (t12 + 56U);
    t14 = *((char **)t13);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    memcpy(t16, t4, 8U);
    xsi_driver_first_trans_fast(t12);
    xsi_set_current_line(65, ng0);
    t2 = (t0 + 11496);
    t5 = (t0 + 7016);
    t8 = (t5 + 56U);
    t11 = *((char **)t8);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    memcpy(t13, t2, 8U);
    xsi_driver_first_trans_fast(t5);
    xsi_set_current_line(66, ng0);
    t2 = (t0 + 11504);
    t5 = (t0 + 7080);
    t8 = (t5 + 56U);
    t11 = *((char **)t8);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    memcpy(t13, t2, 8U);
    xsi_driver_first_trans_fast(t5);
    goto LAB9;

LAB11:    xsi_set_current_line(69, ng0);
    t2 = (t0 + 1672U);
    t8 = *((char **)t2);
    t2 = (t0 + 11512);
    t17 = xsi_mem_cmp(t2, t8, 16U);
    if (t17 == 1)
        goto LAB17;

LAB21:    t12 = (t0 + 11528);
    t18 = xsi_mem_cmp(t12, t8, 16U);
    if (t18 == 1)
        goto LAB18;

LAB22:    t14 = (t0 + 11544);
    t19 = xsi_mem_cmp(t14, t8, 16U);
    if (t19 == 1)
        goto LAB19;

LAB23:
LAB20:    xsi_set_current_line(74, ng0);

LAB16:    goto LAB9;

LAB13:    t2 = (t0 + 1192U);
    t5 = *((char **)t2);
    t7 = *((unsigned char *)t5);
    t9 = (t7 == (unsigned char)2);
    t1 = t9;
    goto LAB15;

LAB17:    xsi_set_current_line(70, ng0);
    t16 = (t0 + 1832U);
    t20 = *((char **)t16);
    t16 = (t0 + 6952);
    t21 = (t16 + 56U);
    t22 = *((char **)t21);
    t23 = (t22 + 56U);
    t24 = *((char **)t23);
    memcpy(t24, t20, 8U);
    xsi_driver_first_trans_fast(t16);
    goto LAB16;

LAB18:    xsi_set_current_line(72, ng0);
    t2 = (t0 + 1832U);
    t4 = *((char **)t2);
    t2 = (t0 + 1840U);
    t5 = *((char **)t2);
    t8 = (t0 + 11560);
    t12 = (t25 + 0U);
    t13 = (t12 + 0U);
    *((int *)t13) = 0;
    t13 = (t12 + 4U);
    *((int *)t13) = 7;
    t13 = (t12 + 8U);
    *((int *)t13) = 1;
    t17 = (7 - 0);
    t26 = (t17 * 1);
    t26 = (t26 + 1);
    t13 = (t12 + 12U);
    *((unsigned int *)t13) = t26;
    t1 = ieee_p_1242562249_sub_1434214030532789707_1035706684(IEEE_P_1242562249, t4, t5, t8, t25);
    if (t1 != 0)
        goto LAB25;

LAB27:    xsi_set_current_line(72, ng0);
    t2 = (t0 + 1832U);
    t4 = *((char **)t2);
    t2 = (t0 + 7080);
    t5 = (t2 + 56U);
    t8 = *((char **)t5);
    t11 = (t8 + 56U);
    t12 = *((char **)t11);
    memcpy(t12, t4, 8U);
    xsi_driver_first_trans_fast(t2);

LAB26:    goto LAB16;

LAB19:    xsi_set_current_line(73, ng0);
    t2 = (t0 + 1832U);
    t4 = *((char **)t2);
    t2 = (t0 + 7016);
    t5 = (t2 + 56U);
    t8 = *((char **)t5);
    t11 = (t8 + 56U);
    t12 = *((char **)t11);
    memcpy(t12, t4, 8U);
    xsi_driver_first_trans_fast(t2);
    goto LAB16;

LAB24:;
LAB25:    xsi_set_current_line(72, ng0);
    t13 = (t0 + 11568);
    t15 = (t0 + 7080);
    t16 = (t15 + 56U);
    t20 = *((char **)t16);
    t21 = (t20 + 56U);
    t22 = *((char **)t21);
    memcpy(t22, t13, 8U);
    xsi_driver_first_trans_fast(t15);
    goto LAB26;

}

static void work_a_0839295153_3212880686_p_2(char *t0)
{
    char *t1;
    char *t2;
    int t3;
    unsigned int t4;
    unsigned int t5;
    unsigned int t6;
    unsigned char t7;
    unsigned char t8;
    char *t9;
    char *t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    char *t24;
    char *t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;

LAB0:    xsi_set_current_line(81, ng0);
    t1 = (t0 + 2152U);
    t2 = *((char **)t1);
    t3 = (0 - 2);
    t4 = (t3 * -1);
    t5 = (1U * t4);
    t6 = (0 + t5);
    t1 = (t2 + t6);
    t7 = *((unsigned char *)t1);
    t8 = (t7 == (unsigned char)3);
    if (t8 != 0)
        goto LAB3;

LAB4:
LAB5:    t19 = (t0 + 2632U);
    t20 = *((char **)t19);
    t21 = (7 - 3);
    t22 = (t21 * 1U);
    t23 = (0 + t22);
    t19 = (t20 + t23);
    t24 = (t0 + 7144);
    t25 = (t24 + 56U);
    t26 = *((char **)t25);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    memcpy(t28, t19, 4U);
    xsi_driver_first_trans_fast_port(t24);

LAB2:    t29 = (t0 + 6744);
    *((int *)t29) = 1;

LAB1:    return;
LAB3:    t9 = (t0 + 2632U);
    t10 = *((char **)t9);
    t11 = (7 - 7);
    t12 = (t11 * 1U);
    t13 = (0 + t12);
    t9 = (t10 + t13);
    t14 = (t0 + 7144);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    t17 = (t16 + 56U);
    t18 = *((char **)t17);
    memcpy(t18, t9, 4U);
    xsi_driver_first_trans_fast_port(t14);
    goto LAB2;

LAB6:    goto LAB2;

}

static void work_a_0839295153_3212880686_p_3(char *t0)
{
    char t16[16];
    unsigned char t1;
    char *t2;
    unsigned char t3;
    char *t4;
    char *t5;
    unsigned char t6;
    unsigned char t7;
    unsigned char t8;
    char *t9;
    unsigned char t10;
    unsigned char t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    char *t17;
    char *t18;
    int t19;
    unsigned int t20;
    char *t21;
    unsigned char t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;

LAB0:    xsi_set_current_line(86, ng0);
    t2 = (t0 + 992U);
    t3 = xsi_signal_has_event(t2);
    if (t3 == 1)
        goto LAB5;

LAB6:    t1 = (unsigned char)0;

LAB7:    if (t1 != 0)
        goto LAB2;

LAB4:
LAB3:    t2 = (t0 + 6760);
    *((int *)t2) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(87, ng0);
    t4 = (t0 + 1512U);
    t9 = *((char **)t4);
    t10 = *((unsigned char *)t9);
    t11 = (t10 == (unsigned char)3);
    if (t11 == 1)
        goto LAB11;

LAB12:    t4 = (t0 + 3432U);
    t12 = *((char **)t4);
    t13 = (27 - 27);
    t14 = (t13 * 1U);
    t15 = (0 + t14);
    t4 = (t12 + t15);
    t17 = (t16 + 0U);
    t18 = (t17 + 0U);
    *((int *)t18) = 27;
    t18 = (t17 + 4U);
    *((int *)t18) = 20;
    t18 = (t17 + 8U);
    *((int *)t18) = -1;
    t19 = (20 - 27);
    t20 = (t19 * -1);
    t20 = (t20 + 1);
    t18 = (t17 + 12U);
    *((unsigned int *)t18) = t20;
    t18 = (t0 + 3112U);
    t21 = *((char **)t18);
    t18 = (t0 + 11224U);
    t22 = ieee_p_1242562249_sub_1434214030532789707_1035706684(IEEE_P_1242562249, t4, t16, t21, t18);
    t8 = t22;

LAB13:    if (t8 != 0)
        goto LAB8;

LAB10:    xsi_set_current_line(90, ng0);
    t2 = (t0 + 3432U);
    t4 = *((char **)t2);
    t2 = (t0 + 11256U);
    t5 = ieee_p_1242562249_sub_1006216973935652998_1035706684(IEEE_P_1242562249, t16, t4, t2, 1);
    t9 = (t16 + 12U);
    t13 = *((unsigned int *)t9);
    t14 = (1U * t13);
    t1 = (28U != t14);
    if (t1 == 1)
        goto LAB14;

LAB15:    t12 = (t0 + 7208);
    t17 = (t12 + 56U);
    t18 = *((char **)t17);
    t21 = (t18 + 56U);
    t23 = *((char **)t21);
    memcpy(t23, t5, 28U);
    xsi_driver_first_trans_fast(t12);

LAB9:    goto LAB3;

LAB5:    t4 = (t0 + 1032U);
    t5 = *((char **)t4);
    t6 = *((unsigned char *)t5);
    t7 = (t6 == (unsigned char)3);
    t1 = t7;
    goto LAB7;

LAB8:    xsi_set_current_line(88, ng0);
    t23 = xsi_get_transient_memory(28U);
    memset(t23, 0, 28U);
    t24 = t23;
    memset(t24, (unsigned char)2, 28U);
    t25 = (t0 + 7208);
    t26 = (t25 + 56U);
    t27 = *((char **)t26);
    t28 = (t27 + 56U);
    t29 = *((char **)t28);
    memcpy(t29, t23, 28U);
    xsi_driver_first_trans_fast(t25);
    goto LAB9;

LAB11:    t8 = (unsigned char)1;
    goto LAB13;

LAB14:    xsi_size_not_matching(28U, t14, 0);
    goto LAB15;

}

static void work_a_0839295153_3212880686_p_4(char *t0)
{
    char t7[16];
    char t9[16];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    char *t8;
    char *t10;
    char *t11;
    int t12;
    unsigned int t13;
    unsigned char t14;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;

LAB0:    xsi_set_current_line(97, ng0);
    t1 = (t0 + 3432U);
    t2 = *((char **)t1);
    t1 = (t0 + 11256U);
    t3 = (t0 + 11576);
    t5 = (t0 + 2952U);
    t6 = *((char **)t5);
    t8 = ((IEEE_P_1242562249) + 2976);
    t10 = (t9 + 0U);
    t11 = (t10 + 0U);
    *((int *)t11) = 0;
    t11 = (t10 + 4U);
    *((int *)t11) = 19;
    t11 = (t10 + 8U);
    *((int *)t11) = 1;
    t12 = (19 - 0);
    t13 = (t12 * 1);
    t13 = (t13 + 1);
    t11 = (t10 + 12U);
    *((unsigned int *)t11) = t13;
    t11 = (t0 + 11224U);
    t5 = xsi_base_array_concat(t5, t7, t8, (char)97, t3, t9, (char)97, t6, t11, (char)101);
    t14 = ieee_p_1242562249_sub_1434214030532753770_1035706684(IEEE_P_1242562249, t2, t1, t5, t7);
    if (t14 != 0)
        goto LAB3;

LAB4:
LAB5:    t22 = xsi_get_transient_memory(8U);
    memset(t22, 0, 8U);
    t23 = t22;
    memset(t23, (unsigned char)3, 8U);
    t24 = (t0 + 7272);
    t25 = (t24 + 56U);
    t26 = *((char **)t25);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    memcpy(t28, t22, 8U);
    xsi_driver_first_trans_fast(t24);

LAB2:    t29 = (t0 + 6776);
    *((int *)t29) = 1;

LAB1:    return;
LAB3:    t15 = xsi_get_transient_memory(8U);
    memset(t15, 0, 8U);
    t16 = t15;
    memset(t16, (unsigned char)2, 8U);
    t17 = (t0 + 7272);
    t18 = (t17 + 56U);
    t19 = *((char **)t18);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    memcpy(t21, t15, 8U);
    xsi_driver_first_trans_fast(t17);
    goto LAB2;

LAB6:    goto LAB2;

}

static void work_a_0839295153_3212880686_p_5(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;

LAB0:    xsi_set_current_line(36, ng0);

LAB3:    t1 = (t0 + 1672U);
    t2 = *((char **)t1);
    t1 = (t0 + 7336);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 16U);
    xsi_driver_first_trans_fast(t1);

LAB2:    t7 = (t0 + 6792);
    *((int *)t7) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_0839295153_3212880686_p_6(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;

LAB0:    xsi_set_current_line(36, ng0);

LAB3:    t1 = (t0 + 1832U);
    t2 = *((char **)t1);
    t1 = (t0 + 7400);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 8U);
    xsi_driver_first_trans_fast(t1);

LAB2:    t7 = (t0 + 6808);
    *((int *)t7) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}


extern void work_a_0839295153_3212880686_init()
{
	static char *pe[] = {(void *)work_a_0839295153_3212880686_p_0,(void *)work_a_0839295153_3212880686_p_1,(void *)work_a_0839295153_3212880686_p_2,(void *)work_a_0839295153_3212880686_p_3,(void *)work_a_0839295153_3212880686_p_4,(void *)work_a_0839295153_3212880686_p_5,(void *)work_a_0839295153_3212880686_p_6};
	xsi_register_didat("work_a_0839295153_3212880686", "isim/tb_system_isim_beh.exe.sim/work/a_0839295153_3212880686.didat");
	xsi_register_executes(pe);
}
