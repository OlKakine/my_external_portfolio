library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity auto is
    port ( clk:     in  std_logic;
           reset:   in  std_logic;
           e:       in  std_logic;
           s:       out std_logic);
end auto;

architecture structural of auto is

component basc_D is
    port (  clk:    in  std_logic;
            d:      in  std_logic;
            q:      out std_logic;
            qb:     out std_logic;
            reset:  in  std_logic);
end component;

signal D0,D1,D2,Q0,Q1,Q2: std_logic;

begin

FD0: basc_D
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

D2 <= Q1 and Q0 and e;
D1 <= (q1 and not q0) or (not e and (Q2 or Q0));
D0 <= e and (not Q0 or not Q1);
s <= Q2;

end structural;

