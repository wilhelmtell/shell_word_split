#ifndef SHELL_WORD_SPLIT_HH_
#define SHELL_WORD_SPLIT_HH_

#include <string>
#include <cctype>
#include "detail/detail.hh"
#include "error.hh"

namespace sws {
template<typename In, typename Out>
Out shell_word_split(In first, In last, Out out)
{
    std::string word;
    bool in_word = false;
    while( first != last ) {
        if( *first == '\'' ) {
            first = detail::parse_single_quoted_string(first, last, word);
            in_word = true;
        } else if( *first == '"' ) {
            first = detail::parse_double_quoted_string(first, last, word);
            in_word = true;
        } else if( *first == '\\' ) {
            first = detail::parse_bare_escape(first, last, word);
            in_word = true;
        } else if( std::isspace(*first) ) {
            if( in_word )
                *out++ = word;
            word.clear();
            in_word = false;
            first = detail::skip_whitespace(first, last);
        } else {
            word.push_back(*first++);
            in_word = true;
        }
    }
    if( in_word )
        *out++ = word;
    return out;
}
}  // namespace sws

#endif  // SHELL_WORD_SPLIT_HH_
