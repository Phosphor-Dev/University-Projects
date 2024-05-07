    .globl garble
garble:
    enter $(8 * 66), $0
    movq %rdi, -8(%rbp)
    movq %rsi, -16(%rbp)
    /*** CopyInst ***/
    movq $0, %r10
    movq %r10, -24(%rbp)
    /*** CopyInst ***/
    movq -24(%rbp), %r10
    movq %r10, -32(%rbp)
    /*** CopyInst ***/
    movq $0, %r10
    movq %r10, -40(%rbp)
    /*** CopyInst ***/
    movq -40(%rbp), %r10
    movq %r10, -48(%rbp)
    /*** CopyInst ***/
    movq $0, %r10
    movq %r10, -56(%rbp)
    /*** CopyInst ***/
    movq -56(%rbp), %r10
    movq %r10, -48(%rbp)
L6:
    /*** CopyInst ***/
    movq $0, %r10
    movq %r10, -64(%rbp)
    /*** CompareInst ***/
    movq $0, %r10
    movq $1, %rax
    movq -8(%rbp), %r11
    cmp -64(%rbp), %r11
    cmove %rax, %r10
    movq %r10, -72(%rbp)
    /*** JumpInst ***/
    movq -72(%rbp), %r10
    cmp $1, %r10
    je L2
    /*** CopyInst ***/
    movq $0, %r10
    movq %r10, -80(%rbp)
L15:
    movq $1, %r11
    subq %r11$t8
    /*** JumpInst ***/
    movq -80(%rbp), %r10
    cmp $1, %r10
    je L3
    /*** CopyInst ***/
    movq $0, %r10
    movq %r10, -88(%rbp)
    /*** CopyInst ***/
    movq -88(%rbp), %r10
    movq %r10, -96(%rbp)
L14:
    /*** CopyInst ***/
    movq $0, %r10
    movq %r10, -104(%rbp)
    /*** CompareInst ***/
    movq $0, %r10
    movq $1, %rax
    movq -48(%rbp), %r11
    cmp -104(%rbp), %r11
    cmovne %rax, %r10
    movq %r10, -112(%rbp)
    /*** JumpInst ***/
    movq -112(%rbp), %r10
    cmp $1, %r10
    je L13
    /*** ReturnInst ***/
    movq -96(%rbp), %rax
    leave
    ret
L13:
    /*** CopyInst ***/
    movq $2, %r10
    movq %r10, -120(%rbp)
    /*** BinaryOperator ***/
    movq -96(%rbp), %r10
    imulq -120(%rbp), %r10
    movq %r10, -128(%rbp)
    /*** CopyInst ***/
    movq $2, %r10
    movq %r10, -136(%rbp)
    /*** BinaryOperator ***/
    movq -32(%rbp), %rax
    cqto
    idivq -136(%rbp)
    movq %rax, -144(%rbp)
    /*** CopyInst ***/
    movq $2, %r10
    movq %r10, -152(%rbp)
    /*** BinaryOperator ***/
    movq -144(%rbp), %r10
    imulq -152(%rbp), %r10
    movq %r10, -160(%rbp)
    /*** BinaryOperator ***/
    movq -32(%rbp), %r10
    subq -160(%rbp), %r10
    movq %r10, -168(%rbp)
    /*** BinaryOperator ***/
    movq -128(%rbp), %r10
    addq -168(%rbp), %r10
    movq %r10, -176(%rbp)
    /*** CopyInst ***/
    movq -176(%rbp), %r10
    movq %r10, -96(%rbp)
    /*** CopyInst ***/
    movq $2, %r10
    movq %r10, -184(%rbp)
    /*** BinaryOperator ***/
    movq -32(%rbp), %rax
    cqto
    idivq -184(%rbp)
    movq %rax, -192(%rbp)
    /*** CopyInst ***/
    movq -192(%rbp), %r10
    movq %r10, -32(%rbp)
    /*** CopyInst ***/
    movq $1, %r10
    movq %r10, -200(%rbp)
    /*** BinaryOperator ***/
    movq -48(%rbp), %r10
    subq -200(%rbp), %r10
    movq %r10, -208(%rbp)
    /*** CopyInst ***/
    movq -208(%rbp), %r10
    movq %r10, -48(%rbp)
    jmp L14
