.option post = 2
.option scale = 1u
.option RUNLVL = 6
.temp 27
.lib '$USFCDK_HSPICE_PATH/SCN3ME_SUBM.lib' TT
.include 'netlist'

.global vdd gnd
Vdd vdd gnd 5.0V
vl0 b gnd pulse 0.0V 5.0V 0.0n 0.1n 0.1n 10.0n 20.0n
vl1 a gnd pulse 0.0V 5.0V 0.0n 0.1n 0.1n 5.0n 10.0n
vl2 s gnd pulse 0.0V 5.0V 0.0n 0.1n 0.1n 20.0n 40.0n
cl0 y gnd 0.01p

.tran 0.1ns 40n
.print tran v(a) v(b) v(s) v(y)
.END

