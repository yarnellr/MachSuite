open_project hls_prj

add_files stencil.c
add_files input.data
add_files check.data
add_files -tb ../../common/harness.c 

set_top stencil3d
open_solution -reset solution

set_part virtex7
create_clock -period 10
source ./stencil_dir

csynth_design
#cosim_design -rtl verilog -tool modelsim -trace_level all
#export_design -rtl verilog -format ip_catalog

exit
