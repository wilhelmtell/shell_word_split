#ifndef DETAIL_HH_
#define DETAIL_HH_

namespace sws { namespace detail {
inline char const * parse_double_quoted_string(char const * p)
{
    while( *p && *++p != '"' )
        if( *p == '\\' && *(p + 1) == '"' ) ++p;
    return *p ? ++p : p;
}

inline char const * parse_single_quoted_string(char const * p)
{
    while( *p && *++p != '\'' );
    return *p ? ++p : p;
}

inline char const * skip_whitespace(char const * p)
{
    while( std::isspace(*p) )
        ++p;
    return p;
}

inline char const * parse_escape(char const * p)
{
    return ++ ++p;
}

} }  // namespace sws::detail

#endif  // DETAIL_HH_
