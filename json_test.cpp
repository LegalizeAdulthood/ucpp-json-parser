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

BOOST_AUTO_TEST_CASE(escaped_characters_in_string)
{
    const std::string text{R"json("\"\\\/\b\f\n\r\t")json"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::String, value.which());
    BOOST_REQUIRE_EQUAL("\"\\/\b\f\n\r\t", boost::get<std::string>(value));
}

BOOST_AUTO_TEST_CASE(string_with_spaces)
{
    const std::string text{R"json("howdy doodly do")json"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::String, value.which());
    BOOST_REQUIRE_EQUAL("howdy doodly do", boost::get<std::string>(value));
}

BOOST_AUTO_TEST_CASE(empty_array)
{
    const std::string text{"[]"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::Array, value.which());
    BOOST_REQUIRE_EQUAL(0, boost::get<json::array>(value).size());
}

BOOST_AUTO_TEST_CASE(array_of_single_integer)
{
    const std::string text{"[1]"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::Array, value.which());
    json::array const& array_value{boost::get<json::array>(value)};
    BOOST_REQUIRE_EQUAL(1, array_value.size());
    BOOST_REQUIRE_EQUAL(json::Integer, array_value[0].which());
    BOOST_REQUIRE_EQUAL(1, boost::get<int>(array_value[0]));
}

BOOST_AUTO_TEST_CASE(mixed_value_array)
{
    const std::string text{R"json([1,"one for me"])json"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::Array, value.which());
    json::array const& array_value{boost::get<json::array>(value)};
    BOOST_REQUIRE_EQUAL(2, array_value.size());
    BOOST_REQUIRE_EQUAL(json::Integer, array_value[0].which());
    BOOST_REQUIRE_EQUAL(1, boost::get<int>(array_value[0]));
    BOOST_REQUIRE_EQUAL(json::String, array_value[1].which());
    BOOST_REQUIRE_EQUAL("one for me", boost::get<std::string>(array_value[1]));
}

BOOST_AUTO_TEST_CASE(nested_array)
{
    const std::string text{R"json([1,"one for me",[2,"and two for you"]])json"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::Array, value.which());
    json::array const& array_value{boost::get<json::array>(value)};
    BOOST_REQUIRE_EQUAL(3, array_value.size());
    BOOST_REQUIRE_EQUAL(json::Array, array_value[2].which());
    json::array const& nested_array{boost::get<json::array>(array_value[2])};
    BOOST_REQUIRE_EQUAL(json::Integer, nested_array[0].which());
    BOOST_REQUIRE_EQUAL(2, boost::get<int>(nested_array[0]));
    BOOST_REQUIRE_EQUAL(json::String, nested_array[1].which());
    BOOST_REQUIRE_EQUAL("and two for you", boost::get<std::string>(nested_array[1]));
}

BOOST_AUTO_TEST_CASE(empty_object)
{
    const std::string text{"{}"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::Object, value.which());
    BOOST_REQUIRE_EQUAL(0, boost::get<json::object>(value).size());
}

BOOST_AUTO_TEST_CASE(object_with_single_field)
{
    const std::string text{R"json({"key": "value"})json"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::Object, value.which());
    json::object const& obj{boost::get<json::object>(value)};
    BOOST_REQUIRE_EQUAL(1, obj.size());
    auto it = obj.find("key");
    BOOST_REQUIRE(obj.end() != it);
    BOOST_REQUIRE_EQUAL(json::String, it->second.which());
    BOOST_REQUIRE_EQUAL("value", boost::get<std::string>(it->second));
}

BOOST_AUTO_TEST_CASE(object_with_multiple_fields)
{
    const std::string text{R"json({
        "s": "value",
        "b": true,
        "i": 1,
        "n": 6.02e23,
        "a": [],
        "o": {}
    })json"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::Object, value.which());
    json::object const& obj{boost::get<json::object>(value)};
    BOOST_REQUIRE_EQUAL(6, obj.size());
    auto it = obj.find("o");
    BOOST_REQUIRE(obj.end() != it);
    BOOST_REQUIRE_EQUAL(json::Object, it->second.which());
    BOOST_REQUIRE_EQUAL(0, boost::get<json::object>(it->second).size());
}

BOOST_AUTO_TEST_CASE(null_value)
{
    const std::string text{"null"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::Null, value.which());
}

BOOST_AUTO_TEST_CASE(escaped_unicode_character_in_ascii_range)
{
    const std::string text{R"json("What\u0020\u0061\u0020great day!")json"};

    const auto value = json::parse(text);

    BOOST_REQUIRE_EQUAL(json::String, value.which());
    BOOST_REQUIRE_EQUAL("What a great day!", boost::get<std::string>(value));
}
