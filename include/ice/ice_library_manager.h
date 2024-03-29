#pragma once

#include "ice_library.h"
#include <map>
#include <string>
#include <vector>

namespace ice {
class LibraryManager;
};

class ice::LibraryManager {
public:
    LibraryManager();
    LibraryManager(LibraryManager&) = delete;
    ~LibraryManager();

    void add(std::string name, std::string path, bool nothrow, bool replace = false);
    void remove(std::string name);
    void remove(ice::Library &library);

    std::vector<std::string> getLibraryNames() const;

    ice::Library *operator[](std::string name);
    ice::Library *get(std::string name) { return m_libs[name]; }

    static LibraryManager &instance();

    bool exists(std::string name) const;

private:
    typedef std::map<std::string, ice::Library *> Libraries;
    Libraries m_libs;
};
