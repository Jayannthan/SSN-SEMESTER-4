#include <iostream>

using namespace std;
#define max 20


void display(int board[max][max], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (board[i][j] == 1)
                cout << " Q";
            else
                cout << " -";
        cout << endl;
    }
}

bool place(int board[max][max], int col, int row, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (board[row][i] == 1)
            return false;
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
        {
            return false;
        }
    }
    for (int i = row, j = col; i < n && j >= 0; i++, j--)
    {
        if (board[i][j] == 1)
        {
            return false;
        }
    }
    return true;
}

bool nqueens(int board[max][max], int col, int n)
{
    if (col >= n)
        return true;
    for (int i = 0; i < n; i++)
    {
        if (place(board, col, i, n))
        {
            board[i][col] = 1;
            if (nqueens(board, col + 1, n))
                return true;
            board[i][col] = 0;
        }
    }
    return false;
}

void solution(int n)
{
    int board[max][max];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 0;
    if (nqueens(board, 0, n))
        display(board, n);
    else
        cout << "Problem has no solution";
}


int main()
{
    int n;
    cin >> n;
    solution(n);
    return 0;
}