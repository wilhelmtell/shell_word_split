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
    bool in_word = false;
    while( *p ) {
        if( *p == '\'' ) {
            p = detail::parse_single_quoted_string(p, word);
            in_word = true;
        } else if( *p == '"' ) {
            p = detail::parse_double_quoted_string(p, word);
            in_word = true;
        } else if( *p == '\\' ) {
            p = detail::parse_bare_escape(p, word);
            in_word = true;
        } else if( std::isspace(*p) ) {
            if( in_word )
                words.push_back(word);
            word.clear();
            in_word = false;
            p = detail::skip_whitespace(p);
        } else {
            word.push_back(*p++);
            in_word = true;
        }
    }
    if( in_word )
        words.push_back(word);
    return words;
}
}  // namespace sws

#endif  // SHELL_WORD_SPLIT_HH_
