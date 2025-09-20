
#pragma once
#include <ntddk.h>
#include <wdf.h>

// Device interface GUID: 401c6c3b-923d-4530-92f0-9abf9dd4ce12
DEFINE_GUID(GUID_DEVINTERFACE_ECHODRV,
    0x401c6c3b, 0x923d, 0x4530,
    0x92, 0xf0, 0x9a, 0xbf, 0x9d, 0xd4, 0xce, 0x12);

// IOCTL base
#define ECHODRV_DEVICE  0x8741

#define IOCTL_ECHODRV_BASE  0x800

#define IOCTL_ECHO CTL_CODE(ECHODRV_DEVICE, IOCTL_ECHODRV_BASE + 1, METHOD_BUFFERED, FILE_ANY_ACCESS)
