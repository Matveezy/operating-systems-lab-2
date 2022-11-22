#include "../ioctl/ioctl_cmd.h"

void print_info_pci_dev_k(my_pci_dev_struct *my_device){
    printk("Device devfn fields is : %u\n" , my_device->devfn);
    printk("Device vendor fields is : %hu\n" , my_device->vendor);
    printk("Device deivce fields is : %hu\n" , my_device->device);
    printk("Device class fields is : %u\n" , my_device->class);
}

void print_info_socket_k(my_socket_struct *my_sock){
    printk("Socket type is : %hx\n" , my_sock->type);
    printk("Socket flags is : %lu\n" , my_sock->flags);
}