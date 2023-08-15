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
    HMODULE m_lib = nullptr;
    std::string m_name;
    bool m_nothrow = false;
    bool m_has_error = true;
    std::string m_last_error;

public:
    Library(std::string name);
    Library(std::string name, bool nothrow);
    Library(Library&) = delete;
    ~Library();
    bool isLoaded() const;
    std::string name() const { return m_name; }

    std::string getPath(bool *okay = NULL);
    const bool hasError() const;
    const std::string getLastError() const;

    HMODULE const &_library() const;
};
