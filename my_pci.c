#include "./ioctl/ioctl_cmd.h"

void print_info_pci_dev_k(my_pci_dev_struct *my_device){
    printk(KERN_INFO "Device devfn fields is : %u\n" , my_device->devfn);
    printk(KERN_INFO "Device vendor fields is : %hu\n" , my_device->vendor);
    printk(KERN_INFO "Device deivce fields is : %hu\n" , my_device->device);
    printk(KERN_INFO "Device class fields is : %u\n" , my_device->class);
    printk(KERN_INFO "Device name is: %s\n" , my_device->driver_name);
}
