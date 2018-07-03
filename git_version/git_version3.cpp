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
        result.push_back(commit);
        visited[commit->id] = true;
        for (auto child: commit->children) {
            if (visited[child->id]) {
                continue;
            }
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

const unsigned ID1 = 1u << 1;
const unsigned ID2 = 1u << 2;

Commit* find_lca(Commit* c1, Commit* c2, int max_id)
{
    queue<Commit*> q;
    vector<unsigned> flags(max_id + 1, 0);
    flags[c1->id] |= ID1;
    flags[c2->id] |= ID2;
    Commit* c = nullptr;
    q.push(c1);
    q.push(c2);
    cout << "Enque: " << c1->id << endl;
    cout << "Enque: " << c2->id << endl;
    while (!q.empty()) {
        c = q.front();
        assert(c);
        q.pop();
        unsigned flag = flags[c->id] & (ID1 | ID2);
        if (flag == (ID1 | ID2)) {
            return c;
        }
        for (auto parent: c->parents) {
            if ((flags[parent->id] & flag) == flag) {
                continue;
            }
            flags[parent->id] |= flag;
            q.push(parent);
            cout << "Enque: " << parent->id << endl;
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
    auto lca = find_lca(all[atoi(argv[2])], all[atoi(argv[3])], max_id);
    //auto lca = find_lca(all[atoi(argv[4])], all[atoi(argv[8])], max_id);
    cout << "LCA is " << lca->id << endl;
    return 0;
}
