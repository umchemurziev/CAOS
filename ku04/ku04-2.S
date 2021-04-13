        .text
        .global вычисления

вычисления:

        push    %ebp
        mov     %esp, %ebp


        push    %ebx
        push    %esi
        mov     8(%ebp), %eax
        movswl  (%eax), %eax
        mov     b, %ebx
        imul    %ebx
        jo      end1

        mov     12(%ebp), %ecx
        mov     16(%ebp), %edx
        sub     (%edx), %ecx
        jo      end1

        add     %ecx, %eax
        jo      end1

        mov     %eax, %esi
        sub     $4, %esp
        mov     12(%ebp), %ecx
        sub     (%edx), %ecx
        mov     %ecx, (%esp)
        mov     20(%ebp), %ebx
        call    *%ebx
        add     $4, %esp
        mov     a, %ebx
        imul    %ebx
        jo      end1

        add     %esi, %eax
        jo      end1

        mov     16(%ebp), %ebx
        mov     %eax, (%ebx)
        mov     $0, %eax
        jmp     end2

end1:
        mov     $1, %eax

end2:
        pop     %esi
        pop     %ebx
        mov     %ebp, %esp
        pop     %ebp
        ret

        .data
a:      .int 64
b:      .int 1000
