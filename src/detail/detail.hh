#ifndef DETAIL_HH_
#define DETAIL_HH_

#include <string>

namespace sws { namespace detail {
inline char const * parse_escaping_double_quotes(char const * p, std::string& word)
{
    word.push_back(*++p);
    return p;
}

inline char const * parse_double_quoted_string(char const * p, std::string& word)
{
    while( *++p && *p != '"' )
        if( *p == '\\' )
            p = parse_escaping_double_quotes(p, word);
        else
            word.push_back(*p);
    return p;
}

inline char const * parse_single_quoted_string(char const * p, std::string& word)
{
    while( *++p && *p != '\'' )
        word.push_back(*p);
    return p;
}

inline char const * skip_whitespace(char const * p)
{
    while( std::isspace(*p) )
        ++p;
    return p;
}

inline char const * parse_bare_escape(char const * p, std::string& word)
{
    word.push_back(*++p);
    return p;
}

} }  // namespace sws::detail

#endif  // DETAIL_HH_
