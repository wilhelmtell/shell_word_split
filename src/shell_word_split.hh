#ifndef SHELL_WORD_SPLIT_HH_
#define SHELL_WORD_SPLIT_HH_

#include <string>
#include <vector>
#include <cctype>
#include "detail/detail.hh"

namespace sws {
inline std::vector<std::string> shell_word_split(char const * p)
{
    std::vector<std::string> words;
    char const * t = p;
    while( *p ) {
        if( *p == '"' ) {
            p = detail::parse_double_quoted_string(p);
        } else if( *p == '\'' ) {
            p = detail::parse_single_quoted_string(p);
        } else if( *p == '\\' && *(p + 1) ) {
            p = detail::parse_escape(p);
        } else if( std::isspace(*p) ) {
            words.push_back(std::string(t, p));
            t = p = detail::parse_whitespace(p);
        } else {
            ++p;
        }
    }
    if( t != p )
        words.push_back(std::string(t, p));
    return words;
}
}  // namespace sws

#endif  // SHELL_WORD_SPLIT_HH_
