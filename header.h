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
    explicit Cell(checker _ch);

    void setChecker(checker _ch);

    checker getChecker();
};

class Board {
private:
    vector<Cell> board;

public:
    explicit Board(vector<checker> _board);

    ~Board();

    vector<Cell> getBoard();

    void printBoard();

    bool checkCellEmpty(unsigned i);
};

void openVertex(unsigned i, unsigned j, Board b);

void formVertex(Board b, void (*callback)(unsigned, unsigned, Board));

#endif //KADRIL_KUZNECHEKOV_HEADER_H
