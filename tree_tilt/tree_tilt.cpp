#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TreeNode {
    TreeNode(int cost_, int children_num):
        children(children_num, nullptr),
        cost(cost_) {}

    void find_min_cost(vector<int>* costs) {
        vector<int> cur_costs;
        int min_cost = INT_MAX;
        cur_costs.push_back(cost);
        find_min_cost_helper_(cost, &min_cost, &cur_costs, costs);
    }

    vector<TreeNode*> children;
    int cost = 0;
private:
    void find_min_cost_helper_(int total_cost, int* min_cost, vector<int>* cur_costs, vector<int>* result) {
        if (children.empty()) {
            if (total_cost < *min_cost) {
                *result = *cur_costs;
                *min_cost = total_cost;
            }
        } else {
            if (total_cost > *min_cost) {
                cout << "hehe" << endl;
                return;
            }
            for (auto child: children) {
                cur_costs->push_back(child->cost);
                child->find_min_cost_helper_(total_cost + child->cost, min_cost, cur_costs, result);
                cur_costs->pop_back();    
            }
        }
    }
};

int main(int argc, char** argv)
{
    vector<int> result;
    TreeNode *root = new TreeNode(1, 2);
    root->children[0] = new TreeNode(2, 2);
    root->children[1] = new TreeNode(7, 3);
    root->children[0]->children[0] = new TreeNode(4, 0);
    root->children[0]->children[1] = new TreeNode(2, 0);
    root->children[1]->children[0] = new TreeNode(3, 0);
    root->children[1]->children[1] = new TreeNode(2, 0);
    root->children[1]->children[2] = new TreeNode(0, 0);
    root->find_min_cost(&result);
    for (auto cost: result) {
        cout << cost << endl;
    }
    return 0;
}