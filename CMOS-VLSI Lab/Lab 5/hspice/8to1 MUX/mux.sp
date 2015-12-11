MUX

.option scale = 1u
.option runlvl = 6
.temp 27
.lib '$USFCDK_HSPICE_PATH/SCN3ME_SUBM.lib' TT
.param SUPPLY = 5.0
.include 'netlist'
.global vdd gnd

vdd vdd gnd 'SUPPLY'

cl0 y gnd 0.01p

.vec 'mux.dat'
.tran 0.1u 40.0u
.print tran v(i7) v(i6) v(i5) v(i4) v(i3) v(i2) v(i1) v(i0)
+ v(a) v(b) v(c) v(z)
.end

