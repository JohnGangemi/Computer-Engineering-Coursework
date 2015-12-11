*   	Filename:	counter.sp	
*	Author: 	Team RAJ
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
	.vec 'Counter.dat'
	.include netlist
	
	cl0 	q 	gnd 	0.01pF	
	cl1 	qbar	gnd	0.01pF	
	cl2 	updwn	gnd	0.01pF	
	cl3 	pre	gnd	0.01pF	
	cl4 	clr	gnd	0.01pF	
	cl5 	a	gnd	0.01pF
	cl6 	b	gnd	0.01pF
	cl7 	mux	gnd	0.01pF

	.tran 0.1ns 130ns
	.print  tran V(updwn) V(q) V(qbar) V(pre) V(clr) V(a) V(b) V(mux)
    .end
