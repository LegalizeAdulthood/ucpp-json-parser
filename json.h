// Copyright (C) 2014, Richard Thomson.  All rights reserved.
#if !defined(JSON_H)
#define JSON_H

#include <string>
#include <vector>

#include <boost/variant/recursive_wrapper.hpp>
#include <boost/variant/variant.hpp>

namespace json
{

enum value_types
{
    Boolean,
    Integer,
    Number,
    String,
    Array
};

struct array;

typedef boost::variant<
    bool, int, double, std::string,
    boost::recursive_wrapper<array>
> value;

struct array : public std::vector<value>
{
};

extern value parse(std::string const& text);

}

#endif
