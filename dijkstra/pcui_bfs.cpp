#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <boost/functional/hash.hpp>
#include <fstream>
#include <queue>

using namespace std;

class Loc
{
    public:
        int x,y;
        Loc(): x(INT_MAX),y(INT_MAX) {}
        Loc(int x, int y): x(x), y(y) {}
        Loc(Loc & l1, Loc & l2)
        {
            x = l1.x + l2.x;
            y = l1.y + l2.y;
        }

        bool operator == (const Loc & l1) const
        {
            return l1.x == x && l1.y == y;
        }
};

namespace std
{
    template <>
        struct hash<Loc> {
            size_t operator()(const Loc & loc) const
            {
                using boost::hash_value;
                using boost::hash_combine;

                size_t seed  = 0;
                hash_combine(seed, hash_value(loc.x));
                hash_combine(seed, hash_value(loc.y));

                return seed;
            }
        };
}

struct Node
{
    Node(const Loc & l):loc(l) {}
    Loc loc;

    Node * prev = nullptr;
};


void get_path(Loc & start, Loc & end)
{
    int shift_arr[8][2] = {{1,2}, {-1,2}, {1,-2}, {-1,-2},
                           {2,1}, {-2,1}, {2,-1}, {-2,-1}};
    
    unordered_map<Loc, Node*> visited;
    queue<Node*> q;
    Node * cur = new Node(start);
    q.push(cur);
    visited[start] = cur;

    cout << start.x << " " << start.y << endl;

    bool endFlag = false;
    while(!q.empty())
    {
        cur = q.front();
        q.pop();
        for(auto shift: shift_arr)
        {
            Loc move = Loc(shift[0], shift[1]);
            Loc shiftloc = Loc(move, cur->loc);
            if(!visited.count(shiftloc))
            {
                visited[shiftloc] = new Node(shiftloc);
                visited[shiftloc]->prev = cur;
                if(shiftloc == end)
                {
                    endFlag = true;
                    break;
                }
                q.push(visited[shiftloc]);
            }
        }
        if(endFlag)
        {
            cur = visited[end];
            while(visited[cur->loc] != visited[start])
            {
                cout << (cur->loc).x << " " << (cur->loc).y << endl;;
                cur = cur->prev;
            }
            break;
        }

    }
    
    return;
}


int main(int argc, char** argv)
{
    ifstream input(argv[1]);
    int x1, x2, y1, y2;
    input >> x1 >> y1 >> x2 >> y2;
    Loc start = Loc(x1, y1);
    Loc end = Loc(x2, y2);
    input.close();
    get_path(start, end);
    return 0;
}
