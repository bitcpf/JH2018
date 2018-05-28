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

string replace_string(const std::string& str, const string& word)
{
    ostringstream os;
    int j = -1;
    int w_size = word.size();
    for (int i = 0; i < str.size(); ) {
        bool match = false;
        if (j == -1 or j == w_size) {
            if (is_boundary(str[i])) {
                match = true;
            }
        } else if (str[i] == word[j]) {
            match = true;
        }
        if (match) {
            if (j == w_size) {
                os << str[i - w_size - 1] << "<b>" << word << "</b>" << str[i];
                j = -1;
            } else if (i == str.size() - 1) {
                os << str.substr(i - j - 1, j + 2);
            } else {
                j++;
            }
        } else {
            os << str.substr(i - j - 1, j + 2);
            j = -1;
        }
        i++;
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