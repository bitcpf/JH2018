#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

void printGrid(vector<vector<int>> & grid)
{
    for(int i = 0; i < grid.size(); i ++)
    {
        for(int j = 0; j < grid.at(i).size(); j ++)
        {
            cout << grid.at(i).at(j) << " ";
        }
        cout << endl;
    }

}

void bleedingBFS(vector<vector<int>> & grid, int x, int y, int ink)
{
    int m = grid.size();
    int n = grid.front().size();
    
    vector<vector<bool>> visited(m, vector<bool>(n,false)); 

    grid.at(x).at(y) = ink;
    visited.at(x).at(y) = true;

    queue<pair<int, int>> q;
    vector<pair<int,int>> shift;
    shift.push_back(make_pair(1,0));
    shift.push_back(make_pair(0,1));
    shift.push_back(make_pair(-1,0));
    shift.push_back(make_pair(0,-1));

    q.push(make_pair(x,y));

    while(!q.empty())
    {
        pair<int, int> cur = q.front();
        q.pop();
        
        for(auto s : shift)
        {
            int sx = cur.first + s.first;
            int sy = cur.second + s.second;
            if(!(sx < m && sy < n && sx >=0 && sy >= 0)) continue;

            if(visited.at(sx).at(sy)) continue;

            grid.at(sx).at(sy) = grid.at(cur.first).at(cur.second) - 1;
            visited.at(sx).at(sy) = true;

            q.push(make_pair(sx,sy));
        }
    }


    return;
}

struct Node
{
    Node(int ix, int iy) 
    {
        x = ix;
        y = iy;
        darkness = 0;
    }

    Node(int ix, int iy, int dark) 
    {
        x = ix;
        y = iy;
        darkness = dark;
    }

    int darkness;
    int x;
    int y;
};


struct nodeCmp
{
    // Max heap
    bool operator()(const Node * n1, const Node * n2)
    {
        return n1->darkness < n2->darkness;
    }
   
};
void bleedingDij(vector<vector<int>> & grid, int x, int y, int ink)
{
    int m = grid.size();
    int n = grid.front().size();
    
    vector<vector<bool>> visited(m, vector<bool>(n,false)); 

    grid.at(x).at(y) = ink;
    visited.at(x).at(y) = true;

    vector<pair<int,int>> shift;
    shift.push_back(make_pair(1,0));
    shift.push_back(make_pair(0,1));
    shift.push_back(make_pair(-1,0));
    shift.push_back(make_pair(0,-1));

    priority_queue<Node *, vector<Node *>, nodeCmp> pq;

    // test
    pq.push(new Node(1,2,1));
    pq.push(new Node(1,2,2));
    pq.push(new Node(1,2,4));
    pq.push(new Node(1,2,5));

    while(!pq.empty())
    {
        cout << "PQ test: " << pq.top()->darkness << endl;
        pq.pop();
    }





    Node * cur = new Node(x, y);
    cur->darkness = ink;
    pq.push(cur);

    while(!pq.empty())
    {
        cur = pq.top();
        cout << cur->x << " " << cur->y << " " << cur->darkness << endl;
        pq.pop();

        for(auto s : shift)
        {
            int sx = cur->x + s.first;
            int sy = cur->y + s.second;
            if(!(sx < m && sy < n && sx >=0 && sy >= 0)) continue;

            if(visited.at(sx).at(sy)) continue;

            int newDark = grid.at(cur->x).at(cur->y) - 1;
            grid.at(sx).at(sy) = max(newDark, grid.at(sx).at(sy));
            visited.at(sx).at(sy) = true;
    
            Node * adjnode = new Node(sx, sy);
            adjnode->darkness = grid.at(sx).at(sy);

            pq.push(adjnode);
        }
    }



    return;
}

int main(int argc, char** argv)
{
    ifstream input(argv[1]);
    vector<vector<int>> grid;
    string line;
    while(getline(input, line)) {
        istringstream is(line);
        string token;

        vector<int> row;
        while(std::getline(is, token, ' '))
        {
            row.push_back(stoi(token));
        }
        grid.push_back(row);

    }

    printGrid(grid);

    int x = stoi(argv[2]);
    int y = stoi(argv[3]);
    int ink = stoi(argv[4]);
    // bleedingBFS(grid,x,y,ink);
    bleedingDij(grid,x,y,ink);




    cout << " Result: " << endl;

    printGrid(grid);


    return 0;
}
