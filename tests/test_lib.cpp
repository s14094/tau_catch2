#include "catch.hpp"

#include <rpn.hpp>
#include <cmath>

using Catch::Matchers::Contains; // see "matchers"

TEST_CASE("Basic operation test")
{
    rpn testee = rpn();
    REQUIRE(testee.count("2 2 +") == 3); // fails

    REQUIRE(testee.count("3 14 2 - * 4 + 2 /") == 20);
}

TEST_CASE("Error handling")
{
    rpn testee = rpn();
    REQUIRE_THROWS_WITH(testee.count("2 l"), Contains("bad token: l"));
    
}

SCENARIO("Exponentiation scenario")
{
    GIVEN("there are numbers 2, 3, rpn testee with ^ opcode")
    {
        rpn testee = rpn();
        testee.put_op("^", [](auto& s) {
                auto a = s.back();
                s.pop_back();
                auto b = s.back();
                s.pop_back();
                auto c = std::pow(b, a);
                s.push_back(c);
        });
        WHEN("we call count with 2 3 ^")
        {
            int z = testee.count("2 3 ^");
            THEN("the result should be 8")
            {
                REQUIRE(z == 7); //fails
            }
        }
    }
}

/*
mkdir build
cd build
cmake ..
CTEST_OUTPUT_ON_FAILURE=1 make check
./tests
*/