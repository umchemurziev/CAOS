       .text
        .global обработка

обработка:
        push 	%ebp
        mov 	%esp, %ebp
        push 	%esi
        push 	%edi
        add  	$12, %edi
        mov  	$0, %edx

while:
        cmp 	$0, %ebx
        jz 		end
        mov  	4(%ebx, %esi, 4), %eax
        mov  	4(%ebx, %edi, 4), %ecx
        add  	%ecx, %eax
        cmp 	$0, %eax
        jl 		neg
res:
        sar 	$1, %eax
        add  	%eax, %edx
        mov  	(%ebx), %ebx
        cmp 	$0, %ebx
        jz 		end
        jmp 	while

end:
        pop 	%edi
        pop 	%esi
        pop		%ebp
        mov  	(%esp), %eax
        push 	%eax
        mov  	%edx, 4(%esp)
        ret
neg:
        incl 	%eax
        jmp 	res

