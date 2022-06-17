#include <drivers/cpu/cpu.h>
#include <kernel/kernel.h>
#include <libc/libc.h>

#include "sys.h"

/*********************
 * System call masks *
 *********************/

void sysmask_getpit() {
    uint32_t tick_ptr;
    __asm__("movl %%ebx, %0" : "=r"(tick_ptr));

    sys_getpit((uint32_t*)tick_ptr);
}

void sysmask_getdatetime() {
    uint32_t dt_ptr;
    __asm__("movl %%ebx, %0" : "=r"(dt_ptr));

    sys_getdatetime((datetime_t*)dt_ptr);
}

void sysmask_setdatetime() {
    uint32_t dt_ptr;
    __asm__("movl %%ebx, %0" : "=r"(dt_ptr));

    sys_setdatetime((datetime_t*)dt_ptr);
}

/***********************
 * System call methods *
 ***********************/

void sys_getpit(uint32_t* tick) {
    *tick = pit_tick;
}

void sys_getdatetime(datetime_t* dt) {
    *dt = k_dt;
}

void sys_setdatetime(datetime_t* dt) {
    // Nothing here yet
}