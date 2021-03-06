#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>


namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;


template <typename Iterator>
bool parse_numbers(Iterator first, Iterator last)
{
    using ascii::space;
    using qi::double_;
    using qi::phrase_parse;

    bool r = phrase_parse(
        first,                        /*< start iterator >*/
        last,                         /*< end iterator >*/
        double_ >> *(',' >> double_), /*< the parser >*/
        space                         /*< the skip-parser >*/
    );
    if (first != last) // fail if we did not get a full match
        return false;
    return r;
}

int main()
{
    const std::string str("1,2,3");
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