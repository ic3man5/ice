#include "ice_library.h"
#include "ice_exception.h"
#include <sstream>

#if defined(__linux__)
#include <linux/limits.h>
#include <link.h>
#endif

using namespace ice;

Library::Library(std::string name)
    : Library(name, false)
{
}

Library::Library(std::string name, bool nothrow)
{
    m_name = name;
    m_nothrow = nothrow;
    m_has_error = false;
#if (defined(_WIN32) || defined(__WIN32__))
#ifdef UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, name.c_str(), -1, NULL, 0);
    if (len) {
        wchar_t* n = new wchar_t[len];
        MultiByteToWideChar(CP_UTF8, 0, name.c_str(), -1, n, len);
        m_lib = LoadLibrary(n);
        delete[] n;
    } else
        m_lib = NULL;
#else
    m_lib = LoadLibrary(name.c_str());
#endif // UNICODE
    if (m_lib == NULL) {
        std::stringstream err;
        DWORD error = GetLastError();
        LPVOID buffer = { 0 };
        err << "Failed to open library: '" << name << "'";
        auto len =
            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                          NULL,
                          error,
                          MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                          (LPTSTR)&buffer,
                          0,
                          NULL);
        if (len) {
            std::string msg;
#if defined(UNICODE)
            msg = (LPSTR)buffer;
            int width = WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)buffer, -1, 0, 0, NULL, NULL);
            char* n = new char[width];
            WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)buffer, -1, n, width, NULL, NULL);
            msg = n;
            delete[] n;
            n = nullptr;
#else
            msg = (LPSTR)buffer;
#endif
            err << ": " << msg << " (#" << error << ")";
        } else {
            err << " with error code: #" << error;
        }
        LocalFree(buffer);
        m_last_error = err.str();
        m_has_error = true;
        if (!m_nothrow) {
            throw Exception(err.str());
        }
    }
#else
    m_lib = dlopen(name.c_str(), RTLD_NOW);
    if (m_lib == NULL) {
        std::stringstream err;
        err << "Failed to open library '" << name << "': " << dlerror();
        m_last_error = err.str();
        m_has_error = true;
        if (!m_nothrow) {
            throw Exception(err.str());
        }
    }
#endif
}

Library::~Library()
{
    if (this->isLoaded()) {
#if (defined(_WIN32) || defined(__WIN32__))
        FreeLibrary(m_lib);
#else
        dlclose(m_lib);
#endif
    }
}

bool Library::isLoaded() const
{
    return m_lib != NULL;
}

std::string Library::getPath(bool* okay)
{
    if (okay)
        *okay = false;
    if (!isLoaded() || m_has_error)
        return m_name;
#if (defined(_WIN32) || defined(__WIN32__))
    TCHAR buffer[MAX_PATH] = { 0 };
    int len = GetModuleFileName(m_lib, buffer, MAX_PATH);
    if (!len) {
        DWORD error = GetLastError();
        std::stringstream err;
        err << "Failed to get Library path: '" << m_name << "' with error code: #" << error;
        m_last_error = err.str();
        m_has_error = true;
        if (!m_nothrow) {
            throw Exception(err.str());
            return m_name;
        }
    }
#ifdef UNICODE
    int length = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, NULL, 0, NULL, NULL);
    if (length) {
        char* temp = new char[MAX_PATH];
        WideCharToMultiByte(CP_UTF8, 0, buffer, -1, temp, length, NULL, NULL);
        std::stringstream ss;
        ss << temp;
        if (okay)
            *okay = true;
        delete[] temp;
        temp = NULL;
        return ss.str();
    }
#else
    std::stringstream ss;
    ss << buffer;
    if (okay)
        *okay = true;
    return ss.str();
#endif // UNICODE
#elif defined(__APPLE__)
    // Apple doesn't support RTLD_DI_LINKMAP
    if (okay)
        *okay = true;
    // Strip @loader_path from the path
    std::string loader = "@loader_path/";
    std::string new_name = m_name;
    auto pos = new_name.find(loader);
    if (pos != std::string::npos) {
        return new_name.replace(pos, loader.length(), "");
    } else {
        return new_name;
    }
#else
    link_map* lm;
    char path[PATH_MAX + 1] = {};
    bool success = dlinfo(m_lib, RTLD_DI_LINKMAP, &lm) != -1;
    if (okay) {
        *okay = success;
    }
    if (!success) {
        std::string origin = "${ORIGIN}/";
        std::string new_name = m_name;
        auto pos = new_name.find(origin);
        if (pos != std::string::npos) {
            new_name.replace(pos, origin.length(), "");
        }
        return new_name;
    }
    return lm->l_name;
#endif // WIN32
    return m_name;
}

const bool Library::hasError() const
{
    return m_has_error;
}

const std::string Library::getLastError() const
{
    return m_last_error;
}

HMODULE const& Library::_library() const
{
    return m_lib;
}
