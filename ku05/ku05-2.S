.text
        .global process

process:
        push    %ebp
        mov     %esp, %ebp

        push    %esi
        push    %edi
        push    %ebx

        mov     20(%esp), %eax
        mov     (%eax), %ebx
        mov     4(%eax), %ecx
        mov     12(%eax), %esi
        mov     8(%eax), %eax

        imul    %ebx
        mov     %eax, %edi
        mov     %esi, %eax
        mov     %edx, %esi

        imul    %ecx
        add     %edi, %eax
        adc     %esi, %edx
        jo      over
        
        pop     %ebx
        pop     %edi
        pop     %esi
        pop     %ebp
        ret

over:
        pop     %ebx
        pop     %edi
        pop     %esi
        mov     $0, %eax
        mov     $0, %edx

        pop     %ebp
        ret
