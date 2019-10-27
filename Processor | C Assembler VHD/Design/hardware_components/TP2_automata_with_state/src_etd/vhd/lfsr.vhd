-- Ceci est une ligne de commentaires

---------------------------------------
-- lfsr.vhd
-- Description du LFSR du TP2 en VHDL

-- Ce fichier décrit le composant ``lfsr'' dans le langage VHDL.
-- La description d'un composant en VHDL se compose de deux parties :
--   - Une partie entité (``entity'') définissant le composant et ses
--     entrées/sorties
--   - Une partie architecture (``architecture'') décrivant le fonctionnement
--     du circuit
---------------------------------------

-- Les mot-clés ``library'' et ``use'' permettent d'indiquer le nom des
-- bibliothèques que ce composant va utiliser.
-- STD_LOGIC_1164 permet de définir le type std_logic utilisé pour décrire un
-- bit
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Avec le mot-clé ``entity'', on définit un composant et ses entrée/sorties.
-- Ici, on définit l'entité nommé lfsr, ayant 3 ports :
--    - Un port d'entrée ``clk'' sur un bit (type std_logic)
--    - Un port d'entrée ``reset'' sur un bit (type std_logic)
--    - Un port de sortie ``s'' sur un bit (type std_logic)
entity lfsr is
    port ( clk:     in  std_logic;
           reset:   in  std_logic;
           s:  out std_logic); -- Notez la position des points-virgules
end lfsr;

-- Avec le mot-clé ``architecture'', on décrit le fonctionnement du circuit.
-- Ce fonctionnement peut être décrit de manière comportementale (description
-- effective de la fonctionnalité) ou structurelle (Instanciation de composants
-- définis par ailleurs, càd soit dans une bibliothèque déclarée, soit dans le
-- projet en cours).
-- Ici, l'architecture du composant lfsr s'appelle ``mixte''.
architecture mixte of lfsr is

    -- Pour pouvoir instancier un composant (approche structurelle), il faut
    -- au préalable le déclarer.
    -- Ici, nous déclarons le composant ``basc_D'' (inclus dans le projet).
    -- Vous pouvez consulter sa définition dans le fichier
    -- ``vhd/basc_d.vhd''.
    component basc_D is
        port (  clk:    in  std_logic;
                d:      in  std_logic;
                q:      out std_logic;
                reset:  in  std_logic);
    end component;
    -- Remarquez la similitude entre la définition d'une entité et la
    -- déclaration d'un composant.

    -- Avec le mot-clé ``signal'', on déclare les signaux internes du circuit.
    -- Pour simplifier, ces signaux correspondent aux fils de votre schéma.
    -- Ici, on déclare six signaux de type ``std_logic''.
    signal q3, q2, q1, q0: std_logic;
    signal d3, d2: std_logic;

begin
    -- D'un point de vue structurel, on peut instancier des composants avec
    -- le mot-clé ``port map''
    -- Par exemple, le code suivant permet d'instancier une bascule D, nommée
    -- ``FD3''. Comme prévu par le schéma, cette bascule est connectée par
    -- Instanciation de quatre bascules D et connexion de leurs entrées/sorties
    -- aux signaux du circuit.
    FD3: basc_D
    port map (  clk     => clk,         -- Connexion du port ``clk'' du
                                        -- composant ``basc_D'' au signal
                                        -- ``clk'' (entrée du composant lfsr).
                d       => d3,          -- Connexion du port ``d'' du
                                        -- composant ``basc_D'' au signal
                                        -- ``d3''
                q       => q3,          -- Connexion du port ``q'' du
                                        -- composant ``basc_D'' au signal
                                        -- ``q3''
                reset   => reset);      -- Connexion du port ``reset'' du
                                        -- composant ``basc_D'' au signal
                                        -- ``reset'' (entrée du composant lfsr).

    -- Charge à vous d'instancier les bascules FD2, FD1 et FD0.
    -- Les signaux ``d1'' et ``d0'' ne sont pas nécessaires.
    FD2: basc_D
    port map (  clk     => clk,
                d       => d2,
                q       => q2,
                reset   => reset);

    FD1: basc_D
    port map (  clk     => clk,
                d       => q2,
                q       => q1,
                reset   => reset);

    FD0: basc_D
    port map (  clk     => clk,
                d       => q1,
                q       => q0,
                reset   => reset);

    -- Il existe de multiples façons de décrire le circuit d'un point de vue
    -- comportemental. L'affectation concurrente (``<='') est la plus simple.
    -- D'un point logique, il est possible d'utiliser les opérateurs booléens
    -- suivants : and, or, nand, nor, xor, xnor, not.
    -- Voici les affectations concurrentes nécessaires pour représenter le LFSR
    -- du TP.
    s   <= q0;              -- Affectation du signal ``q0'' au port
                            -- de sortie ``s'' du module lfsr
    d3  <= q1 xnor q0;      -- Affectation du resultat du xnor entre les
                            -- signaux ``q1'' et ``q0'' au signal ``d3''
    d2  <= not q3;

end mixte;

