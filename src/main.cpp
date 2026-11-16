#include <array>
#include <iostream>
#include <limits>

using Board = std::array<char, 9>;

void printBoard(const Board& board) {
    std::cout << "\n";
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            const int i = row * 3 + col;
            std::cout << ' ' << (board[i] == ' ' ? char('1' + i) : board[i]);
            if (col < 2) std::cout << " |";
        }
        std::cout << "\n";
        if (row < 2) std::cout << "---+---+---\n";
    }
    std::cout << "\n";
}

char winner(const Board& b) {
    constexpr int lines[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (const auto& line : lines) {
        if (b[line[0]] != ' ' &&
            b[line[0]] == b[line[1]] &&
            b[line[1]] == b[line[2]]) return b[line[0]];
    }
    return ' ';
}

bool isFull(const Board& board) {
    for (char cell : board) if (cell == ' ') return false;
    return true;
}

int minimax(Board& board, bool maximizing) {
    const char result = winner(board);
    if (result == 'O') return 10;
    if (result == 'X') return -10;
    if (isFull(board)) return 0;

    if (maximizing) {
        int best = -1000;
        for (int i = 0; i < 9; ++i) {
            if (board[i] != ' ') continue;
            board[i] = 'O';
            const int score = minimax(board, false);
            board[i] = ' ';
            if (score > best) best = score;
        }
        return best;
    }

    int best = 1000;
    for (int i = 0; i < 9; ++i) {
        if (board[i] != ' ') continue;
        board[i] = 'X';
        const int score = minimax(board, true);
        board[i] = ' ';
        if (score < best) best = score;
    }
    return best;
}

int findBestMove(Board& board) {
    int bestScore = -1000;
    int bestMove = -1;
    for (int i = 0; i < 9; ++i) {
        if (board[i] != ' ') continue;
        board[i] = 'O';
        const int score = minimax(board, false);
        board[i] = ' ';
        if (score > bestScore) {
            bestScore = score;
            bestMove = i;
        }
    }
    return bestMove;
}

int main() {
    Board board{};
    board.fill(' ');
    std::cout << "TIC-TAC-TOE | You are X, computer is O\n";

    while (true) {
        printBoard(board);

        int move = 0;
        std::cout << "Choose a square (1-9): ";
        if (!(std::cin >> move)) {
            std::cout << "Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (move < 1 || move > 9 || board[move - 1] != ' ') {
            std::cout << "That square is not available. Try again.\n";
            continue;
        }
        board[move - 1] = 'X';

        if (winner(board) == 'X') { printBoard(board); std::cout << "You win!\n"; break; }
        if (isFull(board)) { printBoard(board); std::cout << "It's a draw.\n"; break; }

        const int aiMove = findBestMove(board);
        board[aiMove] = 'O';
        std::cout << "Computer chose square " << aiMove + 1 << ".\n";

        if (winner(board) == 'O') { printBoard(board); std::cout << "Computer wins.\n"; break; }
        if (isFull(board)) { printBoard(board); std::cout << "It's a draw.\n"; break; }
    }
}
