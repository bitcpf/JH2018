#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <boost/functional/hash.hpp>
#include <fstream>
#include <queue>
#include <deque>

using namespace std;

class Loc {
public:
    Loc(): x(INT_MAX), y(INT_MAX) {}
    Loc(int x_, int y_):
        x(x_), y(y_) {}
    Loc(const Loc& l, int sx, int sy):
        x(l.x + sx), y(l.y + sy) {}
    Loc(const Loc& l): x(l.x), y(l.y) {}
    int x;
    int y;
    bool operator==(const Loc& other) const {
        return other.x == x and other.y == y;
    }
};

namespace std
{
    template <>
    struct hash<Loc>
    {
        size_t operator()( const Loc& k ) const
        {
            using boost::hash_value;
            using boost::hash_combine;

            // Start with a hash value of 0    .
            std::size_t seed = 0;
            hash_combine(seed,hash_value(k.x));
            hash_combine(seed,hash_value(k.y));
            return seed;
        }
    };
}

struct Node {
    Node(const Loc& l): loc(l), flag(0) {}
    Loc loc;
    Node* prev = nullptr;
    unsigned flag;
};

const unsigned ID1 = 1u << 1;
const unsigned ID2 = 1u << 2;

void en(const Loc& loc)
{
    cout << "Enqueue: " << loc.x << ", " << loc.y << endl;
}

void get_path(const Loc& start, const Loc& end)
{
    int shift_array[8][2] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
                            {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};
    std::unordered_map<Loc, Node*> explored;
    std::queue<Node*> que;
    explored[start] = new Node(start);
    explored[start]->flag |= ID1;
    que.push(explored[start]);
    en(start);
    explored[end] = new Node(end);
    explored[end]->flag |= ID2;
    que.push(explored[end]);
    en(end);
    pair<Node*, Node*> result(nullptr, nullptr);
    while (!que.empty()) {
        Node* node = que.front();
        assert(node);
        que.pop();
        cout << "Dequeue: " << node->loc.x << ", " << node->loc.y << endl;
        unsigned flag = node->flag & (ID1 | ID2);
        for (auto shift: shift_array) {
            auto nloc = Loc(node->loc, shift[0], shift[1]);
            if (!explored.count(nloc)) {
                auto n_node = new Node(nloc);
                n_node->prev = node;
                n_node->flag |= flag;
                explored[nloc] = n_node;
                que.push(n_node);
                en(nloc);
            } else {
                auto n_node = explored.at(nloc);
                if ((n_node->flag & flag) == flag) {
                    continue;
                } else if ((n_node->flag | flag) == (ID1 | ID2)) {
                    // Found
                    result.first = node;
                    result.second = n_node;
                    if (node->flag & ID2) {
                        std::swap(result.first, result.second);
                    }
                    break;              
                }
            }
        }
        if (result.first) {
            break;
        }
    }
    deque<Node*> finals;
    Node* n = result.first;
    while (n) {
        finals.push_front(n);
        n = n->prev;
    }
    n = result.second;
    while (n) {
        finals.push_back(n);
        n = n->prev;
    }
    for (auto node: finals) {
        cout << "(" << node->loc.x << ", " << node->loc.y << ")" << endl;
    }
}

int main(int argc, char** argv)
{
    ifstream input(argv[1]);
    Loc start, end;
    input >> start.x >> start.y >> end.x >> end.y;
    input.close();
    get_path(start, end);
    return 0;
}