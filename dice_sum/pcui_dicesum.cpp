#include <iostream>
#include <vector>

using namespace std;

int find_sum(int dice_num, int face_num, int total)
{
    vector<vector<int>> dp(dice_num+1,vector<int>(total + 1,0));
    // dp[dicenum][total] = dp[dicenum-1][total-1] + dp[dicenum-1][total -2] ... dp[dicenum-1]
    for(int i = 1; i <= face_num; i ++)
    {
        dp[1][i] = 1;
    }
    for(int i = 2; i <= dice_num; i ++)
    {
        for(int j = i;j <= total; j ++)
        {
            for(int k = 1; k <= face_num && k < j; k ++)
            {
                dp[i][j] += dp[i-1][j-k];
            }
        }
    }
    for(int i = 0; i <= dice_num ; i ++)
    {
        for(int j = 0; j <= total; j ++)
        {
 //           cout <<  dp[i][j] << " |  ";
        }
//        cout << endl;
    }

    return dp[dice_num][total];
}

int main(int argc, char** argv)
{
    cout << "find_sum(3, 6, 18) = " << find_sum(3, 6, 18) << endl;
    return 0;
}
