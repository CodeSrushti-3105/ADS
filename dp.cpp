#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int knapsackRec(int wt[], int val[], int i, int W) {
    if (i == 0 || W == 0)
        return 0;

    if (wt[i - 1] <= W)
        return max(
            val[i - 1] + knapsackRec(wt, val, i - 1, W - wt[i - 1]),
            knapsackRec(wt, val, i - 1, W)
        );
    else
        return knapsackRec(wt, val, i - 1, W);
}

int dp[101][101]; // assuming n, W ≤ 100

int knapsackMemo(int wt[], int val[], int i, int W) {
    if (i == 0 || W == 0)
        return 0;

    if (dp[i][W] != -1)
        return dp[i][W];

    if (wt[i - 1] <= W)
        dp[i][W] = max(
            val[i - 1] + knapsackMemo(wt, val, i - 1, W - wt[i - 1]),
            knapsackMemo(wt, val, i - 1, W)
        );
    else
        dp[i][W] = knapsackMemo(wt, val, i - 1, W);

    return dp[i][W];
}

int knapsackTab(int W, int wt[], int val[], int n) {
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = max(
                    val[i - 1] + dp[i - 1][w - wt[i - 1]],
                    dp[i - 1][w]
                );
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][W];
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    int wt[100], val[100]; // assuming max 100 items

    cout << "Enter weights of items:\n";
    for (int i = 0; i < n; i++)
        cin >> wt[i];

    cout << "Enter values of items:\n";
    for (int i = 0; i < n; i++)
        cin >> val[i];

    cout << "Enter capacity of knapsack: ";
    cin >> W;

    // Recursive
    cout << "\n1.Recursive Result = " << knapsackRec(wt, val, n, W);

    // Memoized
    memset(dp, -1, sizeof(dp));
    cout << "\n2. Memoized Result = " << knapsackMemo(wt, val, n, W);

    // Tabulated
    cout << "\n3. Tabulated Result = " << knapsackTab(W, wt, val, n) << endl;

    return 0;
}
