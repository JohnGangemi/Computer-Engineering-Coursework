*   	Filename:	AddrSubtr.sp	
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

    	Vdd    vdd    gnd    'SUPPLY'

    	.vec 'AddrSubtr.dat'

	.include netlist		

	cl0    sum     gnd   0.01pF
	cl1    cout    gnd   0.01pF

	.tran   0.1ns 40ns			
    
	.print  tran V(a) V(b) V(s) V(sum) V(cout) V(cin) 

    .end
