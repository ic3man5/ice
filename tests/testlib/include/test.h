#include <stdint.h>
#include <stdbool.h>

extern "C" {
    struct Hello {
        char buffer[32];
        bool is_hello;
    };

    const char* hello(void);

    // Structure needs to be cleaned up with free after use or is considered a memory leak.
    const struct Hello* hello_advanced(void);
}