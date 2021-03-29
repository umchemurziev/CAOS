        .text
        .global forward.args


forward.args:
        push    %ebp
        movl    %esp, %ebp

        subl    $8, %esp

        movl    8(%ebp), %eax
        movl    %eax, 12(%esp)


        movl    20(%ebp), %eax
        movl    %eax, 8(%esp)

        movl    12(%ebp), %eax
        cdq
        movl    %eax, (%esp)
        movl    %edx, 4(%esp)


        call    process

        neg    %eax

        addl    $8, %esp
        movl    %ebp, %esp
        pop     %ebp
        ret
