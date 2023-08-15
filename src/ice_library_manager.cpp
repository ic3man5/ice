#include "ice_library_manager.h"
#include "ice_exception.h"
#include <sstream>
#include <iostream>

using namespace ice;

LibraryManager::LibraryManager() {}

LibraryManager::~LibraryManager()
{
    Libraries::iterator iter = m_libs.begin();
    for (; iter != m_libs.end(); iter = m_libs.begin())
        this->remove(iter->first);
}

void LibraryManager::add(std::string name, std::string path, bool nothrow, bool replace)
{
    if (replace && exists(name)) {
        remove(name);
        m_libs[name] = new ice::Library(path, nothrow);
    } else if (!exists(name)) {
        m_libs[name] = new ice::Library(path, nothrow);
    }
}

void LibraryManager::remove(std::string name)
{
    if (m_libs.find(name) == m_libs.end()) {
        return;
    }
    ice::Library* lib = m_libs[name];
    delete lib;
    lib = NULL;
    m_libs.erase(name);
}

void LibraryManager::remove(ice::Library& library)
{
    for (auto iter : m_libs) {
        if (library.name().compare(iter.second->name()) == 0) {
            remove(iter.first);
            break;
        }
    }
}

std::vector<std::string> LibraryManager::getLibraryNames() const
{
    std::vector<std::string> names;
    names.reserve(m_libs.size());
    Libraries::const_iterator iter = m_libs.begin();
    for (; iter != m_libs.end(); ++iter)
        names.push_back(iter->first);
    return names;
}

ice::Library* LibraryManager::operator[](std::string name)
{
    if (!exists(name)) {
        std::stringstream ss;
        ss << "LibraryManager Failed to retreive '" << name << "' From loaded library list!";
        throw Exception(ss.str());
    }
    return m_libs[name];
}

LibraryManager& LibraryManager::instance()
{
    static LibraryManager* mSingleton = NULL;
    if (!mSingleton)
        mSingleton = new LibraryManager();
    return *mSingleton;
}

bool LibraryManager::exists(std::string name) const
{
    return m_libs.find(name) != m_libs.end();
}
