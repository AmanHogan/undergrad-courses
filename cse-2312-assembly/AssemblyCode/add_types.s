.global add32
.global add16
.global add8
.global addU32

.text 

addU32:
add8:
add16:
add32:
	ADD R0, R0, R1 
	BX LR
