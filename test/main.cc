#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include <shell_word_split/shell_word_split.hh>

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
    REQUIRE(words[0] == "\\ ");
}

TEST_CASE("input/whitespace_mix", "")
{
    auto const words = sws::shell_word_split("two 	 words");
    REQUIRE(words.size() == 2);
    REQUIRE(words[0] == "two");
    REQUIRE(words[1] == "words");
}

TEST_CASE("input/leading_whitespace", "")
{
    auto const words = sws::shell_word_split("	two");
    REQUIRE(words.size() == 1);
    REQUIRE(words[0] == "two");
}
