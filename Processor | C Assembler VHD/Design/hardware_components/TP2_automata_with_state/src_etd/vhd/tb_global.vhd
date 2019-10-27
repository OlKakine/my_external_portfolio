library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_global is
        end tb_global;

architecture behavioral of tb_global is
        component global is
                port ( clk:     in  std_logic;
                       reset:   in  std_logic;
                       s:       out std_logic);
        end component;

        signal clk:     std_logic := '0';
        constant clk_period : time := 8 ns;
        signal reset:   std_logic;
        signal s:       std_logic;

begin

        C_global: global
        port map (  clk     => clk,
                    reset   => reset,
                    s       => s);

        process
        begin
                clk <= not clk;
                wait for clk_period/2 ;
        end process;

        process
        begin
                reset <= '1';
                wait for 3*clk_period/2;
                reset <= '0';
                wait;
        end process;
end behavioral;

