.option post = 2
.option scale = 1u
.option RUNLVL = 6
.temp 27
.lib '$USFCDK_HSPICE_PATH/SCN3ME_SUBM.lib' TT
.include 'netlist'

.global vdd gnd
Vdd vdd gnd 5.0V
vl0 a gnd pulse 0.0V 5.0V 0.0n 0.1n 0.1n 5.0n 10.0n
vl1 b gnd pulse 0.0V 5.0V 0.0n 0.1n 0.1n 10.0n 20.0n
vl2 xin gnd pulse 0.0V 5.0V 0.0n 0.1n 0.1n 20.0n 40.0n
vl3 yin gnd pulse 0.0V 5.0V 0.0n 0.1n 0.1n 40.0n 80.0n
vl4 zin gnd pulse 0.0V 5.0V 0.0n 0.1n 0.1n 80.0n 160.0n

cl0 xout gnd 0.01p
cl1 yout gnd 0.01p
cl2 zout gnd 0.01p

.tran 0.1ns 160.0n
.print tran v(a) v(b) v(xin) v(yin) v(zin) v(xout) v(yout) v(zout)
.END

