# qwave for Unreal Build Accelerator in Windows Server Core containers

This builds a `qwave.dll` file that you can add to the System32 directory of `servercore:ltsc2022` container and have the Unreal Build Accelerator agent work in it. Without this file, `UbaAgent` will exit with a non-zero exit code because `qwave.dll` is missing; it only being present in client/desktop versions of Windows.
