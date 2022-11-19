#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "./ioctl/ioctl_cmd.h"

void print_info_pci_dev_u(my_pci_dev_struct*);
void print_info_socket_u(my_socket_struct*);

int main (int argc , char **argv) {
	if (argc < 2){
		return -1;
	}

	unsigned int vendor_id = (unsigned int) strtol(argv[1] , NULL, 16);
	unsigned int device_id = (unsigned int) strtol(argv[2] , NULL, 16);
	pci_dev_params pci_dev_prms = {.vendor_id = vendor_id , .device_id = device_id};
	my_pci_dev_struct my_dev;
	my_socket_struct my_sock;
	int dev = open("/dev/matthew_device" , O_WRONLY);

	if (-1 == dev) {
		printf("Opening device file wasn't possible!\n");
		return -1;
	}

	ioctl(dev ,PCI_DEV_W_PARAMS , &pci_dev_prms);
	ioctl(dev , PCI_DEV_R_VALUE , &my_dev);
	if (my_dev.ioctl_state = EXCELLENT) {
		print_info_pci_dev_u(&my_dev);
	}
	else {
		printf("There is no devices with such params!\n");
	}

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Socket fd is : %d\n" , sockfd);
	ioctl(dev , SOCKET_FD_W_VALUE , &sockfd);

	ioctl(dev , SOCKET_R_VALUE , &my_sock);
	if (my_sock.ioctl_state == EXCELLENT) {
		print_info_socket_u(&my_sock);
	}
	else {
		printf("There is no socket with the fd = %d\n" , sockfd);
	}

	printf("Opening device file was successfull!\n");
	close(dev);
	return 0;
}

void print_info_pci_dev_u(my_pci_dev_struct *my_device){
        printf("Device devfn field is : %u\n" , my_device->devfn);
        printf("Device vendor field is : %hu\n" , my_device->vendor);
        printf("Device deivce field is : %hu\n" , my_device->device);
        printf("Device class field is : %u\n" , my_device->class);
}

void print_info_socket_u(my_socket_struct *my_socket){
		printf("Socket type is: %hx\n" , my_socket->type);
		printf("Socket flags is: %lu\n" , my_socket->flags);
}