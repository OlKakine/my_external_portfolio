library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity reg4b is
    port (d   : in  unsigned(3 downto 0);
          clk : in  std_logic;
          rst : in  std_logic;
          q   : out unsigned(3 downto 0));
end reg4b;

-- Le mot clé "others" permet de définir plusieurs valeur du vecteur q en une
-- fois. Une autre façon de faire de spécifier les bits un par un de la façon
-- suivante:
--   q <= (0 => '0',
--         1 => '0',
--         2 => '0',
--         3 => '0');
-- "others" est un raccourci permettant de définir tous les bits qui n'ont
-- pas encore été définis. Les deux méthodes peuvent être combinées pour
-- définir la valeur de quelques bits et donner une valeur par défaut aux
-- autres.
architecture Behavioral of reg4b is
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

