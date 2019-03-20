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

Board::Board(vector<checker> _board, vector<checker>* _end) {
    for (checker ch : _board) {
        board.emplace_back(ch);
    }
    end = _end;
    g = 0;
    h = calcH(board, end);
    f = g + h;
}

Board::~Board() {
    board.clear();
}

void Board::updateF() {
    g++;
    h = calcH(board, end);
    f = g + h;
}

unsigned Board::getF() {
    return f;
}

unsigned Board::getH() {
    return f;
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
    cout << endl;
}

void Board::setCell(unsigned i, checker ch) {
    board[i].setChecker(ch);
}

bool Board::checkCellEmpty(unsigned i) {
    return board[i].getChecker() == EMPTY;
}

unsigned calcH(vector<Cell> current, vector<checker>* end) {
    unsigned h = 0;

    for (unsigned i = 0; i < current.size(); i++) {
        if (current[i].getChecker() != (*end)[i]) {
            h++;
        }
    }

    return h;
}

Board formVertex(unsigned i, unsigned j, Board b) {
    Board newBoard(b);

    newBoard.setCell(i, b.getBoard()[j].getChecker());
    newBoard.setCell(j, b.getBoard()[i].getChecker());

    newBoard.updateF();

    return newBoard;
}

void formVertexes(Board b, const function<void(unsigned, unsigned, Board)> callback) {
    vector<Cell> board = b.getBoard();
    for (unsigned i = 0; i < board.size(); i++) {
        checker ch = board[i].getChecker();

        if (ch != EMPTY) {
            if (i / 8 > 0) {
                if (b.checkCellEmpty(i - 8)) {
                    callback(i, i - 8, b);
                }
            }
            if (i / 8 < 8) {
                if (b.checkCellEmpty(i + 8)) {
                    callback(i, i + 8, b);
                }
            }
            if (i % 8 > 0) {
                if (b.checkCellEmpty(i - 1)) {
                    callback(i, i - 1, b);
                }
            }
            if (i % 8 < 7) {
                if (b.checkCellEmpty(i + 1)) {
                    callback(i, i + 1, b);
                }
            }
        }
    }
}

int main() {
    vector<checker> start {
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
    };

    vector<checker> end {
            // 1st row
            BLACK,
            BLACK,
            BLACK,
            BLACK,
            WHITE,
            WHITE,
            WHITE,
            EMPTY,
            // 2nd row
            BLACK,
            BLACK,
            BLACK,
            BLACK,
            WHITE,
            WHITE,
            WHITE,
            EMPTY,
            // 3rd row
            BLACK,
            BLACK,
            BLACK,
            BLACK,
            WHITE,
            WHITE,
            WHITE,
            EMPTY,
            // 4th row
            BLACK,
            BLACK,
            BLACK,
            EMPTY,
            WHITE,
            WHITE,
            WHITE,
            EMPTY,
            // 5th row
            BLACK,
            BLACK,
            BLACK,
            WHITE,
            WHITE,
            WHITE,
            WHITE,
            EMPTY,
            // 6th row
            BLACK,
            BLACK,
            BLACK,
            WHITE,
            WHITE,
            WHITE,
            WHITE,
            EMPTY,
            // 7th row
            BLACK,
            BLACK,
            BLACK,
            WHITE,
            WHITE,
            WHITE,
            WHITE,
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
    };

    vector<Board> open;
    vector<Board> close;
    open.emplace_back(start, &end);

    while (true) {
        Board* x = nullptr;

        unsigned index = 0;

        for (unsigned i = 0; i < open.size(); i++) {
            Board* b = &open[i];

            if (b->getH() == 0) {
                x = b;
                index = i;
                break;
            }
            if (!x) {
                x = b;
                index = i;
                continue;
            }

            if (x->getF() > b->getF()) {
                index = i;
                x = b;
            }
        }

        if (x != nullptr) {
            x = new Board(*x);
            open.erase(open.begin() + index);

            if (x->getH() == 0) {
                break;
            }

            formVertexes(*x, [&](unsigned i, unsigned j, Board b){
                Board board = formVertex(i, j, b);
                open.emplace_back(board);
            });

            x->printBoard();
        }
    }

    for (Board b : open) {
        b.printBoard();
    }

    open.clear();
    close.clear();

    return 0;
}