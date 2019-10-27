library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity tb_mmips_complet  is
end tb_mmips_complet ;

architecture behavior of tb_mmips_complet is 

  component MMIPS_complet
  port (
         clk    : in  std_logic;
         reset  : in  std_logic;
         switch : in  unsigned(3 downto 0);
         push   : in  unsigned(2 downto 0);
         led    : out  unsigned(3 downto 0);
         R      : out  unsigned(4 downto 0);
         G      : out  unsigned(5 downto 0);
         B      : out  unsigned(4 downto 0);
         HS     : out  std_logic;
         VS     : out  std_logic
       );
  end component;

  signal clk    :  std_logic:='0';
  signal reset  :  std_logic;
  signal switch :  unsigned(3 downto 0);
  signal push   :  unsigned(2 downto 0);
  signal led    :  unsigned(3 downto 0);
  signal R      :  unsigned(4 downto 0);
  signal G      :  unsigned(5 downto 0);
  signal B      :  unsigned(4 downto 0);
  signal HS     :  std_logic;
  signal VS  :  std_logic;
  
begin

  C_MMIPS_IO : MMIPS_complet
    port map(
      clk => clk ,
      reset => reset ,
      switch    => switch    ,
      push      => push      ,
      led       => led       ,
      R         => R         ,
      G         => G         ,
      B         => B         ,
      HS        => HS        ,
      VS        => VS        
      );
  
  process 
  begin
    clk<='1';
    wait for 10 ns;
    clk<='0';
    wait for 10 ns;
  end process;

  
  tb : process
  begin
    reset<='1';
    switch<=x"3";
    push<="010";
    for i in 1 to 6 loop    
      wait until rising_edge(clk);
    end loop;
    reset<='0';   
    switch<=x"6";
    push<="111";
    for i in 0 to 10 loop    
      wait until rising_edge(clk);
      switch <= switch + 1 ; 
    end loop;

    -- place stimulus here

    wait; -- will wait forever
  end process;

end;
