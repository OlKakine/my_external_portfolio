library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity global is
    port ( clk:     in  std_logic;
           reset:   in  std_logic;
           s:       out std_logic
            );
end global;

architecture structural of global is
    component auto is
        port ( clk:     in  std_logic;
               reset:   in  std_logic;
               e:       in  std_logic;
               s:       out std_logic);
    end component;

    component lfsr is
        port ( clk:     in  std_logic;
               reset:   in  std_logic;
               s:       out std_logic);
    end component;

    signal lfsr_gen: std_logic;
    
begin
  AUT: auto
    port map(
      clk => clk,
      reset => reset,
      e => lfsr_gen,
      s => s
      );

  LFS: lfsr
    port map(
      clk => clk,
      reset => reset,
      s => lfsr_gen
      );

end structural;

