#include <ice/ice.h>
#include <catch2/catch_all.hpp>
#include <string>

TEST_CASE("LibraryNameBasic", "[library_name]") {
    auto library_name = ice::LibraryName("simple_test");
    REQUIRE( library_name.getName() == "simple_test" );

    const std::string name = library_name.build();    
#if (defined(_WIN32) || defined(__WIN32__))
    REQUIRE( lib_name == "simple_test.dll");
#elif (defined(__APPLE__))
    REQUIRE( lib_name == "@loader_path/libsimple_test.dylib");
#else
    REQUIRE( name == "${ORIGIN}/libsimple_test.so");
#endif


    auto library = ice::Library(name);

    REQUIRE( library.isLoaded() == true );
    REQUIRE( library.name() == name );

    bool path_okay = false;
    auto path = library.getPath(&path_okay);
    INFO("Library Path: " << path);
    REQUIRE( path_okay == true );
    REQUIRE( path.find("simple_test") != std::string::npos );

    REQUIRE( library._library() != NULL );

}
