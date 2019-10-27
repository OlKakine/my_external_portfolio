library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity auto_unparmin is
    port ( clk:     in  std_logic;
           reset:   in  std_logic;
           e:       in  std_logic;
           s:       out std_logic);
end auto_unparmin;

architecture structural of auto_unparmin is

component basc_D is
    port (  clk:    in  std_logic;
            d:      in  std_logic;
            q:      out std_logic;
            qb:     out std_logic;
            reset:  in  std_logic);
end component;

component basc_D_set is
    port (  clk:    in  std_logic;
            d:      in  std_logic;
            q:      out std_logic;
            qb:     out std_logic;
            reset:  in  std_logic);
end component;

signal D0, D1, D2, D3, D4, Q0, Q1, Q2, Q3, Q4: std_logic;

begin
  FD0: basc_D_set
  port map(
    clk => clk,
    d => D0,
    q => Q0,
    qb => open,
    reset => reset
    );
  
  FD1: basc_D
  port map(
    clk => clk,
    d => D1,
    q => Q1,
    qb => open,
    reset => reset
    );
  
  FD2: basc_D
  port map(
    clk => clk,
    d => D2,
    q => Q2,
    qb => open,
    reset => reset
    );
  
  FD3: basc_D
  port map(
    clk => clk,
    d => D3,
    q => Q3,
    qb => open,
    reset => reset
    );
  
  FD4: basc_D
  port map(
    clk => clk,
    d => D4,
    q => Q4,
    qb => open,
    reset => reset
    );

  D0 <= Q0 and not e;
  D1 <= (Q0 or Q1 or Q4) and e;
  D2 <= (Q2 or Q3 or Q1 or Q4) and (not e);
  D3 <= Q2 and e;
  D4 <= Q3 and e;
  s <= Q4;
  
end structural;

