
#include <ntddk.h>
#include <wdf.h>
#include "RandomDrv.h"

NTSTATUS
RandomDrv_EvtDeviceAdd(
    _In_ WDFDRIVER Driver,
    _Inout_ PWDFDEVICE_INIT DeviceInit
    )
{
    UNREFERENCED_PARAMETER(Driver);

    WdfDeviceInitSetIoType(DeviceInit, WdfDeviceIoBuffered);

    WDF_OBJECT_ATTRIBUTES attributes;
    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&attributes, DEVICE_CONTEXT);

    WDFDEVICE device;
    NTSTATUS status = WdfDeviceCreate(&DeviceInit, &attributes, &device);
    if (!NT_SUCCESS(status)) return status;

    // Create device interface
    status = WdfDeviceCreateDeviceInterface(device, &GUID_DEVINTERFACE_RANDOMDRV, NULL);
    if (!NT_SUCCESS(status)) return status;

    // Init context (seed)
    PDEVICE_CONTEXT ctx = GetDeviceContext(device);
    ctx->Seed = 0x12345678;

    // Default queue
    WDF_IO_QUEUE_CONFIG qcfg;
    WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&qcfg, WdfIoQueueDispatchSequential);
    qcfg.EvtIoDeviceControl = RandomDrv_EvtIoDeviceControl;
    qcfg.EvtIoRead = RandomDrv_EvtIoRead;
    qcfg.EvtIoWrite = RandomDrv_EvtIoWrite;

    WDFQUEUE queue;
    status = WdfIoQueueCreate(device, &qcfg, WDF_NO_OBJECT_ATTRIBUTES, &queue);
    return status;
}

VOID RandomDrv_EvtDeviceCleanup(_In_ WDFOBJECT DeviceObject)
{
    UNREFERENCED_PARAMETER(DeviceObject);
}
