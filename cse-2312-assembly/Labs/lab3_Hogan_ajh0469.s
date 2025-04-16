.global sumF32
.global prodF32
.global dotpF64
.global maxF32
.global absSumF64
.global sqrtSumF64
.global getDirection
.global getAddNo
.global getCity
.global sortDecendingInPlace

.text

sumF32:
	MOV R2, #0
	VMOV S0, R2
	
	sumF32loop:
		CMP R1, #0
		BEQ sumF32end
		VLDR.F32 S1, [R0]
		VADD.F32 S0, S0, S1
		ADD R0, R0, #4
		SUB R1, R1, #1 
		B sumF32loop
	sumF32end:
		VMOV R0, S0
		BX LR
		
prodF32:
	MOV R2, #0
	VMOV S0, R2
	VLDR.F32 S0, [R0]
	ADD R0, R0, #4
	SUB R1, R1, #1
	B prodF32loop
	
	prodF32loop:
		CMP R1, #0
		BEQ prodF32end
		VLDR.F32 S1, [R0]
		VMUL.F32 S0, S0, S1
		ADD R0, R0, #4
		SUB R1, R1, #1 
		B prodF32loop
	prodF32end:
		BX LR
		
dotpF64:
	MOV R3, #0
	VMOV D0, R2, R2
	VMOV D1, R2, R2
	VMOV D3, R2, R2
	
	dotpF64loop:
		CMP R2, #0
		BEQ dotpF64end
		VLDR.F64 D1, [R0]
		VLDR.F64 D2, [R1]
		VMUL.F64 D3, D1, D2
		VADD.F64 D0, D0, D3
		ADD R0, R0, #8
		ADD R1, R1, #8
		SUB R2, R2, #1
		B dotpF64loop
	
	dotpF64end:
		VMOV R0, R1, D0
		BX LR
maxF32:
	MOV R2, R0
	MOV R0, #0
	
	VMOV S0, R0
	VMOV S1, R0
	VLDR.F32 S0, [R2]
	SUB R1, R1, #1
	
	maxF32loop:
		CMP R1, #0
		BEQ maxF32end
		SUB R1, R1, #1
		VLDR.F32 S1, [R2]
		VCMP.F32 S0, S1
		VMRS APSR_nzcv, FPSCR 
		BGE maxF32great
		BLT maxF32less
		B maxF32loop
	
	maxF32great:
		MOV R4, #0
		VMOV S1, R4
		B maxF32loop
		
	maxF32less:
		MOV R4, #0
		VMOV S0, R4
		VMOV S0, S1
		VMOV S1, R4
		B maxF32loop
	
	maxF32end:
		BX LR
		

absSumF64:
	MOV R2, #0
	VMOV D0, R2, R2
	VMOV D1, R2, R2
	
	absSumF64loop:
		CMP R1, #0
		BEQ absSumF64end
		VLDR.F64 D1, [R0]
		VADD.F64 D0, D0, D1
		SUB R1, R1, #1
		ADD R0, R0, #8
		B absSumF64loop
	absSumF64end:
		VABS.F64 D0, D0
		BX LR
		
sqrtSumF64:
	MOV R2, #0
	VMOV D0, R2, R2
	VMOV D1, R2, R2
	
	sqrtSumF64loop:
		CMP R1, #0
		BEQ sqrtSumF64end
		VLDR.F64 D1, [R0]
		VADD.F64 D0, D0, D1
		SUB R1, R1, #1
		ADD R0, R0, #8
		B sqrtSumF64loop
	sqrtSumF64end:
		VSQRT.F64 D0, D0
		BX LR
		
getDirection:
    MOV R3, #120
    MUL R2, R1, R3
    ADD R0, R0, #44
    ADD R0, R0, R2
    LDR R0, [R0]
    BX LR
    
getAddNo:
    MOV R3, #120
    MUL R2, R1, R3
    ADD R0, R0, #40
    ADD R0, R0, R2
    LDR R0, [R0]
    BX LR
    
getCity:
    MOV R3, #120
    MUL R2, R1, R3
    ADD R0, R0, #78
    ADD R0, R0, R2
    BX LR
    
sortDecendingInPlace:
	BX LR
