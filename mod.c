#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Matvey Chukhno");
MODULE_DESCRIPTION("Pci dev module.");
MODULE_VERSION("0.01");

#define MYMAJOR 17

static int driver_open(struct inode *device_file , struct file *inctance){
    printk("dev_num - open was called\n");
    return 0;
}

static int driver_close(struct inode *device_file , struct file *inctance){
    printk("dev_num - close was called\n");
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close
};

static int __init mod_init(void) {
    /* register device number */
    int retval;
    retval = register_chrdev(MYMAJOR , "matthew_driver" , &fops);
    if (0 == retval) {
        printk("matthew_driver device number Major:%d , Minor:%d\n" , MYMAJOR , 0);
    }
    else if (retval >0 ){
        printk("matthew_driver device number Major:%d , Minor:%d\n" , retval>>20 , retval&0xffff);
    }
    else {
        printk("Couldn't register device number!\n");
        return -1;
    }
     return 0;
}

static void __exit mod_exit(void) {
    unregister_chrdev(MYMAJOR , "matthew_driver");
    printk(KERN_INFO "Goodbye, World!\n");
}

module_init(mod_init);
module_exit(mod_exit);
