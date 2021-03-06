#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <queue>
#include <assert.h>

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

Commit* loop(queue<Commit*>& q, vector<int>& visited, int id1, int id2)
{
    Commit* c = q.front();
    assert(c);
    q.pop();
    if (visited[c->id] == id2) {
        return c;
    }
    visited[c->id] = id1;
    for (auto parent: c->parents) {
        if (visited[parent->id] == 0) {
            visited[parent->id] = id1;
            q.push(parent);
        } else if (visited[parent->id] == id2) {
            return parent;
        }
    }
    return nullptr;
}

Commit* find_lca(Commit* c1, Commit* c2, int max_id)
{
    queue<Commit*> q1, q2;
    vector<int> visited(max_id, 0);
    visited[c1->id] = 1;
    visited[c2->id] = 2;
    Commit* c = nullptr;
    q1.push(c1);
    q2.push(c2);
    while (!q1.empty() or !q2.empty()) {
        if (!q1.empty()) {
            c = loop(q1, visited, 1, 2);
            if (c) {
                return c;
            }
        }
        if (!q2.empty()) {
            c = loop(q2, visited, 2, 1);
            if (c) {
                return c;
            }
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

int main(int argc, char** argv)
{
    unordered_map<int, Commit*> all;
    ifstream input(argv[1]);
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
    auto lca = find_lca(all[atoi(argv[5])], all[atoi(argv[8])], max_id);
    cout << "LCA is " << lca->id << endl;
    return 0;
}
