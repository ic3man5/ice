#include <ice/ice.h>
#include <catch2/catch_all.hpp>

TEST_CASE("ExceptionBasic", "[exception]") {    
    auto msg = std::string("This is a test exception");
    auto ex = ice::Exception(msg);

    REQUIRE( ex.whatString().compare(ex.what()) == 0 );
    REQUIRE( ex.whatString().compare(msg) == 0 );

    CHECK_NOTHROW( ex.what() );
    CHECK_NOTHROW( ex.whatString() );
}