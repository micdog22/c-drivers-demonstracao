
#pragma once
#include <ntddk.h>
#include <wdf.h>

// Device interface GUID: 2034ad32-e06f-42f7-a85b-e9b6bdc6fc6b
DEFINE_GUID(GUID_DEVINTERFACE_RANDOMDRV,
    0x2034ad32, 0xe06f, 0x42f7,
    0xa8, 0x5b, 0xe9, 0xb6, 0xbd, 0xc6, 0xfc, 0x6b);

// IOCTL base
#define RANDOMDRV_DEVICE  0x892B

#define IOCTL_RANDOMDRV_BASE  0x800

#define IOCTL_RANDOM_FILL CTL_CODE(RANDOMDRV_DEVICE, IOCTL_RANDOMDRV_BASE + 1, METHOD_BUFFERED, FILE_ANY_ACCESS)
