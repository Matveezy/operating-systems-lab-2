#include "../ioctl/ioctl_cmd.h"
#include <stdio.h>

void print_info_pci_dev_u(my_pci_dev_struct *my_device){
		printf("Device driver name is : %s\n" , my_device->driver_name);
        printf("Device devfn field is : %u\n" , my_device->devfn);
        printf("Device vendor field is : %hu\n" , my_device->vendor);
        printf("Device deivce field is : %hu\n" , my_device->device);
        printf("Device class field is : %x\n" , my_device->class);
}

void print_info_socket_u(my_socket_struct *my_socket){
		printf("Socket type is: %hx\n" , my_socket->type);
		printf("Socket flags is: %lu\n" , my_socket->flags);
}