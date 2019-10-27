library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.all;
library UNISIM;
use UNISIM.Vcomponents.ALL;
use work.prog_data_pkg.all;

entity RAM is
	Port (  AD : in  std_logic_vector(15 downto 0);
		    DI : in  std_logic_vector(7 downto 0);
    		DO : out std_logic_vector(7 downto 0);
	    	clk : in STD_LOGIC;
		    WEb : in STD_LOGIC;
    		CEb : in STD_LOGIC);
end RAM;

architecture Behavioral of RAM is

	signal en0,en1,en2,en3: std_logic;
	signal do0,do1,do2,do3: std_logic_vector(7 downto 0);

   attribute INIT       : string ;
   attribute INITP_00   : string ;
   attribute INITP_01   : string ;
   attribute INITP_02   : string ;
   attribute INITP_03   : string ;
   attribute INITP_04   : string ;
   attribute INITP_05   : string ;
   attribute INITP_06   : string ;
   attribute INITP_07   : string ;
   attribute SRVAL      : string ;
   attribute WRITE_MODE : string ;
   attribute BOX_TYPE   : string ;
   component RAMB16_S9
      generic( INIT : bit_vector :=  x"000";
               INIT_00 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_00;
               INIT_01 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_01;
               INIT_02 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_02;
               INIT_03 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_03;
               INIT_04 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_04;
               INIT_05 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_05;
               INIT_06 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_06;
               INIT_07 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_07;
               INIT_08 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_08;
               INIT_09 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_09;
               INIT_0A : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_0a;
               INIT_0B : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_0b;
               INIT_0C : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_0c;
               INIT_0D : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_0d;
               INIT_0E : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_0e;
               INIT_0F : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_0f;
               INIT_10 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_10;
               INIT_11 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_11;
               INIT_12 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_12;
               INIT_13 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_13;
               INIT_14 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_14;
               INIT_15 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_15;
               INIT_16 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_16;
               INIT_17 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_17;
               INIT_18 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_18;
               INIT_19 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_19;
               INIT_1A : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_1a;
               INIT_1B : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_1b;
               INIT_1C : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_1c;
               INIT_1D : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_1d;
               INIT_1E : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_1e;
               INIT_1F : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_1f;
               INIT_20 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_20;
               INIT_21 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_21;
               INIT_22 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_22;
               INIT_23 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_23;
               INIT_24 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_24;
               INIT_25 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_25;
               INIT_26 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_26;
               INIT_27 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_27;
               INIT_28 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_28;
               INIT_29 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_29;
               INIT_2A : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_2a;
               INIT_2B : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_2b;
               INIT_2C : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_2c;
               INIT_2D : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_2d;
               INIT_2E : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_2e;
               INIT_2F : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_2f;
               INIT_30 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_30;
               INIT_31 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_31;
               INIT_32 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_32;
               INIT_33 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_33;
               INIT_34 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_34;
               INIT_35 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_35;
               INIT_36 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_36;
               INIT_37 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_37;
               INIT_38 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_38;
               INIT_39 : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_39;
               INIT_3A : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_3a;
               INIT_3B : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_3b;
               INIT_3C : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_3c;
               INIT_3D : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_3d;
               INIT_3E : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_3e;
               INIT_3F : bit_vector :=  i_periph_iRAM_XLXI_0_INIT_3f;
               INITP_00 : bit_vector :=  x"0000000000000000000000000000000000000000000000000000000000000000";
               INITP_01 : bit_vector :=  x"0000000000000000000000000000000000000000000000000000000000000000";
               INITP_02 : bit_vector :=  x"0000000000000000000000000000000000000000000000000000000000000000";
               INITP_03 : bit_vector :=  x"0000000000000000000000000000000000000000000000000000000000000000";
               INITP_04 : bit_vector :=  x"0000000000000000000000000000000000000000000000000000000000000000";
               INITP_05 : bit_vector :=  x"0000000000000000000000000000000000000000000000000000000000000000";
               INITP_06 : bit_vector :=  x"0000000000000000000000000000000000000000000000000000000000000000";
               INITP_07 : bit_vector :=  x"0000000000000000000000000000000000000000000000000000000000000000";
               SRVAL : bit_vector :=  x"000";
               WRITE_MODE : string :=  "WRITE_FIRST");
      port ( ADDR : in    std_logic_vector (10 downto 0); 
             CLK  : in    std_logic; 
             DI   : in    std_logic_vector (7 downto 0); 
             DIP  : in    std_logic_vector (0 downto 0); 
             EN   : in    std_logic; 
             SSR  : in    std_logic; 
             WE   : in    std_logic; 
             DO   : out   std_logic_vector (7 downto 0); 
             DOP  : out   std_logic_vector (0 downto 0));
   end component;

   attribute INIT of RAMB16_S9 : component is "000";
   attribute INITP_00 of RAMB16_S9 : component is 
         "0000000000000000000000000000000000000000000000000000000000000000";
   attribute INITP_01 of RAMB16_S9 : component is 
         "0000000000000000000000000000000000000000000000000000000000000000";
   attribute INITP_02 of RAMB16_S9 : component is 
         "0000000000000000000000000000000000000000000000000000000000000000";
   attribute INITP_03 of RAMB16_S9 : component is 
         "0000000000000000000000000000000000000000000000000000000000000000";
   attribute INITP_04 of RAMB16_S9 : component is 
         "0000000000000000000000000000000000000000000000000000000000000000";
   attribute INITP_05 of RAMB16_S9 : component is 
         "0000000000000000000000000000000000000000000000000000000000000000";
   attribute INITP_06 of RAMB16_S9 : component is 
         "0000000000000000000000000000000000000000000000000000000000000000";
   attribute INITP_07 of RAMB16_S9 : component is 
         "0000000000000000000000000000000000000000000000000000000000000000";
   attribute SRVAL of RAMB16_S9 : component is "000";
   attribute WRITE_MODE of RAMB16_S9 : component is "WRITE_FIRST";
   attribute BOX_TYPE of RAMB16_S9 : component is "BLACK_BOX";

