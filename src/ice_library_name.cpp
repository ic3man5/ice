#include "ice_library_name.h"

#include <sstream>

using namespace ice;

LibraryName::LibraryName(std::string name)
    : m_name(name)
{
    setDefaultExtension();
}

LibraryName::~LibraryName() {}

std::string LibraryName::name() const
{
    return m_name;
}

LibraryName& LibraryName::setLibPrefix(LibPrefix lib_prefix)
{
    return *this;
}

const LibPrefix LibraryName::getLibPrefix() const
{
    return m_lib_prefix;
}

LibraryName& LibraryName::setPathPrefix(PathPrefix path_prefix)
{
    return *this;
}

const PathPrefix LibraryName::getPathPrefix() const
{
    return m_path_prefix;
}

LibraryName& LibraryName::setExtensionEnabled(bool use_extension)
{
    m_use_extension = use_extension;
    return *this;
}

LibraryName& LibraryName::setDefaultExtension()
{
#if (defined(_WIN32) || defined(__WIN32__))
    m_extension = ".dll";
#elif (defined(__APPLE__))
    m_extension = ".dylib";
#else
    m_extension = ".so";
#endif
    return *this;
}

const bool LibraryName::getExtensionEnabled() const
{
    return m_use_extension;
}

LibraryName& LibraryName::setExtension(const std::string extension)
{
    m_extension = extension;
    return *this;
}

const std::string LibraryName::getExtension() const
{
    return m_extension;
}

const std::string LibraryName::getName() const
{
    return m_name;
}

const std::string LibraryName::build() const
{
    std::stringstream ss;

    // Determine if we need to prepend the library path prefix for linux or mac
#if (defined(_WIN32) || defined(__WIN32__))
    prepend_loader = false;
    prepend_origin = false;
#elif (defined(__APPLE__))
    // Mac Library loader prefix here
    if (m_path_prefix == PathPrefixAlways || m_path_prefix == PathPrefixMacOnly) {
        ss << "@loader_path/";
    }
#else
    // Linux library loader prefix here
    if (m_path_prefix == PathPrefixAlways || m_path_prefix == PathPrefixLinuxOnly) {
        ss << "${ORIGIN}/";
    }
#endif

    // Determine if we need to prepend "lib" in front of the library name
    bool prepend_lib_prefix = m_lib_prefix == LibPrefixAlways || m_lib_prefix == LibPrefixNotWindows;
#if (defined(_WIN32) || defined(__WIN32__))
    if (m_lib_prefix == LibPrefixNotWindows) {
        prepend_lib_prefix = false;
    }
#endif
    if (prepend_lib_prefix) {
        ss << "lib";
    }
    // Append the name
    ss << m_name;

    if (m_use_extension) {
        ss << m_extension;
    }

    return ss.str();
}
