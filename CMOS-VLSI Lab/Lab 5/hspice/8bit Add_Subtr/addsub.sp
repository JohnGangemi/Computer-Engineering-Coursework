ADDER SUBTRACTOR

.option scale = 1u
.option runlvl = 6
.temp 27
.lib '$USFCDK_HSPICE_PATH/SCN3ME_SUBM.lib' TT
.param SUPPLY = 5.0
.include 'netlist'
.global vdd gnd

vdd vdd gnd 'SUPPLY'

cl0 s7 gnd 0.01p
cl1 s6 gnd 0.01p
cl2 s5 gnd 0.01p
cl3 s4 gnd 0.01p
cl4 s3 gnd 0.01p
cl5 s2 gnd 0.01p
cl6 s1 gnd 0.01p
cl7 s0 gnd 0.01p

.vec 'addsub.dat'
.tran 0.1us 80.0us
.print tran v(a7) v(a6) v(a5) v(a4) v(a3) v(a2) v(a1) v(a0)
+ v(b7) v(b6) v(b5) v(b4) v(b3) v(b2) v(b1) v(b0)
+ v(s7) v(s6) v(s5) v(s4) v(s3) v(s2) v(s1) v(s0)
.end

