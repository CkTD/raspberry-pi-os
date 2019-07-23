#include "printf.h"
#include "utils.h"
#include "timer.h"
#include "irq.h"
#include "sched.h"
#include "fork.h"
#include "mini_uart.h"
#include "sys.h"
#include "debug.h"

void user_process1(char *array)
{
	while (1){
			call_sys_write(array);
			DEBUG("User process1 running");
            delay(10000000);
	}
}

void user_process(){
    DEBUG("User process running");
	char buf[30] = {0};
	tfp_sprintf(buf, "this is user process call syscall write\n\r");
	call_sys_write(buf);
	unsigned long stack = call_sys_malloc();
	if (stack < 0) {
		printf("Error while allocating stack for process 1\n\r");
		return;
	}
	int err = call_sys_clone((unsigned long)&user_process1,(unsigned long)"Message from user process 1\r\n", stack);
	if (err < 0){
		printf("Error while clonning process 1\n\r");
		return;
	} 
	stack = call_sys_malloc();
	if (stack < 0) {
		printf("Error while allocating stack for process 1\n\r");
		return;
	}
	err = call_sys_clone((unsigned long)&user_process1, (unsigned long)"Message from user process 2\r\n", stack);
	if (err < 0){
		printf("Error while clonning process 2\n\r");
		return;
	} 
	call_sys_exit();
}

void kernel_process(){
	printf("Kernel process started. EL %d\r\n", get_el());
	int err = move_to_user_mode((unsigned long)&user_process);
	if (err < 0){
		printf("Error while moving process to user mode\n\r");
	} 
}


void kernel_main(void)
{
	uart_init();
	init_printf(0, putc);
	irq_vector_init();
	timer_init();
	enable_interrupt_controller();
	enable_irq();


    DEBUG("kernel running");

	int res = copy_process(PF_KTHREAD, (unsigned long)&kernel_process, 0, 0);
	if (res < 0) {
		printf("error while starting kernel process");
		return;
	}

    

	while (1){
		schedule();
	}	
}
