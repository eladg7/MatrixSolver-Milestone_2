#ifndef MILESTONE_2_STRINGUTILS_H
#define MILESTONE_2_STRINGUTILS_H

#include "string"
#include <vector>
#include <sstream>

using namespace std;

class StringUtils {
public:
    static vector<string> split(const basic_string<char> &s, char delimiter) {
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    static string &ltrim(string &str, const string &chars = "\t\n\v\f\r ") {
        str.erase(0, str.find_first_not_of(chars));
        return str;
    }

    static string &rtrim(string &str, const string &chars = "\t\n\v\f\r ") {
        str.erase(str.find_last_not_of(chars) + 1);
        return str;
    }

    static string &trim(string &str, const string &chars) {
        return ltrim(rtrim(str, chars), chars);
    }
};

#endif //MILESTONE_2_STRINGUTILS_H
