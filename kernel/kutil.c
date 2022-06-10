#include <libc/types.h>

#include "kernel.h"

void k_message(string_t msg) {
    sys_print("Kernel: ");
    sys_print(msg);
    sys_print("\n");
}

void k_message_err(string_t msg) {
    sys_print("Kernel error: ");
    sys_print(msg);
    sys_print("\n");
}