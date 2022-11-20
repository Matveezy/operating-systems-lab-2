#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/kernel.h>
#include <linux/net.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/slab.h>

#include "./ioctl/ioctl_cmd.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Matvey Chukhno");
MODULE_DESCRIPTION("My kernel module.");
MODULE_VERSION("0.01");

#define MYMAJOR 17

void print_info_pci_dev_k(my_pci_dev_struct *);

my_pci_dev_struct my_device = {0};
static struct socket *sock = NULL;
static my_socket_struct my_sock;
int err;

static long int my_ioctl(struct file *file, unsigned cmd, unsigned long arg) {
    pci_dev_params user_params;
    static struct pci_dev *device = NULL;
    int32_t sockfd;
    size_t pci_dev_driver_name_length;
    data_transfer dt;
    switch (cmd) {
        case PCI_DEV_W_PARAMS:
            if (copy_from_user(&user_params, (pci_dev_params *) arg, sizeof(pci_dev_params))) {
                printk("ioctl - PCI_DEV_W_PARAMS error!\n");
            }
            device = pci_get_device(user_params.vendor_id, user_params.device_id, NULL);
            if (NULL == device) {
                my_device.ioctl_state = ERROR;
                printk(KERN_INFO
                "Pci device is not found!\n");
            } else {
                printk(KERN_INFO
                "Pci device found!\n");
                my_device.ioctl_state = EXCELLENT;
                my_device.devfn = device->devfn;
                my_device.vendor = device->vendor;
                my_device.device = device->device;
                my_device.class = device->class;
                print_info_pci_dev_k(&my_device);
            }
            break;
        case SOCKET_FD_W_VALUE:
            if (copy_from_user(&sockfd, (int32_t *) arg, sizeof(sockfd))) {
                printk("ioctl - SOCKET_FD_W_VALUE error!\n");
            } else {
                printk("ioctl - socket file descriptor %d\n", sockfd);
                sock = sockfd_lookup(sockfd, &err);
                if (NULL == sock) {
                    my_sock.ioctl_state = ERROR;
                    printk(KERN_INFO
                    "Socket is not found!\n");
                } else {
                    printk("Socket is found!\n");
                    my_sock.ioctl_state = EXCELLENT;
                    my_sock.type = sock->type;
                    my_sock.flags = sock->flags;
                    printk("Socket type is : %hx\n", sock->type);
                    printk("Socket flags is : %lu\n", sock->flags);
                }
            }
            break;
        case PCI_DEV_R_STR_LENGTH:
            pci_dev_driver_name_length = strlen(device->driver->name);
            if (copy_to_user((size_t *) arg, &pci_dev_driver_name_length, sizeof(size_t))) {
                printk("ioctl - PCI_DEV_R_STR_LENGTH error!\n");
            } else {
                printk("ioctl - Pci driver length is %ld. Send to user space\n", pci_dev_driver_name_length);
            }
            break;
        case PCI_DEV_R_DRIVER_NAME:
            if (copy_from_user(&dt, (data_transfer *) arg, sizeof(data_transfer))) {
                printk(" ioctl - PCI_DEV_R_DRIVER_NAME data_transfer read from user error!\n");
            }
            if (copy_to_user(dt.buffer, device->driver->name, strlen(device->driver->name) + 1)) {
                printk("oictl - PCI_DEV_R_DRIVER_NAME data_transfer write to user error!\n");
            }
            break;
        case SOCKET_R_VALUE:
            if (copy_to_user((my_socket_struct *) arg, &my_sock, sizeof(my_socket_struct))) {
                printk("ioctl - SOCKET_R_VALUE error!\n");
            } else
                printk("ioctl - The socket_r_value command called!\n");
            break;
        case PCI_DEV_R_VALUE:
            if (copy_to_user((my_pci_dev_struct *) arg, &my_device, sizeof(my_pci_dev_struct))) {
                printk("ioctl - PCI_DEV_R_VALUE error!\n");
            }
            break;
    }
    return 0;
}

static int driver_open(struct inode *device_file, struct file *instance) {
    printk("dev_num - open was called\n");
    return 0;
}

static int driver_close(struct inode *device_file, struct file *instance) {
    printk("dev_num - close was called\n");
    return 0;
}

static struct file_operations fops = {
        .owner = THIS_MODULE,
        .open = driver_open,
        .release = driver_close,
        .unlocked_ioctl = my_ioctl
};

static int __init mod_init(void) {
    /* register device number */
    int retval;
    retval = register_chrdev(MYMAJOR, "matthew_driver", &fops);
    if (0 == retval) {
        printk("matthew_driver device number Major:%d , Minor:%d\n", MYMAJOR, 0);
    } else if (retval > 0) {
        printk("matthew_driver device number Major:%d , Minor:%d\n", retval >> 20, retval & 0xffff);
    } else {
        printk("Couldn't register device number!\n");
        return -1;
    }
    return 0;
}

static void __exit mod_exit(void) {
    unregister_chrdev(MYMAJOR, "matthew_driver");
    printk(KERN_INFO
    "Goodbye, World!\n");
}

void print_info_pci_dev_k(my_pci_dev_struct *my_device) {
    printk(KERN_INFO
    "Device devfn fields is : %u\n", my_device->devfn);
    printk(KERN_INFO
    "Device vendor fields is : %hu\n", my_device->vendor);
    printk(KERN_INFO
    "Device deivce fields is : %hu\n", my_device->device);
    printk(KERN_INFO
    "Device class fields is : %u\n", my_device->class);
}

module_init(mod_init);
module_exit(mod_exit);
