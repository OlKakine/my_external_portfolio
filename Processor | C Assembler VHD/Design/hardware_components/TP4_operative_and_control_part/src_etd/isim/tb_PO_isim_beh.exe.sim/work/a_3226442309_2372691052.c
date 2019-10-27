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
static const char *ng0 = "/user/1/.base/checchio/home/Documents/tp_archi/TP4/src_etd/vhd/tb_PO.vhd";
extern char *IEEE_P_2592010699;
extern char *IEEE_P_1242562249;

unsigned char ieee_p_1242562249_sub_1434214030532789707_1035706684(char *, char *, char *, char *, char *);
unsigned char ieee_p_2592010699_sub_374109322130769762_503743352(char *, unsigned char );


static void work_a_3226442309_2372691052_p_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    unsigned char t4;
    unsigned char t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    int64 t10;
    int64 t11;

LAB0:    t1 = (t0 + 4064U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(74, ng0);
    t2 = (t0 + 1032U);
    t3 = *((char **)t2);
    t4 = *((unsigned char *)t3);
    t5 = ieee_p_2592010699_sub_374109322130769762_503743352(IEEE_P_2592010699, t4);
    t2 = (t0 + 4696);
    t6 = (t2 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    *((unsigned char *)t9) = t5;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(75, ng0);
    t2 = (t0 + 3088U);
    t3 = *((char **)t2);
    t10 = *((int64 *)t3);
    t11 = (t10 / 2);
    t2 = (t0 + 3872);
    xsi_process_wait(t2, t11);

LAB6:    *((char **)t1) = &&LAB7;

LAB1:    return;
LAB4:    goto LAB2;

LAB5:    goto LAB4;

LAB7:    goto LAB5;

}

static void work_a_3226442309_2372691052_p_1(char *t0)
{
    char t11[16];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    int64 t7;
    int64 t8;
    unsigned char t9;
    unsigned char t10;
    char *t12;
    int t13;
    unsigned int t14;

LAB0:    t1 = (t0 + 4312U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(81, ng0);
    t2 = (t0 + 4760);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(82, ng0);
    t2 = (t0 + 3088U);
    t3 = *((char **)t2);
    t7 = *((int64 *)t3);
    t8 = (t7 / 4);
    t2 = (t0 + 4120);
    xsi_process_wait(t2, t8);

LAB6:    *((char **)t1) = &&LAB7;

LAB1:    return;
LAB4:    xsi_set_current_line(84, ng0);
    t2 = (t0 + 4824);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(85, ng0);
    t2 = (t0 + 4888);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(88, ng0);
    t2 = (t0 + 2632U);
    t3 = *((char **)t2);
    t9 = *((unsigned char *)t3);
    t10 = (t9 == (unsigned char)3);
    if (t10 == 0)
        goto LAB8;

LAB9:    xsi_set_current_line(89, ng0);
    t2 = (t0 + 2472U);
    t3 = *((char **)t2);
    t9 = *((unsigned char *)t3);
    t10 = (t9 == (unsigned char)2);
    if (t10 == 0)
        goto LAB10;

LAB11:    xsi_set_current_line(90, ng0);
    t2 = (t0 + 2792U);
    t3 = *((char **)t2);
    t2 = (t0 + 7992U);
    t4 = (t0 + 8124);
    t6 = (t11 + 0U);
    t12 = (t6 + 0U);
    *((int *)t12) = 0;
    t12 = (t6 + 4U);
    *((int *)t12) = 7;
    t12 = (t6 + 8U);
    *((int *)t12) = 1;
    t13 = (7 - 0);
    t14 = (t13 * 1);
    t14 = (t14 + 1);
    t12 = (t6 + 12U);
    *((unsigned int *)t12) = t14;
    t9 = ieee_p_1242562249_sub_1434214030532789707_1035706684(IEEE_P_1242562249, t3, t2, t4, t11);
    if (t9 == 0)
        goto LAB12;

LAB13:    xsi_set_current_line(92, ng0);
    t2 = (t0 + 3088U);
    t3 = *((char **)t2);
    t7 = *((int64 *)t3);
    t2 = (t0 + 4120);
    xsi_process_wait(t2, t7);

LAB16:    *((char **)t1) = &&LAB17;
    goto LAB1;

LAB5:    goto LAB4;

LAB7:    goto LAB5;

LAB8:    t2 = (t0 + 8064);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB9;

LAB10:    t2 = (t0 + 8094);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB11;

LAB12:    t12 = (t0 + 8132);
    xsi_report(t12, 31U, (unsigned char)2);
    goto LAB13;

LAB14:    xsi_set_current_line(94, ng0);
    t2 = (t0 + 4824);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(95, ng0);
    t2 = (t0 + 4888);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(96, ng0);
    t2 = (t0 + 4952);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(97, ng0);
    t2 = (t0 + 5016);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(100, ng0);
    t2 = (t0 + 2632U);
    t3 = *((char **)t2);
    t9 = *((unsigned char *)t3);
    t10 = (t9 == (unsigned char)2);
    if (t10 == 0)
        goto LAB18;

LAB19:    xsi_set_current_line(101, ng0);
    t2 = (t0 + 2472U);
    t3 = *((char **)t2);
    t9 = *((unsigned char *)t3);
    t10 = (t9 == (unsigned char)2);
    if (t10 == 0)
        goto LAB20;

LAB21:    xsi_set_current_line(102, ng0);
    t2 = (t0 + 2792U);
    t3 = *((char **)t2);
    t2 = (t0 + 7992U);
    t4 = (t0 + 8223);
    t6 = (t11 + 0U);
    t12 = (t6 + 0U);
    *((int *)t12) = 0;
    t12 = (t6 + 4U);
    *((int *)t12) = 7;
    t12 = (t6 + 8U);
    *((int *)t12) = 1;
    t13 = (7 - 0);
    t14 = (t13 * 1);
    t14 = (t14 + 1);
    t12 = (t6 + 12U);
    *((unsigned int *)t12) = t14;
    t9 = ieee_p_1242562249_sub_1434214030532789707_1035706684(IEEE_P_1242562249, t3, t2, t4, t11);
    if (t9 == 0)
        goto LAB22;

LAB23:    xsi_set_current_line(104, ng0);
    t2 = (t0 + 3088U);
    t3 = *((char **)t2);
    t7 = *((int64 *)t3);
    t2 = (t0 + 4120);
    xsi_process_wait(t2, t7);

LAB26:    *((char **)t1) = &&LAB27;
    goto LAB1;

LAB15:    goto LAB14;

LAB17:    goto LAB15;

LAB18:    t2 = (t0 + 8163);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB19;

LAB20:    t2 = (t0 + 8193);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB21;

LAB22:    t12 = (t0 + 8231);
    xsi_report(t12, 31U, (unsigned char)2);
    goto LAB23;

LAB24:    xsi_set_current_line(106, ng0);
    t2 = (t0 + 4824);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(107, ng0);
    t2 = (t0 + 4952);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(108, ng0);
    t2 = (t0 + 5016);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(111, ng0);
    t2 = (t0 + 2632U);
    t3 = *((char **)t2);
    t9 = *((unsigned char *)t3);
    t10 = (t9 == (unsigned char)2);
    if (t10 == 0)
        goto LAB28;

LAB29:    xsi_set_current_line(112, ng0);
    t2 = (t0 + 2472U);
    t3 = *((char **)t2);
    t9 = *((unsigned char *)t3);
    t10 = (t9 == (unsigned char)2);
    if (t10 == 0)
        goto LAB30;

LAB31:    xsi_set_current_line(113, ng0);
    t2 = (t0 + 2792U);
    t3 = *((char **)t2);
    t2 = (t0 + 7992U);
    t4 = (t0 + 8322);
    t6 = (t11 + 0U);
    t12 = (t6 + 0U);
    *((int *)t12) = 0;
    t12 = (t6 + 4U);
    *((int *)t12) = 7;
    t12 = (t6 + 8U);
    *((int *)t12) = 1;
    t13 = (7 - 0);
    t14 = (t13 * 1);
    t14 = (t14 + 1);
    t12 = (t6 + 12U);
    *((unsigned int *)t12) = t14;
    t9 = ieee_p_1242562249_sub_1434214030532789707_1035706684(IEEE_P_1242562249, t3, t2, t4, t11);
    if (t9 == 0)
        goto LAB32;

LAB33:    xsi_set_current_line(115, ng0);
    t2 = (t0 + 3088U);
    t3 = *((char **)t2);
    t7 = *((int64 *)t3);
    t2 = (t0 + 4120);
    xsi_process_wait(t2, t7);

LAB36:    *((char **)t1) = &&LAB37;
    goto LAB1;

LAB25:    goto LAB24;

LAB27:    goto LAB25;

LAB28:    t2 = (t0 + 8262);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB29;

LAB30:    t2 = (t0 + 8292);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB31;

LAB32:    t12 = (t0 + 8330);
    xsi_report(t12, 31U, (unsigned char)2);
    goto LAB33;

LAB34:    xsi_set_current_line(117, ng0);
    t2 = (t0 + 4824);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(118, ng0);
    t2 = (t0 + 4952);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(119, ng0);
    t2 = (t0 + 5080);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(122, ng0);
    t2 = (t0 + 2632U);
    t3 = *((char **)t2);
    t9 = *((unsigned char *)t3);
    t10 = (t9 == (unsigned char)2);
    if (t10 == 0)
        goto LAB38;

LAB39:    xsi_set_current_line(123, ng0);
    t2 = (t0 + 2472U);
    t3 = *((char **)t2);
    t9 = *((unsigned char *)t3);
    t10 = (t9 == (unsigned char)3);
    if (t10 == 0)
        goto LAB40;

LAB41:    xsi_set_current_line(124, ng0);
    t2 = (t0 + 2792U);
    t3 = *((char **)t2);
    t2 = (t0 + 7992U);
    t4 = (t0 + 8421);
    t6 = (t11 + 0U);
    t12 = (t6 + 0U);
    *((int *)t12) = 0;
    t12 = (t6 + 4U);
    *((int *)t12) = 7;
    t12 = (t6 + 8U);
    *((int *)t12) = 1;
    t13 = (7 - 0);
    t14 = (t13 * 1);
    t14 = (t14 + 1);
    t12 = (t6 + 12U);
    *((unsigned int *)t12) = t14;
    t9 = ieee_p_1242562249_sub_1434214030532789707_1035706684(IEEE_P_1242562249, t3, t2, t4, t11);
    if (t9 == 0)
        goto LAB42;

LAB43:    xsi_set_current_line(126, ng0);
    t2 = (t0 + 3088U);
    t3 = *((char **)t2);
    t7 = *((int64 *)t3);
    t2 = (t0 + 4120);
    xsi_process_wait(t2, t7);

LAB46:    *((char **)t1) = &&LAB47;
    goto LAB1;

LAB35:    goto LAB34;

LAB37:    goto LAB35;

LAB38:    t2 = (t0 + 8361);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB39;

LAB40:    t2 = (t0 + 8391);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB41;

LAB42:    t12 = (t0 + 8429);
    xsi_report(t12, 31U, (unsigned char)2);
    goto LAB43;

LAB44:    xsi_set_current_line(129, ng0);
    t2 = (t0 + 2632U);
    t3 = *((char **)t2);
    t9 = *((unsigned char *)t3);
    t10 = (t9 == (unsigned char)3);
    if (t10 == 0)
        goto LAB48;

LAB49:    xsi_set_current_line(130, ng0);
    t2 = (t0 + 2472U);
    t3 = *((char **)t2);
    t9 = *((unsigned char *)t3);
    t10 = (t9 == (unsigned char)2);
    if (t10 == 0)
        goto LAB50;

LAB51:    xsi_set_current_line(131, ng0);
    t2 = (t0 + 2792U);
    t3 = *((char **)t2);
    t2 = (t0 + 7992U);
    t4 = (t0 + 8520);
    t6 = (t11 + 0U);
    t12 = (t6 + 0U);
    *((int *)t12) = 0;
    t12 = (t6 + 4U);
    *((int *)t12) = 7;
    t12 = (t6 + 8U);
    *((int *)t12) = 1;
    t13 = (7 - 0);
    t14 = (t13 * 1);
    t14 = (t14 + 1);
    t12 = (t6 + 12U);
    *((unsigned int *)t12) = t14;
    t9 = ieee_p_1242562249_sub_1434214030532789707_1035706684(IEEE_P_1242562249, t3, t2, t4, t11);
    if (t9 == 0)
        goto LAB52;

LAB53:    xsi_set_current_line(133, ng0);
    t2 = (t0 + 3088U);
    t3 = *((char **)t2);
    t7 = *((int64 *)t3);
    t2 = (t0 + 4120);
    xsi_process_wait(t2, t7);

LAB56:    *((char **)t1) = &&LAB57;
    goto LAB1;

LAB45:    goto LAB44;

LAB47:    goto LAB45;

LAB48:    t2 = (t0 + 8460);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB49;

LAB50:    t2 = (t0 + 8490);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB51;

LAB52:    t12 = (t0 + 8528);
    xsi_report(t12, 31U, (unsigned char)2);
    goto LAB53;

LAB54:    xsi_set_current_line(135, ng0);
    t2 = (t0 + 4952);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(137, ng0);
    t2 = (t0 + 2632U);
    t3 = *((char **)t2);
    t9 = *((unsigned char *)t3);
    t10 = (t9 == (unsigned char)2);
    if (t10 == 0)
        goto LAB58;

LAB59:    xsi_set_current_line(138, ng0);
    t2 = (t0 + 2472U);
    t3 = *((char **)t2);
    t9 = *((unsigned char *)t3);
    t10 = (t9 == (unsigned char)2);
    if (t10 == 0)
        goto LAB60;

LAB61:    xsi_set_current_line(139, ng0);
    t2 = (t0 + 2792U);
    t3 = *((char **)t2);
    t2 = (t0 + 7992U);
    t4 = (t0 + 8619);
    t6 = (t11 + 0U);
    t12 = (t6 + 0U);
    *((int *)t12) = 0;
    t12 = (t6 + 4U);
    *((int *)t12) = 7;
    t12 = (t6 + 8U);
    *((int *)t12) = 1;
    t13 = (7 - 0);
    t14 = (t13 * 1);
    t14 = (t14 + 1);
    t12 = (t6 + 12U);
    *((unsigned int *)t12) = t14;
    t9 = ieee_p_1242562249_sub_1434214030532789707_1035706684(IEEE_P_1242562249, t3, t2, t4, t11);
    if (t9 == 0)
        goto LAB62;

LAB63:    xsi_set_current_line(141, ng0);
    t2 = (t0 + 3088U);
    t3 = *((char **)t2);
    t7 = *((int64 *)t3);
    t2 = (t0 + 4120);
    xsi_process_wait(t2, t7);

LAB66:    *((char **)t1) = &&LAB67;
    goto LAB1;

LAB55:    goto LAB54;

LAB57:    goto LAB55;

LAB58:    t2 = (t0 + 8559);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB59;

LAB60:    t2 = (t0 + 8589);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB61;

LAB62:    t12 = (t0 + 8627);
    xsi_report(t12, 31U, (unsigned char)2);
    goto LAB63;

LAB64:    xsi_set_current_line(142, ng0);
    t2 = (t0 + 8658);
    xsi_report(t2, 20U, (unsigned char)3);
    goto LAB2;

LAB65:    goto LAB64;

LAB67:    goto LAB65;

}


extern void work_a_3226442309_2372691052_init()
{
	static char *pe[] = {(void *)work_a_3226442309_2372691052_p_0,(void *)work_a_3226442309_2372691052_p_1};
	xsi_register_didat("work_a_3226442309_2372691052", "isim/tb_PO_isim_beh.exe.sim/work/a_3226442309_2372691052.didat");
	xsi_register_executes(pe);
}
