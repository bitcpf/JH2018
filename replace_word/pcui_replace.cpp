#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>

using namespace std;


int findWordEndPos(const string & str, int start)
{
    for(int i = start + 1; i < str.size(); i ++)
    {
        char c = str.at(i);
        if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
        {
            return i;
        }
    }

    return -1;
}

int match_word(const string & str, int start, int end, const string & word, ostringstream & os)
{
    if(end - start != word.size())
    {
        os << str.substr(start, end - start) << str.at(end);
        return end + 1;
    }
    bool isMatch = true;
    for(int i = 0; i < end - start; i ++)
    {
        if(word.at(i) != str.at(start + i))
        {
            isMatch =false;
            break;
        }
    }
    if(isMatch)
    {
        os << "<b>" << word << "</b>" << str.at(end);
    }
    else
    {
        os << str.substr(start, end - start) << str.at(end);
    }

    start = end + 1;
    return start;
}


string replace_string(const std::string& str, const string& word)
{
    ostringstream os;
    int start = 0;
    int end = findWordEndPos(str, start);
    while (end > 0 && end < str.size()) {
        start = match_word(str, start, end, word, os);
        end = findWordEndPos(str, start);
    }
    os << str.substr(start, str.size()-start);
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
