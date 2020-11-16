/*
 * a simple kernel module: timer_list
 *
 * Licensed under GPLv2 or later.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/timer.h>

#include <asm/io.h>

#if 0 // kernel 2.6
// #include <asm/system.h>
//#include <asm/uacess.h>
#endif

#include <asm/atomic.h>

#define TIMER_MAJAR 0

static int timer_major = TIMER_MAJAR;


void time_pre(struct timer_list *timer);

struct timer_list mytimer;


struct timer_dev{
	struct cdev;
	atomic_t counter;
};


void time_pre(struct timer_list *timer)
{
	printk("[%s]mytimer.expires=%ld\n", __func__,mytimer.expires);
	mytimer.expires = jiffies + 2000 * HZ/1000;  // 500ms 运行一次
	
	printk("[%s]mytimer.expires=%ld\n", __func__,mytimer.expires);
	mod_timer(&mytimer, mytimer.expires);       // 2.2 如果需要周期性执行任务，在定时器回调函数中添加 mod_timer
}

static int __init hello_init(void)
{
	init_timer(&mytimer);
	


	mytimer.function = time_pre;
	mytimer.expires = jiffies + 500 * HZ/1000;
		
	add_timer(&mytimer);
	
	printk("init success\n");

	printk(KERN_INFO "Hello World enter\n");
	return 0;
}
module_init(hello_init);

static void __exit hello_exit(void)
{
	printk(KERN_INFO "Hello World exit\n ");
	   if(timer_pending(&mytimer))
	   {
		           del_timer(&mytimer);    // 3.释放定时器
			       
	   }
}
module_exit(hello_exit);

MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("A simple Hello World Module");
MODULE_ALIAS("a simplest module");
