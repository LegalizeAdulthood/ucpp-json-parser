// Copyright (C) 2014, Richard Thomson.  All rights reserved.
#if !defined(JSON_H)
#define JSON_H

#include <map>
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
    Array,
    Object,
    Null
};

struct array;
struct object;
struct null
{
};

typedef boost::variant<
    bool, int, double, std::string,
    boost::recursive_wrapper<array>,
    boost::recursive_wrapper<object>,
    null
> value;

struct array : public std::vector<value>
{
};

struct object : public std::map<std::string, value>
{
};

extern value parse(std::string const& text);

}

#endif
