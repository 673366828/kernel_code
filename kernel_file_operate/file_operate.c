#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/dcache.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <asm/fcntl.h>
#include <asm/processor.h>
#include <asm/uaccess.h>

static int __init hello_init(void)
{
	unsigned char buf1[12] = "hello world.";
	unsigned char buf2[12] = "kernel file.";
	unsigned char buf[30];

	struct file *fp;
	mm_segment_t fs;
	loff_t pos;

	printk("hello enter\n");
	fp = filp_open("/home/hza/git/code/kernel_file_operate/kernel_file.txt",O_RDWR | O_CREAT, 0644);
	if(IS_ERR(fp)){
		printk("create file error\n");
		return -1;
	}

	fs = get_fs();
	set_fs(KERNEL_DS);

	pos = fp->f_pos;
	vfs_write(fp,buf1,sizeof(buf1),&pos);
	fp->f_pos = pos;

	pos = fp->f_pos;
	vfs_write(fp,buf2,sizeof(buf2),&pos);
	fp->f_pos = pos;

	pos = 0;
	vfs_read(fp,buf,sizeof(buf),&pos);
	printk("read:%s\n",buf);

	filp_close(fp,NULL);
	set_fs(fs);

	return 0;	
}	

static void __exit hello_exit(void)
{
	printk("hello exit\n");
}	

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
