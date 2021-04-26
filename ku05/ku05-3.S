        .text
        .global myexp

myexp:
        push    %ebp
        mov     %esp, %ebp

        movsd   mid, %xmm1
        movsd   mer, %xmm2
        movsd   mid, %xmm3
        movsd   mer, %xmm4
        movsd   8(%ebp), %xmm5
        jmp     while

exit:
        sub     $8, %esp
        movsd   %xmm1, (%esp)
        mov     (%esp), %eax
        mov     16(%ebp), %edx
        mov     %eax, (%edx)
        mov     4(%esp), %eax
        mov     %eax, 4(%edx)
        add     $8, %esp

        pop     %ebp
        ret

while:
        addsd   %xmm2, %xmm1
        comisd  %xmm3, %xmm1
        jz      exit

        movsd   %xmm1, %xmm3
        mulsd   %xmm5, %xmm2
        divsd   %xmm4, %xmm2
        addsd   mer, %xmm4
        jmp     while


        .data
mer:    .double 1.0
mid:    .double 0.0
