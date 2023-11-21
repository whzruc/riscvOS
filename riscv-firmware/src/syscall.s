.section .text, "ax"
.global initialize
.global getTicks,getButtonStatus,getCmdInterrupted,getVideoInterrupted,threadInit
.global thread_create,thread_yield,thread_exit





initialize:
    li a4,0
    ecall

getTicks:
    li a4,1
    ecall

getButtonStatus:
    li a4,2
    ecall

getCmdInterrupted:
    li a4,3
    ecall


getVideoInterrupted:
    li a4,4
    ecall

threadInit:
    li a4,5
    ecall


thread_create:
    li a4,6
    ecall

thread_yield:
    li a4,7
    ecall

thread_exit:
    li a4,8
    ecall