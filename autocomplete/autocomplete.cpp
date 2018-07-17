#include <iostream>
#include <vector>


using namespace std;


#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

class TrieNode
{
    public:

        bool isWord;
        vector<TrieNode *> children;
        

        TrieNode * newNode()
        {
            struct TrieNode * pNode = new TrieNode();
            pNode->isWord = false;
            children.resize(ALPHABET_SIZE);
            for(int i = 0 ;i < ALPHABET_SIZE; i ++)
            {
                pNode->children[i] = NULL;
            }
            return pNode;
        }

        void insert(TreeNode * rooot, const string & key)
        {
            int length = key.size();
            TrieNode * pCrawl = root;
            for(int level = 0; level < length; level ++)
            {
                int idx = CHAR_TOINDEX(key.at(level));
                if(!pCrawl->children[idx])
                {
                    pCrawl->children[idx] = newNode();

                }
                pCrawl = pCrawl->children[idx];
            }

            // Make the trie as end of word
            pCrawl->isWord = true;
        }

        bool search(TrieNode * root, const string & key)
        {
            int length = key.legnth();

            TrieNode * pCraw; = root;
            for(int level = 0; level < length; level ++)
            {
                int idx = CHAR_TOINDEX(key.at(level);
                if(!pCrawl->children[idx]) return false;
                pCrawl = pCrawl->children[idx];
            }

            return (pCrawl != NULL && pCrawl->isWord);

        }

        bool isLastNode(TrieNode * root)
        {
            for(int i = 0; i < ALPHABET_SIZE; i++)
            {
                if(root->childrenp[i]) return false;
            }

            return true;
        }

};

void suggestionRec(TrieNode * root, string curPrefix)
{
    if(root->isWord)
    {
        cout << currPrefix << endl;
    }

    if(isLastNode(root)) return;

    for(int i = 0; i < ALPHABET_SIZE; i ++)
    {
        if(root->children[i])
    }
}





int main()
{




    return 0;

}
