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

#include "xsi.h"

struct XSI_INFO xsi_info;

char *IEEE_P_2592010699;
char *STD_STANDARD;
char *IEEE_P_1242562249;
char *WORK_P_3079944648;
char *UNISIM_P_0947159679;
char *STD_TEXTIO;
char *UNISIM_P_3222816464;
char *IEEE_P_1367372525;
char *IEEE_P_2717149903;


int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    ieee_p_2592010699_init();
    ieee_p_1242562249_init();
    unisim_p_0947159679_init();
    work_p_3079944648_init();
    work_a_0160024279_3212880686_init();
    work_a_1527060950_3271922888_init();
    std_textio_init();
    ieee_p_2717149903_init();
    ieee_p_1367372525_init();
    unisim_p_3222816464_init();
    unisim_a_4126813653_0883528894_init();
    unisim_a_1953693685_0883528894_init();
    unisim_a_1007432910_0883528894_init();
    unisim_a_1727970514_0883528894_init();
    unisim_a_3774351931_0883528894_init();
    unisim_a_2178776508_0883528894_init();
    unisim_a_2120798889_0883528894_init();
    unisim_a_1448748903_0883528894_init();
    unisim_a_3933570554_0883528894_init();
    unisim_a_0385501738_0883528894_init();
    unisim_a_1220082426_0883528894_init();
    unisim_a_0484761457_0883528894_init();
    unisim_a_4224007769_0883528894_init();
    unisim_a_0561946210_0883528894_init();
    unisim_a_2300962535_0883528894_init();
    unisim_a_1294857759_0883528894_init();
    unisim_a_2517038934_0883528894_init();
    unisim_a_1210527137_0883528894_init();
    unisim_a_1941865869_0883528894_init();
    unisim_a_4107109759_0883528894_init();
    unisim_a_4061833343_0883528894_init();
    unisim_a_3735947232_0883528894_init();
    unisim_a_2482943209_0883528894_init();
    unisim_a_2147786568_0883528894_init();
    unisim_a_0012942499_0883528894_init();
    unisim_a_2439503589_0883528894_init();
    unisim_a_3197752772_0883528894_init();
    unisim_a_0131101039_0883528894_init();
    unisim_a_2569795511_0883528894_init();
    unisim_a_2251972221_0883528894_init();
    unisim_a_3080686366_0883528894_init();
    unisim_a_0506893965_0883528894_init();
    unisim_a_2472100108_0883528894_init();
    unisim_a_1684671624_0883528894_init();
    unisim_a_2727692145_0883528894_init();
    unisim_a_1583016430_0883528894_init();
    unisim_a_0882487138_0883528894_init();
    unisim_a_3472233688_0883528894_init();
    unisim_a_0363796591_0883528894_init();
    unisim_a_0868434958_0883528894_init();
    unisim_a_0850001934_0883528894_init();
    unisim_a_1531599289_0883528894_init();
    unisim_a_3507429849_0883528894_init();
    unisim_a_2288590265_0883528894_init();
    unisim_a_1996550586_0883528894_init();
    unisim_a_1303730585_0883528894_init();
    unisim_a_2077842781_0883528894_init();
    unisim_a_4010037911_0883528894_init();
    unisim_a_0815921694_0883528894_init();
    unisim_a_1071075660_0883528894_init();
    unisim_a_1948846473_0883528894_init();
    unisim_a_1647083109_0883528894_init();
    unisim_a_4127592315_0883528894_init();
    unisim_a_0606047183_0883528894_init();
    unisim_a_1975692252_0883528894_init();
    unisim_a_2385241394_0883528894_init();
    unisim_a_1520724898_0883528894_init();
    unisim_a_0578764078_0883528894_init();
    unisim_a_2311363787_0883528894_init();
    unisim_a_1395484876_0883528894_init();
    unisim_a_4029104588_0883528894_init();
    unisim_a_1226794538_0883528894_init();
    unisim_a_2720875908_0883528894_init();
    unisim_a_0189104903_0883528894_init();
    unisim_a_0279232705_0883528894_init();
    unisim_a_1444617546_0883528894_init();
    unisim_a_1455467230_0883528894_init();
    unisim_a_1730118861_0883528894_init();
    unisim_a_4124926014_0883528894_init();
    unisim_a_2485655113_0883528894_init();
    unisim_a_3970888811_0883528894_init();
    unisim_a_1796380928_0883528894_init();
    unisim_a_1197393976_0883528894_init();
    unisim_a_0377076941_0883528894_init();
    unisim_a_2179241312_0883528894_init();
    unisim_a_3017409610_0883528894_init();
    unisim_a_1995823859_0883528894_init();
    unisim_a_2167378430_0883528894_init();
    unisim_a_3561063024_0883528894_init();
    unisim_a_4258311174_0883528894_init();
    unisim_a_3304544010_0883528894_init();
    unisim_a_1323371283_0883528894_init();
    unisim_a_0419416143_0883528894_init();
    unisim_a_0546256335_0883528894_init();
    unisim_a_3932426916_0883528894_init();
    unisim_a_0303513189_0883528894_init();
    unisim_a_3056701248_0883528894_init();
    unisim_a_3333058318_0883528894_init();
    work_a_1899952104_3212880686_init();
    work_a_0871606977_3271922888_init();
    work_a_2739800806_2372691052_init();


    xsi_register_tops("work_a_2739800806_2372691052");

    IEEE_P_2592010699 = xsi_get_engine_memory("ieee_p_2592010699");
    xsi_register_ieee_std_logic_1164(IEEE_P_2592010699);
    STD_STANDARD = xsi_get_engine_memory("std_standard");
    IEEE_P_1242562249 = xsi_get_engine_memory("ieee_p_1242562249");
    WORK_P_3079944648 = xsi_get_engine_memory("work_p_3079944648");
    UNISIM_P_0947159679 = xsi_get_engine_memory("unisim_p_0947159679");
    STD_TEXTIO = xsi_get_engine_memory("std_textio");
    UNISIM_P_3222816464 = xsi_get_engine_memory("unisim_p_3222816464");
    IEEE_P_1367372525 = xsi_get_engine_memory("ieee_p_1367372525");
    IEEE_P_2717149903 = xsi_get_engine_memory("ieee_p_2717149903");

    return xsi_run_simulation(argc, argv);

}
