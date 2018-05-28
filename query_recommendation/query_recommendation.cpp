#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class QueryRecommendation
{
public:
    QueryRecommendation() {}

    ~QueryRecommendation() {}

    pair<string, int> get_recommendation(const string& user, const string& word) {
        if (!word_users_.count(word)) {
            user_words_[user].insert(word);
            word_users_[word].insert(user);
            return make_pair(string(""), 0);
        }
        const auto& users = word_users_.at(word);
        unordered_map<string, int> word_freq;
        int max_freq = 0;
        string rec_word;
        for (const auto& u: users) {
            if (!user_words_.count(u)) {
                continue;
            }
            for (const auto& w: user_words_.at(u)) {
                // Ignore the word itself, you don't want to recommend the same word
                if (w == word) {
                    continue;
                }
                int freq = ++word_freq[w];
                if (freq > max_freq) {
                    max_freq = freq;
                    rec_word = w;
                }
            }
        }
        user_words_[user].insert(word);
        word_users_[word].insert(user);
        return make_pair(rec_word, max_freq);
    }

private:
    // User -> all the words user serarched
    unordered_map<string, unordered_set<string>> user_words_;
    // Word -> all the user who searched this word
    unordered_map<string, unordered_set<string>> word_users_;
};


int main(int argc, char** argv)
{
    ifstream input(argv[1]);
    vector<pair<string, string>> inputs;
    string line;
    QueryRecommendation qr;
    while(getline(input, line)) {
        istringstream is(line);
        string user;
        string word;
        is >> user >> word;
        auto result = qr.get_recommendation(user, word);
        cout << result.second << " " << result.first << endl;
    }
    return 0;
}