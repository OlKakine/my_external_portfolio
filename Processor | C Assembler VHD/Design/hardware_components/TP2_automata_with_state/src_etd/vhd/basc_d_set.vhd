library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity basc_D_set is
    port (  clk:    in  std_logic;
            d:      in  std_logic;
            q:      out std_logic;
            qb:     out std_logic;
            reset:  in  std_logic);
end basc_D_set;

architecture behavioral of basc_D_set is
    signal val: std_logic;
begin
    -- Utilisation d'un processus avec une liste de sensibilité
    -- Le processus sera déclenché chaque fois qu'un des signaux de la liste
    -- change. Ici, soit clk soit le signal reset
    process (clk,reset) -- bascule D avec entrée de remise à zéro asynchrone
    begin
        if reset='1' then
            val <= '1'; -- remise à zéro de la bascule
        elsif clk'event and clk='1' then -- détection d'un front montant
            val <= d; -- acquisition d'une valeur
        end if;
    end process;

    qb <= not(val);
    q <= val;
end behavioral;

