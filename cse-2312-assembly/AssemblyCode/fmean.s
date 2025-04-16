.global fmean

.text

@ double fmean(double x[], uint32_t count);

fmean:
	VMOV S4, R1 @ Save count in scalar, we'll need it later
	MOV R2, #0
	VMOV D0, R2, R2 @ Zero out accumulator

fmean_loop:
	CMP R1, #0 @ Check counter
	BEQ fmean_end

	VLDR.F64 D1, [R0]	@ Load double in [R0] to D1
	VADD.F64 D0, D0, D1 @ Add D1 to accumulator

	SUB R1, R1, #1 @ Decrement counter
	ADD R0, R0, #8 @ Move address forward 64-bits
	B fmean_loop

fmean_end:
	VCVT.F64.U32 D1, S4 @ Convert uint32_t to double, save in D1
	VDIV.F64 D0, D0, D1

	BX LR
