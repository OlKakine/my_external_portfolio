library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity Compteur is
    port (cpt : out unsigned(16 downto 0);
          max : in unsigned(16 downto 0);
          clk : in std_logic;
          rst : in std_logic);
end Compteur;

architecture mixte of Compteur is
  signal cptq, cptd : unsigned(16 downto 0);
  signal rst_interne : std_logic;
component bascule_d_nbits is
    generic(
      n: positive :=8
    );
    port (d : in unsigned(n-1 downto 0);
          q : out unsigned(n-1 downto 0);
          clk : in std_logic;
          rst : in std_logic);
end component;

begin

    BASCULE: bascule_d_nbits
    generic map (
    n => 17
    )
    port map (
      d => cptd, 
      q=> cptq, 
      clk => clk,
      rst => rst_interne
    );

    cptd <= cptq + 1;
    cpt <= cptq; -- On utilise un signal interne pour ne pas lire sur la sortie

    -- On introduit ici l'affectation concurrente conditionnelle qui permet de représenter un multiplexeur 2v1
    rst_interne <= '1' when cptq = max else rst; 
end mixte;
