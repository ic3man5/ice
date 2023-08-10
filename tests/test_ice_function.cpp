#include <ice/ice.h>
#include <catch2/catch_all.hpp>
#include <string>

TEST_CASE("FunctionBasic", "[function]") {
    auto library = ice::Library("libtest");
    // const char* hello(void)
    auto hello = ice::Function<const char* (void)>(&library, "hello");
    REQUIRE( std::string(hello()).compare("Hello World!") == 0 );
    REQUIRE( hello.isValid() == true );
    REQUIRE( hello.name().compare("hello") == 0 );

    REQUIRE_THROWS_AS( ice::Function<const char* (void)>(&library, "failure"), ice::Exception );
}
