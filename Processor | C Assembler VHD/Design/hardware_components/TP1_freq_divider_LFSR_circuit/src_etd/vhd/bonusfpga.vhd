library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity bonusfpga is
    port ( clk:     in  std_logic;
           reset:   in  std_logic;
           s0:  out std_logic;
           s1:  out std_logic;
           s2:  out std_logic;
           s3:  out std_logic);
end bonusfpga ;

architecture mixte of bonusfpga is

    component AC is
    port ( a:  in  std_logic;
           b:  in  std_logic;
           c:  in  std_logic;
           s:  out std_logic;
           co: out std_logic);
    end component;
    component div_freq is
    port ( clk:     in  std_logic;
           s:  out std_logic;
           reset:  in  std_logic);
    end component;
    component basc_D is
    port (  clk:    in  std_logic;
            d:      in  std_logic;
            q:      out std_logic;
            qb:     out std_logic;
            reset:  in  std_logic);
    end component;

    constant facteur : integer := 25;
    signal tmpH: std_logic_vector(facteur downto 0);
    signal fil1, fil2, fil3, D0, D1, D2, D3, SC0, SC1, SC2, SC3: std_logic;

begin
    -- On génére une horloge à l'Hertz comme pour le LFSR
    Div0: div_freq port map (
         clk => clk,
         s => tmpH(0),
         reset => reset);

    Horloge:
    for i in 0 to facteur -1 generate 
            DivX: div_freq port map (
                 clk => tmpH(i),
                 s => tmpH(i+1),
                 reset => reset);
    end generate Horloge;

    -- tmpH(facteur) est l'horloge à utiliser pour le reste du circuit
    -- A compléter en fonction du circuit mystère fourni par l'enseignant
    
    AC0: AC port map (
      a => SC0,
      b => '1',
      c => '0',
      co => fil1 ,
      s => D0
      );

    AC1: AC port map (
      a => SC1,
      b => '1',
      c => fil1,
      co => fil2 ,
      s => D1
      );

    AC2: AC port map (
      a => SC2,
      b => '0',
      c => fil2,
      co => fil3 ,
      s => D2
      );

    AC3: AC port map (
      a => SC3,
      b => '0',
      c => fil2,
      co => open ,
      s => D3
      );

    FD0: basc_d port map(
      d => D0,
      q => SC0,
      qb => open,
      clk => tmpH(facteur),
      reset => reset);
    
    FD1: basc_d port map(
      d => D1,
      q => SC1,
      qb => open,
      clk => tmpH(facteur),
      reset => reset);
    
    FD2: basc_d port map(
      d => D2,
      q => SC2,
      qb => open,
      clk => tmpH(facteur),
      reset => reset);
    
    FD3: basc_d port map(
      d => D3,
      q => SC3,
      qb => open,
      clk => tmpH(facteur),
      reset => reset);

    s0 <= SC0;
    s1 <= SC1;
    s2 <= SC2;
    s3 <= SC3;
    

end mixte;

