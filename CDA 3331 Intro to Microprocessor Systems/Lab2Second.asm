		ORG		$0900
LAB2	MOVE.L 	#10,D0 ;SET D0 TO VALUE YOU WISH TO PUT IN A
CLEAR	CLR.L	D1;X
		CLR.L	D2;Y
		CLR.L	D3;F
		CLR.L 	D4;
		MOVEA.L	#0,A0
		
XCALC	MOVE.L	#1,D1;Skips the first loop where i=0
		MOVE.L	#1,D4;
XLOOP	CMPA.L	#0,A0
		BNE		NORMLOOP
		CMPI.L	#$06F0,D1
		BLT		NORMLOOP
		MOVEA.L	D4,A0
NORMLOOP 
		MOVE.L	D4,D5 ;first do 5*i
		MOVE.L	D4,D6
		MULU.W	#5,D5
		ADD.L 	D5,D1
		;next do i/3 roofed factoral
		
		MOVE.L	#1,D5;Set up for i!
		DIVU.W	#3,D6;Now do i/3
		MOVE.L D6,D7
		SWAP D7
		CMPI.W #0,D7
		BEQ		FACTLOOP
		ADDI.L	#1,D6
FACTLOOP ;DO FACTORIAL
		MULU.W	D6,D5 
		SUBQ.W	#1,D6
		BNE		FACTLOOP
		
		ADD.L	 D5,D1
		ADD.L	#1,D4
		CMP.L		D0,D4
		BNE		XLOOP 
		MOVE.L D1,D2;LINE TO MAKE BREAKPOINT TO
YCALC	;(A+2)^2
		MOVE.W 	D0, D4
		ADDI.W 	#2,D4
		MOVE.W 	D4,D2
		MULU.W 	D4,D2
FCALC;DO X/Y
		MOVE.W 	D1,D3
		DIVU.W	D2,D3
		END
		