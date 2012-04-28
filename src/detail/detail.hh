#ifndef DETAIL_HH_
#define DETAIL_HH_

#include <string>
#include "../error.hh"
#include <cassert>
#include <iterator>

namespace sws { namespace detail {
template<typename In>
In parse_escaping_double_quotes(In first, In last, std::string& word)
{
    assert(first != last && *first == '\\');
    if( std::next(first) == last )
        throw invalid_token("unexpected eos in an escape inside double-quoted string");
    word.push_back(*++first);
    return ++first;
}

template<typename In>
In parse_double_quoted_string(In first, In last, std::string& word)
{
    assert(first != last && *first == '"');
    ++first;
    while( first != last && *first != '"' ) {
        if( *first == '\\' )
            first = parse_escaping_double_quotes(first, last, word);
        else
            word.push_back(*first++);
    }
    if( first == last )
        throw invalid_token("unexpected eos inside double-quoted string");
    return ++first;
}

template<typename In>
In parse_single_quoted_string(In first, In last, std::string& word)
{
    assert(first != last && *first == '\'');
    ++first;
    while( first != last && *first != '\'' )
        word.push_back(*first++);
    if( first == last )
        throw invalid_token("unexpected eos inside single-quoted string");
    return ++first;
}

template<typename In>
In skip_whitespace(In first, In last)
{
    assert(first != last && std::isspace(*first));
    while( first != last && std::isspace(*first) )
        ++first;
    return first;
}

template<typename In>
In parse_bare_escape(In first, In last, std::string& word)
{
    assert(first != last && *first == '\\');
    if( std::next(first) == last )
        throw invalid_token("unexpected eos in an escape");
    word.push_back(*++first);
    return ++first;
}

} }  // namespace sws::detail

#endif  // DETAIL_HH_
