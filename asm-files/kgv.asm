LDA #13
STA 1
LDA #7
STA 2
LDA (1)  	  
STA 12
LDA (2)
SUB #1
STA 12
LDA (11)  
ADD (1)
STA 11
LDA (12) 
SUB #1
BRN #3
STA 12   
JMP 9
NOP 
LDA (1)
STA 21
LDA (2)
STA 22
LDA (21)  
SUB (22)
BRN #4
BRZ #10 
STA 21
JMP 22
LDA (22)
STA 23		 
LDA (21)
STA 22
LDA (23)
STA 21
JMP 22
NOP
LDA #0
STA 41   
LDA (11)
SUB (22)
STA 11
LDA (41)
ADD #1
STA 41
LDA (11)
BRZ #3
STA 11 
JMP 38
NOP
