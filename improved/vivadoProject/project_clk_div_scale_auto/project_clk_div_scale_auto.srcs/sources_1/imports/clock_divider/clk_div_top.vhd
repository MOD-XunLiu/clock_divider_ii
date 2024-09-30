----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/01/2024 04:13:11 PM
-- Design Name: 
-- Module Name: clk_div_top - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;
use IEEE.MATH_REAL.ALL;
-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity clk_div_top is
    generic (
       THRESHOLD : integer := 16;
       NUM_WIN : integer := 8   -- must be power of 2 to avoid dividing
    );
    Port ( 
           rst_n : in STD_LOGIC;
           pps_clk : in STD_LOGIC;
           sys_clk : in STD_LOGIC;
           out_ready : out STD_LOGIC;
           out_clk : out STD_LOGIC;
           clk_lost : out STD_LOGIC;
           SCALE : in UNSIGNED (31 downto 0);
           -- Debug ports
           rst_n_monitor : out STD_LOGIC;
           pps_clk_monitor : out STD_LOGIC;
           edge_monitor : out STD_LOGIC);
end clk_div_top;

architecture Behavioral of clk_div_top is
    type cnts_array is array (0 to NUM_WIN-1) of UNSIGNED (31 downto 0);
    signal sys_array : cnts_array;
    signal r_sys_array : cnts_array;
    -- signals needed to count sys_clk
    signal M : UNSIGNED (31 downto 0);
    signal m_cnt : UNSIGNED (31 downto 0) := TO_UNSIGNED(0, 32);
    signal sys_cnt_vct : STD_LOGIC_VECTOR (31 downto 0);
    signal sys_cnt_sum : UNSIGNED (31 downto 0) := TO_UNSIGNED(0, 32);
    signal set_cnt : integer := 0;
    signal r_rst_n : STD_LOGIC;
    
    -- signal that compares divisor and prev_divisor so we can use threshold
    signal newLarger : boolean;
    signal comparator : UNSIGNED (31 downto 0);
    
    -- signal that indicates clk_ratio is ready
    signal prep_ready : STD_LOGIC;
    signal r_out_ready : STD_LOGIC;
    signal r_out_clk : STD_LOGIC;
    signal r_r_out_clk : STD_LOGIC := '0';
      
    -- signals used to scale the sys_clk
    signal divisor_by_2 : STD_LOGIC_VECTOR (31 downto 0);
    signal divisor : STD_LOGIC_VECTOR (31 downto 0);
    signal prev_divisor : STD_LOGIC_VECTOR (31 downto 0);
    signal div_cnt : UNSIGNED (31 downto 0) := TO_UNSIGNED(0, 32);
    
    -- Signals for edge_detector instance
    signal edge_pulse : STD_LOGIC;
    signal r_M : UNSIGNED (31 downto 0);
    
    signal rep_cnt : UNSIGNED (31 downto 0);
    
    signal clk_change : STD_LOGIC;
    
    signal counter : integer := 0;

    
    constant WIN_WIDTH : positive := positive(ceil(log2(real(NUM_WIN))));
    
    signal ZERO_WIN : STD_LOGIC_VECTOR (WIN_WIDTH-1 downto 0);
    
    -- Component declaration for the lower-level entity (edge_detector)
    component edge_detector is
        generic (use_neg_edge_of_clock: boolean;
                 detect_falling_edge: boolean);
        port ( clk : in STD_LOGIC;
               reset_n : in STD_LOGIC;
               r_reset_n : in STD_LOGIC;
               edge_in : in STD_LOGIC;
               edge_pulse : out STD_LOGIC);
    end component;
