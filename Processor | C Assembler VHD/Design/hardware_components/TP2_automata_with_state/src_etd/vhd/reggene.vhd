library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity reggene is
    -- parametre statique (c'est-à-dire que ce n'est pas un fil du circuit, c'est une
    -- directive de construction du circuit qui signifie : prendre le modèle
    -- reggene et l'instancier avec la taille n)
    generic(
      n: positive :=8  -- 8 est la valeur par défaut si on ne spécifie rien
      );
    port (d   : in  unsigned(n-1 downto 0);
          clk : in  std_logic;
          rst : in  std_logic;
          q   : out unsigned(n-1 downto 0));
end reggene;

architecture Behavioral of reggene is
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

