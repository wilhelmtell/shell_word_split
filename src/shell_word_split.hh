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
    std::string word;
    while( *p ) {
        if( *p == '"' ) {
            char const * t = p;
            p = detail::parse_double_quoted_string(p);
            word.append(t + 1, p - 1);
        } else if( *p == '\'' ) {
            char const * t = p;
            p = detail::parse_single_quoted_string(p);
            word.append(t + 1, p - 1);
        } else if( *p == '\\' && *(p + 1) ) {
            char const * t = p;
            p = detail::parse_escape(p);
            word.append(t + 1, p);
        } else if( std::isspace(*p) ) {
            if( ! word.empty() )
                words.push_back(word);
            word.clear();
            p = detail::skip_whitespace(p);
        } else {
            word.push_back(*p++);
        }
    }
    if( ! word.empty() )
        words.push_back(word);
    return words;
}
}  // namespace sws

#endif  // SHELL_WORD_SPLIT_HH_
