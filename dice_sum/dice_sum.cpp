#include <iostream>
#include <vector>

using namespace std;

int find_sum(int dice_num, int face_num, int total)
{
    // num[n][x] = num[n-1][x-1] + num[n-1][x-2] + ... + num[n-1][x-m]
    vector<vector<int>> num(dice_num + 1, vector<int>(total + 1, 0));
    for (int i = 1; i <= face_num and i < total; i++) {
        num[1][i] = 1;
    }
    for (int i = 2; i <= dice_num; i++) {
        for (int j = 1; j <= total; j++) {
            for (int k = 1; k <= face_num and k < j; k++) {
                num[i][j] += num[i-1][j - k];
            }
        }
    }
    return num[dice_num][total];
}

int main(int argc, char** argv)
{
    cout << "find_sum(3, 6, 19) = " << find_sum(3, 6, 19) << endl;
    return 0;
}