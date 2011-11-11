/**
 * Ice multiplatform dynamic library loader.
 *
 * @copyright 2011 David Rebbe
 */

#include "ice_library.h"
#include "ice_exception.h"
#include <sstream>

using namespace ice;

Library::Library(std::string name)
{
	#if (defined(_WIN32) || defined(__WIN32__))
		m_lib = LoadLibrary(name.c_str());
		if (m_lib == NULL)
		{
			DWORD error = GetLastError();
			std::stringstream err;
			err << "Failed to open library: '" << name << 
				"' with error code: #" << error;
			throw Exception(err.str());
		}
	#else
		m_lib = dlopen(name.c_str(), RTLD_NOW);
		if (m_lib == NULL)
		{
			std::stringstream err;
			err << "Failed to open library '" << name <<
				"': " << dlerror();
			throw Exception(err.str());
		}
	#endif
}

Library::~Library()
{
	if (this->isLoaded())
	{
		#if (defined(_WIN32) || defined(__WIN32__))
			FreeLibrary(m_lib);
		#else
			dlclose(m_lib);
		#endif
	}
}

bool Library::isLoaded() const throw()
{
	return m_lib != NULL;
}

HMODULE const& Library::_library() const throw()
{
	return m_lib;
}
