
#include <iostream>
#include <vector>
using namespace std;

// Backtracking function
bool solve(int row, int n, int fixedRow, vector<vector<int>>& board, vector<int>& colUsed, vector<int>& diag1,vector<int>& diag2) {

    // All rows have been processed
    if(row == n) return true;

    // Skip the row containing the already placed queen
    if(row == fixedRow)
        return solve(row + 1, n, fixedRow,
                     board, colUsed, diag1, diag2);

    // Try placing queen in every column
    for(int col = 0; col < n; col++) {
        int d1 = row + col;
        int d2 = row - col + n - 1;

        // Check whether position is safe
        if(!colUsed[col] && !diag1[d1] && !diag2[d2]) {

            // Place queen
            board[row][col] = 1;

            colUsed[col] = 1;
            diag1[d1] = 1;
            diag2[d2] = 1;

            // Recursively solve next row
            if(solve(row + 1, n, fixedRow,
                     board, colUsed, diag1, diag2))
                return true;

            // Backtrack: Remove queen
            board[row][col] = 0;

            colUsed[col] = 0;
            diag1[d1] = 0;
            diag2[d2] = 0;
        }
    }

    return false;
}

int main() {

    int n, fixedRow, fixedCol;

    cout << "Enter board size: ";
    cin >> n;

    if(n <= 0) {
        cout << "Invalid board size";
        return 0;
    }

    cout << "Enter position of first queen (row col): ";
    cin >> fixedRow >> fixedCol;

    // Convert to 0-based indexing
    fixedRow--;
    fixedCol--;

    if(fixedRow < 0 || fixedRow >= n ||
       fixedCol < 0 || fixedCol >= n) {
        cout << "Invalid queen position";
        return 0;
    }

    // Initialize board
    vector<vector<int>> board(
        n, vector<int>(n, 0)
    );

    vector<int> colUsed(n, 0);
    vector<int> diag1(2*n-1, 0);
    vector<int> diag2(2*n-1, 0);

    // Place the first queen permanently
    board[fixedRow][fixedCol] = 1;

    colUsed[fixedCol] = 1;
    diag1[fixedRow + fixedCol] = 1;
    diag2[fixedRow - fixedCol + n - 1] = 1;

    // Solve using Backtracking
    if(solve(0, n, fixedRow,
             board, colUsed, diag1, diag2)) {

        cout << "\nSolution:\n";

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(board[i][j] == 1)
                    cout << "Q ";
                else
                    cout << ". ";
            }
            cout << endl;
        }
    }
    else {
        cout << "\nNo solution exists for this position.";
    }

    return 0;
}
