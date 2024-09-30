----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/01/2024 05:37:16 PM
-- Design Name: 
-- Module Name: clk_div_top_tb - Behavioral
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

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

use STD.ENV.FINISH;

entity clk_div_top_tb is
--  Port ( );
end clk_div_top_tb;

architecture Behavioral of clk_div_top_tb is

component clk_div_top is
    Generic (THRESHOLD : integer);
    Port ( 
        SCALE : in unsigned(31 downto 0);
        rst_n : in STD_LOGIC;
        pps_clk : in STD_LOGIC;
        sys_clk : in STD_LOGIC;
        out_ready : out STD_LOGIC;
        out_clk : out STD_LOGIC;
        clk_lost : out STD_LOGIC;
        rst_n_monitor : out STD_LOGIC;
        pps_clk_monitor : out STD_LOGIC;
        edge_monitor : out STD_LOGIC);
end component;

signal reset_n : std_logic := '1';
signal ready : std_logic;

signal pps_clock0 : std_logic := '0';
signal pps_clock1 : std_logic := '0';
signal clock_en : std_logic := '0';
signal sys_clock : std_logic := '0';
signal out_clock : std_logic;
signal clock_lost : std_logic;
signal muxed_clock : std_logic;
signal clock_sel : std_logic := '0';

signal rst_n_monitor : std_logic;
signal pps_clk_monitor : std_logic;
signal SCALE : unsigned(31 downto 0);

signal edge : std_logic;

constant pps_clock_period0 : time := 1 ms;  --1 Khz
constant pps_clock_period1 : time := 10 ms; -- 10hz
signal sys_clock_period : time := 1 ns;  --1 Mhz

begin

pps_clock0 <= ((not pps_clock0) AND clock_en)after pps_clock_period0/2;
pps_clock1 <= ((not pps_clock1) AND clock_en)after pps_clock_period1/2;
muxed_clock <= (clock_sel AND pps_clock1) OR ((NOT clock_sel) AND pps_clock0);
sys_clock <= not sys_clock after sys_clock_period/2;

CLK_DIV_TOP_UNIT : clk_div_top 
    generic map(
    THRESHOLD => 16)
    port map(
        SCALE => SCALE,
        rst_n => reset_n,
        pps_clk => muxed_clock,
        sys_clk => sys_clock,
        out_ready => ready,
        out_clk => out_clock,
        clk_lost => clock_lost,
        rst_n_monitor => rst_n_monitor,
        pps_clk_monitor => pps_clk_monitor,
        edge_monitor => edge);
        
sim_process : process
begin
    wait for 2 us;
    SCALE <= to_unsigned(3, 32);
    reset_n <= '0'; 
    clock_en <= '1';
    wait for 1 ns;
    reset_n <= '1';
--    wait for 15 ms;
--    clock_en <= '0';
--    wait for 20 ms;
--    clock_sel <= '1';
--    clock_en <= '1';
    wait for 10 ms;
--    clock_en <= '0';
--    sys_clock_period <= 2 ns;
    wait for 10 ms;
--    clock_en <= '1';
    sys_clock_period <= 5 ns;
--    SCALE <= to_unsigned(4, 32);
--    reset_n <= '0'; 
--    wait for 1 ns;
--    reset_n <= '1';
    wait for 20 ms;
    clock_en <= '0';
    wait for 5 ms;
     reset_n <= '0';
    finish;

end process;

end Behavioral;