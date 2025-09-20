
#include <ntddk.h>
#include <wdf.h>
#include "NullDrv.h"

VOID NullDrv_EvtIoDeviceControl(
    _In_ WDFQUEUE Queue,
    _In_ WDFREQUEST Request,
    _In_ size_t OutputBufferLength,
    _In_ size_t InputBufferLength,
    _In_ ULONG IoControlCode
)
{
    UNREFERENCED_PARAMETER(OutputBufferLength);
    UNREFERENCED_PARAMETER(InputBufferLength);

    NTSTATUS status = STATUS_SUCCESS;
    ULONG bytes = 0;


    switch (IoControlCode)
    {
        case IOCTL_NULL_SINK:
        {
            // apenas consome entrada
            PVOID inBuf = NULL; size_t inLen = 0;
            (void)WdfRequestRetrieveInputBuffer(Request, 0, &inBuf, &inLen);
            status = STATUS_SUCCESS;
            bytes = 0;
            break;
        }
        default: status = STATUS_INVALID_DEVICE_REQUEST; break;
    }


    WdfRequestCompleteWithInformation(Request, status, bytes);
}

VOID NullDrv_EvtIoRead(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t Length)
{
    UNREFERENCED_PARAMETER(Queue);
    // Não implementado: complete sem dados
    WdfRequestCompleteWithInformation(Request, STATUS_NOT_SUPPORTED, 0);
}

VOID NullDrv_EvtIoWrite(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t Length)
{
    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(Length);
    // Não implementado: aceitar e descartar
    WdfRequestCompleteWithInformation(Request, STATUS_SUCCESS, 0);
}
