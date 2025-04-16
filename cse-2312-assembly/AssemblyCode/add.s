.global add

.text 

@int32_t add(int32_t x, int32_t y); 
@					x + y
@	R0			R0			R1

add:
	ADD R0, R0, R1 
	BX LR
