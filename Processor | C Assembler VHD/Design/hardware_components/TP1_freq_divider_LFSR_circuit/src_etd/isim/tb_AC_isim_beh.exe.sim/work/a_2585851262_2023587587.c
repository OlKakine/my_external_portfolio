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
static const char *ng0 = "/user/1/.base/checchio/home/Documents/tp_archi/src_etd/vhd/tb_AC.vhd";



static void work_a_2585851262_2023587587_p_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    int64 t7;
    unsigned char t8;
    unsigned char t9;

LAB0:    t1 = (t0 + 2824U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(49, ng0);
    t2 = (t0 + 3208);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(50, ng0);
    t2 = (t0 + 3272);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(51, ng0);
    t2 = (t0 + 3336);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(52, ng0);
    t7 = (5 * 1000LL);
    t2 = (t0 + 2632);
    xsi_process_wait(t2, t7);

LAB6:    *((char **)t1) = &&LAB7;

LAB1:    return;
LAB4:    xsi_set_current_line(57, ng0);
    t2 = (t0 + 1512U);
    t3 = *((char **)t2);
    t8 = *((unsigned char *)t3);
    t9 = (t8 == (unsigned char)2);
    if (t9 == 0)
        goto LAB8;

LAB9:    xsi_set_current_line(58, ng0);
    t2 = (t0 + 1672U);
    t3 = *((char **)t2);
    t8 = *((unsigned char *)t3);
    t9 = (t8 == (unsigned char)2);
    if (t9 == 0)
        goto LAB10;

LAB11:    xsi_set_current_line(60, ng0);
    t2 = (t0 + 3208);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(61, ng0);
    t7 = (5 * 1000LL);
    t2 = (t0 + 2632);
    xsi_process_wait(t2, t7);

LAB14:    *((char **)t1) = &&LAB15;
    goto LAB1;

LAB5:    goto LAB4;

LAB7:    goto LAB5;

LAB8:    t2 = (t0 + 5405);
    xsi_report(t2, 29U, (unsigned char)2);
    goto LAB9;

LAB10:    t2 = (t0 + 5434);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB11;

LAB12:    xsi_set_current_line(62, ng0);
    t2 = (t0 + 1512U);
    t3 = *((char **)t2);
    t8 = *((unsigned char *)t3);
    t9 = (t8 == (unsigned char)3);
    if (t9 == 0)
        goto LAB16;

LAB17:    xsi_set_current_line(63, ng0);
    t2 = (t0 + 1672U);
    t3 = *((char **)t2);
    t8 = *((unsigned char *)t3);
    t9 = (t8 == (unsigned char)2);
    if (t9 == 0)
        goto LAB18;

LAB19:    xsi_set_current_line(65, ng0);
    t2 = (t0 + 3272);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(66, ng0);
    t7 = (5 * 1000LL);
    t2 = (t0 + 2632);
    xsi_process_wait(t2, t7);

LAB22:    *((char **)t1) = &&LAB23;
    goto LAB1;

LAB13:    goto LAB12;

LAB15:    goto LAB13;

LAB16:    t2 = (t0 + 5464);
    xsi_report(t2, 29U, (unsigned char)2);
    goto LAB17;

LAB18:    t2 = (t0 + 5493);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB19;

LAB20:    xsi_set_current_line(67, ng0);
    t2 = (t0 + 1512U);
    t3 = *((char **)t2);
    t8 = *((unsigned char *)t3);
    t9 = (t8 == (unsigned char)2);
    if (t9 == 0)
        goto LAB24;

LAB25:    xsi_set_current_line(68, ng0);
    t2 = (t0 + 1672U);
    t3 = *((char **)t2);
    t8 = *((unsigned char *)t3);
    t9 = (t8 == (unsigned char)3);
    if (t9 == 0)
        goto LAB26;

LAB27:    xsi_set_current_line(70, ng0);
    t2 = (t0 + 3336);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(71, ng0);
    t7 = (5 * 1000LL);
    t2 = (t0 + 2632);
    xsi_process_wait(t2, t7);

LAB30:    *((char **)t1) = &&LAB31;
    goto LAB1;

LAB21:    goto LAB20;

LAB23:    goto LAB21;

LAB24:    t2 = (t0 + 5523);
    xsi_report(t2, 29U, (unsigned char)2);
    goto LAB25;

LAB26:    t2 = (t0 + 5552);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB27;

LAB28:    xsi_set_current_line(72, ng0);
    t2 = (t0 + 1512U);
    t3 = *((char **)t2);
    t8 = *((unsigned char *)t3);
    t9 = (t8 == (unsigned char)3);
    if (t9 == 0)
        goto LAB32;

LAB33:    xsi_set_current_line(73, ng0);
    t2 = (t0 + 1672U);
    t3 = *((char **)t2);
    t8 = *((unsigned char *)t3);
    t9 = (t8 == (unsigned char)3);
    if (t9 == 0)
        goto LAB34;

LAB35:    xsi_set_current_line(75, ng0);
    t2 = (t0 + 3272);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(76, ng0);
    t7 = (5 * 1000LL);
    t2 = (t0 + 2632);
    xsi_process_wait(t2, t7);

LAB38:    *((char **)t1) = &&LAB39;
    goto LAB1;

LAB29:    goto LAB28;

LAB31:    goto LAB29;

LAB32:    t2 = (t0 + 5582);
    xsi_report(t2, 29U, (unsigned char)2);
    goto LAB33;

LAB34:    t2 = (t0 + 5611);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB35;

LAB36:    xsi_set_current_line(77, ng0);
    t2 = (t0 + 1512U);
    t3 = *((char **)t2);
    t8 = *((unsigned char *)t3);
    t9 = (t8 == (unsigned char)2);
    if (t9 == 0)
        goto LAB40;

LAB41:    xsi_set_current_line(78, ng0);
    t2 = (t0 + 1672U);
    t3 = *((char **)t2);
    t8 = *((unsigned char *)t3);
    t9 = (t8 == (unsigned char)3);
    if (t9 == 0)
        goto LAB42;

LAB43:    xsi_set_current_line(80, ng0);
    t2 = (t0 + 3208);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(81, ng0);
    t7 = (5 * 1000LL);
    t2 = (t0 + 2632);
    xsi_process_wait(t2, t7);

LAB46:    *((char **)t1) = &&LAB47;
    goto LAB1;

LAB37:    goto LAB36;

LAB39:    goto LAB37;

LAB40:    t2 = (t0 + 5641);
    xsi_report(t2, 29U, (unsigned char)2);
    goto LAB41;

LAB42:    t2 = (t0 + 5670);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB43;

LAB44:    xsi_set_current_line(82, ng0);
    t2 = (t0 + 1512U);
    t3 = *((char **)t2);
    t8 = *((unsigned char *)t3);
    t9 = (t8 == (unsigned char)3);
    if (t9 == 0)
        goto LAB48;

LAB49:    xsi_set_current_line(83, ng0);
    t2 = (t0 + 1672U);
    t3 = *((char **)t2);
    t8 = *((unsigned char *)t3);
    t9 = (t8 == (unsigned char)2);
    if (t9 == 0)
        goto LAB50;

LAB51:    xsi_set_current_line(85, ng0);
    t2 = (t0 + 3272);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)3;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(86, ng0);
    t7 = (5 * 1000LL);
    t2 = (t0 + 2632);
    xsi_process_wait(t2, t7);

