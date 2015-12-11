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
vl2 s gnd pulse 0.0V 5.0V 0.0n 0.1n 0.1n 40.0n 80.0n
vl3 cin gnd pulse 0.0V 5.0V 0.0n 0.1n 0.1n 20.0n 40.0n
cl0 sum gnd 0.01p
cl1 cout gnd 0.01p

.tran 0.1ns 80n
.print tran v(a) v(b) v(cin) v(s) v(sum) v(cout)
.END

