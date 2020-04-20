    global  set_bit_elem
    global  get_bit_elem
    section .text

set_bit_elem:
    push rbp            ; save the base pointer on the stack (at rsp+8)
    mov rbp, rsp        ; set up the rbp for the bottom of this frame

    ; rdi contains array pointer
    ; rsi contains row width
    ; rdx contains row
    ; rcx contains col

    mov rax,rdx
    imul rax,rsi
    add rax,rcx
    sal rax,4
    add rax,rdi
    mov rdx,1
    mov rax,rdx

    mov rax, 1

    mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
    pop rbp             ; remove rbp from the stack to restore rsp to initial value
    ret                 ; return value in rax

get_bit_elem:
    push rbp            ; save the base pointer on the stack (at rsp+8)
    mov rbp, rsp        ; set up the rbp for the bottom of this frame

    ; rdi contains array pointer
    ; rsi contains row width
    ; rdx contains row
    ; rcx contains col

    ; add your code here - for now returning 0

    mov rax, rdx    ; store the row in the return value
    mov rdx, 0      ; rdx = 0
    imul rax, rsi   ; multiply by the width of a row to get down to the row we want
    add rax, rcx    ; add the collumn we want. We now have the index of the element in the array we want
    mov rsi, 8      ; rsi = 8
    idiv rsi        ; rax/rsi
    add rdi, rax    ; rdi = rdi + rax
    mov rsi, 1      ; rsi = 1
    mov rbx, 7      ; rbx = 7
    sub rbx, rdx    ; rbx = rbx - rdx (rdx = 0 so this line is useless
    mov rcx, rbx    ; rcx = rbx
    sal rsi, cl
    mov rax, rdi    ; rax = rdi
    or [rax], rsi
;    cmp rax,1
    mov rax, 1      ; rax = 1

    mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
    pop rbp             ; remove rbp from the stack to restore rsp to initial value
    ret                 ; return value in rax