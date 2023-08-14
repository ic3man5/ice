#pragma once

#if (defined(_WIN32) || defined(__WIN32__))
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <dlfcn.h>
#define HMODULE void *
#endif

#include <string>

namespace ice {
class Library;
};

class ice::Library {
    HMODULE m_lib;
    std::string m_name;

public:
    Library(std::string name);
    Library(Library&) = delete;
    ~Library();
    bool isLoaded() const;
    std::string name() const { return m_name; }

    std::string getPath(bool *okay = NULL);

    HMODULE const &_library() const;
};
