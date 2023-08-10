#include "test.h"
#include <stdlib.h>
#include <string.h>

static const char* HELLO_STR = "Hello World!";

const char* hello(void)
{
    return HELLO_STR;
}

const struct Hello* hello_advanced(void)
{
    Hello* hello = (Hello*)malloc(sizeof(Hello));
    memset((void*)hello, 0, sizeof(hello));
    strcpy(hello->buffer, HELLO_STR);
    hello->is_hello = true;
    return hello;
}