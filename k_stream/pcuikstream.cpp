#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <deque>
#include <queue>
#include <unordered_set>

using namespace std;


struct cmp
{
    bool operator()(const pair<int,int> & p1, const pair<int,int> & p2)
    {
        return p1.first > p2.first;
    }
};


vector<int> merge(vector<vector<int>>& streams, int target_num)
{
    vector<int> rst;
    cout << " Merge " << endl;

    int nStream = streams.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>,cmp> q;
    for(int i = 0; i <nStream; i ++)
    {
        q.push(make_pair(streams.at(i).front(),i));
        cout << "First: " << streams.at(i).front() << " " << i << endl;
    }

    vector<int> pos(nStream,1);
    int pre = q.top().first - 1;
    int freq;
    while(!q.empty())
    {
        pair<int, int> cur = q.top();
        q.pop();
        int ns = cur.second;
        cout << cur.first << " in " << ns << endl;

        if(cur.first != pre) 
        {
            freq = 1;
            pre = cur.first;
        }
        else
            freq ++;

        if(freq == target_num) rst.push_back(cur.first);
        
        //if(!rst.size()) rst.push_back(cur.first);
        //else if(rst.size() > 0 && cur.first != rst.back()) rst.push_back(cur.first);
        if(pos.at(ns) < streams.at(ns).size())
        {
            q.push(make_pair(streams.at(ns).at(pos.at(ns)),ns));
            pos.at(ns) ++;
        }
    }


    return rst;
}

int main(int argc, char** argv)
{
    ifstream input(argv[1]);
    string line;
    vector<vector<int>> streams;
    while (getline(input, line)) {
        int i;
        istringstream is(line);
        vector<int> nums;
        while (is >> i) {
            nums.push_back(i);
        }
        streams.push_back(nums);
    }

    cout << "Done input" << endl;
    auto result = merge(streams, atoi(argv[2]));
    cout << "Done Merge" << endl;
    for (auto a: result) {
        cout << " " << a;
    }
    cout << endl;
    return 0;
}
