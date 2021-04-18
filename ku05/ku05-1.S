        .text
        .global forward.args

forward.args:
        push 	%ebp
        mov 	%esp, %ebp

        push 	%ebx
        push 	%esi
        push 	%edi

        mov 	8(%ebp), %ebx
        mov 	12(%ebp), %esi
        mov 	16(%ebp), %edi
        mov 	20(%ebp), %ecx

        push 	%ebx
        push 	%ecx
        push 	%edi
        push 	%esi

        call 	process
        addl 	$16, %esp
		negl 	%eax

        pop 	%edi
        pop 	%esi
        pop 	%ebx

        pop 	%ebp
        ret
