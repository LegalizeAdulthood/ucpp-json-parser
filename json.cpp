// Copyright (C) 2014, Richard Thomson.  All rights reserved.
#include "json.h"
#include <boost/spirit/include/qi.hpp>

using namespace boost::spirit::qi;

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
        quoted_string = '"' >> *(char_ - '"') >> '"';
        start = boolean | integer | number | quoted_string;
    }

    rule<Iter, json::value(), skipper> start;
    rule<Iter, bool(),        skipper> boolean;
    rule<Iter, int(),         skipper> integer;
    rule<Iter, double(),      skipper> number;
    rule<Iter, std::string(), skipper> quoted_string;
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
