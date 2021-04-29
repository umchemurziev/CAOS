unsigned _strlen(const char *rhs){
    int res = 0;
    while(*rhs++) ++res;
 
    return res;
} 
 
// проверка только длины..
int _strcmp(const char *first, const char *last){
    unsigned f = _strlen(first);
    unsigned l = _strlen(last);
 
    if(f == l) return 0;
 
    return (f < l) ? -1 : 1;
}


	.text
	.global mystrcmp

mystrcmp:
	push	{ fp, lr }

while:
	mov	r2, r0
	ldrb	r2, [r2]

	mov	r3, r1
	ldrb	r3, [r3]

	tst	r3, r3
	beq	fin
	
	tst	r2, r2
	beq	fin

	cmp	r2, r3
	bhi	greater
	blo	lesser

	add	r0, r0, #1
	add	r1, r1, #1
	bal	while

fin:
	sub	r2, r2, r3
	mov	r0, r2
	pop	{ fp, pc }

greater:
	mov	r0, r2
	pop	{ fp, pc }

lesser:
	mov	r0, #-1
	pop	{ fp, pc }