begin
    process (CEb,AD(15 downto 11))
    variable en_tmp : std_logic;
    begin
       en_tmp:= not(CEb or AD(15) or AD(13));
       en0<= en_tmp and not AD(14) and AD(12) and not AD(11);
       en1<= en_tmp and not AD(14) and AD(12) and AD(11);
       en2<= en_tmp and AD(14) and not AD(12) and not AD(11);
       en3<= en_tmp and AD(14) and not AD(12) and AD(11);
    end process;

    with AD(14)&AD(12 downto 11) select DO <=
        DO0 when "010",
        DO1 when "011",
        DO2 when "100",
        DO3 when others;

   XLXI_0 : RAMB16_S9
generic map (
INIT_00=>i_periph_iRAM_XLXI_0_INIT_00,
INIT_01=>i_periph_iRAM_XLXI_0_INIT_01,
INIT_02=>i_periph_iRAM_XLXI_0_INIT_02,
INIT_03=>i_periph_iRAM_XLXI_0_INIT_03,
INIT_04=>i_periph_iRAM_XLXI_0_INIT_04,
INIT_05=>i_periph_iRAM_XLXI_0_INIT_05,
INIT_06=>i_periph_iRAM_XLXI_0_INIT_06,
INIT_07=>i_periph_iRAM_XLXI_0_INIT_07,
INIT_08=>i_periph_iRAM_XLXI_0_INIT_08,
INIT_09=>i_periph_iRAM_XLXI_0_INIT_09,
INIT_0a=>i_periph_iRAM_XLXI_0_INIT_0A,
INIT_0b=>i_periph_iRAM_XLXI_0_INIT_0B,
INIT_0c=>i_periph_iRAM_XLXI_0_INIT_0C,
INIT_0d=>i_periph_iRAM_XLXI_0_INIT_0D,
INIT_0e=>i_periph_iRAM_XLXI_0_INIT_0E,
INIT_0f=>i_periph_iRAM_XLXI_0_INIT_0F,
INIT_10=>i_periph_iRAM_XLXI_0_INIT_10,
INIT_11=>i_periph_iRAM_XLXI_0_INIT_11,
INIT_12=>i_periph_iRAM_XLXI_0_INIT_12,
INIT_13=>i_periph_iRAM_XLXI_0_INIT_13,
INIT_14=>i_periph_iRAM_XLXI_0_INIT_14,
INIT_15=>i_periph_iRAM_XLXI_0_INIT_15,
INIT_16=>i_periph_iRAM_XLXI_0_INIT_16,
INIT_17=>i_periph_iRAM_XLXI_0_INIT_17,
INIT_18=>i_periph_iRAM_XLXI_0_INIT_18,
INIT_19=>i_periph_iRAM_XLXI_0_INIT_19,
INIT_1a=>i_periph_iRAM_XLXI_0_INIT_1A,
INIT_1b=>i_periph_iRAM_XLXI_0_INIT_1B,
INIT_1c=>i_periph_iRAM_XLXI_0_INIT_1C,
INIT_1d=>i_periph_iRAM_XLXI_0_INIT_1D,
INIT_1e=>i_periph_iRAM_XLXI_0_INIT_1E,
INIT_1f=>i_periph_iRAM_XLXI_0_INIT_1F,
INIT_20=>i_periph_iRAM_XLXI_0_INIT_20,
INIT_21=>i_periph_iRAM_XLXI_0_INIT_21,
INIT_22=>i_periph_iRAM_XLXI_0_INIT_22,
INIT_23=>i_periph_iRAM_XLXI_0_INIT_23,
INIT_24=>i_periph_iRAM_XLXI_0_INIT_24,
INIT_25=>i_periph_iRAM_XLXI_0_INIT_25,
INIT_26=>i_periph_iRAM_XLXI_0_INIT_26,
INIT_27=>i_periph_iRAM_XLXI_0_INIT_27,
INIT_28=>i_periph_iRAM_XLXI_0_INIT_28,
INIT_29=>i_periph_iRAM_XLXI_0_INIT_29,
INIT_2a=>i_periph_iRAM_XLXI_0_INIT_2A,
INIT_2b=>i_periph_iRAM_XLXI_0_INIT_2B,
INIT_2c=>i_periph_iRAM_XLXI_0_INIT_2C,
INIT_2d=>i_periph_iRAM_XLXI_0_INIT_2D,
INIT_2e=>i_periph_iRAM_XLXI_0_INIT_2E,
INIT_2f=>i_periph_iRAM_XLXI_0_INIT_2F,
INIT_30=>i_periph_iRAM_XLXI_0_INIT_30,
INIT_31=>i_periph_iRAM_XLXI_0_INIT_31,
INIT_32=>i_periph_iRAM_XLXI_0_INIT_32,
INIT_33=>i_periph_iRAM_XLXI_0_INIT_33,
INIT_34=>i_periph_iRAM_XLXI_0_INIT_34,
INIT_35=>i_periph_iRAM_XLXI_0_INIT_35,
INIT_36=>i_periph_iRAM_XLXI_0_INIT_36,
INIT_37=>i_periph_iRAM_XLXI_0_INIT_37,
INIT_38=>i_periph_iRAM_XLXI_0_INIT_38,
INIT_39=>i_periph_iRAM_XLXI_0_INIT_39,
INIT_3a=>i_periph_iRAM_XLXI_0_INIT_3A,
INIT_3b=>i_periph_iRAM_XLXI_0_INIT_3B,
INIT_3c=>i_periph_iRAM_XLXI_0_INIT_3C,
INIT_3d=>i_periph_iRAM_XLXI_0_INIT_3D,
INIT_3e=>i_periph_iRAM_XLXI_0_INIT_3E,
INIT_3f=>i_periph_iRAM_XLXI_0_INIT_3F
)
      port map (ADDR=>AD(10 downto 0),
                CLK=> not CLK,
                DI=>DI,
                DIP(0)=>'0',
                EN=>en0,
                SSR=>'0',
                WE=>not web,
                DO=>DO0,
                DOP=>open);

   XLXI_1 : RAMB16_S9
