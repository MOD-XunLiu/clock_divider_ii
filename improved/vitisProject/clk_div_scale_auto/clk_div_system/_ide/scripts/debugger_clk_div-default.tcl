# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\17877\workspace\clk_div_scale_auto\clk_div_system\_ide\scripts\debugger_clk_div-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\Users\17877\workspace\clk_div_scale_auto\clk_div_system\_ide\scripts\debugger_clk_div-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent JTAG-HS2 210249AEC15D" && level==0 && jtag_device_ctx=="jsn-JTAG-HS2-210249AEC15D-4ba00477-0"}
fpga -file C:/Users/17877/workspace/clk_div_scale_auto/clk_div/_ide/bitstream/clk_div_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/17877/workspace/clk_div_scale_auto/clk_div_wrapper/export/clk_div_wrapper/hw/clk_div_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source C:/Users/17877/workspace/clk_div_scale_auto/clk_div/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow C:/Users/17877/workspace/clk_div_scale_auto/clk_div/Debug/clk_div.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
