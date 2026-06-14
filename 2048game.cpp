#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

const int SIZE = 4;
int board[SIZE][SIZE];
int score = 0;

void init() {
    srand(time(0));
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = 0;
}

void addTile() {
    vector<pair<int,int>> empty;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == 0)
                empty.push_back({i, j});
    if (empty.empty()) return;
    auto [r, c] = empty[rand() % empty.size()];
    board[r][c] = (rand() % 10 < 9) ? 2 : 4;
}

void display() {
    system("cls");
    cout << "========== 2048 ==========\n";
    cout << "Score: " << score << "\n";
    cout << "==========================\n";
    for (int i = 0; i < SIZE; i++) {
        cout << "+------+------+------+------+\n";
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j])
                cout << "| " << board[i][j];
            else
                cout << "|      ";
            if (board[i][j]) {
                int digits = to_string(board[i][j]).length();
                for (int k = 0; k < 5 - digits; k++) cout << " ";
            }
        }
        cout << "|\n";
    }
    cout << "+------+------+------+------+\n";
}

vector<int> merge(vector<int> row) {
    vector<int> filtered;
    for (int x : row)
        if (x != 0) filtered.push_back(x);

    for (int i = 0; i < (int)filtered.size() - 1; i++) {
        if (filtered[i] == filtered[i+1]) {
            filtered[i] *= 2;
            score += filtered[i];
            filtered.erase(filtered.begin() + i + 1);
        }
    }
    while (filtered.size() < SIZE)
        filtered.push_back(0);
    return filtered;
}

bool moveLeft() {
    bool moved = false;
    for (int i = 0; i < SIZE; i++) {
        vector<int> row(board[i], board[i] + SIZE);
        vector<int> merged = merge(row);
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != merged[j]) moved = true;
            board[i][j] = merged[j];
        }
    }
    return moved;
}

bool moveRight() {
    bool moved = false;
    for (int i = 0; i < SIZE; i++) {
        vector<int> row(board[i], board[i] + SIZE);
        reverse(row.begin(), row.end());
        vector<int> merged = merge(row);
        reverse(merged.begin(), merged.end());
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != merged[j]) moved = true;
            board[i][j] = merged[j];
        }
    }
    return moved;
}

bool moveUp() {
    bool moved = false;
    for (int j = 0; j < SIZE; j++) {
        vector<int> col;
        for (int i = 0; i < SIZE; i++) col.push_back(board[i][j]);
        vector<int> merged = merge(col);
        for (int i = 0; i < SIZE; i++) {
            if (board[i][j] != merged[i]) moved = true;
            board[i][j] = merged[i];
        }
    }
    return moved;
}

bool moveDown() {
    bool moved = false;
    for (int j = 0; j < SIZE; j++) {
        vector<int> col;
        for (int i = 0; i < SIZE; i++) col.push_back(board[i][j]);
        reverse(col.begin(), col.end());
        vector<int> merged = merge(col);
        reverse(merged.begin(), merged.end());
        for (int i = 0; i < SIZE; i++) {
            if (board[i][j] != merged[i]) moved = true;
            board[i][j] = merged[i];
        }
    }
    return moved;
}

bool hasWon() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == 2048) return true;
    return false;
}

bool hasLost() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) return false;
            if (i + 1 < SIZE && board[i][j] == board[i+1][j]) return false;
            if (j + 1 < SIZE && board[i][j] == board[i][j+1]) return false;
        }
    return true;
}

int main() {
    init();
    addTile();
    addTile();

    while (true) {
        display();

        if (hasWon()) {
            cout << "You Win! Final Score: " << score << "\n";
            break;
        }
        if (hasLost()) {
            cout << "Game Over! Final Score: " << score << "\n";
            break;
        }

        cout << "Use Arrow Keys to move. Press Q to quit.\n";

        int ch = _getch();
        bool moved = false;

        if (ch == 224) {
            ch = _getch();
            if (ch == 72) moved = moveUp();
            else if (ch == 80) moved = moveDown();
            else if (ch == 75) moved = moveLeft();
            else if (ch == 77) moved = moveRight();
        } else if (ch == 'q' || ch == 'Q') {
            cout << "Thanks for playing! Score: " << score << "\n";
            break;
        }

        if (moved) addTile();
    }

    return 0;
}