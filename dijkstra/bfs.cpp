#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <boost/functional/hash.hpp>
#include <fstream>
#include <queue>

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
    Node(const Loc& l): loc(l) {}
    Loc loc;
    Node* prev = nullptr;
};

void get_path(const Loc& start, const Loc& end)
{
    int shift_array[8][2] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
                            {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};
    std::unordered_map<Loc, Node*> explored;
    explored[start] = new Node(start);
    std::queue<Node*> que;
    que.push(explored[start]);
    Node* final_node = nullptr;
    while (!que.empty()) {
        auto node = que.front();
        que.pop();
        auto loc = node->loc;
        for (auto shift: shift_array) {
            auto nloc = Loc(loc, shift[0], shift[1]);
            if (nloc == end) {
                final_node = new Node(nloc);
                final_node->prev = node;
                break;
            }
            if (!explored.count(nloc)) {
                auto n_node = new Node(nloc);
                n_node->prev = node;
                explored[nloc] = n_node;
                que.push(n_node);
            }
        }
        if (final_node) {
            break;
        }
    }

    while (final_node) {
        cout << "(" << final_node->loc.x << ", " << final_node->loc.y << ")" << endl;
        final_node = final_node->prev;
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