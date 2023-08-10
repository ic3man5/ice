#include <ice/ice.h>
#include <catch2/catch_all.hpp>
#include <string>

TEST_CASE("LibraryBasic", "[library]") {
    auto library = ice::Library("libtest");

    REQUIRE( library.isLoaded() == true );
    REQUIRE( library.name() == "libtest" );

    bool path_okay = false;
    auto path = library.getPath(&path_okay);
    INFO("Library Path: " << path);
    REQUIRE( path_okay == true );
    REQUIRE( path.find("libtest") != std::string::npos );

    REQUIRE( library._library() != NULL );

    try {
        auto failure_library = ice::Library("This_Should_Always_Fail");
    } catch (ice::Exception& ex) {
        auto error_msg = ex.whatString();
        INFO( error_msg );
        REQUIRE( error_msg.find("Failed") != std::string::npos );
    }
}
