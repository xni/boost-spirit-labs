#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;


struct add_my_value_to_the_parent_parser {
    void operator()(int i) const {
        std::cout << "Add my value to the parent parser called with args " << i << std::endl;
    }
};


template <typename Iterator>
struct digitparser : qi::grammar<Iterator, int()>
{
    digitparser() : digitparser::base_type(start) {
        using qi::int_;
        add_my_value_to_the_parent_parser action;
        start = int_[action];
    }

    qi::rule<Iterator, int()> start;
};


template <typename Iterator>
bool parse_numbers(Iterator first, Iterator last)
{
    digitparser<Iterator> parser;
    int result;

    bool r = qi::parse(
        first,                                        /*< start iterator >*/
        last,                                         /*< end iterator >*/
        parser,                                       /*< the parser >*/
        result                                        /*< the skip-parser >*/
    );
    if (first != last) // fail if we did not get a full match
        return false;

    std::cout << "Parsing result = " << result << std::endl;
    return r;
}

int main()
{
    const std::string str("2224");
    if (parse_numbers(str.begin(), str.end()))
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded\n";
        std::cout << str << " Parses OK: " << std::endl;
    }
    else
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------\n";
    }
}