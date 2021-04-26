	.text
	.global main

main:
	push    { fp, lr }
	sub     sp, sp, #8

	ldr 	r0, =ifmt
	mov 	r1, sp
	add	r2, sp, #4
	bl 	scanf

	ldr	r1, [sp]
	ldr 	r2, [sp, #4]
	add 	r1, r1, r2
	ldr 	r0, =ofmt
	bl 	printf

	add 	sp, sp, #8
	mov 	r0, #0
	pop 	{ fp, pc }


	.section	.rodata
ifmt:	.asciz	"%d%d"
ofmt:	.asciz	"%d\n"

// Решение взял с лекции