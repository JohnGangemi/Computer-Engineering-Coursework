MAG COMP

.option scale = 1u
.option runlvl = 6
.temp 27
.lib '$USFCDK_HSPICE_PATH/SCN3ME_SUBM.lib' TT
.param SUPPLY = 5.0
.include 'netlist'
.global vdd gnd

vdd vdd gnd 'SUPPLY'

cl0 Zout gnd 0.01p
cl1 Xout gnd 0.01p
cl2 Yout gnd 0.01p

.vec 'magcomp.dat'
.tran 0.1u 40.0u
.print tran v(a7) v(a6) v(a5) v(a4) v(a3) v(a2) v(a1) v(a)
+ v(b7) v(b6) v(b5) v(b4) v(b3) v(b2) v(b1) v(b) v(Zout) v(Xout) v(Yout)
.end
