#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/sched.h>

int pid = 0; 
module_param(pid, int, 0);
static void __exit kk(void) {
    printk("Hello!!");
}
static int __init hh(void) {
    struct task_struct *t= pid_task(find_vpid(pid), PIDTYPE_PID);
    if (t == NULL) {
        printk(KERN_ERR "Invalid PID\n");
        return -EINVAL;
    }
    printk("pid %d\n", t->pid);
    printk("Process Group ID %d\n", t->group_leader->pid);
    printk("User Id %d\n", t->cred->uid.val);
    printk("Command Path %s\n", t->comm);
    return 0;
}



module_init(hh);
module_exit(kk);
MODULE_LICENSE("GPL");