		ORG $0900 ;start program at this address 
LAB4 	BSR NEG ;call subroutine negative 
		BSR LSR ;call subroutine left side right 
		BSR USD ;call subroutine upside 
		BSR FRAME ;call subroutine frame 
		BRA STOP ;stop the program 
 
NEG 
		MOVE.L #16,D0
		MOVEA.L #IMAGE, A1
		MOVEA.L #IMNEG, A2
NEGLOOP
		MOVE.W (A1)+,D1
		NOT.W D1
		MOVE.W D1,(A2)+
		SUBQ #1,D0
		BNE NEGLOOP
		RTS
	
LSR 
		MOVE.L #16,D0
		MOVEA.L #IMAGE, A1
		MOVEA.L #IMLSR, A2
MAINLOOP
		MOVE.W (A1)+,D2
		MOVE.L #16,D1
		CLR D3
SUBLOOP
		LSL.W #1,D2
		ROXR.W #1,D3
		SUBQ #1,D1
		BNE SUBLOOP
		MOVE.W D3,(A2)+
		SUBQ #1,D0
		BNE MAINLOOP
		RTS
	
USD
		MOVE.L #16,D0
		MOVEA.L #IMAGE, A1
		MOVEA.L #IMUSD, A2
		ADDA.L #32, A1
USDLOOP
		MOVE -(A1), (A2)+
		SUBQ #1,D0
		BNE USDLOOP
		RTS
FRAME
		MOVE.L #14,D0	
		MOVEA.L #IMAGE, A1
		MOVEA.L #IMFRM, A2
		ADDA.L #2,A1
		MOVE.W	#$FFFF,(A2)+
FRAMELOOP
		MOVE.W (A1)+,D1
		ORI.W #$8001,D1
		MOVE.W D1,(A2)+
		SUBQ #1,D0
		BNE FRAMELOOP
		MOVE.W #$FFFF,(A2)+
		RTS
 
		ORG $0C00 ;at this address, create an image 
IMAGE 	DC.W $0000 ;................ 
		DC.W $0000 ;................ 
		DC.W $3FE0 ;..111111111..... 
		DC.W $3FF0 ;..1111111111.... 
		DC.W $3878 ;..111....1111... 
		DC.W $3838 ;..111.....111... 
		DC.W $3838 ;..111.....111... 
		DC.W $3870 ;..111....111.... 
		DC.W $3FE0 ;..111111111..... 
		DC.W $3FE0 ;..111111111..... 
		DC.W $3870 ;..111....111.... 
		DC.W $3870 ;..111....111.... 
		DC.W $3838 ;..111.....111... 
		DC.W $3838 ;..111.....111... 
		DC.W $0000 ;................ 
		DC.W $0000 ;................ 
		DC.L $C0C0C0C0 ;
		 
		ORG $0C40 ;at this address 
IMNEG 	DS.W 16 ;allocate space for negative image 
		DC.L $C4C4C4C4 ;a marker at the end of negative image 
		 
		ORG $0C80 ;at this address 
IMUSD	DS.W 16 ;allocate space for upside down image 
		DC.L $C8C8C8C8 ;a marker at the end of flipped image 
		 
		ORG $0CC0 ;at this address 
IMLSR 	DS.W 16 ;allocate space for left side right 
		DC.L $CCCCCCCC ;a marker at the end of rotated image 
		
		ORG $0D00 ;at this address 
IMFRM 	DS.W 16 ;allocate space for left side right 
		DC.L $DDDDDDDD ;a marker at the end of rotated image 
		 
STOP 
		MOVE.B #228,D7 
		TRAP #14 
		END 