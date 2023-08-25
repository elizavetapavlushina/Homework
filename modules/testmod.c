#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/rwlock.h>
#include <linux/proc_fs.h>
#include <linux/sysfs.h>
#include <linux/string.h>
#include <linux/kobject.h>

static char test_string[20] = "Hello world!\0";
static int major = 0;
static rwlock_t lock;


ssize_t test_read(struct file *fd, char __user *buff, size_t size, loff_t *off) {

	size_t rc;

	read_lock(&lock);
	rc = simple_read_from_buffer(buff, size, off, test_string, 20);

	read_unlock(&lock);

	return rc;
}

ssize_t test_write(struct file *fd, const char __user *buff, size_t size, loff_t *off) {

	size_t rc = 0;

	if (size > 20) 
		return -EINVAL;

	write_lock(&lock);
	rc = simple_write_to_buffer(test_string, 20, off, buff, size);

	write_unlock(&lock);

	return rc;
}

static struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.read = test_read,
	.write = test_write

};

int init_module(void) {

	int retval = 0;

	pr_info("Test module loaded\n");

	rwlock_init(&lock);
	major = register_chrdev(major, "testmod", &fops);
	pr_info("Major = %d\n", major);
	
	if (major < 0)
		return major;
	pr_info("Major = %d\n", major);

	return 0;
}

void cleanup_module(void) {

	unregister_chrdev(major, "testmod");
	pr_info("Test module unloaded\n");
}

MODULE_LICENSE("GPL");