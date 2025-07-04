-- (c) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- (c) Copyright 2022-2024 Advanced Micro Devices, Inc. All rights reserved.
-- 
-- This file contains confidential and proprietary information
-- of AMD and is protected under U.S. and international copyright
-- and other intellectual property laws.
-- 
-- DISCLAIMER
-- This disclaimer is not a license and does not grant any
-- rights to the materials distributed herewith. Except as
-- otherwise provided in a valid license issued to you by
-- AMD, and to the maximum extent permitted by applicable
-- law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
-- WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
-- AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
-- BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
-- INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
-- (2) AMD shall not be liable (whether in contract or tort,
-- including negligence, or under any other theory of
-- liability) for any loss or damage of any kind or nature
-- related to, arising under or in connection with these
-- materials, including for any direct, or any indirect,
-- special, incidental, or consequential loss or damage
-- (including loss of data, profits, goodwill, or any type of
-- loss or damage suffered as a result of any action brought
-- by a third party) even if such damage or loss was
-- reasonably foreseeable or AMD had been advised of the
-- possibility of the same.
-- 
-- CRITICAL APPLICATIONS
-- AMD products are not designed or intended to be fail-
-- safe, or for use in any application requiring fail-safe
-- performance, such as life-support or safety devices or
-- systems, Class III medical devices, nuclear facilities,
-- applications related to the deployment of airbags, or any
-- other applications that could lead to death, personal
-- injury, or severe property or environmental damage
-- (individually and collectively, "Critical
-- Applications"). Customer assumes the sole risk and
-- liability of any use of AMD products in Critical
-- Applications, subject only to applicable laws and
-- regulations governing limitations on product liability.
-- 
-- THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
-- PART OF THIS FILE AT ALL TIMES.
-- 
-- DO NOT MODIFY THIS FILE.

-- IP VLNV: xilinx.com:module_ref:clk_div_top:1.0
-- IP Revision: 1

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY clk_div_clk_div_top_0_0 IS
  PORT (
    rst_n : IN STD_LOGIC;
    pps_clk : IN STD_LOGIC;
    sys_clk : IN STD_LOGIC;
    out_ready : OUT STD_LOGIC;
    out_clk : OUT STD_LOGIC;
    clk_lost : OUT STD_LOGIC;
    SCALE : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    rst_n_monitor : OUT STD_LOGIC;
    pps_clk_monitor : OUT STD_LOGIC;
    edge_monitor : OUT STD_LOGIC
  );
END clk_div_clk_div_top_0_0;

ARCHITECTURE clk_div_clk_div_top_0_0_arch OF clk_div_clk_div_top_0_0 IS
  ATTRIBUTE DowngradeIPIdentifiedWarnings : STRING;
  ATTRIBUTE DowngradeIPIdentifiedWarnings OF clk_div_clk_div_top_0_0_arch: ARCHITECTURE IS "yes";
  COMPONENT clk_div_top IS
    GENERIC (
      THRESHOLD : INTEGER;
      NUM_WIN : INTEGER
    );
    PORT (
      rst_n : IN STD_LOGIC;
      pps_clk : IN STD_LOGIC;
      sys_clk : IN STD_LOGIC;
      out_ready : OUT STD_LOGIC;
      out_clk : OUT STD_LOGIC;
      clk_lost : OUT STD_LOGIC;
      SCALE : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
      rst_n_monitor : OUT STD_LOGIC;
      pps_clk_monitor : OUT STD_LOGIC;
      edge_monitor : OUT STD_LOGIC
    );
  END COMPONENT clk_div_top;
  ATTRIBUTE X_INTERFACE_INFO : STRING;
  ATTRIBUTE X_INTERFACE_PARAMETER : STRING;
  ATTRIBUTE X_INTERFACE_PARAMETER OF out_clk: SIGNAL IS "XIL_INTERFACENAME out_clk, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN clk_div_clk_div_top_0_0_out_clk, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF out_clk: SIGNAL IS "xilinx.com:signal:clock:1.0 out_clk CLK";
  ATTRIBUTE X_INTERFACE_PARAMETER OF pps_clk: SIGNAL IS "XIL_INTERFACENAME pps_clk, FREQ_HZ 1000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN clk_div_pps_clk, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF pps_clk: SIGNAL IS "xilinx.com:signal:clock:1.0 pps_clk CLK";
  ATTRIBUTE X_INTERFACE_PARAMETER OF rst_n: SIGNAL IS "XIL_INTERFACENAME rst_n, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF rst_n: SIGNAL IS "xilinx.com:signal:reset:1.0 rst_n RST";
  ATTRIBUTE X_INTERFACE_PARAMETER OF sys_clk: SIGNAL IS "XIL_INTERFACENAME sys_clk, FREQ_HZ 1000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN clk_div_processing_system7_0_0_FCLK_CLK0, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF sys_clk: SIGNAL IS "xilinx.com:signal:clock:1.0 sys_clk CLK";
BEGIN
  U0 : clk_div_top
    GENERIC MAP (
      THRESHOLD => 16,
      NUM_WIN => 8
    )
    PORT MAP (
      rst_n => rst_n,
      pps_clk => pps_clk,
      sys_clk => sys_clk,
      out_ready => out_ready,
      out_clk => out_clk,
      clk_lost => clk_lost,
      SCALE => SCALE,
      rst_n_monitor => rst_n_monitor,
      pps_clk_monitor => pps_clk_monitor,
      edge_monitor => edge_monitor
    );
END clk_div_clk_div_top_0_0_arch;
