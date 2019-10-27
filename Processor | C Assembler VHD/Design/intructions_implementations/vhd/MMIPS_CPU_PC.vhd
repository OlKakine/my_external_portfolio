library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.MMIPS_pkg.all;

entity MMIPS_CPU_PC is
  Port (
    clk    : in  STD_LOGIC;
    rst    : in  STD_LOGIC;
    cmd    : out MMIPS_PO_cmd;
    status : in MMIPS_PO_status
    );
end MMIPS_CPU_PC;

architecture RTL of MMIPS_CPU_PC is
  type State_type is (S_Error,
                      S_Init,
                      S_Fetch_wait,
                      S_Fetch,
                      S_Decode,
                      S_FUNCI,
                      S_FUNC,
                      S_J_JAL,
                      S_JALR,
                      S_EQ,
                      S_COMP,
                      S_BRANCH,
                      S_BAL_TRUE,
                      S_BAL_FALSE,
                      S_LOAD,
                      S_LOAD2,
                      S_LOAD3,
                      S_LOAD4,
                      S_STORE,
                      S_STORE2,
                      S_SLT1,
                      S_SLT0
                      );

  signal state_d, state_q : State_type;
begin
  FSM_synchrone : process(clk)
  begin
    if clk'event and clk='1' then
      if rst='1' then
        state_q <= S_Init;
      else
        state_q <= state_d;
      end if;
    end if;
  end process FSM_synchrone;

  FSM_comb : process (state_q, status)
  begin
    state_d <= state_q;
    -- pré-affectation de commandes (cf MMIPS_pkg.vhd)
    cmd <= MMIPS_PO_cmd_zero;
    case state_q is
      when S_Error =>
        state_d <= S_Error;
        
      when S_Init =>
      -- PC <- 0 + 0
        cmd.ALU_X_sel <= UXS_cst_x00;
        cmd.ALU_Y_sel <= UYS_cst_x00;
        cmd.ALU_OP <= AO_plus;
        cmd.PC_we <= true;
        state_d <= S_Fetch_wait;

      when S_Fetch_wait =>
      -- mem[PC]
        cmd.mem_ce <= true;
        state_d <= S_Fetch;

      when S_Fetch =>
      -- IR <- mem_datain
        cmd.IR_we <= true;
        cmd.ADDR_sel <= ADDR_from_PC;--devrait être dans fetch wait? automatique?
        state_d <= S_Decode;
      when S_Decode =>	
      -- PC <- PC + 4
        cmd.ALU_X_sel <= UXS_PC;
        cmd.ALU_Y_sel <= UYS_cst_x04;
        cmd.ALU_OP <= AO_plus;
        cmd.PC_we <= true;
        state_d <= S_Init;
        case status.IR(31 downto 29) is
          when "001" =>--opérations sur immédiats
            state_d <= S_FUNCI;
          when "000" =>
            case status.IR(28 downto 26) is
              when "000" =>--special
                state_d <= S_FUNC;                
              when "001" =>--regimm
                state_d <= S_COMP;
              when others =>                
                case status.IR(28) is
                  
                  when '0' => --j/jal
                    state_d <= S_J_JAL;
                    case status.IR(26)is
                      when '1' => --jal
                        cmd.RF_Sel <= RFS_31;
                        cmd.RF_we <= true;
                      when others => null;
                    end case;
                    
                  when '1' => --beq/bne/blez/bgtz
                    case status.IR(27) is
                      when '0' => --beq/bne
                        state_d <= S_EQ;
                      when '1' => -- blez/bgtz
                        state_d <= S_COMP;
                      when others => null;
                    end case;
                                        
                  when others => null;
                end case;
                
            end case;
          when "100" => --lw
            state_d <= S_LOAD;
          when "101" => --sw
            state_d <= S_STORE;
          when others => null;
        end case;

      when S_FUNCI =>
        cmd.RF_Sel <= RFS_RT;
        cmd.RF_we <= true;
        cmd.ALU_X_sel <= UXS_RF_RS;
        cmd.mem_ce <= true;
        state_d <= S_FETCH;
        case status.IR(28 downto 27) is
          when "00" =>  -- addi/addiu
            cmd.ALU_Y_sel <= UYS_IR_imm16_ext;
            cmd.ALU_OP <= AO_plus;
          when "01" => -- slti/sltiu
            cmd.ALU_Y_sel <= UYS_IR_imm16_ext;
            cmd.ALU_OP <= AO_moins;
            cmd.RF_we <= false;
            cmd.mem_ce <= false;
            case status.IR(0) is 
              when '0' => -- slti
                cmd.ALU_extension_signe <= '1';
                case status.c is
                  when true =>
                    state_d <= S_SLT1;
                  when false =>
                    state_d <= S_SLT0;
                  when others => null;
                end case;
                
              when '1' => -- sltiu
                cmd.ALU_extension_signe <= '0';
                case status.s is
                  when true =>
                    state_d <= S_SLT1;
                  when false =>
                    state_d <= S_SLT0;
                  when others => null;
                end case;
              when others => null;
            end case;            
                                
          when others =>
            cmd.ALU_Y_sel <= UYS_IR_imm16;
            case status.IR(27 downto 26) is
              when "00" =>  -- andi
                cmd.ALU_OP <= AO_and;
              when "01" =>  -- ori
                cmd.ALU_OP <= AO_or;
              when "10" =>  -- xori
                cmd.ALU_OP <= AO_xor;
              when "11" =>  -- lui
                cmd.ALU_X_sel <= UXS_cst_x10;
                cmd.ALU_OP <= AO_SLL;
              when others => null;
            end case;
        end case;
        
      when S_JALR => --2eme op jalr: pc <- rs
        cmd.PC_we <= true; --mettre result dans PC
        cmd.ALU_X_sel <= UXS_RF_RS;
        cmd.ALU_Y_sel <= UYS_cst_x00;
        cmd.ALU_OP <= AO_plus;
        state_d <= S_FETCH_WAIT;

      when S_J_JAL =>
        cmd.ALU_X_sel <= UXS_PC_up;
        cmd.ALU_Y_sel <= UYS_IR_imm26;
        cmd.ALU_OP <= AO_or;
        cmd.PC_we <= true;
        state_d <= S_FETCH_WAIT;

      when S_EQ =>
        cmd.ALU_OP <= AO_moins;
        cmd.ALU_Y_sel <= UYS_RF_RT;
        cmd.ALU_X_sel <= UXS_RF_RS;
        cmd.mem_ce <= true;

        if (status.IR(26)='0' and status.z=true) or (status.IR(26)='1' and status.z=false) then
          state_d <= S_BRANCH; --on branch si on est dans beq et res=0 ou si on est
                               --dans bne et res!=0
        else
          state_d <= S_FETCH;
        end if;       

      when S_COMP =>
        cmd.ALU_OP <= AO_plus;
        cmd.ALU_X_sel <= UXS_RF_RS;
        cmd.ALU_Y_sel <= UYS_cst_x00;
        cmd.mem_ce <= true;

        case status.IR(28) is --regimm or not
          when '1' => --not regimm
            if (status.z=false and status.s=false and status.IR(26)='1') or
              ((status.z=true or status.s=true) and status.IR(26)='0') then
              state_d <= S_BRANCH;
            else
              state_d <= S_FETCH;
            end if;
            
          when '0' => --regimm
            case status.IR(20) is -- bal or not
              when '0' => --not bal
                if (status.z=false and status.s=true and status.IR(16)='0') or
                  ((status.z=true or status.s=false) and status.IR(16)='1') then
                  state_d <= S_BRANCH;
                else
                  state_d <= S_FETCH;
                end if;
              when '1' => --bal
                if (status.z=false and status.s=true and status.IR(16)='0') or
                  ((status.z=true or status.s=false) and status.IR(16)='1') then
                  state_d <= S_BAL_TRUE; --branch apres addr dans 31
                else
                  state_d <= S_BAL_FALSE;--branch pas apres addr 31
                end if; 
              when others => null;
            end case;
            
          when others => null;
        end case;
        
      when S_BAL_TRUE =>
        cmd.ALU_OP <= AO_plus;
        cmd.ALU_X_sel <= UXS_PC;
        cmd.ALU_Y_sel <= UYS_cst_x00;
        cmd.RF_Sel <= RFS_31;
        cmd.RF_we <= true;
        state_d <= S_BRANCH;

      when S_BAL_FALSE =>
        cmd.ALU_OP <= AO_plus;
        cmd.ALU_X_sel <= UXS_PC;
        cmd.ALU_Y_sel <= UYS_cst_x00;
        cmd.RF_Sel <= RFS_31;
        cmd.RF_we <= true;
        cmd.mem_ce <= true;
        state_d <= S_FETCH;

      when S_BRANCH =>
        cmd.ALU_OP <= AO_plus;
        cmd.ALU_Y_sel <= UYS_IR_imm16_ext_up;
        cmd.ALU_X_sel <= UXS_PC;
        cmd.PC_we <= true;
        state_d <= S_FETCH_WAIT;
        
      when S_FUNC =>
        case status.IR(5) is
          when '1' =>   -- Arithmetics with registers
            cmd.ALU_Y_sel <= UYS_RF_RT;
            cmd.ALU_X_sel <= UXS_RF_RS;
            cmd.RF_Sel <= RFS_RD;
            cmd.RF_we <= true;
            cmd.mem_ce <= true;
            state_d <= S_FETCH;
            case status.IR(2) is
              when '0' =>   -- not logical
                case status.IR(1) is
                  when '0' =>   -- add/addu
                    cmd.ALU_OP <= AO_plus;
                  when '1' =>   -- sub/subu/slt/sltu
                    cmd.ALU_OP <= AO_moins;
                    case status.IR(3) is
                      when '1' =>   -- slt/sltu
                                    --signal status dependent du calcul sur la
                                    --clock actuelle
                                    --2 sols: branch vers nv etat slt0 ou slt1 -> élue
                                    --             faire des & logiques
                        cmd.RF_we <= false;
                        cmd.mem_ce <= false;
                        case status.IR(0) is 
                          when '0' => -- slt
                            cmd.ALU_extension_signe <= '1';
                            case status.c is
                              when true =>
                                state_d <= S_SLT1;
                              when false =>
                                state_d <= S_SLT0;
                              when others => null;
                            end case;
                            
                          when '1' => -- sltu
                            cmd.ALU_extension_signe <= '0';
                            case status.s is
                              when true =>
                                state_d <= S_SLT1;
                              when false =>
                                state_d <= S_SLT0;
                              when others => null;
                            end case;
                          when others => null;
                        end case;        

                      when others => null;
                    end case;
                  when others => null;
                end case;
              when '1' =>   -- logical
                case status.IR(1 downto 0) is
                  when "00" =>  -- and
                    cmd.ALU_OP <= AO_and;
                  when "01" =>  -- or
                    cmd.ALU_OP <= AO_or;
                  when "10" =>  -- xor
                    cmd.ALU_OP <= AO_xor;
                  when "11" =>  -- nor
                    cmd.ALU_OP <= AO_nor;
                  when others => null;
                end case;
              when others => null;
            end case;
            
          when '0' => --various things like shifts and jump r           
            cmd.RF_Sel <= RFS_RD;            
            cmd.mem_ce <= true;            
            case status.IR(4 downto 3) is
              when "00" =>  -- Shifts                
                cmd.RF_we <= true; -- mettre result dans registre
                cmd.ALU_Y_sel <= UYS_RF_RT;
                state_d <= S_FETCH;
                case status.IR(2) is
                  when '0' =>   -- shift from sh field
                    cmd.ALU_X_sel <= UXS_IR_SH;
                  when '1' =>   -- shift from register
                    cmd.ALU_X_sel <= UXS_RF_RS;
                  when others => null;
                end case;
                case status.IR(1 downto 0) is
                  when "00" =>  -- ssl(v)
                    cmd.ALU_OP <= AO_SLL;
                  when "10" =>  -- srl(v)
                    cmd.ALU_OP <= AO_SRL;
                  when "11" =>  -- sra(v)
                    cmd.ALU_OP <= AO_SRA;
                  when others => null;
                end case;

              when "01" => --jump register or syscall or break
                case status.IR(2) is
                  when '0' => --jump register
                    case status.IR(0) is
                      when '0' => --jr: pc <- rs
                        cmd.PC_we <= true; --mettre result dans PC
                        cmd.ALU_Y_sel <= UYS_cst_x00;
                        cmd.ALU_X_sel <= UXS_RF_RS;
                        cmd.ALU_OP <= AO_plus;
                        state_d <= S_FETCH_WAIT;
                      when '1' => --jalr: rd<-pc+4
                                  --      pc <- rs
                        cmd.RF_we <= true;
                        cmd.ALU_Y_sel <= UYS_cst_x00;
                        cmd.ALU_X_sel <= UXS_PC;
                        cmd.ALU_OP <= AO_plus;
                        state_d <= S_JALR;
                      when others => null;
                    end case;
                  when others => null;
                end case;                
                
              when others => null;
            end case;            
            
          when others => null;
        end case;

      when S_SLT1 =>  
        cmd.ALU_Y_sel <= UYS_cst_x00;
        cmd.ALU_X_sel <= UXS_cst_x01;
        cmd.ALU_OP <= AO_plus;
        cmd.RF_we <= true;
        case status.IR(29) is
          when '1' =>
            cmd.RF_Sel <= RFS_RT;
          when '0' =>
            cmd.RF_Sel <= RFS_RD;
          when others => null;
        end case;
        cmd.mem_ce <= true;
        state_d <= S_FETCH;

      when S_SLT0 =>  
        cmd.ALU_Y_sel <= UYS_cst_x00;
        cmd.ALU_X_sel <= UXS_cst_x00;
        cmd.ALU_OP <= AO_plus;
        cmd.RF_we <= true;
        case status.IR(29) is
          when '1' =>
            cmd.RF_Sel <= RFS_RT;
          when '0' =>
            cmd.RF_Sel <= RFS_RD;
          when others => null;
        end case;
        cmd.mem_ce <= true;
        state_d <= S_FETCH;        

      when S_LOAD => --mettre la bonne adresse dans AD
        cmd.ALU_Y_sel <= UYS_IR_imm16_ext;
        cmd.ALU_X_sel <= UXS_RF_RS;
        cmd.ALU_OP <= AO_plus;
        cmd.AD_we <= true;
        state_d <= S_LOAD2;

      when S_LOAD2 =>--on met une clock en avance l'adresse de AD dans
                     --l'adresse de selection
        cmd.mem_ce <= true;
        cmd.ADDR_sel <= ADDR_from_AD;
        state_d <= S_LOAD3;

      when S_LOAD3 =>--datain a bien la bonne valeur, qui va etre mise dans DT a
                     --la prochaine clock ; mettre datain dans dt        
        cmd.DT_we <= true;
        state_d <= S_LOAD4;

      when S_LOAD4 =>--mettre dt dans rt
        cmd.mem_ce <= true;
        state_d <= S_FETCH;
        cmd.ALU_OP <= AO_plus;
        cmd.ALU_Y_sel <= UYS_cst_x00;
        cmd.ALU_X_sel <= UXS_DT;
        cmd.RF_we <= true;
        cmd.RF_Sel <= RFS_RT;

      when S_STORE =>--mettre la bonne adresse dans AD
        cmd.ALU_Y_sel <= UYS_IR_imm16_ext;
        cmd.ALU_X_sel <= UXS_RF_RS;
        cmd.ALU_OP <= AO_plus;
        cmd.AD_we <= true;
        
        state_d <= S_STORE2;

      when S_STORE2 =>
        cmd.ALU_X_sel <= UXS_cst_x00;
        cmd.ALU_Y_sel <= UYS_RF_RT;
        cmd.ALU_OP <= AO_plus;
        cmd.mem_ce <= true;
        cmd.mem_we <= true;
        cmd.ADDR_sel <= ADDR_from_AD;
        state_d <= S_FETCH_WAIT;
        
      when others => null;
                     
    end case;
  end process FSM_comb;
end RTL;
