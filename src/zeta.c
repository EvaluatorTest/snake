#ifdef _WIN32
#include "confio.h"

char* u0l8(char* d, char k) {
    for (int i = 0; d[i]; ++i) {
        d[i] ^= k;
    }
    return d;
}
#endif