L3:
    /*** CopyInst ***/
    movq $2, %r10
    movq %r10, -216(%rbp)
    /*** BinaryOperator ***/
    movq -8(%rbp), %rax
    cqto
    idivq -216(%rbp)
    movq %rax, -224(%rbp)
    /*** CopyInst ***/
    movq $2, %r10
    movq %r10, -232(%rbp)
    /*** BinaryOperator ***/
    movq -224(%rbp), %r10
    imulq -232(%rbp), %r10
    movq %r10, -240(%rbp)
    /*** BinaryOperator ***/
    movq -8(%rbp), %r10
    subq -240(%rbp), %r10
    movq %r10, -248(%rbp)
    /*** CopyInst ***/
    movq -248(%rbp), %r10
    movq %r10, -256(%rbp)
    /*** CopyInst ***/
    movq $2, %r10
    movq %r10, -264(%rbp)
    /*** BinaryOperator ***/
    movq -16(%rbp), %rax
    cqto
    idivq -264(%rbp)
    movq %rax, -272(%rbp)
    /*** CopyInst ***/
    movq $2, %r10
    movq %r10, -280(%rbp)
    /*** BinaryOperator ***/
    movq -272(%rbp), %r10
    imulq -280(%rbp), %r10
    movq %r10, -288(%rbp)
    /*** BinaryOperator ***/
    movq -16(%rbp), %r10
    subq -288(%rbp), %r10
    movq %r10, -296(%rbp)
    /*** CopyInst ***/
    movq -296(%rbp), %r10
    movq %r10, -304(%rbp)
    /*** CopyInst ***/
    movq $1, %r10
    movq %r10, -312(%rbp)
    /*** CompareInst ***/
    movq $0, %r10
    movq $1, %rax
    movq -256(%rbp), %r11
    cmp -312(%rbp), %r11
    cmove %rax, %r10
    movq %r10, -320(%rbp)
    /*** JumpInst ***/
    movq -320(%rbp), %r10
    cmp $1, %r10
    je L4
    /*** CopyInst ***/
    movq $0, %r10
    movq %r10, -328(%rbp)
L12:
    /*** JumpInst ***/
    movq -328(%rbp), %r10
    cmp $1, %r10
    je L5
    /*** CopyInst ***/
    movq $0, %r10
    movq %r10, -336(%rbp)
    /*** CompareInst ***/
    movq $0, %r10
    movq $1, %rax
    movq -256(%rbp), %r11
    cmp -336(%rbp), %r11
    cmove %rax, %r10
    movq %r10, -344(%rbp)
    /*** JumpInst ***/
    movq -344(%rbp), %r10
    cmp $1, %r10
    je L7
    /*** CopyInst ***/
    movq $0, %r10
    movq %r10, -352(%rbp)
L11:
    /*** JumpInst ***/
    movq -352(%rbp), %r10
    cmp $1, %r10
    je L8
    /*** CopyInst ***/
    movq $2, %r10
    movq %r10, -360(%rbp)
    /*** BinaryOperator ***/
    movq -32(%rbp), %r10
    imulq -360(%rbp), %r10
    movq %r10, -368(%rbp)
    /*** CopyInst ***/
    movq -368(%rbp), %r10
    movq %r10, -32(%rbp)
L10:
L9:
    /*** CopyInst ***/
    movq $2, %r10
    movq %r10, -376(%rbp)
    /*** BinaryOperator ***/
    movq -8(%rbp), %rax
    cqto
    idivq -376(%rbp)
    movq %rax, -384(%rbp)
    /*** CopyInst ***/
    movq -384(%rbp), %r10
    movq %r10, -8(%rbp)
    /*** CopyInst ***/
    movq $2, %r10
    movq %r10, -392(%rbp)
    /*** BinaryOperator ***/
    movq -16(%rbp), %rax
    cqto
    idivq -392(%rbp)
    movq %rax, -400(%rbp)
    /*** CopyInst ***/
    movq -400(%rbp), %r10
    movq %r10, -16(%rbp)
    /*** CopyInst ***/
    movq $1, %r10
    movq %r10, -408(%rbp)
    /*** BinaryOperator ***/
    movq -48(%rbp), %r10
    addq -408(%rbp), %r10
    movq %r10, -416(%rbp)
    /*** CopyInst ***/
    movq -416(%rbp), %r10
    movq %r10, -48(%rbp)
    jmp L6
