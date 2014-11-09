// Copyright (C) 2014, Richard Thomson.  All rights reserved.
#include "json.h"
#include <boost/spirit/include/qi.hpp>

namespace json
{

value parse(std::string const& text)
{
    using namespace boost::spirit::qi;
    std::string::const_iterator start{text.begin()};
    value result;
    if (phrase_parse(start, text.end(),
            bool_
            | (int_ >> !no_case[char_(".e")])
            | double_
            | ('"' >> *(char_ - '"') >> '"'), ascii::space, result)
        && start == text.end())
    {
        return result;
    }

    throw std::domain_error("invalid JSON input");
}

}
