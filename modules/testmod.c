#include <linux/kernel.h>
#include <linux/module.h>

int init_module(void) {

	pr_info("Test module loaded\n");

	return 0;
}

void cleanup_module(void) {

	pr_info("Test module unloaded\n");
}

MODULE_LICENSE("GPL");