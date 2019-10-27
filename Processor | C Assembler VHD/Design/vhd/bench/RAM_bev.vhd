library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use std.textio.all;
use ieee.STD_LOGIC_TEXTIO.all;

use work.MMIPS_pkg.all;

entity RAM_bev  is
    generic (
    nbit_addr : integer;
    init_from_file : boolean := false;
    file_name : string := ""
);
port ( 
         clk  : in    std_logic;
         addr : in   unsigned(nbit_addr-1 downto 0);
         do   : out  w32;
         di   : in   w32;
         ce   : in   std_logic;
         we   : in   std_logic
     );
end RAM_bev;

architecture behavioral of RAM_bev is
    type zone_memoire is array (natural range 0 to 2**nbit_addr-1) of w32;
        signal m: zone_memoire := (others=>w32_zero);
begin

    process(clk)
        variable ram_init : boolean := false;
        file ram_file : text open read_MODE is file_name;
        variable ligne_texte, buf : line ;
        variable dta : std_logic_vector(31 downto 0);
        variable addr_file : integer:=0;
        variable c : character;
    begin 
        if (clk'event AND clk='1') then
            if (init_from_file and not ram_init)  then
                while not endfile(ram_file) loop
                    readline(ram_file, ligne_texte);
                    if ligne_texte(1)='@' then
                        read(ligne_texte,c);
                        hread(ligne_texte, dta);
                        addr_file := to_integer(unsigned(dta(30 downto 2)));  --les adresses sont en octets !!!
                    else
                        hread(ligne_texte, dta);
                        m(addr_file) <= w32(dta);
                        addr_file := addr_file+1;
                    end if;
                end loop;
                ram_init:=true;	
            end if;
            if ce = '1'then
                do <= m(to_integer(addr));
                if we='1' then
                    m(to_integer(addr)) <= di;
                end if;
            else
                do <= (others => '0');
            end if;
        end if;
    end process;
end behavioral;
