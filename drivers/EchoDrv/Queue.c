
#include <ntddk.h>
#include <wdf.h>
#include "EchoDrv.h"

VOID EchoDrv_EvtIoDeviceControl(
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
        case IOCTL_ECHO:
        {
            PVOID inBuf = NULL, outBuf = NULL;
            size_t inLen = 0, outLen = 0;
            status = WdfRequestRetrieveInputBuffer(Request, 1, &inBuf, &inLen);
            if (!NT_SUCCESS(status)) break;
            status = WdfRequestRetrieveOutputBuffer(Request, 1, &outBuf, &outLen);
            if (!NT_SUCCESS(status)) break;
            size_t toCopy = (inLen < outLen) ? inLen : outLen;
            RtlCopyMemory(outBuf, inBuf, toCopy);
            bytes = (ULONG)toCopy;
            status = STATUS_SUCCESS;
            break;
        }
        default: status = STATUS_INVALID_DEVICE_REQUEST; break;
    }


    WdfRequestCompleteWithInformation(Request, status, bytes);
}

VOID EchoDrv_EvtIoRead(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t Length)
{
    UNREFERENCED_PARAMETER(Queue);
    // Não implementado: complete sem dados
    WdfRequestCompleteWithInformation(Request, STATUS_NOT_SUPPORTED, 0);
}

VOID EchoDrv_EvtIoWrite(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t Length)
{
    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(Length);
    // Não implementado: aceitar e descartar
    WdfRequestCompleteWithInformation(Request, STATUS_SUCCESS, 0);
}
