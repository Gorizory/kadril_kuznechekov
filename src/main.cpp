#include "header.h"

#define N 6

Cell::Cell(checker _ch) {
    ch = _ch;
}

void Cell::setChecker(checker _ch) {
    ch = _ch;
}

checker Cell::getChecker() {
    return ch;
}

Board::Board(vector<checker> _board, vector<checker> *_end) {
    for (checker ch : _board) {
        board.emplace_back(ch);
    }
    end = _end;
    g = 0;
    h = calcH();
    f = g + h;
}

Board::~Board() {
    board.clear();
}

bool Board::operator==(Board* b) {
    bool equal = true;
    for (unsigned i = 0; i < board.size(); i++) {
        if (board[i].getChecker() != b->board[i].getChecker()) {
            equal = false;
            break;
        }
    }
    return equal;
}

void Board::updateF() {
    g++;
    h = calcH();
    f = g + h;
}

unsigned Board::getF() {
    return f;
}

unsigned Board::getG() {
    return g;
}

unsigned Board::getH() {
    return h;
}

vector<Cell> Board::getBoard() {
    return board;
}

vector<checker> *Board::getEnd() {
    return end;
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

        if ((i + 1) % N == 0 && i != 0) {
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

unsigned Board::calcH() {
    unsigned newH = 0;
    if (previous == nullptr) {
        return 0;
    }
    bool shouldFail = false;
    unsigned centerRow = N / 2 - 1;
    int move1= -1, move2 = -1;

    for (unsigned i = 0; i < board.size(); i++) {
        if (board[i].getChecker() != previous->getBoard()[i].getChecker()) {
            if (move1 < 0) {
                move1 = i;
            } else {
                move2 = i;
            }
        }
    }

    for (unsigned j = 0; j < N; j++) {
        for (unsigned i = 0; i < N; i++) {
            if (board[i *  N + j].getChecker() != end->at(i *  N + j)) {
                if (i == N - 1 || j == N - 1) {
                    shouldFail = true;
                } else {
                    newH += N;
                }
            }
        }
    }

    if (move1 / N != move2 / N) {
        if (move1 % N != centerRow) {
            shouldFail = true;
        } else {
            newH += numeric_limits<unsigned int>::max() / 4;
        }
    }

//    cout << newH << " " << move1 << " " << move2 << endl;
//    unsigned rowWithEmptyChecker = [&]()->unsigned{
//        for (unsigned i = 0; i < N - 1; i++) {
//            unsigned num = 0;
//
//            for (unsigned j = 0; j < N; j++) {
//                if (current[i * N + j].getChecker() == EMPTY) {
//                    num++;
//                }
//                if (num == 2) {
//                    return i;
//                }
//            }
//        }
//
//        return 0;
//    }();
//    for (unsigned i = 0; i < current.size(); i++) {
//        unsigned row = i / N;
//
//        if (current[i].getChecker() != end->at(i)) {
//            if (row != rowWithEmptyChecker) {
//                h += 5;
//            } else {
//                h += 2;
//            }
//        }
//    }

//    for (unsigned i = 0; i < current.size(); i++) {
//        checker ch = current[i].getChecker();
//
//        if (ch != end->at(i) && end->at(i) != EMPTY) {
//            if (ch == BLACK) {
//                unsigned ip = i % N;
//                unsigned jp = i / N;
//                h += ip > jp ? ip : jp;
//            }
//            if (ch == WHITE) {
//                unsigned col = i % N;
//                unsigned row = i / N;
//                unsigned ip = col < N - 1 ? N - 1 - col : 1;
//                unsigned jp = row < N - 1 ? N - 1 - row : 1;
//                h += ip > jp ? ip : jp;
//            }
//            if (ch != EMPTY && (i / N == N - 1 || i % N == N - 1)) {
//                unsigned ip = N - i % N;
//                unsigned jp = N - i / N;
//                h += ip > jp ? ip : 1000;
//            }
//        }
//    }

//    for (unsigned i = 0; i < current.size(); i++) {
//        int minDist = 1024;
//        checker chCur = current[i].getChecker();
//
//        for (unsigned j = 0; j < end->size(); j++) {
//            checker chEnd = end->at(j);
//            int dist = [i, j]()->int {
//                int ix = i % N;
//                int iy = i / N;
//                int jx = j % N;
//                int jy = j / N;
//
//                int diffX = ix - jx;
//                diffX = diffX > 0 ? diffX : -diffX;
//
//                int diffY = iy - jy;
//                diffY = diffY > 0 ? diffY : -diffY;
//
//                return diffX + diffY;
//            }();
//
//            if (chCur == chEnd && dist < minDist) {
//                minDist = dist;
//            }
//        }
//
//        h += minDist;
//    }

    return !shouldFail ? newH : numeric_limits<unsigned int>::max() / 2;
}

bool checkEnd(Board *board) {
    for (unsigned i = 0; i < board->getBoard().size(); i++) {
        if (board->getBoard()[i].getChecker() != board->getEnd()->at(i)) {
            return false;
        }
    }

    return true;
}

Board* formVertex(unsigned i, unsigned j, Board* b) {
    auto newBoard = new Board(*b);

    newBoard->setCell(i, b->getBoard()[j].getChecker());
    newBoard->setCell(j, b->getBoard()[i].getChecker());

    newBoard->previous = b;
    newBoard->updateF();

    return newBoard;
}

void addVertex(unsigned i, unsigned j, Board* b, vector<Board*> *open, vector<Board*> *close) {
    Board* board = formVertex(i, j, b);
    bool shouldOpen = true;
    for (Board *_b : *open) {
        if (*board == _b) {
            shouldOpen = false;
            break;
        }
    }
    for (Board *_b : *close) {
        if (*board == _b) {
            shouldOpen = false;
            break;
        }
    }
    if (shouldOpen) {
        open->emplace_back(board);
    }
}

void formVertexes(Board* b, vector<Board*> *open, vector<Board*> *close) {
    vector<Cell> board = b->getBoard();

    auto canJump = [](checker c1, checker c2) -> bool {
        return c1 != c2 && c2 != EMPTY;
    };

    for (unsigned i = 0; i < board.size(); i++) {
        checker ch = board[i].getChecker();

        if (ch != EMPTY) {
            // step
            if (i / N > 0 && ch == BLACK) {
                if (b->checkCellEmpty(i - N)) {
                    addVertex(i, i - N, b, open, close);
                }
            }
            if (i / N < N - 1 && ch == WHITE) {
                if (b->checkCellEmpty(i + N)) {
                    addVertex(i, i + N, b, open, close);
                }
            }
            if (i % N > 0 && ch == BLACK) {
                if (b->checkCellEmpty(i - 1)) {
                    addVertex(i, i - 1, b, open, close);
                }
            }
            if (i % N < N - 1 && ch == WHITE) {
                if (b->checkCellEmpty(i + 1)) {
                    addVertex(i, i + 1, b, open, close);
                }
            }
            // jump
            if (i / N > 1) {
                if (b->checkCellEmpty(i - 2 * N) && canJump(ch, b->getBoard()[i - N].getChecker())) {
                    addVertex(i, i - 2 * N, b, open, close);
                }
            }
            if (i / N < N - 2) {
                if (b->checkCellEmpty(i + 2 * N) && canJump(ch, b->getBoard()[i + N].getChecker())) {
                    addVertex(i, i + 2 * N, b, open, close);
                }
            }
            if (i % N > 1) {
                if (b->checkCellEmpty(i - 2) && canJump(ch, b->getBoard()[i - 1].getChecker())) {
                    addVertex(i, i - 2, b, open, close);
                }
            }
            if (i % N < N - 2) {
                if (b->checkCellEmpty(i + 2) && canJump(ch, b->getBoard()[i + 1].getChecker())) {
                    addVertex(i, i + 2, b,
                            open, close);
                }
            }
        }
    }
}

int main() {
//    vector<checker> start {
//            // 1st row
//            WHITE,
//            WHITE,
//            WHITE,
//            WHITE,
//            BLACK,
//            BLACK,
//            BLACK,
//            EMPTY,
//            // 2nd row
//            WHITE,
//            WHITE,
//            WHITE,
//            WHITE,
//            BLACK,
//            BLACK,
//            BLACK,
//            EMPTY,
//            // 3rd row
//            WHITE,
//            WHITE,
//            WHITE,
//            WHITE,
//            BLACK,
//            BLACK,
//            BLACK,
//            EMPTY,
//            // 4th row
//            WHITE,
//            WHITE,
//            WHITE,
//            EMPTY,
//            BLACK,
//            BLACK,
//            BLACK,
//            EMPTY,
//            // 5th row
//            WHITE,
//            WHITE,
//            WHITE,
//            BLACK,
//            BLACK,
//            BLACK,
//            BLACK,
//            EMPTY,
//            // 6th row
//            WHITE,
//            WHITE,
//            WHITE,
//            BLACK,
//            BLACK,
//            BLACK,
//            BLACK,
//            EMPTY,
//            // 7th row
//            WHITE,
//            WHITE,
//            WHITE,
//            BLACK,
//            BLACK,
//            BLACK,
//            BLACK,
//            EMPTY,
//            // 8th row
//            EMPTY,
//            EMPTY,
//            EMPTY,
//            EMPTY,
//            EMPTY,
//            EMPTY,
//            EMPTY,
//            EMPTY,
//    };
//
//    vector<checker> end {
//            // 1st row
//            BLACK,
//            BLACK,
//            BLACK,
//            BLACK,
//            WHITE,
//            WHITE,
//            WHITE,
//            EMPTY,
//            // 2nd row
//            BLACK,
//            BLACK,
//            BLACK,
//            BLACK,
//            WHITE,
//            WHITE,
//            WHITE,
//            EMPTY,
//            // 3rd row
//            BLACK,
//            BLACK,
//            BLACK,
//            BLACK,
//            WHITE,
//            WHITE,
//            WHITE,
//            EMPTY,
//            // 4th row
//            BLACK,
//            BLACK,
//            BLACK,
//            EMPTY,
//            WHITE,
//            WHITE,
//            WHITE,
//            EMPTY,
//            // 5th row
//            BLACK,
//            BLACK,
//            BLACK,
//            WHITE,
//            WHITE,
//            WHITE,
//            WHITE,
//            EMPTY,
//            // 6th row
//            BLACK,
//            BLACK,
//            BLACK,
//            WHITE,
//            WHITE,
//            WHITE,
//            WHITE,
//            EMPTY,
//            // 7th row
//            BLACK,
//            BLACK,
//            BLACK,
//            WHITE,
//            WHITE,
//            WHITE,
//            WHITE,
//            EMPTY,
//            // 8th row
//            EMPTY,
//            EMPTY,
//            EMPTY,
//            EMPTY,
//            EMPTY,
//            EMPTY,
//            EMPTY,
//            EMPTY,
//    };

    vector<checker> start{
            // 1st row
            WHITE,
            WHITE,
            WHITE,
            BLACK,
            BLACK,
            EMPTY,
            // 2nd row
            WHITE,
            WHITE,
            WHITE,
            BLACK,
            BLACK,
            EMPTY,
            // 3rd row
            WHITE,
            WHITE,
            EMPTY,
            BLACK,
            BLACK,
            EMPTY,
            // 4th row
            WHITE,
            WHITE,
            BLACK,
            BLACK,
            BLACK,
            EMPTY,
            // 5th row
            WHITE,
            WHITE,
            BLACK,
            BLACK,
            BLACK,
            EMPTY,
            // 6th row
            EMPTY,
            EMPTY,
            EMPTY,
            EMPTY,
            EMPTY,
            EMPTY
    };

    vector<checker> end{
            // 1st row
            BLACK,
            BLACK,
            BLACK,
            WHITE,
            WHITE,
            EMPTY,
            // 2nd row
            BLACK,
            BLACK,
            BLACK,
            WHITE,
            WHITE,
            EMPTY,
            // 3rd row
            BLACK,
            BLACK,
            EMPTY,
            WHITE,
            WHITE,
            EMPTY,
            // 4th row
            BLACK,
            BLACK,
            WHITE,
            WHITE,
            WHITE,
            EMPTY,
            // 5th row
            BLACK,
            BLACK,
            WHITE,
            WHITE,
            WHITE,
            EMPTY,
            // 6th row
            EMPTY,
            EMPTY,
            EMPTY,
            EMPTY,
            EMPTY,
            EMPTY,
    };

    vector<Board*> open;
    vector<Board*> close;
    open.emplace_back(new Board(start, &end));

    unsigned iteration = 0;

    while (true) {
        Board *x = nullptr;

        unsigned index = 0;

        for (unsigned i = 0; i < open.size(); i++) {
            Board *b = open[i];

            if (checkEnd(b)) {
                x = b;
                index = i;
                break;
            }
            if (x == nullptr) {
                x = b;
                index = i;
                continue;
            }

            if (x->getF() > b->getF()) {
                index = i;
                x = b;
            }
        }

        iteration++;

        if (x != nullptr) {
            open.erase(open.begin() + index);

            close.emplace_back(x);
            x->printBoard();

            if (checkEnd(x)) {
                break;
            }

            formVertexes(x, &open, &close);
        } else {
            cout << "No open vertexes" << endl;
            return 1;
        }
    }

    cout << "Result:" << endl;

    Board *x = close[close.size() - 1];
    vector<Board*> result;

    while (x != nullptr) {
        result.emplace_back(x);
        x = x->previous;
    }

    for (int i = result.size() - 1; i > -1; i--) {
        result.at(i)->printBoard();
    }

    cout << result.size() - 1 << " steps" << endl;

    cout << iteration << " iterations" << endl;

    return 0;
}
