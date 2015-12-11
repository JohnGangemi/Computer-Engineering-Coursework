*  Filename:	shift.sp	
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
	.vec 'shift.dat'
	.include netlist
	
	cl0 	q1 	gnd 	0.01pF	
	cl1 	q2 	gnd	0.01pF
   cl2 	q3 	gnd	0.01pF
   cl3 	q4 	gnd	0.01pF
   cl4 	q5 	gnd	0.01pF
   cl5 	q6 	gnd	0.01pF
   cl6 	q7 	gnd	0.01pF
   cl7 	q8 	gnd	0.01pF

	.tran 0.1us 70us
	.print  tran V(clk) V(pre) V(clr) V(rs_ls) V(ld_sh) V(rs_in) V(ls_in) V(p1) V(p2) V(p3) V(p4) V(p5) V(p6) V(p7) V(p8) V(q1) V(q2) V(q3) V(q4) V(q5) V(q6) V(q7) V(q8)
    .end
