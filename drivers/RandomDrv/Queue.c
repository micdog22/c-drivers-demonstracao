
#include <ntddk.h>
#include <wdf.h>
#include "RandomDrv.h"

VOID RandomDrv_EvtIoDeviceControl(
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
        case IOCTL_RANDOM_FILL:
        {
            PVOID outBuf = NULL;
            size_t outLen = 0;
            status = WdfRequestRetrieveOutputBuffer(Request, 1, &outBuf, &outLen);
            if (!NT_SUCCESS(status)) break;
            PDEVICE_CONTEXT ctx = GetDeviceContext(WdfIoQueueGetDevice(Queue));
            ULONG seed = ctx->Seed;
            PUCHAR p = (PUCHAR)outBuf;
            for (size_t i=0;i<outLen;i++)
            {
                seed = 1664525 * seed + 1013904223; // LCG
                p[i] = (UCHAR)(seed >> 24);
            }
            ctx->Seed = seed;
            bytes = (ULONG)outLen;
            status = STATUS_SUCCESS;
            break;
        }
        default: status = STATUS_INVALID_DEVICE_REQUEST; break;
    }


    WdfRequestCompleteWithInformation(Request, status, bytes);
}

VOID RandomDrv_EvtIoRead(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t Length)
{
    UNREFERENCED_PARAMETER(Queue);
    // Não implementado: complete sem dados
    WdfRequestCompleteWithInformation(Request, STATUS_NOT_SUPPORTED, 0);
}

VOID RandomDrv_EvtIoWrite(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t Length)
{
    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(Length);
    // Não implementado: aceitar e descartar
    WdfRequestCompleteWithInformation(Request, STATUS_SUCCESS, 0);
}
