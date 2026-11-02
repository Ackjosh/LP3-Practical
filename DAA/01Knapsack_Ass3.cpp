
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(int W, vector<int>& wt,
             vector<int>& val, int n) {

    // Create DP table
    vector<vector<int>> dp(
        n + 1, vector<int>(W + 1, 0)
    );

    // Fill the DP table
    for (int i = 1; i <= n; i++) {

        for (int w = 1; w <= W; w++) {

            // Check if current item can fit
            if (wt[i - 1] <= w) {

                dp[i][w] = max(
                    dp[i - 1][w],
                    val[i - 1] +
                    dp[i - 1][w - wt[i - 1]]
                );
            }
            else {

                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Print maximum profit
    cout << "\nMaximum Profit: " << dp[n][W] << endl;

    // Find selected items
    int w = W;

    cout << "Selected Items: ";

    for (int i = n; i > 0 && w > 0; i--) {

        if (dp[i][w] != dp[i - 1][w]) {

            cout << i << " ";

            w -= wt[i - 1];
        }
    }

    cout << endl;

    return dp[n][W];
}

int main() {

    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of items";
        return 0;
    }

    vector<int> wt(n), val(n);

    cout << "Enter weights:\n";
    for (int i = 0; i < n; i++) {
        cin >> wt[i];

        if (wt[i] <= 0) {
            cout << "Invalid weight";
            return 0;
        }
    }

    cout << "Enter profits:\n";
    for (int i = 0; i < n; i++) {
        cin >> val[i];

        if (val[i] < 0) {
            cout << "Invalid profit";
            return 0;
        }
    }

    cout << "Enter knapsack capacity: ";
    cin >> W;

    if (W < 0) {
        cout << "Invalid capacity";
        return 0;
    }

    knapsack(W, wt, val, n);

    return 0;
}