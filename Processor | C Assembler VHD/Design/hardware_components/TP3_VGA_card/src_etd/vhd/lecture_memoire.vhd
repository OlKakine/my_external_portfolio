library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity lecture_memoire is
    port (data : out unsigned(23 downto 0);
          clk : in std_logic;
          rst : in std_logic);
end lecture_memoire;

architecture mixte of lecture_memoire is

  component Compteur is
      port (cpt : out unsigned(16 downto 0);
            max : in unsigned(16 downto 0);
            clk : in std_logic;
            rst : in std_logic);
  end component;

  component RAM_Video is
    port (
      clk  : in    std_logic;
      addr : in    unsigned (16 downto 0);
      do   : out   unsigned(23 downto 0);
      we   : in    std_logic
      );
  end component;

  -- Ajouter ici les signaux internes nécessaires
  -- Utiliser les mêmes types de signaux en interne que vu en externe
  signal count: unsigned(16 downto 0);
  signal rgb: unsigned(23 downto 0);

begin
-- A COMPLETER
  COMPT: Compteur
    port map(
      cpt => count,
      --max => unsigned := 131072,
      max => (others => '1'),
      clk => clk,
      rst => rst);

  RAM: RAM_Video
    port map(
      clk => clk,
      addr => count,
      do => rgb,
      we => '0');

  data <= rgb when count/3 mod 16 = 0;

end mixte;
