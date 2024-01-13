#include <windows.h>

void wTitle(char* title){
    HMODULE kernel32 = LoadLibraryA("C:\\Windows\\System32\\kernel32.dll");
    
    if(kernel32 != NULL){
        FARPROC setWindowTitle = GetProcAddress(kernel32, "SetConsoleTitleA");
        
        if(setWindowTitle != NULL){
            ((void (*)(LPCSTR))setWindowTitle)(title);
        }

        FreeLibrary(kernel32);
    }

}