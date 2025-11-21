#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_AUTHOR("Shostak");
MODULE_DESCRIPTION("hello module 1");
MODULE_LICENSE("Dual BSD/GPL");

struct h_entry {
    struct list_head node;
    ktime_t t_start;
    ktime_t t_end;
};

static LIST_HEAD(h_list);

void print_hello(void)
{
    struct h_entry *e = kmalloc(sizeof(*e), GFP_KERNEL);
    if (!e) {
        pr_err("h1: no mem\n");
        return;
    }

    e->t_start = ktime_get();
    pr_info("h1: hello\n");
    e->t_end = ktime_get();

    list_add_tail(&e->node, &h_list);
}
EXPORT_SYMBOL(print_hello);

static int __init h1_init(void)
{
    pr_info("h1: loaded\n");
    return 0;
}

static void __exit h1_exit(void)
{
    struct h_entry *p, *n;

    pr_info("h1: exit, showing times\n");

    list_for_each_entry_safe(p, n, &h_list, node) {
        s64 ns = ktime_to_ns(ktime_sub(p->t_end, p->t_start));
        pr_info("h1: took %lld ns\n", ns);
        list_del(&p->node);
        kfree(p);
    }

    pr_info("h1: bye\n");
}

module_init(h1_init);
module_exit(h1_exit);
