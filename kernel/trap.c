// FILE: trap.c
// 2025/01/28 Voltline

#include "trap.h"
#include "kernel.h"

__attribute__((naked))
__attribute__((aligned(4)))
void kernel_entry(void)
{
    __asm__ __volatile__(
        "csrw sscratch, sp\n"
        "addi sp, sp, -4 * 31\n"
        "sw ra, 0(sp)\n"
        "sw gp, 4(sp)\n"
        "sw tp, 8(sp)\n"
        "sw t0, 12(sp)\n"
        "sw t1, 16(sp)\n"
        "sw t2, 20(sp)\n"
        "sw t3, 24(sp)\n"
        "sw t4, 28(sp)\n"
        "sw t5, 32(sp)\n"
        "sw t6, 36(sp)\n"
        "sw a0, 40(sp)\n"
        "sw a1, 44(sp)\n"
        "sw a2, 48(sp)\n"
        "sw a3, 52(sp)\n"
        "sw a4, 56(sp)\n"
        "sw a5, 60(sp)\n"
        "sw a6, 64(sp)\n"
        "sw a7, 68(sp)\n"
        "sw s0, 72(sp)\n"
        "sw s1, 76(sp)\n"
        "sw s2, 80(sp)\n"
        "sw s3, 84(sp)\n"
        "sw s4, 88(sp)\n"
        "sw s5, 92(sp)\n"
        "sw s6, 96(sp)\n"
        "sw s7, 100(sp)\n"
        "sw s8, 104(sp)\n"
        "sw s9, 108(sp)\n"
        "sw s10, 112(sp)\n"
        "sw s11, 116(sp)\n"

        "csrr a0, sscratch\n"
        "sw a0, 120(sp)\n"

        "mv a0, sp\n"
        "call handle_trap\n"

        "lw ra, 0(sp)\n"
        "lw gp, 4(sp)\n"
        "lw tp, 8(sp)\n"
        "lw t0, 12(sp)\n"
        "lw t1, 16(sp)\n"
        "lw t2, 20(sp)\n"
        "lw t3, 24(sp)\n"
        "lw t4, 28(sp)\n"
        "lw t5, 32(sp)\n"
        "lw t6, 36(sp)\n"
        "lw a0, 40(sp)\n"
        "lw a1, 44(sp)\n"
        "lw a2, 48(sp)\n"
        "lw a3, 52(sp)\n"
        "lw a4, 56(sp)\n"
        "lw a5, 60(sp)\n"
        "lw a6, 64(sp)\n"
        "lw a7, 68(sp)\n"
        "lw s0, 72(sp)\n"
        "lw s1, 76(sp)\n"
        "lw s2, 80(sp)\n"
        "lw s3, 84(sp)\n"
        "lw s4, 88(sp)\n"
        "lw s5, 92(sp)\n"
        "lw s6, 96(sp)\n"
        "lw s7, 100(sp)\n"
        "lw s8, 104(sp)\n"
        "lw s9, 108(sp)\n"
        "lw s10, 112(sp)\n"
        "lw s11, 116(sp)\n"
        "lw sp, 120(sp)\n"
        "sret\n"
    );
}

void handle_trap(struct trap_frame *f) 
{
    uint32_t scause = READ_CSR(scause);
    uint32_t stval = READ_CSR(stval);
    uint32_t user_pc = READ_CSR(sepc);

    PANIC("unexpected trap scause=%x, stval=%x, sepc=%x\n", scause, stval, user_pc);
}