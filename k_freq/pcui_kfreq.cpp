#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

struct NumFreq {
    int num = 0;
    int freq = 0;
};

vector<int> get_freq(const vector<int>& array, int k)
{
    unordered_map<int, int> m;
    for(auto num : array)
    {
        m[num] ++;
    }

    vector<int> bucket(array.size(),0);
    for(unordered_map<int, int>::iterator itr = m.begin(); itr != m.end(); itr ++)
    {
        bucket.at(itr->second) = itr->first;
    }

    vector<int> rst;
    for(int i = bucket.size()-1; i >= 0; i --)
    {
        if(bucket.at(i) > 0) rst.push_back(bucket.at(i));
    }

    return rst;

}

vector<int> get_freq2(const vector<int>& array, int k)
{
    unordered_map<int,int> m;
    for(auto num: array)
    {
        m[num] ++;
    }
    priority_queue<pair<int, int>> q;
    vector<int> rst;
    for(auto itr : m)
    {
        q.push(make_pair(itr.second, itr.first));

    }
    for(int i =0; i < k; i ++)
    {
        rst.push_back(q.top().second);
        q.pop();
    }
    return rst;
}


int main(int argc, char** argv)
{
    vector<int> input = {5, 4, 1, 4, 5, 6, 6, 6};
    auto res = get_freq(input, 3);
    for (auto n: res) {
        cout << n << " ";
    }
    cout << endl;
    return 0;
}
