#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <queue>
#include <map>
#include <set>

using namespace std;

struct commit
{
    int id;
    int level;
    vector<int> children;
    vector<int> parents;
};


    vector<int>
bfs_commit(unordered_map<int,commit> & all, int root)
{
    vector<int> rst;
    queue<commit> q;
    set<int> visited;
    q.push(all[root]);
    all[root].level = 0;
    while(!q.empty())
    {
        commit cur = q.front();
        rst.push_back(cur.id);
        q.pop();
        for(auto c:all[cur.id].children)
        {
            if(visited.find(c) == visited.end()) 
            {
                visited.insert(c);
                all[c].level = (cur.level + 1);
                q.push(all[c]);
            }
        }
    }
    return rst;
}

void find_path(unordered_map<int, commit> & all, int last, vector<int> & path)
{
    path.push_back(last);
    while(all[last].parents.size())
    {
        path.push_back(all[last].parents.front());
        last = all[last].parents.front();
    }

}

int find_lca(int a, int b, unordered_map<int, commit> & all)
{
    vector<int> patha;
    vector<int> pathb;
    find_path(all, a, patha);
    find_path(all, b, pathb);


    std::reverse(patha.begin(), patha.end());
    std::reverse(pathb.begin(), pathb.end());

    for(int i = 0 ; i < min(patha.size(), pathb.size()); i ++)
    {
        if(patha.at(i)!= pathb.at(i)) return patha.at(i-1);
    }

    if(patha.size() > pathb.size()) return pathb.back();
    return patha.back();

    return -1;

}

int find_lca2(int a, int b, unordered_map<int, commit> & all)
{
    queue<int> q;
    q.push(a);
    map<int, int> ma;
    ma[a] = all[a].level;
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        vector<int> parents = all[cur].parents;
        for(int i = 0; i < parents.size(); i ++)
        {
            if(ma.find(parents.at(i)) != ma.end()) continue;
            ma[parents.at(i)] = all[parents.at(i)].level;
            cout << "Ck map: " << parents.at(i) << " " << ma[parents.at(i)] << endl;
            q.push(parents.at(i));
        }
    }

    int level = INT_MIN;
    int rst = 0;
    q.push(b);
    if(ma.find(b) != ma.end()) return b;
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        vector<int> parents = all[cur].parents;

        for(int i = 0; i < parents.size(); i ++)
        {
            if(all[parents.at(i)].level > level)
            {
                rst = parents.at(i);
                level = all[parents.at(i)].level;
                q.push(parents.at(i));
            }
        }
    }

    return rst;

}

int find_lca3(int a, int b, unordered_map<int, commit> & all)
{
    queue<int> q;
    unordered_map<int, int> visited;
    q.push(a);
    visited[a] = 1;
    q.push(b);
    visited[b] = 2;

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        vector<int> parents = all[cur].parents;

        for(int i = 0; i < parents.size(); i ++)
        {
            if((visited.find(parents.at(i)) != visited.end()) && (visited[parents.at(i)] != visited[cur]))
            {
                return parents.at(i);
            }
            q.push(parents.at(i));
            visited[parents.at(i)] = visited[cur];
        }

    }

    return 0;

}


int main()
{
    unordered_map<int, commit> all;
    // input is parent to child
    ifstream input("input.txt");

    map<int,int> indegree;
    int child_id, parent_id;
    // Need to find root here
    while (input >> parent_id >> child_id) {
        all[parent_id].id = parent_id;
        all[child_id].id = child_id;
        all[parent_id].children.push_back(child_id);
        all[child_id].parents.push_back(parent_id);
        indegree[parent_id];
        indegree[child_id] ++;
    }

    input.close();
    int root = indegree.begin()->first;
    cout << "Initialization done." << endl;
    cout << "Root is: " << root << " " << endl;
    auto everything = bfs_commit(all, root);
    for (auto c: everything) {
        cout << c << " " << all[c].level << endl;
    }

    auto lca = find_lca3(8, 3, all);
    cout << "LCA is " << lca << endl;

    return 0;
}
