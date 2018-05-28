#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TreeNode {
    TreeNode(int cost_):
        cost(cost_) {}

    int get_tree_tilt() {
        int total_tilt = 0;
        get_tilt_helper_(&total_tilt);
        return total_tilt;
    }

    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    int cost = 0;
private:
    int get_tilt_helper_(int *total_tilt) {
        int left_total_cost = 0;
        int right_total_cost = 0;
        if (left) {
            left_total_cost = left->get_tilt_helper_(total_tilt);
        }
        if (right) {
            right_total_cost = right->get_tilt_helper_(total_tilt);
        }
        *total_tilt += abs(left_total_cost - right_total_cost);
        return cost + left_total_cost + right_total_cost;
    }
};

int main(int argc, char** argv)
{
    vector<int> result;
    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(4);
    root->right= new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(7);
    root->right->left = new TreeNode(8);
    root->right->right = new TreeNode(10);
    int tilt = root->get_tree_tilt();
    cout << "Tilt = " << tilt << endl;
    return 0;
}