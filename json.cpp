// Copyright (C) 2014, Richard Thomson.  All rights reserved.
#include "json.h"
#include <boost/spirit/include/qi.hpp>

namespace json
{

bool parse(std::string const& text)
{
    using namespace boost::spirit::qi;
    std::string::const_iterator start{text.begin()};
    bool result = false;
    if (phrase_parse(start, text.end(), bool_, ascii::space, result)
        && start == text.end())
    {
        return result;
    }

    throw std::domain_error("invalid JSON input");
}

}
