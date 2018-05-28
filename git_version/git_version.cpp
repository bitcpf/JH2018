#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <queue>

using namespace std;

struct Commit {
    Commit() {
        id = 0;
    }
    int id;
    std::vector<Commit*> parents;
    std::vector<Commit*> children; 
};

vector<Commit*> find_all_commit(unordered_map<int, Commit*> commits, int max_id)
{
    Commit* head = nullptr;
    {
        vector<bool> visited(max_id + 1, false);
        vector<bool> root(max_id + 1, true);
        for (auto& cp: commits) {
            int id = cp.first;
            if (cp.second->parents.size()) {
                root[id] = false;
            }
        }
        for (auto& cp: commits) {
            if (root[cp.first]) {
                head = cp.second;
                break;
            }
        }
    }
    vector<Commit*> result;
    queue<Commit*> que;
    cout << "Root is " << head->id << endl;
    vector<bool> visited(max_id + 1, false);
    que.push(head);
    while (!que.empty()) {
        Commit* commit = que.front();
        que.pop();
        if (visited[commit->id]) {
            continue;
        }
        result.push_back(commit);
        visited[commit->id] = true;
        for (auto child: commit->children) {
            que.push(child);
        }
    }
    return result;
}

void bfs(Commit* c, int max_id, vector<Commit*>* result)
{
    queue<Commit*> que;
    vector<bool> visited(max_id + 1, false);
    que.push(c);
    while (!que.empty()) {
        Commit* commit = que.front();
        que.pop();
        if (visited[commit->id]) {
            continue;
        }
        result->push_back(commit);
        visited[commit->id] = true;
        for (auto parent: commit->parents) {
            que.push(parent);
        }
    }
}

Commit* find_lca(Commit* c1, Commit* c2, int max_id)
{
    vector<Commit*> c1_roots;
    vector<Commit*> c2_roots;
    bfs(c1, max_id, &c1_roots);
    cout << "BFS1:";
    for (auto c: c1_roots) {
        cout << " " << c->id;
    }
    cout << endl;
    cout << "BFS2:";
    bfs(c2, max_id, &c2_roots);
    for (auto c: c2_roots) {
        cout << " " << c->id;
    }
    cout << endl;
    for (auto iter1 = c1_roots.rbegin(), iter2 = c2_roots.rbegin();
        iter1 != c1_roots.rend() and iter2 != c2_roots.rend(); iter1++, iter2++) {
        if (*iter1 != *iter2) {
            return *(iter1-1);
        }
    }
    return nullptr;
}

Commit* find_or_add_commit(int i, unordered_map<int, Commit*>* all, int* max_id)
{
    if (!all->count(i)) {
        auto commit = new Commit;
        commit->id = i;
        (*all)[i] = commit;
        if (i > *max_id) {
            *max_id = i;
        }
    }
    return all->at(i);
}

int main()
{
    unordered_map<int, Commit*> all;
    ifstream input("input.txt");
    int child_id, parent_id;
    int max_id = INT_MIN;
    while (input >> parent_id >> child_id) {
        auto child = find_or_add_commit(child_id, &all, &max_id);
        auto parent = find_or_add_commit(parent_id, &all, &max_id);
        child->parents.push_back(parent);
        parent->children.push_back(child);
    }
    input.close();
    cout << "Initialization done." << endl;
    auto everything = find_all_commit(all, max_id);
    for (auto c: everything) {
        cout << c->id << endl;
    }
    auto lca = find_lca(all[3], all[4], max_id);
    cout << "LCA is " << lca->id << endl;
    return 0;
}