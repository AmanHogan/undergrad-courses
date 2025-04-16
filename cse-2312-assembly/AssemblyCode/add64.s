.global add64

.text 

@ int64_t add64(int64_t x, int64_t y);
@   R1:R0			R1:R0		R3:R2

add64:
	ADDS R0, R0, R2
	ADC R1, R1, R3
	BX LR
