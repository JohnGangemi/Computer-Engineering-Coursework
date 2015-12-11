COUNTER 

.option scale = 1u
.option runlvl = 6
.temp 27
.lib '$USFCDK_HSPICE_PATH/SCN3ME_SUBM.lib' TT

.include 'netlist'
.global vdd gnd

vdd vdd gnd 5.0
vl0 clk gnd pulse 0.0 5.0 0.0n 0.1n 0.1n 2.5n 5.0n
vl2 pre_not gnd pwl 0.0n 5.0 44.9n 5.0 45.0n 0.0 45.9n 0.0 46.0n 5.0
vl3 clr_not gnd pwl 0.0n 0.0 0.9n 0.0 1.0n 5.0
vl4 sel gnd pwl 0.0n 0.0 44.9n 0.0 45.0n 5.0

.tran 0.01n 90.0n
.print tran v(clk) v(pre_not) v(clr_not) v(sel) v(y7) v(y6) v(y5) v(y4) v(y3) v(y2) v(y1) v(y0)
.end

