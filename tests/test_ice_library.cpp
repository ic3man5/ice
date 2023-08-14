#include <ice/ice.h>
#include <catch2/catch_all.hpp>
#include <string>
#include <sstream>

constexpr char LIBRARY_NAME[] = "simple_test";

const ice::LibraryName& getLibraryName() {
    static auto library_name = ice::LibraryName(LIBRARY_NAME);
    return library_name;
}

TEST_CASE("ExceptionBasic", "[exception]") {    
    auto msg = std::string("This is a test exception");
    auto ex = ice::Exception(msg);

    REQUIRE( ex.whatString().compare(ex.what()) == 0 );
    REQUIRE( ex.whatString().compare(msg) == 0 );

    CHECK_NOTHROW( ex.what() );
    CHECK_NOTHROW( ex.whatString() );
}

TEST_CASE("LibraryNameBasic", "[library_name]")
{
    const auto& library_name = getLibraryName();
    REQUIRE(library_name.getName() == LIBRARY_NAME);

    const std::string name = library_name.build();
    std::stringstream ss;
#if (defined(_WIN32) || defined(__WIN32__))
    ss << LIBRARY_NAME << ".dll";
#elif (defined(__APPLE__))
    ss << "@loader_path/lib" << LIBRARY_NAME << ".dylib";
#else
    ss << "${ORIGIN}/lib" << LIBRARY_NAME << ".so";
#endif
    REQUIRE(ss.str().compare(name) == 0 );
}

TEST_CASE("LibraryBasic", "[library]") {
    auto& name = getLibraryName().build();
    auto library = ice::Library(name);

    REQUIRE( library.isLoaded() == true );
    REQUIRE( library.name() == name );

    bool path_okay = false;
    auto path = library.getPath(&path_okay);
    INFO("Library Path: " << path);
    REQUIRE( path_okay == true );
    REQUIRE( path.find("simple_test") != std::string::npos );

    REQUIRE( library._library() != NULL );

    try {
        auto failure_library = ice::Library("This_Should_Always_Fail");
    } catch (ice::Exception& ex) {
        auto error_msg = ex.whatString();
        INFO( error_msg );
        REQUIRE( error_msg.find("Failed") != std::string::npos );
    }
}

TEST_CASE("FunctionBasic", "[function]") {
    auto& name = getLibraryName().build();
    auto library = ice::Library(name);
    // const char* hello(void)
    auto hello = ice::Function<const char* (void)>(&library, "hello");
    REQUIRE( std::string(hello()).compare("Hello World!") == 0 );
    REQUIRE( hello.isValid() == true );
    REQUIRE( hello.name().compare("hello") == 0 );

    REQUIRE_THROWS_AS( ice::Function<const char* (void)>(&library, "failure"), ice::Exception );
}

TEST_CASE("LibraryManagerBasic", "[librarymanager]") {
    auto& name = getLibraryName().build();
    auto& mgr = ice::LibraryManager::instance();
    // Add the library and test its existance
    mgr.add("test", name);
    REQUIRE( mgr["test"] == mgr.get("test") );
    REQUIRE ( mgr.exists("test") == true );
    // Make sure its in the list
    auto names = mgr.getLibraryNames();
    REQUIRE( std::find(names.begin(), names.end(), "test") != names.end() );
    // Make sure its loaded and the name is right
    auto* library = mgr["test"];
    REQUIRE( library->isLoaded() == true );
    REQUIRE( library->name() == name );
    // Test the library
    bool path_okay = false;
    auto path = library->getPath(&path_okay);
    INFO("Library Path: " << path);
    REQUIRE( path_okay == true );
    REQUIRE( path.find(name) != std::string::npos );
    REQUIRE( library->_library() != NULL );
    // Test a failure library being added
    try {
        mgr.add("failure", "This_Should_Always_Fail");
        //auto failure_library = ice::Library("This_Should_Always_Fail");
    } catch (ice::Exception& ex) {
        auto error_msg = ex.whatString();
        INFO( error_msg );
        REQUIRE( error_msg.find("Failed") != std::string::npos );
        REQUIRE ( mgr.exists("failure") == false );
    }
    // Remove the library by the libary itself
    mgr.remove(*library);
    REQUIRE ( mgr.exists("test") == false );
    names = mgr.getLibraryNames();
    REQUIRE( std::find(names.begin(), names.end(), "test") == names.end() );
    // Add and remove the library again, this time by name
    mgr.add("test", name);
    REQUIRE ( mgr.exists("test") == true );
    mgr.remove("test");
    REQUIRE ( mgr.exists("test") == false );
    names = mgr.getLibraryNames();
    REQUIRE( std::find(names.begin(), names.end(), "test") == names.end() );
}
