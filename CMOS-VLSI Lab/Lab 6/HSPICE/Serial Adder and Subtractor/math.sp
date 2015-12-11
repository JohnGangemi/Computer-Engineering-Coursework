*  Filename:	math.sp	
*	Author: 	   Team RAJ
*	Class:		CDA4213L.F[14]
	
	.param SUPPLY = 5.0V            
  	.param GROUND = 0.0V		 
	.option post = ASCII 						
	.option list							 
	.option scale = 1u 						
	.option RUNLVL = 6			
	.temp 27							
	.lib '$USFCDK_HSPICE_PATH/SCN3ME_SUBM.lib' TT

 	Vdd    vdd    	gnd    'SUPPLY'
	.vec 'math.dat'
	.include netlist
	
	cl0 	a1 	gnd 	0.01pF	
	cl1 	a2 	gnd	0.01pF
   cl2 	a3 	gnd	0.01pF
   cl3 	a4 	gnd	0.01pF
   cl4 	a5 	gnd	0.01pF
   cl5 	a6 	gnd	0.01pF
   cl6 	a7 	gnd	0.01pF
   cl7 	a8 	gnd	0.01pF
   cl8 	b1 	gnd 	0.01pF	
	cl9 	b2 	gnd	0.01pF
   cl10 	b3 	gnd	0.01pF
   cl11	b4 	gnd	0.01pF
   cl12	b5 	gnd	0.01pF
   cl13	b6 	gnd	0.01pF
   cl14	b7 	gnd	0.01pF
   cl15	b8 	gnd	0.01pF
   cl16	sum 	gnd	0.01pF
   cl17	cout 	gnd	0.01pF

	.tran 0.1us 85us
	.print  tran V(clk) V(pre) V(clr) V(ld_sh) V(b_in) V(ap1) V(ap2) V(ap3) V(ap4) V(ap5) V(ap6) V(ap7) V(ap8) V(a1) V(a2) V(a3) V(a4) V(a5) V(a6) V(a7) V(a8) V(bp1) V(bp2) V(bp3) V(bp4) V(bp5) V(bp6) V(bp7) V(bp8) V(b1) V(b2) V(b3) V(b4) V(b5) V(b6) V(b7) V(b8) V(add_sub)
    .end
