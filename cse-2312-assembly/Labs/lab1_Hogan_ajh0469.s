.global add64
.global sub64
.global minS16
.global minU8
.global isLessThanU32
.global isLessThanS8
.global shiftLeftU16
.global shiftU16
.global shiftS8
.global isEqualS16
.global isEqualU32

.text

add64:
	ADDS R0, R0, R1 
	MOV R1, #0 
	ADC R1, R1, #0
	BX LR

sub64:
	SUBS R0, R0, R2
	SBC R1, R1, R3
	BX LR
	
minS16:
	CMP R0, R1 @ Compare R0 with R1
	BLT lessThan
	BGE GreaterThan
	lessThan:
		BX LR
	GreaterThan:
		MOV R0, R1
		BX LR
		
minU8:
	CMP R0, R1 @ Compare R0 with R1
	BLT lessThan2
	BGE GreaterThan2
	lessThan2:
		BX LR
	GreaterThan2:
		MOV R0, R1
		BX LR
		
isLessThanU32:
	CMP R0, R1 @ Compare R0 with R1
	BLT lessThan3
	BGE GreaterThan3
	lessThan3:
		MOV R0, #1
		BX LR
	GreaterThan3:
		MOV R0, #0
		BX LR
	
isLessThanS8:
	CMP R0, R1 @ Compare R0 with R1
	BLT lessThan4
	BGE GreaterThan4
	lessThan4:
		MOV R0, #1
		BX LR
	GreaterThan4:
		MOV R0, #0
		BX LR
		
shiftLeftU16:
	MOV R0, R0, LSL R1
	BX LR
	
shiftU16:
	CMP R1, #0
	BLT right1
	BGE left1
	
	left1:
		MOV R0, R0, ASL R1
		BX LR
	right1:
		RSB R1, R1, #0
		MOV R0, R0, ASR R1
		BX LR

shiftS8:
		
	CMP R1, #0
	BLT right
	BGE left
	
	left:
		MOV R0, R0, ASL R1
		BX LR
	right:
		RSB R1, R1, #0
		MOV R0, R0, ASR R1
		BX LR
		
isEqualS16:
	CMP R0, R1
	BNE F
	BEQ T
	
		T:
			MOV R0, #1
			BX LR
		F:
			MOV R0, #0
			BX LR

isEqualU32:
	CMP R0, R1
	BNE F2
	BEQ T2
	
		T2:
			MOV R0, #1
			BX LR
		F2:
			MOV R0, #0
			BX LR
