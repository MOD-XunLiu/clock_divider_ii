# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\17877\workspace\clk_div_scale_auto\clk_div_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\17877\workspace\clk_div_scale_auto\clk_div_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {clk_div_wrapper}\
-hw {C:\Users\17877\Vivado_Projects\project_clk_div_scale_auto\clk_div_wrapper_scale_auto.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {C:/Users/17877/workspace/clk_div_scale_auto}

platform write
platform generate -domains 
platform active {clk_div_wrapper}
platform generate
bsp reload
domain active {zynq_fsbl}
bsp reload
platform clean
platform generate
platform clean
platform generate
platform config -updatehw {C:/Users/17877/Vivado_Projects/project_clk_div_scale_auto/clk_div_wrapper.xsa}
platform clean
platform generate
platform clean
platform generate
platform active {clk_div_wrapper}
platform active {clk_div_wrapper}
platform config -updatehw {C:/Users/17877/Vivado_Projects/project_clk_div_scale_auto/clk_div_wrapper.xsa}
platform generate
platform config -updatehw {C:/Users/17877/Vivado_Projects/project_clk_div_scale_auto/clk_div_wrapper.xsa}
platform generate -domains 
platform active {clk_div_wrapper}
platform active {clk_div_wrapper}
platform active {clk_div_wrapper}
platform config -updatehw {C:/Users/17877/Vivado_Projects/project_clk_div_scale_auto/clk_div_wrapper.xsa}
platform generate
platform config -updatehw {C:/Users/17877/Vivado_Projects/project_clk_div_scale_auto/clk_div_wrapper.xsa}
platform generate -domains 
platform config -updatehw {C:/Users/17877/Vivado_Projects/project_clk_div_scale_auto/clk_div_wrapper.xsa}
platform generate -domains 
platform config -updatehw {C:/Users/17877/Vivado_Projects/project_clk_div_scale_auto/clk_div_wrapper.xsa}
platform generate -domains 
platform config -updatehw {C:/Users/17877/Vivado_Projects/project_clk_div_scale_auto/clk_div_wrapper.xsa}
platform generate -domains 
platform active {clk_div_wrapper}
platform config -updatehw {C:/Users/17877/Vivado_Projects/project_clk_div_scale_auto/clk_div_wrapper.xsa}
platform generate
platform active {clk_div_wrapper}
platform config -updatehw {C:/Users/17877/Vivado_Projects/project_clk_div_scale_auto/clk_div_wrapper.xsa}
platform generate -domains 
platform config -updatehw {C:/Users/17877/Vivado_Projects/project_clk_div_scale_auto/clk_div_wrapper.xsa}
platform generate -domains 
platform config -updatehw {C:/Users/17877/Vivado_Projects/project_clk_div_scale_auto/clk_div_wrapper.xsa}
platform generate -domains 
platform config -updatehw {C:/Users/17877/Vivado_Projects/project_clk_div_scale_auto/clk_div_wrapper.xsa}
platform generate -domains 
platform config -updatehw {C:/Users/17877/Vivado_Projects/project_clk_div_scale_auto/clk_div_wrapper.xsa}
platform generate -domains 
platform active {clk_div_wrapper}
platform config -updatehw {C:/Users/17877/Vivado_Projects/project_clk_div_scale_auto/clk_div_wrapper.xsa}
platform generate -domains 
platform active {clk_div_wrapper}
platform active {clk_div_wrapper}
platform config -updatehw {C:/Users/17877/Vivado_Projects/project_clk_div_scale_auto/clk_div_wrapper.xsa}
platform generate
