#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>

using namespace std;

struct Interval {
    Interval(int s, int e):
        start(s), end(e) {}
    int start;
    int end;
};

struct Cmp {
    bool operator()(const Interval& i1, const Interval& i2) const {
        return i1.end + 1 < i2.start;
    }
};

void summary_range2(const vector<int>& nums)
{
    Cmp cmp;
    set<Interval, Cmp> intervals(cmp);
    for (auto num: nums) {
        Interval interval(num, num);
        auto iter = intervals.lower_bound(interval);
        if (iter != intervals.end()) {
            if (interval.start >= iter->start) {
                interval.start = iter->start;
                interval.end = max(interval.end, iter->end);
                auto hehe = iter;
                auto iter2 = ++hehe;
                intervals.erase(iter);
                if (iter2 != intervals.end() and interval.end + 1 == iter2->start) {
                    interval.end = iter2->end;
                    intervals.erase(iter2);
                }
            }
        }
        intervals.insert(interval);
    }
    for (const auto& interval: intervals) {
        if (interval.start == interval.end) {
            cout << " " << interval.start;
        } else {
            cout << " " << interval.start << "->" << interval.end;
        }
    }
    cout << endl;
}

void summary_range(const vector<int>& nums)
{
    vector<Interval> intervals;
    auto cmp =[](const Interval& i1, const Interval& i2) {
        return i1.end + 1 < i2.start;
    };
    for (auto num: nums) {
        Interval interval(num, num);
        auto iter = lower_bound(intervals.begin(), intervals.end(), interval, cmp);
        if (iter != intervals.end()) {
            if (interval.start >= iter->start) {
                interval.start = iter->start;
                interval.end = max(interval.end, iter->end);
                auto iter2 = iter + 1;
                if (iter2 != intervals.end() and interval.end + 1 == iter2->start) {
                    interval.end = iter2->end;
                    intervals.erase(iter2);
                }
                *iter = interval;
                continue;
            }
        } else {
            iter = intervals.begin();
        }
        intervals.insert(iter, interval);
    }
    for (const auto& interval: intervals) {
        if (interval.start == interval.end) {
            cout << " " << interval.start;
        } else {
            cout << " " << interval.start << "->" << interval.end;
        }
    }
    cout << endl;
}

int main(int argc, char** argv)
{
    ifstream input(argv[1]);
    string line;
    while (getline(input, line)) {
        int i;
        istringstream is(line);
        vector<int> nums;
        while (is >> i) {
            nums.push_back(i);
        }
        summary_range(nums);
        summary_range2(nums);
    }
    input.close();
    return 0;
}