begin

    -- Instantiate the edge_detector entity
    U_edge_detector: edge_detector
        generic map (
            use_neg_edge_of_clock => false,
            detect_falling_edge => false
        )
        port map (
            clk => sys_clk,
            reset_n => rst_n,
            r_reset_n => r_rst_n,
            edge_in => pps_clk,
            edge_pulse => edge_pulse
        );
        

    divisor_by_2 <= '0' & divisor(31 downto 1); -- divide by 2
    out_clk <= r_out_clk AND r_out_ready;
    out_ready <= r_out_ready;
    newLarger <= divisor>prev_divisor;
    comparator <= (unsigned(divisor) - unsigned(prev_divisor)) when newLarger
        else (unsigned(prev_divisor) - unsigned(divisor));
    
    rst_n_monitor <= rst_n;
    pps_clk_monitor <= pps_clk;
    
    edge_monitor <= edge_pulse;
    
    ZERO_WIN <= std_logic_vector(TO_UNSIGNED(0, WIN_WIDTH));

    -- Combinational process
    process(sys_array)
    variable temp_sum : unsigned (31 downto 0) := to_unsigned(0, 32);
    begin
        temp_sum := to_unsigned(0, 32); -- Initialize sum
        for i in 0 to NUM_WIN-1 loop
            temp_sum := temp_sum + r_sys_array(i);
        end loop;
        sys_cnt_vct <= std_logic_vector(temp_sum); -- Output the sum
    end process;
    
    process (sys_clk)
    begin
        if (sys_clk'event and sys_clk = '1') then
          r_rst_n <= rst_n;
          M <= SCALE-1;
          r_M <= M;
          if ((r_rst_n = '1' AND rst_n = '0') or (M /= r_M)) then
            for i in 0 to NUM_WIN-1 loop
                sys_array(i) <= TO_UNSIGNED(0, 32);
                r_sys_array(i) <= TO_UNSIGNED(0,32);
            end loop;
            set_cnt <= 0;
            rep_cnt <= TO_UNSIGNED (0, 32);
            divisor <= std_logic_vector(TO_UNSIGNED(0,32));
            prep_ready <= '0';
            r_out_ready <= '0';
            div_cnt <= TO_UNSIGNED(0, 32);
            clk_lost <= '0';
            clk_change <= '0';
            m_cnt <= TO_UNSIGNED(0, 32);
            counter <= 0;
            if (r_rst_n = '1' and rst_n = '0') then 
                M <= TO_UNSIGNED(0, 32);
                r_M <= TO_UNSIGNED(0, 32);
             end if;
          else
            

              
              if ((r_out_clk = '0') and (r_r_out_clk = '1')) then
                clk_change <= '1';
              else 
                clk_change <= '0';
              end if;
              
              if (r_out_ready = '1') then
                r_r_out_clk <= r_out_clk;
              else
                r_r_out_clk <= '0';
              end if;
                        
              if (m_cnt < M) then
                m_cnt <= m_cnt+1;
              else
                m_cnt <= TO_UNSIGNED(0, 32);
              end if;
                       
              -- case statement for counting and getting stable divisor
              -- hard code case
--              case (set_cnt) is
--                when "00" =>
--                  if (m_cnt = M) then
--                    sys_array(0) <= sys_array(0) + 1;
--                  end if;
--                  if (sys_array(0) > (sys_array(3)(30 downto 0) & '0')) AND (r_out_ready = '1') then
--                      clk_lost <= '1';
--                  end if;
--                when "01" =>
--                  if (m_cnt = M) then
--                    sys_array(1) <= sys_array(1) + 1;
--                  end if;
--                  if (sys_array(1) > (sys_array(0)(30 downto 0) & '0')) AND (r_out_ready = '1')then
--                      clk_lost <= '1';
--                  end if;
--                when "10" =>
--                  if (m_cnt = M) then
--                    sys_array(2) <= sys_array(2) + 1;
--                  end if;
--                  if (sys_array(2) > (sys_array(1)(30 downto 0) & '0')) AND (r_out_ready = '1')then
--                      clk_lost <= '1';
--                  end if;
--                when others =>
--                  if (m_cnt = M) then
--                    sys_array(3) <= sys_array(3) + 1;
--                  end if;
--                  if (sys_array(3) > (sys_array(2)(30 downto 0) & '0')) AND (r_out_ready = '1')then
--                      clk_lost <= '1';
--                  end if;
--              end case;
              
              if (m_cnt = M) then
                sys_array(set_cnt) <= sys_array(set_cnt) + 1;
              end if;
              
              if (set_cnt = 0) then
                if (sys_array(set_cnt) > (sys_array(NUM_WIN-1)(30 downto 0) & '0')) AND (r_out_ready = '1') then
                    clk_lost <= '1';
                end if;
              else
                if (sys_array(set_cnt) > (sys_array(set_cnt-1)(30 downto 0) & '0')) AND (r_out_ready = '1') then
                    clk_lost <= '1';
                end if;
              end if;
              
              -- output out_clk when divisor is stable
              if (((div_cnt >= (unsigned(divisor)-1)) OR (prep_ready = '1')) and edge_pulse = '0') then
                  div_cnt <= TO_UNSIGNED(0, 32);
              else
                  div_cnt <= div_cnt + 1;
              end if;
              
            if (prep_ready = '1') then
                      prep_ready <= '0';
                      r_out_ready <= '1';
              end if;
              
              if ((edge_pulse = '0') and (rep_cnt < SCALE)) then
                  if (div_cnt < unsigned(divisor_by_2))then
                    r_out_clk <= '1';               
                  else
                    r_out_clk <= '0';
                  end if;
              end if;
              
              if (clk_change = '1') then
                rep_cnt <= rep_cnt + 1;
              end if;
        
              if (edge_pulse = '1') then--r_pps = '0' and pps_clk = '1') then
                r_out_clk <= '1';
                rep_cnt <= TO_UNSIGNED(0, 32);
                div_cnt <= TO_UNSIGNED(0, 32);
                -- increment set_cnt for pps_clk
                if (set_cnt = NUM_WIN-1) then
                    set_cnt <= 0;
                else
                    set_cnt <= set_cnt + 1;
                end if;
                
                -- update registered counter
                -- and zero out unregister counter
--                case (set_cnt) is
--                  when "00" =>
--                    r_sys_array(3) <= sys_array(3);
--                    sys_array(1) <= TO_UNSIGNED(0, 32);
--                  when "01" =>
--                    r_sys_array(0) <= sys_array(0);
--                    sys_array(2) <= TO_UNSIGNED(0, 32);
--                  when "10" =>
--                    r_sys_array(1) <= sys_array(1);
--                    sys_array(3) <= TO_UNSIGNED(0, 32);
--                  when others =>
--                    r_sys_array(2) <= sys_array(2);
--                    sys_array(0) <= TO_UNSIGNED(0, 32);
--                end case;
                
                r_sys_array(set_cnt) <= sys_array(set_cnt);
                if (set_cnt = NUM_WIN-1) then
                    sys_array(0) <= TO_UNSIGNED(0, 32);
                else
                    sys_array(set_cnt+1) <= TO_UNSIGNED(0, 32);
                end if;
                
                -- update divisor based on registered counter
                divisor <= ZERO_WIN & sys_cnt_vct(31 downto WIN_WIDTH);
                -- store previous divisor
                prev_divisor <= divisor;
              
                -- determine if we can start to output clock
                if (comparator < THRESHOLD) AND (r_sys_array(0)/=0 AND r_sys_array(1)/=0 AND r_sys_array(2)/=0 AND r_sys_array(3)/=0) AND (r_out_ready = '0') then
                      prep_ready <= '1';
                end if;
              end if;
        
            end if;
        end if;
    end process;
    

end Behavioral;