generic map (
INIT_00=>i_periph_iRAM_XLXI_1_INIT_00,
INIT_01=>i_periph_iRAM_XLXI_1_INIT_01,
INIT_02=>i_periph_iRAM_XLXI_1_INIT_02,
INIT_03=>i_periph_iRAM_XLXI_1_INIT_03,
INIT_04=>i_periph_iRAM_XLXI_1_INIT_04,
INIT_05=>i_periph_iRAM_XLXI_1_INIT_05,
INIT_06=>i_periph_iRAM_XLXI_1_INIT_06,
INIT_07=>i_periph_iRAM_XLXI_1_INIT_07,
INIT_08=>i_periph_iRAM_XLXI_1_INIT_08,
INIT_09=>i_periph_iRAM_XLXI_1_INIT_09,
INIT_0a=>i_periph_iRAM_XLXI_1_INIT_0A,
INIT_0b=>i_periph_iRAM_XLXI_1_INIT_0B,
INIT_0c=>i_periph_iRAM_XLXI_1_INIT_0C,
INIT_0d=>i_periph_iRAM_XLXI_1_INIT_0D,
INIT_0e=>i_periph_iRAM_XLXI_1_INIT_0E,
INIT_0f=>i_periph_iRAM_XLXI_1_INIT_0F,
INIT_10=>i_periph_iRAM_XLXI_1_INIT_10,
INIT_11=>i_periph_iRAM_XLXI_1_INIT_11,
INIT_12=>i_periph_iRAM_XLXI_1_INIT_12,
INIT_13=>i_periph_iRAM_XLXI_1_INIT_13,
INIT_14=>i_periph_iRAM_XLXI_1_INIT_14,
INIT_15=>i_periph_iRAM_XLXI_1_INIT_15,
INIT_16=>i_periph_iRAM_XLXI_1_INIT_16,
INIT_17=>i_periph_iRAM_XLXI_1_INIT_17,
INIT_18=>i_periph_iRAM_XLXI_1_INIT_18,
INIT_19=>i_periph_iRAM_XLXI_1_INIT_19,
INIT_1a=>i_periph_iRAM_XLXI_1_INIT_1A,
INIT_1b=>i_periph_iRAM_XLXI_1_INIT_1B,
INIT_1c=>i_periph_iRAM_XLXI_1_INIT_1C,
INIT_1d=>i_periph_iRAM_XLXI_1_INIT_1D,
INIT_1e=>i_periph_iRAM_XLXI_1_INIT_1E,
INIT_1f=>i_periph_iRAM_XLXI_1_INIT_1F,
INIT_20=>i_periph_iRAM_XLXI_1_INIT_20,
INIT_21=>i_periph_iRAM_XLXI_1_INIT_21,
INIT_22=>i_periph_iRAM_XLXI_1_INIT_22,
INIT_23=>i_periph_iRAM_XLXI_1_INIT_23,
INIT_24=>i_periph_iRAM_XLXI_1_INIT_24,
INIT_25=>i_periph_iRAM_XLXI_1_INIT_25,
INIT_26=>i_periph_iRAM_XLXI_1_INIT_26,
INIT_27=>i_periph_iRAM_XLXI_1_INIT_27,
INIT_28=>i_periph_iRAM_XLXI_1_INIT_28,
INIT_29=>i_periph_iRAM_XLXI_1_INIT_29,
INIT_2a=>i_periph_iRAM_XLXI_1_INIT_2A,
INIT_2b=>i_periph_iRAM_XLXI_1_INIT_2B,
INIT_2c=>i_periph_iRAM_XLXI_1_INIT_2C,
INIT_2d=>i_periph_iRAM_XLXI_1_INIT_2D,
INIT_2e=>i_periph_iRAM_XLXI_1_INIT_2E,
INIT_2f=>i_periph_iRAM_XLXI_1_INIT_2F,
INIT_30=>i_periph_iRAM_XLXI_1_INIT_30,
INIT_31=>i_periph_iRAM_XLXI_1_INIT_31,
INIT_32=>i_periph_iRAM_XLXI_1_INIT_32,
INIT_33=>i_periph_iRAM_XLXI_1_INIT_33,
INIT_34=>i_periph_iRAM_XLXI_1_INIT_34,
INIT_35=>i_periph_iRAM_XLXI_1_INIT_35,
INIT_36=>i_periph_iRAM_XLXI_1_INIT_36,
INIT_37=>i_periph_iRAM_XLXI_1_INIT_37,
INIT_38=>i_periph_iRAM_XLXI_1_INIT_38,
INIT_39=>i_periph_iRAM_XLXI_1_INIT_39,
INIT_3a=>i_periph_iRAM_XLXI_1_INIT_3A,
INIT_3b=>i_periph_iRAM_XLXI_1_INIT_3B,
INIT_3c=>i_periph_iRAM_XLXI_1_INIT_3C,
INIT_3d=>i_periph_iRAM_XLXI_1_INIT_3D,
INIT_3e=>i_periph_iRAM_XLXI_1_INIT_3E,
INIT_3f=>i_periph_iRAM_XLXI_1_INIT_3F
)
      port map (ADDR=>AD(10 downto 0),
                CLK=> not CLK,
                DI=>DI,
                DIP(0)=>'0',
                EN=>en1,
                SSR=>'0',
                WE=>not web,
                DO=>DO1,
                DOP=>open);
   
      XLXI_2 : RAMB16_S9
