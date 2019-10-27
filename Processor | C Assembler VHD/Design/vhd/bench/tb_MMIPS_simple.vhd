library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity tb_mmips_simple  is
  end tb_mmips_simple ;

architecture behavior of tb_mmips_simple is

  component MMIPS_simple
  port (
         clk    : in  std_logic;
         reset  : in  std_logic;
         switch : in  unsigned(2 downto 0);
         push   : in  std_logic;
         led    : out  unsigned(3 downto 0)
       );
  end component;

  signal clk    :  std_logic:='0';
  signal reset  :  std_logic;
  signal led    :  unsigned(3 downto 0);
  signal switch :  unsigned(2 downto 0);
  signal push   :  std_logic;

begin

  C_MMIPS_IO : MMIPS_simple
  port map(
            clk    => clk,
            reset  => reset,
            led    => led,
            switch => switch,
            push   => push
          );

  gen_horloge: process
  begin
    clk<='1';
    wait for 10 ns;
    clk<='0';
    wait for 10 ns;
  end process;

  tb : process
  begin
    reset  <= '1';
    switch <= "000";
    push   <= '0';
    for i in 1 to 6 loop
      wait until rising_edge(clk);
    end loop;
    reset <= '0';

    -- Ajouter ici le reste du scnénario à effectuer
    -- attention, la fréquence d'horloge du banc d'essai n'est
    -- pas la même que celle du processeur
--a_supprimer_debut
    for i in 1 to 50 loop
        wait until rising_edge(clk);
    end loop;
    push <= '1'; --interruption
    for i in 1 to 3 loop
        wait until rising_edge(clk);
    end loop;
    push <= '0'; --interruption fini
--a_supprimer_fin
  wait; -- will wait forever
  end process;

end;
