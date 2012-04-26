#ifndef DETAIL_HH_
#define DETAIL_HH_

#include <string>
#include "../error.hh"
#include <cassert>

namespace sws { namespace detail {
inline char const * parse_escaping_double_quotes(char const * p, std::string& word)
{
    assert(p[0] == '\\');
    word.push_back(*++p);
    return p;
}

inline char const * parse_double_quoted_string(char const * p, std::string& word)
{
    assert(p[0] == '"');
    while( *++p != '"' ) {
        if( *p == 0 )
            throw invalid_token("unexpected eos inside double-quoted string");
        if( *p == '\\' )
            p = parse_escaping_double_quotes(p, word);
        else
            word.push_back(*p);
    }
    return ++p;
}

inline char const * parse_single_quoted_string(char const * p, std::string& word)
{
    assert(p[0] == '\'');
    while( *++p != '\'' ) {
        if( *p == 0 )
            throw invalid_token("unexpected eos inside single-quoted string");
        word.push_back(*p);
    }
    return ++p;
}

inline char const * skip_whitespace(char const * p)
{
    assert(std::isspace(p[0]));
    while( std::isspace(*++p) );
    return p;
}

inline char const * parse_bare_escape(char const * p, std::string& word)
{
    assert(p[0] == '\\');
    word.push_back(*++p);
    return ++p;
}

} }  // namespace sws::detail

#endif  // DETAIL_HH_
