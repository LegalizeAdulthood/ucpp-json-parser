// Copyright (C) 2014, Richard Thomson.  All rights reserved.
#include "json.h"
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>

using namespace boost::spirit::qi;

namespace
{
    typedef std::pair<std::string, json::value> key_value_pair;
}

BOOST_FUSION_ADAPT_STRUCT(::key_value_pair,
    (std::string, first)
    (json::value, second)
);

namespace
{

typedef ascii::space_type skipper;

template <typename Iter>
struct json_grammar : grammar<Iter, json::value(), skipper>
{
    json_grammar() : json_grammar::base_type(start)
    {
        boolean = bool_;
        integer = int_ >> !no_case[char_(".e")];
        number = double_;
        escapes.add(R"(\")", '"')
            (R"(\\)", '\\')
            (R"(\/)", '/')
            (R"(\b)", '\b')
            (R"(\f)", '\f')
            (R"(\n)", '\n')
            (R"(\r)", '\r')
            (R"(\t)", '\t');
        quoted_string = lexeme['"' >> *(escapes | (char_ - '"')) >> '"'];
        array_value = '[' >> ((value % ',') | eps) >> ']';
        key_value = quoted_string >> ':' >> value;
        object_value = ('{' >> ((key_value % ',') | eps) >> '}');
        value = boolean | integer | number | quoted_string
            | array_value | object_value;
        start = value;
    }

    rule<Iter, json::value(),    skipper> start;
    rule<Iter, bool(),           skipper> boolean;
    rule<Iter, int(),            skipper> integer;
    rule<Iter, double(),         skipper> number;
    rule<Iter, std::string(),    skipper> quoted_string;
    symbols<char const, char const> escapes;
    rule<Iter, json::value(),    skipper> value;
    rule<Iter, json::array(),    skipper> array_value;
    rule<Iter, key_value_pair(), skipper> key_value;
    rule<Iter, json::object(),   skipper> object_value;
};

}

namespace json
{

value parse(std::string const& text)
{
    std::string::const_iterator start{text.begin()};
    value result;
    if (phrase_parse(start, text.end(),
            json_grammar<std::string::const_iterator>(),
            ascii::space, result)
        && start == text.end())
    {
        return result;
    }

    throw std::domain_error("invalid JSON input");
}

}
