This is an example of a recursive descent [JSON](http://www.json.org/) parser written using
[Boost.Spirit](http://www.boost.org/doc/libs/1_57_0/libs/spirit/doc/html/index.html).

This parser is developed incrementally, commit by commit.  Browse the commits to see how
this parser evolved from simple cases up to handling the full JSON grammar.

Here are some tips for creating parsers with Spirit:

- Develop your parsers incrementally, starting with the smallest parsable unit.  Drive
  your parser forward step-by-step with unit tests to keep everything working as you
  enhance the parser.
- Remember that rule and grammar attribute types are specified by function signatures:
  write `rule<Iter, bool(), skipper> boolean;`, not `rule<Iter, bool, skipper> boolean;`
- Use [`boost::recursive_wrapper`](http://www.boost.org/doc/libs/1_57_0/doc/html/boost/recursive_wrapper.html) from [Boost.Variant](http://www.boost.org/doc/libs/1_57_0/doc/html/variant.html)
  to handle recursive alternatives.
- Spirit parsers leverage templates heavily to achieve fast runtime at the expense of
  compile time.  Isolate your parsers behind an application specific API as is done
  here in `json.h`.  The parser implementation in `json.cpp` only needs to be recompiled
  when the parser changes.  The parser can be reused in as many places as possible without
  recompiling the parser.
