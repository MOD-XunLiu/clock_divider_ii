
----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/20/2021 11:16:42 AM
-- Design Name: 
-- Module Name: src_code_to_test - Behavioral
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
use IEEE.std_logic_unsigned.all;
use IEEE.numeric_std.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity edge_detector is
    generic (use_neg_edge_of_clock: boolean := false;
             detect_falling_edge: boolean := false);
    port ( clk : in STD_LOGIC;
           reset_n : in STD_LOGIC;
           r_reset_n : in STD_LOGIC;
           edge_in : in STD_LOGIC;
           edge_pulse : out STD_LOGIC);
end edge_detector;

architecture Behavioral of edge_detector is
signal Q1, Q2, Q3: std_logic;

begin
    POS_EDGE_CLK: if (use_neg_edge_of_clock = false) generate
    EDGE_SYNC: process(clk)
    begin
        if (clk'event and clk = '1') then
          if (reset_n = '0' AND r_reset_n = '1') then
             Q1 <= '0';
             Q2 <= '0';
             Q3 <= '0'; 
          else
             Q1 <= edge_in;
             Q2 <= Q1;
             Q3 <= Q2;
          end if;
        end if;
    end process;
    end generate POS_EDGE_CLK;
    NEG_EDGE_CLK: if (use_neg_edge_of_clock = true) generate
    EDGE_SYNC: process(clk)
    begin
        if (clk'event and clk = '0') then
          if (reset_n = '0' AND r_reset_n = '1') then
             Q1 <= '0';
             Q2 <= '0';
             Q3 <= '0'; 
          else
             Q1 <= edge_in;
             Q2 <= Q1;
             Q3 <= Q2;
          end if;
        end if;
    end process;
    end generate NEG_EDGE_CLK;
    
    RISING_EDGE_OPT: if(detect_falling_edge = false) generate
        edge_pulse <= Q1 and Q2 and (not Q3);
    end generate RISING_EDGE_OPT;
    FALLING_EDGE_OPT: if(detect_falling_edge = true) generate
        edge_pulse <= (not Q1) and (not Q2) and (Q3);
    end generate FALLING_EDGE_OPT;

end Behavioral;