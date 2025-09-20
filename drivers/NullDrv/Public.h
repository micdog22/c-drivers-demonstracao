
#pragma once
#include <ntddk.h>
#include <wdf.h>

// Device interface GUID: 9db0cbcd-c097-4b96-a8d4-aef0988e42df
DEFINE_GUID(GUID_DEVINTERFACE_NULLDRV,
    0x9db0cbcd, 0xc097, 0x4b96,
    0xa8, 0xd4, 0xae, 0xf0, 0x98, 0x8e, 0x42, 0xdf);

// IOCTL base
#define NULLDRV_DEVICE  0x89D3

#define IOCTL_NULLDRV_BASE  0x800

#define IOCTL_NULL_SINK CTL_CODE(NULLDRV_DEVICE, IOCTL_NULLDRV_BASE + 1, METHOD_BUFFERED, FILE_ANY_ACCESS)
