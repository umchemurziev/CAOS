.text
        .global process

process:
        push    %ebp
        mov     %esp, %ebp

        push    %ebx
        push    %esi
        push    %edi


        mov     20(%esp), %eax
        mov     (%eax), %ebx
        mov     4(%eax), %ecx
        mov     8(%eax), %esi
        mov     12(%eax), %edi

        mov     %edi, %eax
        imul    %ecx
        mov     %eax, %edi
        mov     %esi, %eax
        mov     %edx, %esi

        imul    %ebx
        add     %edi, %eax
        adc     %esi, %edx
        jo      over

        jmp     end

over:
        mov     $0, %eax
        mov     $0, %edx

end:
        pop     %edi
        pop     %esi
        pop     %ebx
        pop     %ebp
        ret
