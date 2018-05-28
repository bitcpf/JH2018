#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

void word_break(const std::string& str, const unordered_set<string>& dict)
{
    size_t size = str.size();
    vector<int> breaks(size, -2);
    for (int i = 0; i < size; i++) {
        for (int j = -1; j < i; j++) {
            if ((j == -1 or breaks[j] != -2) and dict.count(str.substr(j+1, i - j))) {
                breaks[i] = j;
            }
        }
    }
    int i = 0;
    for (auto b: breaks) {
        cout << "b[" << i << "] = " << b << endl;
        i++; 
    }
    cout << endl;
    if (breaks[size] == -1) {
        cout << "Failed to do word break." << endl;
    } else {
        int i = size - 1;
        vector<string> strs;
        while (breaks[i] != -2) {
            if (i == -1) {
                break;
            }
            strs.push_back(str.substr(breaks[i]+1, i - breaks[i]));
            i = breaks[i];
        }
        for (auto s: strs) {
            cout << " " << s;
        }
        cout << endl;
    }
}

int main(int argc, char** argv)
{
    string s = "applepenapple";
    unordered_set<string> dict = {"apple", "pen"};
    word_break(s, dict);
    return 0;
}