#pragma once

#include <string>
#include <functional>

typedef std::string String;

String StringPrintf(const char *fmt, ...);
String StringFromInt(int value);
String MakeLower(const String &text);

//----- (00452C30) --------------------------------------------------------
inline char *RemoveQuotes(char *str) {
    if (*str == '"') {
        str[strlen(str) - 1] = 0;
        return str + 1;
    }
    return str;
}

struct ci_less : std::binary_function<std::string, std::string,
                                      bool> {  // case insensitive comparator for
                                               // dictionaries
    // case-independent (ci) compare_less binary function
    struct nocase_compare
        : public std::binary_function<unsigned char, unsigned char, bool> {
        bool operator()(const unsigned char &c1,
                        const unsigned char &c2) const {
            return tolower(c1) < tolower(c2);
        }
    };
    bool operator()(const std::string &s1, const std::string &s2) const {
        return std::lexicographical_compare(s1.begin(),
                                            s1.end(),  // source range
                                            s2.begin(), s2.end(),  // dest range
                                            nocase_compare());     // comparison
    }
};