generic map (
INIT_00=>i_periph_iRAM_XLXI_2_INIT_00,
INIT_01=>i_periph_iRAM_XLXI_2_INIT_01,
INIT_02=>i_periph_iRAM_XLXI_2_INIT_02,
INIT_03=>i_periph_iRAM_XLXI_2_INIT_03,
INIT_04=>i_periph_iRAM_XLXI_2_INIT_04,
INIT_05=>i_periph_iRAM_XLXI_2_INIT_05,
INIT_06=>i_periph_iRAM_XLXI_2_INIT_06,
INIT_07=>i_periph_iRAM_XLXI_2_INIT_07,
INIT_08=>i_periph_iRAM_XLXI_2_INIT_08,
INIT_09=>i_periph_iRAM_XLXI_2_INIT_09,
INIT_0a=>i_periph_iRAM_XLXI_2_INIT_0A,
INIT_0b=>i_periph_iRAM_XLXI_2_INIT_0B,
INIT_0c=>i_periph_iRAM_XLXI_2_INIT_0C,
INIT_0d=>i_periph_iRAM_XLXI_2_INIT_0D,
INIT_0e=>i_periph_iRAM_XLXI_2_INIT_0E,
INIT_0f=>i_periph_iRAM_XLXI_2_INIT_0F,
INIT_10=>i_periph_iRAM_XLXI_2_INIT_10,
INIT_11=>i_periph_iRAM_XLXI_2_INIT_11,
INIT_12=>i_periph_iRAM_XLXI_2_INIT_12,
INIT_13=>i_periph_iRAM_XLXI_2_INIT_13,
INIT_14=>i_periph_iRAM_XLXI_2_INIT_14,
INIT_15=>i_periph_iRAM_XLXI_2_INIT_15,
INIT_16=>i_periph_iRAM_XLXI_2_INIT_16,
INIT_17=>i_periph_iRAM_XLXI_2_INIT_17,
INIT_18=>i_periph_iRAM_XLXI_2_INIT_18,
INIT_19=>i_periph_iRAM_XLXI_2_INIT_19,
INIT_1a=>i_periph_iRAM_XLXI_2_INIT_1A,
INIT_1b=>i_periph_iRAM_XLXI_2_INIT_1B,
INIT_1c=>i_periph_iRAM_XLXI_2_INIT_1C,
INIT_1d=>i_periph_iRAM_XLXI_2_INIT_1D,
INIT_1e=>i_periph_iRAM_XLXI_2_INIT_1E,
INIT_1f=>i_periph_iRAM_XLXI_2_INIT_1F,
INIT_20=>i_periph_iRAM_XLXI_2_INIT_20,
INIT_21=>i_periph_iRAM_XLXI_2_INIT_21,
INIT_22=>i_periph_iRAM_XLXI_2_INIT_22,
INIT_23=>i_periph_iRAM_XLXI_2_INIT_23,
INIT_24=>i_periph_iRAM_XLXI_2_INIT_24,
INIT_25=>i_periph_iRAM_XLXI_2_INIT_25,
INIT_26=>i_periph_iRAM_XLXI_2_INIT_26,
INIT_27=>i_periph_iRAM_XLXI_2_INIT_27,
INIT_28=>i_periph_iRAM_XLXI_2_INIT_28,
INIT_29=>i_periph_iRAM_XLXI_2_INIT_29,
INIT_2a=>i_periph_iRAM_XLXI_2_INIT_2A,
INIT_2b=>i_periph_iRAM_XLXI_2_INIT_2B,
INIT_2c=>i_periph_iRAM_XLXI_2_INIT_2C,
INIT_2d=>i_periph_iRAM_XLXI_2_INIT_2D,
INIT_2e=>i_periph_iRAM_XLXI_2_INIT_2E,
INIT_2f=>i_periph_iRAM_XLXI_2_INIT_2F,
INIT_30=>i_periph_iRAM_XLXI_2_INIT_30,
INIT_31=>i_periph_iRAM_XLXI_2_INIT_31,
INIT_32=>i_periph_iRAM_XLXI_2_INIT_32,
INIT_33=>i_periph_iRAM_XLXI_2_INIT_33,
INIT_34=>i_periph_iRAM_XLXI_2_INIT_34,
INIT_35=>i_periph_iRAM_XLXI_2_INIT_35,
INIT_36=>i_periph_iRAM_XLXI_2_INIT_36,
INIT_37=>i_periph_iRAM_XLXI_2_INIT_37,
INIT_38=>i_periph_iRAM_XLXI_2_INIT_38,
INIT_39=>i_periph_iRAM_XLXI_2_INIT_39,
INIT_3a=>i_periph_iRAM_XLXI_2_INIT_3A,
INIT_3b=>i_periph_iRAM_XLXI_2_INIT_3B,
INIT_3c=>i_periph_iRAM_XLXI_2_INIT_3C,
INIT_3d=>i_periph_iRAM_XLXI_2_INIT_3D,
INIT_3e=>i_periph_iRAM_XLXI_2_INIT_3E,
INIT_3f=>i_periph_iRAM_XLXI_2_INIT_3F
)
      port map (ADDR=>AD(10 downto 0),
                CLK=> not CLK,
                DI=>DI,
                DIP(0)=>'0',
                EN=>en2,
                SSR=>'0',
                WE=>not web,
                DO=>DO2,
                DOP=>open);

   XLXI_3 : RAMB16_S9
