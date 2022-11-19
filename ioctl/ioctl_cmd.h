#ifndef IOCTL_CMD_H
#define IOCTL_CMD_H

#define SOCKET_FD_W_VALUE _IOW('a' , 'a' , int32_t *)
#define SOCKET_R_VALUE _IOR('a' , 'b' , my_socket_struct *)
#define PCI_DEV_W_PARAMS _IOW('a' , 'd' , pci_dev_params *)
#define PCI_DEV_R_VALUE _IOR('a' , 'c' , my_pci_dev_struct *)

typedef enum {
    EXCELLENT = 1,
    ERROR = 0
} ioctl_state;

typedef struct my_socket_struct {
    ioctl_state ioctl_state;
    short type;
    unsigned long flags;
} my_socket_struct;

typedef struct pci_dev_params {
    unsigned int vendor_id;
    unsigned int device_id;
} pci_dev_params;

typedef struct my_pci_dev_struct {
    ioctl_state ioctl_state;
    unsigned int devfn;
    unsigned short vendor;
    unsigned short device;
    unsigned int class;
    const char *driver_name;
} my_pci_dev_struct;

#endif IOCTL_CMD_H