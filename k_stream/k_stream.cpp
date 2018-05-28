#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>
#include <deque>
#include <queue>
#include <unordered_set>

using namespace std;

class Stream {
public:
    Stream(const deque<int>& v):
        nums_(v) {}
    
    bool has_next() const {
        return nums_.size() > 0;
    }

    int peek() const {
        return nums_.front();
    }
    int next() {
        int res = nums_.front();
        nums_.pop_front();
        return res;
    }
private:
    deque<int> nums_;
};

struct A {
    A(int n, int i):
        num(n), index(i) {}
    int num;
    int index;
};

struct CmpA {
    bool operator()(const A& a1, const A& a2) {
        return a1.num > a2.num;
    }
};

vector<int> merge(vector<Stream>& streams, int target_num)
{
    vector<int> result;
    int size = streams.size();
    CmpA cmp;
    priority_queue<A, vector<A>, CmpA> q(cmp);
    for (int i = 0; i < size; i++) {
        if (streams[i].has_next()) {
            q.push(A(streams[i].next(), i));
        }
    }

    int freq = 0;
    int prev = INT_MAX;
    while (!q.empty()) {
        A a = q.top();
        cout << "a.num = " << a.num << " a.index = " << a.index << endl;
        if (a.num != prev) {
            prev = a.num;
            freq = 1;
        } else {
            freq++;
        }
        if (freq == target_num) {
            result.push_back(prev);
        }
        auto &s = streams[a.index];
        q.pop();
        while (s.has_next()) {
            int num = s.next();
            if (num == prev) {
                continue;
            }
            q.push(A(num, a.index));
            break;
        }
    }
    return result;
}

int main(int argc, char** argv)
{
    ifstream input(argv[1]);
    string line;
    vector<Stream> streams;
    while (getline(input, line)) {
        int i;
        istringstream is(line);
        deque<int> nums;
        while (is >> i) {
            nums.push_back(i);
        }
        streams.push_back(Stream(nums));
    }

    auto result = merge(streams, atoi(argv[2]));
    for (auto a: result) {
        cout << " " << a;
    }
    cout << endl;
    return 0;
}