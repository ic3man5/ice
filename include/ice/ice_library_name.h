#pragma once

#include <string>

namespace ice {
class LibraryName;

enum LibPrefix
{
    // Never prepend the "lib" prefix
    LibPrefixNone,
    // Always prepend the "lib" prefix
    LibPrefixAlways,
    // Always prepend the "lib" prefix EXCEPT on windows
    LibPrefixNotWindows,
};

enum PathPrefix
{
    // Never prepend the "${ORIGIN}" or "@loader_path" prefix
    PathPrefixNone,
    // Always prepend the "path" prefix
    PathPrefixAlways,
    // Always prepend the "lib" prefix on Linux only
    PathPrefixLinuxOnly,
    // Always prepend the "lib" prefix on Mac only
    PathPrefixMacOnly,
};
};

class ice::LibraryName
{
    std::string m_name = "";
    LibPrefix m_lib_prefix = LibPrefixNotWindows;
    PathPrefix m_path_prefix = PathPrefixAlways;

    std::string m_extension;
    bool m_use_extension = true;

  public:
    LibraryName(std::string name);
    LibraryName(LibraryName&) = delete;
    ~LibraryName();
    std::string name() const;

    // Adds the "lib" prefix to the library name for dlopen/LoadLibrary calls
    LibraryName& setLibPrefix(LibPrefix lib_prefix);
    const LibPrefix getLibPrefix() const;

    // Prepends "${ORIGIN}/" or "@loader_path/" prefix
    LibraryName& setPathPrefix(PathPrefix path_prefix);
    const PathPrefix getPathPrefix() const;

    LibraryName& setExtensionEnabled(bool use_extension);
    const bool getExtensionEnabled() const;
    LibraryName& setExtension(const std::string extension);
    LibraryName& setDefaultExtension();
    const std::string getExtension() const;

    const std::string getName() const;
    const std::string build() const;
};
