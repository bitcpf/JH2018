#include<unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/functional/hash.hpp>
#include <fstream>
#include <queue>

using namespace std;

class Loc
{
    public:
    int x, y;
    Loc():x(INT_MAX), y(INT_MAX){}
    Loc(int x, int y):x(x), y(y) {}
    Loc(Loc & l1, Loc & l2)
    {
        x = l1.x + l2.x;
        y = l1.y + l2.y;
    }

    bool operator ==(const Loc & l1) const
    {
        return x == l1.x && y == l1.y;
    }

};

namespace std
{
    template<>
    struct hash<Loc>
    {
        size_t operator()(const Loc & loc) const
        {
            using boost::hash_value;
            using boost::hash_combine;

            size_t seed = 0;
            hash_combine(seed, loc.x);
            hash_combine(seed, loc.y);

            return seed;
        }
    };
}

struct Node
{
    Node(Loc & l):loc(l), dist(INT_MAX) {}
    Loc loc;
    int dist;


    Node * prev = nullptr;
};

class nodeCmp
{
    public:
        bool operator() (const Node *a, const Node * b)
        {
            return a->dist > b->dist;
        }
};

void
find_pathDijk(Loc & start, Loc & end)
{
    int shiftarr[8][2] = {{1,2}, {-1,2}, {1,-2}, {-1,-2}, {2,1}, {-2,1}, {2,-1}, {-2,-1}};

    priority_queue<Node*, std::vector<Node*>, nodeCmp> pq;
    unordered_map<Loc, Node*> visited;

    Node * cur = new Node(start);
    cur->dist = 0;
    pq.push(cur);
    visited[start] =  cur;
    
    bool isEnd = false;
    while(!pq.empty())
    {
        cur = pq.top();
        pq.pop();
        for(auto shift: shiftarr)
        {
            Loc shiftloc = Loc(shift[0], shift[1]);
            Loc adj = Loc(shiftloc, cur->loc);
            if(!visited.count(adj) || visited[adj]->dist > cur->dist+1)
            {
                Node * adjNode = new Node(adj);
                adjNode->dist = cur->dist + 1;
                adjNode->prev = cur;
                pq.push(adjNode);
                visited[adj] = adjNode;

                if(adj == end)
                {
                    isEnd = true;
                    cur = adjNode;
                    break;
                }
            }
        }
        if(isEnd)
        {
            cout << "Path: " << endl;
            while(visited[start] != visited[cur->loc])
            {
                cout << cur->loc.x << " " << cur->loc.y << endl;
                cur = cur->prev;
            }
            break;
        }
    }
}

int main(int argc, char ** argv)
{
    ifstream input(argv[1]);
    int x1, x2, y1, y2;
    input >> x1 >> y1 >> x2 >> y2;
    Loc start = Loc(x1, y1);
    Loc end = Loc(x2, y2);

    input.close();

    find_pathDijk(start, end);

}
