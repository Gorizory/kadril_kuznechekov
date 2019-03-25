#ifndef KADRIL_KUZNECHEKOV_HEADER_H
#define KADRIL_KUZNECHEKOV_HEADER_H

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

enum checker {
    EMPTY = 0,
    WHITE = 1,
    BLACK = 2,
};

class Cell {
private:
    checker ch;

public:
    explicit Cell(checker);

    void setChecker(checker);

    checker getChecker();
};

class Board {
private:
    vector<Cell> board;
    vector<checker>* end;
    unsigned g;
    unsigned h;
    unsigned f;

public:
    Board(vector<checker>, vector<checker>*);

    ~Board();

    bool operator==(Board);

    vector<Cell> getBoard();

    vector<checker>* getEnd();

    void updateF();

    unsigned getF();

    unsigned getH();

    void printBoard();

    bool checkCellEmpty(unsigned);

    void setCell(unsigned, checker);
};

Board formVertex(unsigned, unsigned, Board);

void formVertexes(Board, function<void(unsigned, unsigned, Board)>);

unsigned calcH(vector<Cell>, vector<checker>*);

#endif //KADRIL_KUZNECHEKOV_HEADER_H
