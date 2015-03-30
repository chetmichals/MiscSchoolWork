		ORG $900 ;start program at address #0900 
PIT 	EQU $FE8000 ;initial the starting address of PIT 
		LEA PIT,A0 ;load PIT address to A0 
		MOVE.B #$AA,D2 ;Initialize D2
		MOVE.B #$00,1(A0) ;set PIT mode0 
		MOVE.B #$FF,5(A0) ;set port A to all outputs 
		MOVE.B #$00,7(A0) ;set port B to all inputs 
LOOP 	MOVE.B 19(A0),D1 ;read switches for port B
		BTST #7,D1 ;Check if system is in read or write mode
		BEQ RUNMODE
		MOVE.B D1,D2
		AND.B #$0F,D2
		MOVE.B D2,17(A0)
		BRA LOOP ;loop 
RUNMODE
		BTST #6,D1 ;Check if system is to rotate left or right
		BEQ RIGHT
		ROR #1,D2
		BRA TIMEDELAY
RIGHT
		ROL #1,D2
TIMEDELAY	;Delays system to not run to fast
		BRA TIMEDELAY 
		BTST #5,D1 ;Check if in fast or slow mode
		BEQ INVERTIT
		BRA TIMEDELAY
INVERTIT ;Check if in "Blink" mode
		BTST #4,D1
		BNE MOVEIT
		NOT D2
MOVEIT ;Set LEDs
		MOVE.B D2,17(A0) ;and light LEDs on port A 
		BRA LOOP ;loop 
 
DELAY
		MOVE.B #$80,33(A0) ; Set the Timer Control Register to be prepared for a value in the counter
		MOVE.B #$0F,39(A0) ; Set the high bits of the counter
		MOVE.B #$FF,41(A0) ; Set the mid bits of the counter
		MOVE.B #$FF,43(A0) ; Set the low bits of the counter
		MOVE.B #$81,33(A0) ; Turn time on
TIMELOOP
		MOVE.B 53(A0),D4 ; Move the timer register value to D4
		CMP 0,D4 ;Check if 0
		BNE TIMELOOP ;If not zero, check again
		MOVE.B #1,53(A0);reset timer register
		RTS
 
STOP 	MOVE.B #228,D7 
		TRAP #14 
		END