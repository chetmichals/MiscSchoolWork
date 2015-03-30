*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
START   ORG    $0900
LAB3    CLR.L   D0
        BRA     SORT1    

ARY1    DC.B    10
        DC.B    82,-5,8,23,-9,18,4,13,-50,0
ARY1S   DS.B    10
ARY2    DC.B    12
        DC.B    $11,$A4,$F9,$69,$D7,$E3,$3E,$7,$CC,$29,$D7,$40
ARY2S   DS.B    12

SORT1   MOVEA.L #ARY1,A0
        MOVEA.L #ARY1S,A1
        MOVE.B (A0)+,D0
        BSR     SORT
        
SORT2   MOVEA.L #ARY2,A0
        MOVEA.L #ARY2S,A1
        MOVE.B  (A0)+,D0
        BSR     SORT
        BRA     SKIPSUB

;start bubblesort
SORT    MOVE.B  D0,D1
        MOVEA.L A1,A2
        MOVEA.L A0,A6
LOADLOOP
;MOVE CONTENTS FROM OLD ARAY TO NEW
        MOVE.B  (A0)+,(A1)+
        SUBQ.B  #1,D1
        BNE     LOADLOOP
        
        MOVEA.L A2,A1
        MOVE.B  D0,D1
;DO BUBBLE SORT
BUBBLELOOP 
;Main for loop
        SUBQ.B  #1,D1
        BEQ     EXITLOOP
        MOVE.B  D1,D2
        MOVEA.L A1,A2
        MOVEA.L A1,A3
        ADD.B  #0,(A3)+
;inner for loop (compairs two elements, swpas if needed
INNERLOOP
        MOVE.B  (A2),D4
        MOVE.B  (A3),D5
        CMP.B     D4,D5
        BGT     AFTERSWAP
        MOVE.B  D5,(A2)
        MOVE.B  D4,(A3)
AFTERSWAP
        ADD.B  #0,(A2)+
        ADD.B  #0,(A3)+
        SUBQ.B  #1,D2
        BNE     INNERLOOP
        BRA     BUBBLELOOP
EXITLOOP
        MOVEA.L A6,A0
        RTS
;EndBubbleSort
SKIPSUB
        MOVE.B  #228,D7
        TRAP    #14
        END
     
        
        

        END
*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
