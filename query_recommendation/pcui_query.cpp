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
        pair<string, int> get_recommendation(string & user, string & word)
        {
            // If the first time user query
            if(!m_wordToUsersMap.count(word))
            {
                m_wordToUsersMap[word].insert(user);
                m_userToWordsMap[user].insert(word);

                return make_pair("", 0);
            }


            unordered_set<string> userHasWord = m_wordToUsersMap[word];
            unordered_map<string, int> wordFreq;

            int maxFreq = 0;
            string maxWord = "";
            for(auto u: userHasWord)
            {
                // Exclude self
                if(u == user) continue;
                unordered_set<string> userQuery = m_userToWordsMap[u];
                for(auto w: userQuery)
                {
                    // Exclude self
                    if(w == word) continue;
                    wordFreq[w] ++;
                    if(maxFreq < wordFreq[w])
                    {
                        maxFreq = wordFreq[w];
                        maxWord = w;
                    }
                }

            }

            // If someone has query the word
            m_wordToUsersMap[word].insert(user);
            m_userToWordsMap[user].insert(word);
            return make_pair(maxWord,maxFreq);

        }


    private:
        unordered_map<string, unordered_set<string>> m_userToWordsMap;
        unordered_map<string, unordered_set<string>> m_wordToUsersMap;
};


class QueryRecommendation2
{

    public:
        pair<string, int> get_recommendation(string & user, string & word)
        {
            // If the first time user query
            if(m_userToWordMap.find(user) == m_userToWordMap.end())
            {
                m_userToWordMap[user].insert(word);
            }

            // Get word recomendation
            unordered_map<string, int> w2wFreq = m_wordToWordFreqMap[word];
            int maxFreq = 0;
            string maxWord = "";
            for(auto item : w2wFreq)
            {
                if(maxFreq < item.second)
                {
                    maxFreq = item.second;
                    maxWord = item.first;
                }

            }

            // If user has query before, but the word is the first time search
            if(m_userToWordMap[user].find(word) == m_userToWordMap[user].end())
            {
                // If the user has not query the word before, update the word to word score
                unordered_set<string> userWord = m_userToWordMap[user];
                for(auto w2 : userWord)
                {
                    if(w2 == word) continue;
                    m_wordToWordFreqMap[word][w2] ++;
                    m_wordToWordFreqMap[w2][word] ++;
                }
                
            }

            // Insert word to user queried set
            m_userToWordMap[user].insert(word);

            return make_pair(maxWord, maxFreq);        



        }



    private:
        unordered_map<string, unordered_set<string>> m_userToWordMap;
        unordered_map<string, unordered_map<string, int>> m_wordToWordFreqMap;
};


int main(int argc, char** argv)
{
    ifstream input(argv[1]);
    vector<pair<string, string>> inputs;
    string line;
    QueryRecommendation2 qr;
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
