#pragma once

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")

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

// from https://yal.cc/printf-without-standard-library/
void nolib_printf(const char* pszFormat, ...) {
    char buf[1024];
    va_list argList;
    va_start(argList, pszFormat);
    wvsprintfA(buf, pszFormat, argList);
    va_end(argList);
    DWORD done;
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buf, strlen(buf), &done, NULL);
}

ExternC __declspec(dllexport) BOOL WINAPI QOSCreateHandle(
    _In_ void* Version,
    _Out_ PHANDLE QOSHandle)
{
    // We have to provide a valid handle, even if we're not going to use it.
    nolib_printf("qwave QOSCreateHandle\n");
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
    nolib_printf("qwave QOSAddSocketToFlow %p\n", QOSHandle);
    return (QOSHandle == (HANDLE)0x8000);
}

BOOL WINAPI _DllMainCRTStartup(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    nolib_printf("qwave DllMainCRTStartup\n");
    return(TRUE);
}

#if 0

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        printf("qwave DLL_PROCESS_ATTACH\n");
        break;
    case DLL_THREAD_ATTACH:
        printf("qwave DLL_THREAD_ATTACH\n");
        break;
    case DLL_THREAD_DETACH:
        printf("qwave DLL_THREAD_DETACH\n");
        break;
    case DLL_PROCESS_DETACH:
        printf("qwave DLL_PROCESS_DETACH\n");
        break;
    }
    return TRUE;
}

#endif