LAB54:    *((char **)t1) = &&LAB55;
    goto LAB1;

LAB45:    goto LAB44;

LAB47:    goto LAB45;

LAB48:    t2 = (t0 + 5700);
    xsi_report(t2, 29U, (unsigned char)2);
    goto LAB49;

LAB50:    t2 = (t0 + 5729);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB51;

LAB52:    xsi_set_current_line(87, ng0);
    t2 = (t0 + 1512U);
    t3 = *((char **)t2);
    t8 = *((unsigned char *)t3);
    t9 = (t8 == (unsigned char)2);
    if (t9 == 0)
        goto LAB56;

LAB57:    xsi_set_current_line(88, ng0);
    t2 = (t0 + 1672U);
    t3 = *((char **)t2);
    t8 = *((unsigned char *)t3);
    t9 = (t8 == (unsigned char)3);
    if (t9 == 0)
        goto LAB58;

LAB59:    xsi_set_current_line(90, ng0);
    t2 = (t0 + 3336);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    *((unsigned char *)t6) = (unsigned char)2;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(91, ng0);
    t7 = (5 * 1000LL);
    t2 = (t0 + 2632);
    xsi_process_wait(t2, t7);

LAB62:    *((char **)t1) = &&LAB63;
    goto LAB1;

LAB53:    goto LAB52;

LAB55:    goto LAB53;

LAB56:    t2 = (t0 + 5759);
    xsi_report(t2, 29U, (unsigned char)2);
    goto LAB57;

LAB58:    t2 = (t0 + 5788);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB59;

LAB60:    xsi_set_current_line(92, ng0);
    t2 = (t0 + 1512U);
    t3 = *((char **)t2);
    t8 = *((unsigned char *)t3);
    t9 = (t8 == (unsigned char)3);
    if (t9 == 0)
        goto LAB64;

LAB65:    xsi_set_current_line(93, ng0);
    t2 = (t0 + 1672U);
    t3 = *((char **)t2);
    t8 = *((unsigned char *)t3);
    t9 = (t8 == (unsigned char)2);
    if (t9 == 0)
        goto LAB66;

LAB67:    xsi_set_current_line(102, ng0);
    t2 = (t0 + 5877);
    xsi_report(t2, 20U, (unsigned char)3);
    goto LAB2;

LAB61:    goto LAB60;

LAB63:    goto LAB61;

LAB64:    t2 = (t0 + 5818);
    xsi_report(t2, 29U, (unsigned char)2);
    goto LAB65;

LAB66:    t2 = (t0 + 5847);
    xsi_report(t2, 30U, (unsigned char)2);
    goto LAB67;

}


extern void work_a_2585851262_2023587587_init()
{
	static char *pe[] = {(void *)work_a_2585851262_2023587587_p_0};
	xsi_register_didat("work_a_2585851262_2023587587", "isim/tb_AC_isim_beh.exe.sim/work/a_2585851262_2023587587.didat");
	xsi_register_executes(pe);
}
