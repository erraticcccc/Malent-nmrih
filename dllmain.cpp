// dllmain.cpp : Defines the entry point for the DLL application.
#include "includes.h"
//addresses that i need to put here
uintptr_t server = (uintptr_t)GetModuleHandle(L"server.dll");
uintptr_t engine = (uintptr_t)GetModuleHandle(L"engine.dll");
uintptr_t client = (uintptr_t)GetModuleHandle(L"client.dll");
uintptr_t playerFOV = (uintptr_t)(client + 0x5647E4);
//hooking funcs
typedef int(__fastcall* AmmoFunction)(int* MagAmmo);
typedef int(__thiscall* VeryLargeFunction)(void* pThis, int* probablyhp, int idk);
//original hook functions
AmmoFunction oAmmoFunc;
//hooks
BYTE ammoFuncBytes[5]{ 0 };
int __fastcall hkAmmoFunction(int* MagAmmo) {
    bool bInfAmmo = 1;
    if (*(float*)playerFOV = 90){
        *(float*)playerFOV = 20;
    }
    if (bInfAmmo) {
        *MagAmmo = *MagAmmo + 1;
    }
    if (GetAsyncKeyState(VK_MBUTTON)){
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 10, 0, 0);
        Sleep(10);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(10);
    }
    return oAmmoFunc(MagAmmo);
}
void __fastcall hkStamina(void* pThis, void* notUsed, int* pointless, float pStamina) {
    if (pStamina != 130.0f) {
        pStamina = 130.0f;
    }
}
/*
int __thiscall hkVeryLargeFunction(int* hp, int idk) {

}
*/


//main thread
DWORD WINAPI HackThread(HMODULE hModule) 
{
    oAmmoFunc = (AmmoFunction)(server + 0x32b190);
    memcpy(ammoFuncBytes, (BYTE*)oAmmoFunc, 5);
    oAmmoFunc = (AmmoFunction)TrampHook32((BYTE*)oAmmoFunc, (BYTE*)hkAmmoFunction, 5);
    
    while (!GetAsyncKeyState(VK_END))
    {
        Sleep(1);
    };

    mem::Patch((BYTE*)oAmmoFunc, ammoFuncBytes, 5);//unhook ammo func
        
    return 0;
}
//dllmain
BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

