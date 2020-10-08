#if defined(__linux__) || defined(__unix__) || defined(__APPLE__) || defined(__HAIKU__)
#include <unistd.h>
#endif

#if defined(__POX_VERSION) && !defined(__CYGWIN__)
#include <dlfcn.h>
#pragma message "Is poxis -y"
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#include <windows.h>
#endif

#if __has_include(<unistd.h>)
#pragma message "1"
#include <unistd.h>
#endif

#if __has_include(<dlfnc.h>)
#pragma message "2"
#include <dlfcn.h>
#endif

#if __has_include(<windows.h>)
#pragma message "3"
#include <windows.h>
#endif


int main() {}