.global stringCopy
.global stringCat
.global sumS32
.global sumS8
.global sumU32_64
.global countNegative
.global countNonNegative
.global countMatches
.global returnMax
.global returnMin

.text

stringCopy:
	LDRB R2, [R1], #1 @load second string in R2
	STRB R2, [R0], #1 @Store second string in R0
	CMP R2, #0 @if R2 has '\0', end
	BNE stringCopy
	BX LR

stringCat:
	MOV R2, R1
	
	stringCatLoop1:
		LDRB R3, [R2], #1 @ post-index, i++
		CMP R3, #0 @ Check for null-terminator
		BNE stringCatLoop1
		SUB R2, R2, #1
	
	stringCatLoop2:
		LDRB R3, [R0], #1 
		STRB R3, [R2], #1
		CMP R3, #0 @ Check for null-terminator
		BNE stringCatLoop2
		BX LR

sumS32:
	MOV R2, R0
	MOV R0, #0
	
	sumS32Loop:
		LDRSB R3, [R2], #4
		ADDS R0, R0, R3
		SUBS R1, R1, #1 @ i--
		BNE sumS32Loop
		BX LR
	
sumS8:
	MOV R2, R0
	MOV R0, #0
	
	sumS8Loop:
		LDRB R3, [R2], #1
		ADD R0, R0, R3
		SUBS R1, R1, #1 @ i--
		BNE sumS8Loop
		BX LR

sumU32_64:
	MOV R2, R0
	MOV R0, #0
	MOV R4, R1
	MOV R1, #0

	sumU32_64Loop:
		LDR R3, [R2], #4
		ADDS R0, R0, R3
		ADC R1, R1, #0
		SUBS R4, R4, #1
		BNE sumU32_64Loop
		BX LR

countNegative:
	MOV R2, R0
	MOV R0, #0
	
	countNegativeLoop:
		CMP R1, #0
		BEQ countNegativeEnd
		SUB R1, R1, #1
		LDRSB R3, [R2], #1
		CMN R3, #0
		BMI NegativeFound
		B countNegativeLoop
		
	NegativeFound:
		ADD R0, R0, #1
		B countNegativeLoop
		BX LR
	
	countNegativeEnd:
		BX LR
	
countNonNegative:
	MOV R2, R0
	MOV R0, #0
	
	countNonNegativeLoop:
		CMP R1, #0
		BEQ countNonNegativeEnd
		SUB R1, R1, #1
		LDR R3, [R2], #4
		CMP R3, #0
		BGE NonNegativeFound
		B countNonNegativeLoop
	
	NonNegativeFound:
		ADD R0, R0, #1
		B countNonNegativeLoop
	
	countNonNegativeEnd:
		BX LR
	
countMatches:
	MOV R2, R0
	MOV R0, #0
	
	countMatchesLoop1:
		LDRB R3, [R2], #1
		CMP R1, R3
		BEQ countMatchesCounter
		
	countMatchesLoop2:
		CMP R3, #0
		BEQ countMatchesEnd
		B countMatchesLoop1
		
	countMatchesCounter:
		ADD R0, R0, #1
		B countMatchesLoop2
		
	countMatchesEnd:
		BX LR
	
returnMax:
	MOV R2, R0
	MOV R0, #0
	MOV R3, #0
	LDRSB R0, [R2], #1
	SUB R1, R1, #1
	
	returnMaxLoop:
		CMP R1, #0
		BEQ MaxEnd
		SUB R1, R1, #1
		LDRSB R3, [R2], #1
		CMP R0, R3
		BGE MaxGreat
		BLT MaxLess
		B returnMaxLoop
	
	MaxGreat:
		MOV R3, #0
		B returnMaxLoop
		
	MaxLess:
		MOV R0, #0
		MOV R0, R3
		MOV R3, #0
		B returnMaxLoop
	
	MaxEnd:
		BX LR
	
returnMin:
	MOV R2, R0
	MOV R0, #0
	MOV R3, #0
	LDRSB R0, [R2], #1
	SUB R1, R1, #1

	returnMinLoop:
		CMP R1, #0
		BEQ MinEnd
		LDRSB R3, [R2], #1
		SUB R1, R1, #1
		CMP R0, R3
		BMI NEGCOMP
		BLT MinLess
		BGE MinGreat
		B returnMinLoop
	
	NEGCOMP:
		CMN R0, R3
		BLT MinLess
		BGE MinGreat
		
	MinLess:
		MOV R3, #0
		B returnMinLoop
		
	MinGreat:
		MOV R0, #0
		MOV R0, R3
		MOV R3, #0
		B returnMinLoop
	
	MinEnd:
		BX LR
	

