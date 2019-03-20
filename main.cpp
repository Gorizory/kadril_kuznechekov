#include "header.h"

Cell::Cell(checker _ch) {
    ch = _ch;
}

void Cell::setChecker(checker _ch) {
    ch = _ch;
}

checker Cell::getChecker() {
    return ch;
}

Board::Board(vector<checker> _board) {
    for (checker ch : _board) {
        board.emplace_back(ch);
    }
}

Board::~Board() {
    board.clear();
}

vector<Cell> Board::getBoard() {
    return board;
}

void Board::printBoard() {
    for (unsigned i = 0; i < board.size(); i++) {
        switch (board[i].getChecker()) {
            case WHITE:
                cout << "W ";
                break;

            case BLACK:
                cout << "B ";
                break;

            case EMPTY:
                cout << "E ";
                break;
        }

        if ((i + 1) % 8 == 0 && i != 0) {
            cout << endl;
        }
    }
}

bool Board::checkCellEmpty(unsigned i) {
    return board[i].getChecker() == EMPTY;
}

void openVertex(int i, int j, Board b) {

}

void formVertex(Board b, void (*callback)(unsigned, unsigned, Board)) {
    vector<Cell> board = b.getBoard();
    for (unsigned i = 0; i < board.size(); i++) {
        checker ch = board[i].getChecker();

        if (ch != EMPTY) {
            if (i / 8 > 0) {
                if (b.checkCellEmpty(i - 8)) {
                    callback(i, i - 8, b);
                }
            }
        }
    }
}

int main() {
    vector<Board> stateSpace;
    stateSpace.emplace_back(vector<checker>{
            // 1st row
            WHITE,
            WHITE,
            WHITE,
            WHITE,
            BLACK,
            BLACK,
            BLACK,
            EMPTY,
            // 2nd row
            WHITE,
            WHITE,
            WHITE,
            WHITE,
            BLACK,
            BLACK,
            BLACK,
            EMPTY,
            // 3rd row
            WHITE,
            WHITE,
            WHITE,
            WHITE,
            BLACK,
            BLACK,
            BLACK,
            EMPTY,
            // 4th row
            WHITE,
            WHITE,
            WHITE,
            EMPTY,
            BLACK,
            BLACK,
            BLACK,
            EMPTY,
            // 5th row
            WHITE,
            WHITE,
            WHITE,
            BLACK,
            BLACK,
            BLACK,
            BLACK,
            EMPTY,
            // 6th row
            WHITE,
            WHITE,
            WHITE,
            BLACK,
            BLACK,
            BLACK,
            BLACK,
            EMPTY,
            // 7th row
            WHITE,
            WHITE,
            WHITE,
            BLACK,
            BLACK,
            BLACK,
            BLACK,
            EMPTY,
            // 8th row
            EMPTY,
            EMPTY,
            EMPTY,
            EMPTY,
            EMPTY,
            EMPTY,
            EMPTY,
            EMPTY,
    });

    formVertex(stateSpace[0], openVertex);

    for (Board b : stateSpace) {
        b.printBoard();
    }
    return 0;
}