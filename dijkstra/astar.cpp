#include <iostream>
#include <string>
#include <vector>
#include <boost/heap/priority_queue.hpp>
#include <boost/heap/fibonacci_heap.hpp>
#include <unordered_map>
#include <map>
#include <boost/functional/hash.hpp>
#include <fstream>

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

class Node;
class NodeCmp;

struct NodeCmp {
    bool operator()(const Node* n1, const Node* n2) const;
};

typedef boost::heap::fibonacci_heap<Node*, boost::heap::compare<NodeCmp>> Queue;

struct Node {
    Node(const Loc& l): loc(l) {}

    Queue::handle_type handle;
    Loc loc;
    Node* prev = nullptr;
    int dist = INT_MAX;
    int est = INT_MAX;
};

bool NodeCmp::operator()(const Node* n1, const Node* n2) const
{
    return n1->est > n2->est;
}

class Graph {
public:
    bool is_visited(const Loc& n) {
        return v_.count(n);
    }
    
    Node* add_node(const Loc& loc) {
        Node* n = new Node(loc);
        v_[loc] = n;
        return n;
    }
    
    Node* node(const Loc& loc) {
        return v_[loc];
    }
private:
    /// Visited vertexes (locations)
    std::unordered_map<Loc, Node*> v_;
};

int apox(const Loc&l1, const Loc& l2)
{
    return max(abs(l1.x - l2.x)/2 , abs(l1.y-l2.y)/2);
}

void get_path(const Loc& start, const Loc& end)
{
    int shift_array[8][2] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
                     {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};
    Graph g;
    Node* node = g.add_node(start);
    node->dist = 0;
    node->est = apox(start, end);
    Queue pq;
    node->handle = pq.push(node);
    Node* final_node = nullptr;
    int loop_num = 0;
    while (!pq.empty()) {
        loop_num++;
        Node* node = pq.top();
        pq.pop();
        for (auto shift: shift_array) {
            Loc loc(node->loc, shift[0], shift[1]);
            if (loc == end) {
                final_node = g.add_node(loc);
                final_node->prev = node;
                break;
            }
            Node* neighbor_node = nullptr;
            if (!g.is_visited(loc)) {
                neighbor_node = g.add_node(loc);
                neighbor_node->handle = pq.push(neighbor_node);
            } else {
                neighbor_node = g.node(loc);
            }
            if (node->dist + 1 < neighbor_node->dist) {
                neighbor_node->dist = node->dist + 1;
                neighbor_node->est = neighbor_node->dist + apox(loc, end);
                neighbor_node->prev = node;
                pq.update(neighbor_node->handle);
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
    cout << "Loop num = " << loop_num << endl;
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