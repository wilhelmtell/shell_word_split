#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include <shell_word_split/shell_word_split.hh>
#include <shell_word_split/error.hh>
#include <algorithm>
#include <cctype>
#include <iterator>


namespace test {
template<typename In, typename Pred>
typename std::iterator_traits<In>::difference_type
find_if(In first, In last, Pred pred)
{
    typename std::iterator_traits<In>::difference_type position =
        typename std::iterator_traits<In>::difference_type();
    while( first != last ) {
        if( pred(*first) )
            return position;
        ++first;
        ++position;
    }
    return -1;
}
}  // namespace test


TEST_CASE("input/one_word", "")
{
    auto const words = sws::shell_word_split("word");
    REQUIRE(words.size() == 1);
    REQUIRE(words[0] == "word");
}

TEST_CASE("input/two_words", "")
{
    auto const words = sws::shell_word_split("two words");
    REQUIRE(words.size() == 2);
    REQUIRE(words[0] == "two");
    REQUIRE(words[1] == "words");
}

TEST_CASE("input/escaped_space_character", "")
{
    auto const words = sws::shell_word_split("\\ ");
    REQUIRE(words.size() == 1);
    REQUIRE(words[0] == " ");
}

TEST_CASE("input/whitespace_mix", "")
{
    auto const words = sws::shell_word_split("two 	 words");
    REQUIRE(words.size() == 2);
    REQUIRE(words[0] == "two");
    REQUIRE(test::find_if(words[0].begin(), words[0].end(), [](char c) {
        return iscntrl(c);
    }) == -1);
    REQUIRE(words[1] == "words");
    REQUIRE(test::find_if(words[1].begin(), words[1].end(), [](char c) {
        return iscntrl(c);
    }) == -1);
}

TEST_CASE("input/leading_whitespace", "")
{
    auto const words = sws::shell_word_split("	two");
    REQUIRE(words.size() == 1);
    REQUIRE(words[0] == "two");
    REQUIRE(test::find_if(words[0].begin(), words[0].end(), [](char c) {
        return iscntrl(c);
    }) == -1);
}

TEST_CASE("input/trailing_whitespace", "")
{
    auto const words = sws::shell_word_split("two  ");
    REQUIRE(words.size() == 1);
    REQUIRE(words[0] == "two");
    REQUIRE(test::find_if(words[0].begin(), words[0].end(), [](char c) {
        return iscntrl(c);
    }) == -1);
}

TEST_CASE("input/leading_and_trailing_whitespace", "")
{
    auto const words = sws::shell_word_split("  	 two  ");
    REQUIRE(words.size() == 1);
    REQUIRE(words[0] == "two");
    REQUIRE(test::find_if(words[0].begin(), words[0].end(), [](char c) {
        return iscntrl(c);
    }) == -1);
}

TEST_CASE("input/double_quoted_words", "")
{
    auto const words = sws::shell_word_split("word \"quoted words\"");
    REQUIRE(words.size() == 2);
    REQUIRE(words[0] == "word");
    REQUIRE(test::find_if(words[0].begin(), words[0].end(), [](char c) {
        return iscntrl(c);
    }) == -1);
    REQUIRE(words[1] == "quoted words");
    REQUIRE(test::find_if(words[1].begin(), words[1].end(), [](char c) {
        return iscntrl(c);
    }) == -1);
}

TEST_CASE("input/double_quoted_words_with_escape", "")
{
    auto const words = sws::shell_word_split("word \"quoted \\\"words\"");
    REQUIRE(words.size() == 2);
    REQUIRE(words[0] == "word");
    REQUIRE(test::find_if(words[0].begin(), words[0].end(), [](char c) {
        return iscntrl(c);
    }) == -1);
    REQUIRE(words[1] == "quoted \"words");
    REQUIRE(test::find_if(words[1].begin(), words[1].end(), [](char c) {
        return iscntrl(c);
    }) == -1);
}

TEST_CASE("input/single_quoted_words_with_escape", "")
{
    auto const words = sws::shell_word_split("word 'quoted words'");
    REQUIRE(words.size() == 2);
    REQUIRE(words[0] == "word");
    REQUIRE(test::find_if(words[0].begin(), words[0].end(), [](char c) {
        return iscntrl(c);
    }) == -1);
    REQUIRE(words[1] == "quoted words");
    REQUIRE(test::find_if(words[1].begin(), words[1].end(), [](char c) {
        return iscntrl(c);
    }) == -1);
}

TEST_CASE("input/empty_string", "")
{
    auto const words = sws::shell_word_split("");
    REQUIRE(words.size() == 0);
}

TEST_CASE("input/empty_string_with_whitespace", "")
{
    auto const words = sws::shell_word_split(" ");
    REQUIRE(words.size() == 0);
}

TEST_CASE("input/a_single_escape", "")
{
    auto const words = sws::shell_word_split("\\f");
    REQUIRE(words.size() == 1);
    REQUIRE(words[0] == "f");
    REQUIRE(test::find_if(words[0].begin(), words[0].end(), [](char c) {
        return iscntrl(c);
    }) == -1);
}

TEST_CASE("input/a_single_single_quote", "")
{
    REQUIRE_THROWS_AS(sws::shell_word_split("'"), sws::invalid_token);
}

TEST_CASE("input/a_single_double_quote", "")
{
    REQUIRE_THROWS_AS(sws::shell_word_split("\""), sws::invalid_token);
}

TEST_CASE("input/eos_in_double_quote_escape", "")
{
    REQUIRE_THROWS_AS(sws::shell_word_split("\"\\"), sws::invalid_token);
}

TEST_CASE("input/eos_in_escape", "")
{
    REQUIRE_THROWS_AS(sws::shell_word_split("\""), sws::invalid_token);
}
