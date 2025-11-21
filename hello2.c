#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include "hello1.h"

MODULE_AUTHOR("Shostak");
MODULE_DESCRIPTION("hello module 2");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count, "how many times to print");

static int __init h2_init(void)
{
    int i;

    if (count == 0 || (count >= 5 && count <= 10))
        pr_warn("h2: strange count %u\n", count);
    else if (count > 10) {
        pr_err("h2: too big %u\n", count);
        return -EINVAL;
    }

    pr_info("h2: printing %u times\n", count);

    for (i = 0; i < count; i++)
        print_hello();

    pr_info("h2: done\n");
    return 0;
}

static void __exit h2_exit(void)
{
    pr_info("h2: unloaded\n");
}

module_init(h2_init);
module_exit(h2_exit);
