#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/delay.h>

static struct task_struct *tsk;

static int thread_function(void *data) {
	int time_count = 0;
	do {
		printk(KERN_INFO "Hello, World!");
		msleep(1000);
	} while (!kthread_should_stop() && time_count <= 15);
	return time_count;
}

static int hello_init(void) {
	tsk = kthread_run(thread_function, NULL, "mythread%d", 1);
	return 0;
}

static void hello_exit(void) {
	if (!IS_ERR(tsk)) {
		int ret = kthread_stop(tsk);
		printk(KERN_INFO "thread function has run %ds\n", ret);
	}
}

module_init(hello_init);
module_exit(hello_exit);