generic map (
INIT_00=>i_periph_iRAM_XLXI_3_INIT_00,
INIT_01=>i_periph_iRAM_XLXI_3_INIT_01,
INIT_02=>i_periph_iRAM_XLXI_3_INIT_02,
INIT_03=>i_periph_iRAM_XLXI_3_INIT_03,
INIT_04=>i_periph_iRAM_XLXI_3_INIT_04,
INIT_05=>i_periph_iRAM_XLXI_3_INIT_05,
INIT_06=>i_periph_iRAM_XLXI_3_INIT_06,
INIT_07=>i_periph_iRAM_XLXI_3_INIT_07,
INIT_08=>i_periph_iRAM_XLXI_3_INIT_08,
INIT_09=>i_periph_iRAM_XLXI_3_INIT_09,
INIT_0a=>i_periph_iRAM_XLXI_3_INIT_0A,
INIT_0b=>i_periph_iRAM_XLXI_3_INIT_0B,
INIT_0c=>i_periph_iRAM_XLXI_3_INIT_0C,
INIT_0d=>i_periph_iRAM_XLXI_3_INIT_0D,
INIT_0e=>i_periph_iRAM_XLXI_3_INIT_0E,
INIT_0f=>i_periph_iRAM_XLXI_3_INIT_0F,
INIT_10=>i_periph_iRAM_XLXI_3_INIT_10,
INIT_11=>i_periph_iRAM_XLXI_3_INIT_11,
INIT_12=>i_periph_iRAM_XLXI_3_INIT_12,
INIT_13=>i_periph_iRAM_XLXI_3_INIT_13,
INIT_14=>i_periph_iRAM_XLXI_3_INIT_14,
INIT_15=>i_periph_iRAM_XLXI_3_INIT_15,
INIT_16=>i_periph_iRAM_XLXI_3_INIT_16,
INIT_17=>i_periph_iRAM_XLXI_3_INIT_17,
INIT_18=>i_periph_iRAM_XLXI_3_INIT_18,
INIT_19=>i_periph_iRAM_XLXI_3_INIT_19,
INIT_1a=>i_periph_iRAM_XLXI_3_INIT_1A,
INIT_1b=>i_periph_iRAM_XLXI_3_INIT_1B,
INIT_1c=>i_periph_iRAM_XLXI_3_INIT_1C,
INIT_1d=>i_periph_iRAM_XLXI_3_INIT_1D,
INIT_1e=>i_periph_iRAM_XLXI_3_INIT_1E,
INIT_1f=>i_periph_iRAM_XLXI_3_INIT_1F,
INIT_20=>i_periph_iRAM_XLXI_3_INIT_20,
INIT_21=>i_periph_iRAM_XLXI_3_INIT_21,
INIT_22=>i_periph_iRAM_XLXI_3_INIT_22,
INIT_23=>i_periph_iRAM_XLXI_3_INIT_23,
INIT_24=>i_periph_iRAM_XLXI_3_INIT_24,
INIT_25=>i_periph_iRAM_XLXI_3_INIT_25,
INIT_26=>i_periph_iRAM_XLXI_3_INIT_26,
INIT_27=>i_periph_iRAM_XLXI_3_INIT_27,
INIT_28=>i_periph_iRAM_XLXI_3_INIT_28,
INIT_29=>i_periph_iRAM_XLXI_3_INIT_29,
INIT_2a=>i_periph_iRAM_XLXI_3_INIT_2A,
INIT_2b=>i_periph_iRAM_XLXI_3_INIT_2B,
INIT_2c=>i_periph_iRAM_XLXI_3_INIT_2C,
INIT_2d=>i_periph_iRAM_XLXI_3_INIT_2D,
INIT_2e=>i_periph_iRAM_XLXI_3_INIT_2E,
INIT_2f=>i_periph_iRAM_XLXI_3_INIT_2F,
INIT_30=>i_periph_iRAM_XLXI_3_INIT_30,
INIT_31=>i_periph_iRAM_XLXI_3_INIT_31,
INIT_32=>i_periph_iRAM_XLXI_3_INIT_32,
INIT_33=>i_periph_iRAM_XLXI_3_INIT_33,
INIT_34=>i_periph_iRAM_XLXI_3_INIT_34,
INIT_35=>i_periph_iRAM_XLXI_3_INIT_35,
INIT_36=>i_periph_iRAM_XLXI_3_INIT_36,
INIT_37=>i_periph_iRAM_XLXI_3_INIT_37,
INIT_38=>i_periph_iRAM_XLXI_3_INIT_38,
INIT_39=>i_periph_iRAM_XLXI_3_INIT_39,
INIT_3a=>i_periph_iRAM_XLXI_3_INIT_3A,
INIT_3b=>i_periph_iRAM_XLXI_3_INIT_3B,
INIT_3c=>i_periph_iRAM_XLXI_3_INIT_3C,
INIT_3d=>i_periph_iRAM_XLXI_3_INIT_3D,
INIT_3e=>i_periph_iRAM_XLXI_3_INIT_3E,
INIT_3f=>i_periph_iRAM_XLXI_3_INIT_3F
)
      port map (ADDR=>AD(10 downto 0),
                CLK=> not CLK,
                DI=>DI,
                DIP(0)=>'0',
                EN=>en3,
                SSR=>'0',
                WE=>not web,
                DO=>DO3,
                DOP=>open);

  end Behavioral;
