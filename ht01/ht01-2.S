	.text
	.global print_fib

print_fib:
	push    { fp, lr }
	sub     sp, sp, #12

	ldr 	r0, =ofmt
	mov 	r1, sp
	add		r2, sp, #4
	add 	r3, sp, #8

	ldr		r1, =A
	ldr 	r1, [r1]
	ldr 	r2,	=B
	ldr 	r2, [r2]
	add 	r1, r1, r2
	add 	r2, r1, r2
	add 	r3, r1, r2
	bl 		printf

	add 	sp, sp, #12
	mov 	r0, #0
	pop 	{ fp, pc }


	.section	.rodata
ofmt:	.asciz	"%d %d %d\n"
