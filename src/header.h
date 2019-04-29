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

    Board* previous = nullptr;

    Board(vector<checker>, vector<checker>*);

    Board(Board*);

    ~Board();

    bool operator==(Board);

    vector<Cell> getBoard();

    vector<checker>* getEnd();

    void updateF();

    unsigned getG();

    unsigned getF();

    unsigned getH();

    void printBoard();

    bool checkCellEmpty(unsigned);

    void setCell(unsigned, checker);

    unsigned calcH();
};

Board formVertex(unsigned, unsigned, Board);

void addVertex(unsigned, unsigned, Board, vector<Board>*, vector<Board>*, vector<Board>*);

void formVertexes(Board, vector<Board>*, vector<Board>*, vector<Board>*);

#endif //KADRIL_KUZNECHEKOV_HEADER_H
