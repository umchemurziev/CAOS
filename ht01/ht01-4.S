	.text
	.global satsum
	.align 4

satsum:
	push	{ fp, lr }
	sub     sp, sp, #8
	adds	r0, r0, r1
	bcs	fin
	add 	sp, sp, #8
	pop 	{ fp, pc }

fin:
	mov	r0, #max
	add 	sp, sp, #8
	pop 	{ fp, pc }

	.section	.rodata
max: 	.long	4294967295