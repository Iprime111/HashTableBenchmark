.global _Z9StreqFastPcS_

.section .text

_Z9StreqFastPcS_:
    vmovdqu8 (%rdi), %zmm0
    vmovdqu8 (%rsi), %zmm1
    vpcmpeqb %zmm1, %zmm0, %k0
    kmovq %k0, %rax
    ret

