#include <cstdio>

template <class T>
void dumpobject(T const* t) {
    unsigned char const* p = reinterpret_cast<unsigned char const*>(t);
    for (size_t n = 0; n < sizeof(T); ++n)
        printf("%02d ", p[n]);
    printf("\n");
}
