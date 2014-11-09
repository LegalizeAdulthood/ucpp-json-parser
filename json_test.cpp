#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/variant/get.hpp>
#include "json.h"

BOOST_AUTO_TEST_CASE(boolean_true)
{
    const std::string text{"true"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::Boolean, value.which());
    BOOST_REQUIRE(boost::get<bool>(value));
}

BOOST_AUTO_TEST_CASE(boolean_false)
{
    const std::string text{"false"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::Boolean, value.which());
    BOOST_REQUIRE(!boost::get<bool>(value));
}

BOOST_AUTO_TEST_CASE(malformed_json_throws_domain_error)
{
    const std::string text{"some arbitrary text"};

    BOOST_REQUIRE_THROW(json::parse(text), std::domain_error);
}

BOOST_AUTO_TEST_CASE(positive_integer_value)
{
    const std::string text{"666"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::Integer, value.which());
    BOOST_REQUIRE_EQUAL(666, boost::get<int>(value));
}

BOOST_AUTO_TEST_CASE(negative_integer_value)
{
    const std::string text{"-666"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::Integer, value.which());
    BOOST_REQUIRE_EQUAL(-666, boost::get<int>(value));
}

BOOST_AUTO_TEST_CASE(number_value)
{
    const std::string text{"6.02e23"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::Number, value.which());
    BOOST_REQUIRE_EQUAL(6.02e23, boost::get<double>(value));
}

BOOST_AUTO_TEST_CASE(upper_case_number_value)
{
    const std::string text{"6.02E23"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::Number, value.which());
    BOOST_REQUIRE_EQUAL(6.02e23, boost::get<double>(value));
}

BOOST_AUTO_TEST_CASE(negative_number_value)
{
    const std::string text{"-6.02e23"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::Number, value.which());
    BOOST_REQUIRE_EQUAL(-6.02e23, boost::get<double>(value));
}

BOOST_AUTO_TEST_CASE(empty_string)
{
    const std::string text{R"json("")json"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::String, value.which());
    BOOST_REQUIRE_EQUAL("", boost::get<std::string>(value));
}

BOOST_AUTO_TEST_CASE(non_empty_string)
{
    const std::string text{R"json("scooby")json"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::String, value.which());
    BOOST_REQUIRE_EQUAL("scooby", boost::get<std::string>(value));
}
