#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/bind.hpp>
#include <boost/fusion/include/at_c.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;


struct set_my_value_to_the_parent_parser_local {
    void operator()(
            int i, 
            boost::spirit::context<
                /* context.attributes */
                boost::fusion::cons<
                    /* context.attributes.car */
                    int&,
                    /* context.attributes.cdr */
                    boost::fusion::nil_>,
                boost::fusion::vector<int>
            >& context,
            bool& success) const {
        using boost::fusion::at_c;
        std::cout << "Set my value to the parent parser local " << i << std::endl;
        at_c<0>(context.locals) = i;
    }
};

struct compare_value_with_the_parent_parser_local {
    void operator()(
            int i, 
            boost::spirit::context<
                /* context.attributes */
                boost::fusion::cons<
                    /* context.attributes.car */
                    int&,
                    /* context.attributes.cdr */
                    boost::fusion::nil_>,
                boost::fusion::vector<int>
            >& context,
            bool& success) const {
        using boost::fusion::at_c;
        const auto parent_local_value = at_c<0>(context.locals);
        success = parent_local_value < i;
        if (success) {
            context.attributes.car = parent_local_value + i;
            std::cout << "Set my value to the parent parser local " << i << std::endl;
        } else {
            std::cout << "Parsing unsuccessful, second value is smaller than the first one\n";
        }
    }
};


template <typename Iterator>
struct digitparser : qi::grammar<Iterator, int()>
{
    digitparser() : digitparser::base_type(start) {
        using qi::int_;
        set_my_value_to_the_parent_parser_local action_set;
        compare_value_with_the_parent_parser_local action_compare;
        two_ints_parser = int_[action_set] >> "," >> int_[action_compare];
        start = two_ints_parser;
    }

    qi::rule<Iterator, int()> start;
    qi::rule<Iterator, int(), qi::locals<int>> two_ints_parser;
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
    const std::string str("2224,3200");
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