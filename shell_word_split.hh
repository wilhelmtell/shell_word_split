#ifndef SHELL_WORD_SPLIT_HH_
#define SHELL_WORD_SPLIT_HH_

#include <string>
#include <vector>
#include <cctype>

namespace shell_word_split {
inline char const * parse_double_quoted_string(char const * p)
{
    while( *p && *++p != '"' )
        if( *p == '\\' && *(p + 1) == '"' ) ++ ++p;
    return *p ? p : ++p;
}

inline char const * parse_single_quoted_string(char const * p)
{
    while( *p && *++p != '\'' );
    return *p ? p : ++p;
}

inline char const * parse_whitespace(char const * p)
{
    while( std::isspace(*p) )
        ++p;
    return p;
}

inline char const * parse_escape(char const * p)
{
    return ++ ++p;
}

inline std::vector<std::string> shell_split(char const * p)
{
    std::vector<std::string> words;
    char const * t = p;
    while( *p ) {
        if( *p == '"' ) {
            p = parse_double_quoted_string(p);
        } else if( *p == '\'' ) {
            p = parse_single_quoted_string(p);
        } else if( *p == '\\' && *(p + 1) ) {
            p = parse_escape(p);
        } else if( std::isspace(*p) ) {
            words.push_back(std::string(t, p));
            t = p = parse_whitespace(p);
        } else {
            ++p;
        }
    }
    if( t != p )
        words.push_back(std::string(t, p));
    return words;
}
}  // namespace shell_word_split

#endif  // SHELL_WORD_SPLIT_HH_
