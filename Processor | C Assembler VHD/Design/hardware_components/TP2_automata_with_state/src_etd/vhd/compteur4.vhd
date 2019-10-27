library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Pour pouvoir utiliser les types et les opérations arithmétiques
use ieee.numeric_std.all;

entity compteur4 is
  port (
    clk :    in  std_logic;
    reset :  in  std_logic;
    -- la sortie cpt est un vecteur de 4 bits cpt(3), cpt(2), cpt(1), cpt(0)
    -- utilisable comme un nombre non signé, c'est-à-dire qu'on peut lui
    -- appliquer des opérateurs arithmétiques +, -, *, etc. ainsi que des
    -- comparaisons <, >,  <=, >=, =, /=
    cpt:     out unsigned (3 downto 0)
  );
end compteur4 ;

architecture mixte of compteur4 is

  -- Registre 4 bits
  component reg4b
    port (
      d   : in unsigned(3 downto 0);
      clk : in std_logic ;
      rst : in  std_logic;
      q   : out unsigned(3 downto 0)
      );
  end component;


  signal  dd :     unsigned(3 downto 0);
  signal  curval : unsigned(3 downto 0);
  signal rst_inactif : std_logic := '0';
  signal zero : unsigned(3 downto 0) := "0000"; 

  -- si on veut ne pas se servir du reset du registre
  -- instancier le registre avec
  --     rst => rst_inactif
  -- en declarant :
  --     signal  rstinactif : std_logic := '0';

begin
  REG: reg4b
    port map(
      d => dd,
      clk => clk,
      rst => rst_inactif,
      q => curval
      );
  
  process (reset,curval)
  begin
    if (reset = '0' ) then 
      dd <= curval + 1;
    else
      dd <= "0000";
    end if;
  end process;
  
  cpt <= curval;

end mixte;

