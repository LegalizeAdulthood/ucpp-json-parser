#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include "json.h"

BOOST_AUTO_TEST_CASE(boolean_true)
{
    const std::string text{"true"};
    const bool value = json::parse(text);

    BOOST_REQUIRE(value);
}

BOOST_AUTO_TEST_CASE(boolean_false)
{
    const std::string text{"false"};
    const bool value = json::parse(text);

    BOOST_REQUIRE(!value);
}
