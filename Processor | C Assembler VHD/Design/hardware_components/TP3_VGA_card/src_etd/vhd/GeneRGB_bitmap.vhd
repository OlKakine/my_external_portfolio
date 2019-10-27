library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity GeneRGB is
    Port (
          X: in unsigned(9 downto 0);
          Y: in unsigned(8 downto 0);
          DATA: in unsigned(23 downto 0);
          CLK: in std_logic; -- Utile juste pour des optimisations
          R : OUT unsigned(4 downto 0);
          G : OUT unsigned(5 downto 0);
          B : OUT unsigned(4 downto 0);
          ADDR: out unsigned(16 downto 0)
	);
end GeneRGB;



architecture Behavioral of GeneRGB is
-- Conseils : 
-- 1) Pour générer l'adresse, vous pouvez utiliser les opérateurs * et +, mais pas les opérateurs / et mod.
-- 2) L'accès à un bit d'un vecteur est possible par exemple DATA(2) 
-- 3) De même, pour l'accès à un sous-vecteur. Exemple, DATA(4 downto 2) 
-- 4) & est l'opérateur de concaténation
-- 5) L'utilisation d'un signal pour exprimer la sortie du multiplexeur simplifie l'écriture. Ce signal peut être affecter en utilisant l'affectation conditionnel (val0 when condition0 else val1 when condition1 else ... else valn)
  signal PIXEL: unsigned(5 downto 0);
  signal POS: unsigned(1 downto 0);
  signal ADDRt: unsigned(17 downto 0);

begin
  --ADDR <= (X + 640*Y) srl 2;
  --ADDRt <= 160*Y +  X(9 downto 2);
  ADDR <= "00000000000000000" + (Y & "0000000") + (Y & "00000") + ("00" & X(9 downto 2));
  --ADDR <= ADDRt(16 downto 0);
  POS <= X(1 downto 0);
  
  PIXEL <= DATA(23 downto 18) when POS="00" else
           DATA(17 downto 12) when POS="01" else
           DATA(11 downto 6) when POS="10" else
           DATA(5 downto 0) ;
  
  R <= PIXEL(5 downto 4) & "000";
  G <= PIXEL(3 downto 2) & "0000";
  B <= PIXEL(1 downto 0) & "000";
end Behavioral;

