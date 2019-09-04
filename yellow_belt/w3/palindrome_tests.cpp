//
// Created by dkushn on 13.08.19.
//
#include "../../TestRunner.h"

void testEmptyPalindrome(){
    AssertEqual(IsPalindrom(""), true, "Empty string is palindrome");
}
void testOneCharPalindrome(){
    AssertEqual(IsPalindrom(" "), true, "Space string is palindrome");
    AssertEqual(IsPalindrom("\n"), true, "Space string is palindrome");
    AssertEqual(IsPalindrom("\r"), true, "Space string is palindrome");
    AssertEqual(IsPalindrom("  "), true, "Space string is palindrome");
    AssertEqual(IsPalindrom("a"), true, "a string is palindrome");
    AssertEqual(IsPalindrom("-"), true, "- string is palindrome");
    AssertEqual(IsPalindrom("1"), true, "1 string is palindrome");
}
void testIsPalindrome(){
    vector<string> positive_tests{
            "aa", "aba", " aba ", "  aa  ", " a "
    };
    for (const auto& test_string: positive_tests){
        AssertEqual(IsPalindrom(test_string), true, "[" + test_string + "]");
    }
}
void testNotPalindrome(){
    vector<string> negative_tests{
            "ab", "aab", " aba", " aa  ", " a", "a ", "\na"
    };
    for (const auto& test_string: negative_tests){
        AssertEqual(IsPalindrom(test_string), false, "[" + test_string + "]");
    }
}

/*
int main() {
    TestRunner runner;
    runner.RunTest(testOneCharPalindrome, "testOneCharPalindrome");
    runner.RunTest(testEmptyPalindrome, "testEmptyPalindrome");
    runner.RunTest(testIsPalindrome, "testIsPalindrome");
    runner.RunTest(testNotPalindrome, "testNotPalindrome");
    // добавьте сюда свои тесты
    return 0;
}
*/