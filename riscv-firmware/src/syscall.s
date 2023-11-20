.section .text, "ax"
.global initialize
.global getTicks,getButtonStatus,getCmdInterrupted,getVideoInterrupted,threadInit




initialize:
    li a3,0
    ecall

getTicks:
    li a3,1
    ecall

getButtonStatus:
    li a3,2
    ecall

getCmdInterrupted:
    li a3,3
    ecall


getVideoInterrupted:
    li a3,4
    ecall

threadInit:
    li a3,5
    ecall