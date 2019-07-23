#include "debug.h"
#include "utils.h"
#include "printf.h"

const char msg_irq_entry[] = "IRQ entry";
const char msg_irq_exit[] = "IRQ exit";
const char msg_ret_from_fork_kernel[] = "ret from fork(to kernel mode)";
const char msg_ret_from_fork_user[] = "ret from fork(to user mode)";
const char msg_svc_entry[] = "SVC entry(lr for #syscall)";
const char msg_svc_exit[] = "SVC exit(lr for return value)";

void debug(unsigned long msg, unsigned long lr, unsigned long sp)
{
    printf("[%s], lr: 0x%x, sp: 0x%x\r\n", msg, lr, sp);
}
