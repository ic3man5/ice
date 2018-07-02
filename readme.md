# ice Library
This is a very simple class to make dynamic library loads simple and easy. This code should multi-platform. The library gets automatically cleaned up and ice::Exception is thrown when an error occurs.

### Example Code
```
#include "ice.h"

try
{
    ice::Library lib("foo");
    ice::Function<int (int, int)> func(&lib, "foofunc");
    int i = func(2, 5);
}
catch (ice::Exception& ex)
{
    // ex.whatString() will look similar to this:
    // Failed to Retrieve address of function 'foofunc': Windows Error #0 for 'foo'
}

// lib and func auto clean up when they go out of scope

```

Using Library Manager:

```
#include "ice.h"

try
{
    std::cout << "Testing LibraryManager...\n\n";
    ice::LibraryManager& mgr = ice::LibraryManager::getLibraryManager();
    mgr.add("iesetup", "iesetup.dll");
    mgr.add("iertutil", "iertutil.dll");
    mgr.add("ieapfltr", "ieapfltr.dll");
    mgr.add("iedkcs32", "iedkcs32.dll");
    mgr.add("iesetup4", "iesetup.dll");
    mgr.add("iesetup5", "iesetup.dll");
    mgr.add("iesetup6", "iesetup.dll");
    mgr.add("iesetup7", "iesetup.dll");
    mgr.add("iesetup8", "iesetup.dll");
    mgr.add("iesetup9", "iesetup.dll");
    std::cout << "Path: " << mgr["iesetup"].getPath() << "\n";
    
    std::vector<std::string> names = mgr.getLibraryNames();
    for (int i=0; i < names.size(); ++i)
        std::cout << "Loaded Library #" << i+1 << ": " << names.at(i) << "\n\t"
            << mgr[names.at(i)].name() << ":\t" << mgr[names.at(i)].getPath() << "\n\n";
            
    mgr["nope"].getPath();
}
catch (ice::Exception& ex)
{
    std::cout << ex.what() << "\n";
    return 1;
}

// lib and func auto clean up when they go out of scope



// Output:
Testing LibraryManager...

Path: C:\Windows\system32\iesetup.dll
Loaded Library #1: ieapfltr
       ieapfltr.dll:   C:\Windows\system32\ieapfltr.dll

Loaded Library #2: iedkcs32
       iedkcs32.dll:   C:\Windows\system32\iedkcs32.dll

Loaded Library #3: iertutil
       iertutil.dll:   C:\Windows\syswow64\iertutil.dll

Loaded Library #4: iesetup
       iesetup.dll:    C:\Windows\system32\iesetup.dll

Loaded Library #5: iesetup4
       iesetup.dll:    C:\Windows\system32\iesetup.dll

Loaded Library #6: iesetup5
       iesetup.dll:    C:\Windows\system32\iesetup.dll

Loaded Library #7: iesetup6
       iesetup.dll:    C:\Windows\system32\iesetup.dll

Loaded Library #8: iesetup7
       iesetup.dll:    C:\Windows\system32\iesetup.dll

Loaded Library #9: iesetup8
       iesetup.dll:    C:\Windows\system32\iesetup.dll

Loaded Library #10: iesetup9
       iesetup.dll:    C:\Windows\system32\iesetup.dll

LibraryManager Failed to retreive 'nope' From loaded library list!

```

### License
The MIT License (MIT)

Copyright (c) <2015> <David Rebbe>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
