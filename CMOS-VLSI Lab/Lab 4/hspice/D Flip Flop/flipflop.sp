D FLIP FLOP

.param SUPPLY = 5.0v
.param GROUND = 0.0v

.option scale = 1u
.option runlvl = 6
.temp 27
.lib '$USFCDK_HSPICE_PATH/SCN3ME_SUBM.lib' TT

.global vdd gnd

vdd vdd gnd 'SUPPLY'
vl0 d gnd pulse 'GROUND' 'SUPPLY' 0.0n 0.1n 0.1n 10.0n 20.0n
vl1 clk gnd pulse 'GROUND' 'SUPPLY' 2.5n 0.1n 0.1n 5.0n 10.0n
vl2 pre_not gnd pulse 'SUPPLY' 'GROUND' 0.0n 0.1n 0.1n 20.0n 40.0n
vl3 clr_not gnd pulse 'SUPPLY' 'GROUND' 0.0n 0.1n 0.1n 40.0n 80.0n

.include 'netlist'

cl0 q_not gnd 0.01p
cl1 q gnd 0.01p

.tran 0.1n 80.0n
.print tran v(d) v(clk) v(clr_not) v(pre_not) v(q) v(q_not)

.end

