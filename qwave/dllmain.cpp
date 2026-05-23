#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <WinSock2.h>

#if defined(__cplusplus)
#define ExternC extern "C"
#else
#define ExternC
#endif

typedef enum _QOS_TRAFFIC_TYPE
{
    QOSTrafficTypeBestEffort = 0,
    QOSTrafficTypeBackground = 1,
    QOSTrafficTypeExcellentEffort = 2,
    QOSTrafficTypeAudioVideo = 3,
    QOSTrafficTypeVoice = 4,
    QOSTrafficTypeControl = 5
} QOS_TRAFFIC_TYPE, * PQOS_TRAFFIC_TYPE;

ExternC __declspec(dllexport) BOOL WINAPI QOSCreateHandle(
    _In_ void* Version,
    _Out_ PHANDLE QOSHandle)
{
    // We have to provide a valid handle, even if we're not going to use it.
    *QOSHandle = (HANDLE)0x8000;
    return TRUE;
}

ExternC __declspec(dllexport) BOOL WINAPI QOSAddSocketToFlow(
    _In_ HANDLE QOSHandle,
    _In_ SOCKET Socket,
    _In_opt_ PSOCKADDR DestAddr,
    _In_ QOS_TRAFFIC_TYPE TrafficType,
    _In_opt_ DWORD Flags,
    _Inout_ ULONG* FlowId)
{
    // This operation only succeeds for handles that we made with QOSCreateHandle.
    return (QOSHandle == (HANDLE)0x8000);
}

BOOL WINAPI _DllMainCRTStartup(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    return(TRUE);
}