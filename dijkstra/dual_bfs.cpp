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
    Node(const Loc& l, bool s): loc(l), start(s) {}
    Loc loc;
    Node* prev = nullptr;
    bool start;
};

bool loop(std::queue<Node*>& que, std::unordered_map<Loc, Node*>& explored, const Loc& end,
             bool start, std::pair<Node*, Node*>& result)
{
    int shift_array[8][2] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
                            {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};
    auto node = que.front();
    que.pop();
    auto loc = node->loc;
    for (auto shift: shift_array) {
        auto nloc = Loc(loc, shift[0], shift[1]);
        if (nloc == end) {
            auto final_node = new Node(nloc, start);
            final_node->prev = node;
            result.first = final_node;
            result.second = nullptr;
            if (!start) {
                swap(result.first, result.second);
            }
            return true;
        }
        if (!explored.count(nloc)) {
            auto n_node = new Node(nloc, start);
            n_node->prev = node;
            explored[nloc] = n_node;
            que.push(n_node);
        } else {
            if (explored.at(nloc)->start != node->start) {
                result.first = explored.at(nloc);
                result.second = node;
                if (node->start) {
                    std::swap(result.first, result.second);
                }
                return true;
            }
        }
    }
    return false;
}

void get_path(const Loc& start, const Loc& end)
{
    std::unordered_map<Loc, Node*> explored;
    explored[start] = new Node(start, true);
    std::queue<Node*> que1;
    que1.push(explored[start]);
    explored[end] = new Node(end, false);
    std::queue<Node*> que2;
    que2.push(explored[end]);
    pair<Node*, Node*> result(nullptr, nullptr);
    while (!que1.empty() or !que2.empty()) {
        if (!que1.empty()) {
            if (loop(que1, explored, end, true, result)) {
                break;
            }
        }
        if (!que2.empty()) {
            if (loop(que2, explored, start, false, result)) {
                break;
            }
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