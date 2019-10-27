library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity PC is
        port ( clk:    in  std_logic;
               reset:  in  std_logic;
               start: in  std_logic;
               inf  :  in std_logic;
               egal :  in  std_logic;
               getA:   out  std_logic;
               getB:   out  std_logic;
               subBA:  out  std_logic;
               ldA:    out  std_logic;
               ldB:    out  std_logic;
               done  : out  std_logic
       );
end PC;

architecture mixte of PC is
-- Déclaration des composants BDC et BDS
-- Aller voir ce qu'ils font dans le fichier .vhd correspondant.
   component BDC
      port ( C   : in    std_logic; 
             CLR : in    std_logic; 
             D   : in    std_logic; 
             Q   : out   std_logic
				 );
   end component;
   component BDS
      port ( C   : in    std_logic; 
             D   : in    std_logic; 
             S   : in    std_logic; 
             Q   : out   std_logic
				 );
   end component;

   signal q0,q1,q2,q3,q4,q5,d0,d1,d2,d3,d4,d5: std_logic;

begin
-- A completer
  E0: BDS
    port map(
      C => clk,
      S   => reset,
      D => d0,
      Q => q0);

  E1: BDC
    port map(
      C => clk,
      CLR => reset,
      D => d1,
      Q => q1);

  E2: BDC
    port map(
      C => clk,
      CLR => reset,
      D => d2,
      Q => q2);

  E3: BDC
    port map(
      C => clk,
      CLR => reset,
      D => d3,
      Q => q3);
  
  E4: BDC
    port map(
      C => clk,
      CLR => reset,
      D => d4,
      Q => q4);

  E5: BDC
    port map(
      C => clk,
      CLR => reset,
      D => d5,
      Q => q5);

  d0 <= q5 or (not start and q0);
  d1 <= start and q0;
  d2 <= q1 or q3 or q4;
  d3 <= not egal and not inf and q2;
  d4 <= not egal and inf and q2;
  d5 <= q2 and egal;

  done <= q5;
  getA <= q1;
  ldA <= q1 or q3;
  getB <= q1;
  ldB <= q1 or q4;
  subBA <= q4;
  
  
end mixte;
