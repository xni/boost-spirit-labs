#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

struct TwoDoubles
{
    double d1;
    double d2;
};

BOOST_FUSION_ADAPT_STRUCT(
    TwoDoubles,
    (double, d1)
    (double, d2)
)

template <typename Iterator>
bool parse_numbers(Iterator first, Iterator last)
{
    TwoDoubles result;
    using qi::double_;
    qi::rule<Iterator, TwoDoubles()> start = double_ >> ' ' >> double_;

    bool r = qi::parse(
        first,                                        /*< start iterator >*/
        last,                                         /*< end iterator >*/
        start,                                        /*< the parser >*/
        result                                        /*< the skip-parser >*/
    );
    if (first != last) // fail if we did not get a full match
        return false;

    std::cout << result.d1 << " ; " << result.d2 << std::endl;

    return r;
}

int main()
{
    const std::string str("1.3 2.4");
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