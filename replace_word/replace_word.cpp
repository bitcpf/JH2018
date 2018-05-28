#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>

using namespace std;

bool is_boundary(char c) {
    return !((c >= 'a' and c <= 'z') or
            (c >= 'A' and c <= 'Z'));
}

int skip_until_next_boundary(const string& str, int start, ostringstream* os)
{
    for (int i = start; i < str.size(); i++) {
        *os << str[i];
        if (is_boundary(str[i]) and i + 1 < str.size() and !is_boundary(str[i + 1])) {
            return i + 1;
        }
    }
    return str.size();
}

int match_word_with_boundary(const string& str, int start, const string& word, ostringstream* os)
{
    if (start + word.size() >= str.size() or !is_boundary(str[start + word.size()])) {
        // Does not have boundary, continue to next word boundary
        return skip_until_next_boundary(str, start, os);
    }
    for (int i = 0; i < word.size(); i++) {
        if (str[start + i] != word[i]) {
            // Does not match continue to next word bounary
            return skip_until_next_boundary(str, start, os);
        }
    }
    *os << "<b>" << word << "</b>";
    return skip_until_next_boundary(str, start + word.size(), os);
}

string replace_string(const std::string& str, const string& word)
{
    ostringstream os;
    int i = skip_until_next_boundary(str, 0, &os);
    while (i < str.size()) {
        i = match_word_with_boundary(str, i, word, &os);
    }
    return os.str();
}

int main(int argc, char** argv)
{
    string s = "There is all in all, two all";
    string replace = "all";
    auto str = replace_string(s, replace);
    cout << s << endl << "=>" << endl << str << endl;
    return 0;
}