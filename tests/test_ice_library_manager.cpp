#include <ice/ice.h>
#include <catch2/catch_all.hpp>
#include <string>
#include <algorithm>

TEST_CASE("LibraryManagerBasic", "[librarymanager]") {
    auto& mgr = ice::LibraryManager::instance();
    // Add the library and test its existance
    mgr.add("test", "libtest");
    REQUIRE( mgr["test"] == mgr.get("test") );
    REQUIRE ( mgr.exists("test") == true );
    // Make sure its in the list
    auto names = mgr.getLibraryNames();
    REQUIRE( std::find(names.begin(), names.end(), "test") != names.end() );
    // Make sure its loaded and the name is right
    auto* library = mgr["test"];
    REQUIRE( library->isLoaded() == true );
    REQUIRE( library->name() == "libtest" );
    // Test the library
    bool path_okay = false;
    auto path = library->getPath(&path_okay);
    INFO("Library Path: " << path);
    REQUIRE( path_okay == true );
    REQUIRE( path.find("libtest") != std::string::npos );
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
    mgr.add("test", "libtest");
    REQUIRE ( mgr.exists("test") == true );
    mgr.remove("test");
    REQUIRE ( mgr.exists("test") == false );
    names = mgr.getLibraryNames();
    REQUIRE( std::find(names.begin(), names.end(), "test") == names.end() );
}
