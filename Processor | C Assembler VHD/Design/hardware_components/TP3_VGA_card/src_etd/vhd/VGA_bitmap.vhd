library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

ENTITY VGA IS
    PORT( CLK : IN std_logic;
          HS : OUT std_logic;
          VS : OUT std_logic;
          R : OUT unsigned(4 downto 0);
          G : OUT unsigned(5 downto 0);
          B : OUT unsigned(4 downto 0)
      );
END VGA;

ARCHITECTURE Behavioral OF VGA IS

    COMPONENT GeneSync
        Port ( CLK : in std_logic;
               HSYNC : out std_logic;
               VSYNC : out std_logic;
               IMG : out std_logic;
               X : out unsigned(9 downto 0);
               Y : out unsigned(8 downto 0)
           );
    END COMPONENT;


    component GeneRGB
    	Port (
		X: in unsigned(9 downto 0);
		Y: in unsigned(8 downto 0);
		DATA: in unsigned(23 downto 0);
		CLK: in std_logic;
        R : OUT unsigned(4 downto 0);
        G : OUT unsigned(5 downto 0);
        B : OUT unsigned(4 downto 0);
		ADDR: out unsigned(16 downto 0)
	);
    end component;

    component RAM_VIDEO is
  	port (
	    clk  : in    std_logic;
	    addr : in    unsigned (16 downto 0);
	    do   : out   unsigned(23 downto 0);
            we   : in    std_logic
	    );
    end component;

    -- Signaux internes
    signal AD: unsigned(16 downto 0);
    signal DATA: unsigned(23 downto 0);
    signal Xi : unsigned(9 downto 0);
    signal Yi : unsigned(8 downto 0);
    signal IMGi: std_logic;
    signal Ri : unsigned(4 downto 0);
    signal Gi : unsigned(5 downto 0);
    signal Bi : unsigned(4 downto 0);
BEGIN
    cRAM_VIDEO: RAM_VIDEO port map(CLK => CLK, ADDR => AD, DO =>DATA, WE=> '0');
    cGeneSync: GeneSync PORT MAP(HSYNC => HS, VSYNC => VS, IMG => IMGi,
                                 X => Xi, Y => Yi, CLK => CLK);
    cGeneGRB: GeneRGB port map(X => Xi, Y => Yi, R => Ri, G => Gi, B => Bi, DATA => DATA, CLK => CLK, ADDR => AD);

    R <= Ri when IMGi ='1' else (others =>'0');
    G <= Gi when IMGi ='1' else (others =>'0');
    B <= Bi when IMGi ='1' else (others =>'0');

END Behavioral;