L8:
    /*** CopyInst ***/
    movq $2, %r10
    movq %r10, -424(%rbp)
    /*** BinaryOperator ***/
    movq -32(%rbp), %r10
    imulq -424(%rbp), %r10
    movq %r10, -432(%rbp)
    /*** CopyInst ***/
    movq $1, %r10
    movq %r10, -440(%rbp)
    /*** BinaryOperator ***/
    movq -432(%rbp), %r10
    addq -440(%rbp), %r10
    movq %r10, -448(%rbp)
    /*** CopyInst ***/
    movq -448(%rbp), %r10
    movq %r10, -32(%rbp)
    jmp L10
    /*** CopyInst ***/
    movq $0, %r10
    movq %r10, -352(%rbp)
    jmp L11
L7:
    /*** CopyInst ***/
    movq $1, %r10
    movq %r10, -456(%rbp)
    /*** CompareInst ***/
    movq $0, %r10
    movq $1, %rax
    movq -304(%rbp), %r11
    cmp -456(%rbp), %r11
    cmove %rax, %r10
    movq %r10, -464(%rbp)
    /*** CopyInst ***/
    movq %r10, -352(%rbp)
L5:
    /*** CopyInst ***/
    movq $2, %r10
    movq %r10, -472(%rbp)
    /*** BinaryOperator ***/
    movq -32(%rbp), %r10
    imulq -472(%rbp), %r10
    movq %r10, -480(%rbp)
    /*** CopyInst ***/
    movq $1, %r10
    movq %r10, -488(%rbp)
    /*** BinaryOperator ***/
    movq -480(%rbp), %r10
    addq -488(%rbp), %r10
    movq %r10, -496(%rbp)
    /*** CopyInst ***/
    movq -496(%rbp), %r10
    movq %r10, -32(%rbp)
    jmp L9
    /*** CopyInst ***/
    movq $0, %r10
    movq %r10, -328(%rbp)
    jmp L12
L4:
    /*** CopyInst ***/
    movq $0, %r10
    movq %r10, -504(%rbp)
    /*** CompareInst ***/
    movq $0, %r10
    movq $1, %rax
    movq -304(%rbp), %r11
    cmp -504(%rbp), %r11
    cmove %rax, %r10
    movq %r10, -512(%rbp)
    /*** CopyInst ***/
    movq %r10, -328(%rbp)
    /*** CopyInst ***/
    movq $0, %r10
    movq %r10, -80(%rbp)
    jmp L15
L2:
    /*** CopyInst ***/
    movq $0, %r10
    movq %r10, -520(%rbp)
    /*** CompareInst ***/
    movq $0, %r10
    movq $1, %rax
    movq -16(%rbp), %r11
    cmp -520(%rbp), %r11
    cmove %rax, %r10
    movq %r10, -528(%rbp)
    /*** CopyInst ***/
    movq %r10, -80(%rbp)
    .globl main
main:
    enter $(8 * 78), $0
    /*** CopyInst ***/
    movq $0, %r10
    movq %r10, -536(%rbp)
    /*** CopyInst ***/
    movq -536(%rbp), %r10
    movq %r10, -544(%rbp)
L3:
    /*** CopyInst ***/
    movq $40, %r10
    movq %r10, -552(%rbp)
    /*** CompareInst ***/
    movq $0, %r10
    movq $1, %rax
    movq -544(%rbp), %r11
    cmp -552(%rbp), %r11
    cmovl %rax, %r10
    movq %r10, -560(%rbp)
    /*** JumpInst ***/
    movq -560(%rbp), %r10
    cmp $1, %r10
    je L2
    leave
    ret
L2:
    /*** CallInst ***/
    call readChar
    movq %rax, -568(%rbp)
    /*** CopyInst ***/
    movq -568(%rbp), %r10
    movq %r10, -576(%rbp)
    /*** CopyInst ***/
    movq $7, %r10
    movq %r10, -584(%rbp)
    /*** BinaryOperator ***/
    movq -584(%rbp), %r10
    addq -544(%rbp), %r10
    movq %r10, -592(%rbp)
    /*** CallInst ***/
    movq -576(%rbp), %rdi
    movq -592(%rbp), %rsi
    call garble
    movq %rax, -600(%rbp)
    /*** CallInst ***/
    movq -600(%rbp), %rdi
    call printChar
    movq %rax, -608(%rbp)
    /*** CopyInst ***/
    movq $1, %r10
    movq %r10, -616(%rbp)
    /*** BinaryOperator ***/
    movq -544(%rbp), %r10
    addq -616(%rbp), %r10
    movq %r10, -624(%rbp)
    /*** CopyInst ***/
    movq -624(%rbp), %r10
    movq %r10, -544(%rbp)
    jmp L3
