// Copyright (C) 2014, Richard Thomson.  All rights reserved.
#if !defined(JSON_H)
#define JSON_H

#include <string>

#include <boost/variant/variant.hpp>

namespace json
{

enum value_types
{
    Boolean,
    Integer,
    Number
};

typedef boost::variant<bool, int, double> value;
extern value parse(std::string const& text);

}

#endif
