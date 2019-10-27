library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity bascule_d_nbits is
    generic(
      n: positive :=8);
    port (d   : in unsigned(n-1 downto 0);
          q   : out unsigned(n-1 downto 0);
          clk : in std_logic;
          rst : in std_logic);
end bascule_d_nbits;

architecture Behavioral of bascule_d_nbits is
begin
   process (clk)
   begin
      if rising_edge(clk) then
        if rst='1' then
          q <= (others => '0');
        else
          q <= d;
        end if;
      end if;
   end process;
end Behavioral;
