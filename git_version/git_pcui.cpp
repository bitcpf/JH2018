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
        cout << c << endl;
    }

    auto lca = find_lca(5, 9, all);
    cout << "LCA is " << lca << endl;

    return 0;
}
