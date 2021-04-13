        .text
        .global обработка

обработка:
        push    %ebp
        mov     %esp, %ebp
        push    %ebx

        mov     тарам, %eax
        imul    %ecx
        mov     %eax, %ebx

        mov     парам, %eax
        imul    %ecx
        sub     $1, %ecx
        imul    %ecx
        add     %eax, %ebx
        
        mov     пампам, %eax
        shr     $2, %eax
        sub     %eax, %ebx
        mov     %ebx, %ecx
       
        pop     %ebx
        pop     %ebp
        ret


        .data
парам:          .int 0
пампам:         .int 0
тарам:          .int 0

        .global парам, пампам, тарам
