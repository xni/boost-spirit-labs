#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;


template <typename Iterator>
bool parse_numbers(Iterator first, Iterator last)
{
    using boost::spirit::qi::_1;
    using ascii::space;
    using qi::double_;
    using qi::phrase_parse;

    std::vector<double> res;
    const auto appender = [&res](double const& d, qi::unused_type, qi::unused_type) {
        res.push_back(d);
    };

    bool r = phrase_parse(
        first,                                        /*< start iterator >*/
        last,                                         /*< end iterator >*/
        double_[appender] >> *(',' >> double_[appender]), /*< the parser >*/
        space                                         /*< the skip-parser >*/
    );
    if (first != last) // fail if we did not get a full match
        return false;

    std::ostream_iterator<double> out_it (std::cout,"<--\n");
    std::copy(res.begin(), res.end(), out_it);
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