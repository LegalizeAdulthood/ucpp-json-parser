This is an example of a recursive descent [JSON](http://www.json.org/) parser written using
[Boost.Spirit](http://www.boost.org/doc/libs/1_57_0/libs/spirit/doc/html/index.html).

This parser is developed incrementally, commit by commit.  Browse the commits to see how
this parser evolved from simple cases up to handling the full JSON grammar.

Tips
====
Here are some tips for creating parsers with Spirit:

- Develop your parsers incrementally, starting with the smallest parsable
  unit.  Drive your parser forward step-by-step with unit tests to keep
  everything working as you enhance the parser.
- When building up parser rules and grammars driven by tests:
  - Use `lit("expected input text")` and `attr()` to match the input of
    test cases and supply the necessary attribute values.  As you add more
    test cases for your grammar, you will drive out these intermediate
    steps with parser details.
  - Start with the simplest cases that omit all optional elements of your
    grammar.
  - Start with a single choice among alternatives in your rules.  Use
    additional tests to drive the remaining alternatives into your grammar.
    This keeps your grammar from adding too many new rules and non-terminals
    in a single step, keeping it easy to debug.
  - Extract grammar rules incrementally as you build up functionality.
    Refactor out rules in your grammar after passing new test cases.
- Remember that rule and grammar attribute types are specified by function signatures:
  write `rule<Iter, bool(), skipper> boolean;`, not `rule<Iter, bool, skipper> boolean;`
- Order the elements of a struct in `BOOST_FUSION_ADAPT_STRUCT` so that it is convenient
  for your parser attribute sequence.
- When using `BOOST_FUSION_ADAPT_STRUCT`, make sure that your grammar generates attributes
  for each adapted struct member.
- Use [`boost::recursive_wrapper`](http://www.boost.org/doc/libs/1_57_0/doc/html/boost/recursive_wrapper.html) from [Boost.Variant](http://www.boost.org/doc/libs/1_57_0/doc/html/variant.html)
  to handle recursive alternatives.
- Spirit parsers leverage templates heavily to achieve fast runtime at the expense of
  compile time.  Isolate your parsers behind an application specific API as is done
  here in `json.h`.  The parser implementation in `json.cpp` only needs to be recompiled
  when the parser changes.  The parser can be reused in as many places as possible without
  recompiling the parser.

JSON Grammar
============

See [json.org](http://www.json.org) for a
[syntax diagram](http://en.wikipedia.org/wiki/Syntax_diagram) representation
of the grammar.

```
object := "{" [key-value-pair-list] "}"

key-value-pair-list := key-value-pair
    | key-value-pair-list "," key-value-pair

key-value-pair := string ":" value

array := "[" [value-list] "]"

value-list := value
    | value-list "," value

value := string
    | number
    | object
    | array
    | "true"
    | "false"
    | "null"

string := "\"" string-char* "\""

string-char := <any UNICODE character except " or \>
    | "\\\""
    | "\\\\"
    | "\\/"
    | "\\b"
    | "\\f"
    | "\\n"
    | "\\r"
    | "\\t"
    | "\\u" hex-digit*4

hex-digit := digit
    | "a" | "b" | "c" | "d" | "e" | "f"

number := ["-"] integer-part ["." digit+] [exponent-part]

integer-part := "0"
    | non-zero-digit digit*

non-zero-digit := "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"

digit := "0" | non-zero-digit

exponent-part := ("e" | "E") [("+" | "-")] digit+
```

This repository contains source code to accompany a Utah C++ Programmers presentation.

[Utah C++ Programmers](https://meetup.com/utah-cpp-programmers)\
[Past Topics](https://utahcpp.wordpress.com/past-meeting-topics/)\
[Future Topics](https://utahcpp.wordpress.com/future-meeting-topics/)
