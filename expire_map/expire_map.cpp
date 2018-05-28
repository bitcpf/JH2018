#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <deque>

using namespace std;

struct Key {
    Key(int a, int b):
    key(a),
    expire_time(b) {}
    int key;
    int expire_time;

    bool operator==(const Key& other) const {
        return key == other.key;
    }
};

namespace std {

  template <>
  struct hash<Key>
  {
    std::size_t operator()(const Key& k) const
    {
      using std::size_t;
      using std::hash;

      return hash<int>()(k.key);
    }
  };

}
struct KeyTimeCmp {
    bool operator()(const Key& k1, const Key& k2) const {
        return k1.expire_time < k2.expire_time;
    }
};

struct KeyCmp {
    bool operator()(const Key& k1, const Key& k2) const {
        return k1.key < k2.key;
    }
};

class ExpireMap {
public:
    ExpireMap(int duration):
        duration_(duration),
        queue_(KeyTimeCmp())
        {}
    
    void put(int k, const string& v, int time) {
        cleanup(time);
        Key key(k, time + duration_);
        if (map_.count(key)) {
            map_.erase(key);
        }
        map_[key] = v;
        queue_.push(key);
    }

    void cleanup(int current_time) {
        while (!queue_.empty()) {
            const auto& key = queue_.top();
            if (key.expire_time <= current_time) {
                map_.erase(key);
                queue_.pop();
            } else {
                break;
            }
        }
    }

    std::string get(int k, int time) {
        cleanup(time);
        Key key(k, time);
        if (map_.count(key)) {
            return map_[key];
        }
        return "";
    }
private:
    int duration_;
    // Hash map from key to index in priority queue's internal vector
    std::unordered_map<Key, string> map_;
    std::priority_queue<Key, std::vector<Key>, KeyTimeCmp> queue_;
};

int main(int argc, char** argv)
{
    ExpireMap map(10);
    map.put(1, "hehe1", 0);
    map.put(3, "hehe3", 0);
    map.put(5, "hehe5", 0);
    map.put(3, "hehe4", 5);
    cout << "Get(1, time = 2) = " << map.get(1, 2) << endl;
    cout << "Get(1, time = 11) = " << map.get(1, 11) << endl;
    cout << "Get(3, time = 12) = " << map.get(3, 12) << endl;
    return 0;
}