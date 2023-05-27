//
// Created by Javier on 27-05-2023.
//

#ifndef KLOTSKI_NODEKLOTSKY_H
#define KLOTSKI_NODEKLOTSKY_H


#include "Klotsky.h"

struct NodeKlotsky {
    NodeKlotsky() {
        board = Klotsky();
        parent = nullptr;

        g = 0;
        h = 0;
    }

    NodeKlotsky(Klotsky board) : board(board) {

    }

    Klotsky board;
    std::shared_ptr<NodeKlotsky> parent;

    // Getters and setters for g and h values
    int getG() const { return g; }
    void setG(int value) { g = value; }

    int getH() const { return h; }
    void setH(int value) { h = value; }

    void print() const {std::cout << " h = "<< getH() << " |g = " << getG()  << std::endl;}

private:
    int g; // Cost from the initial state
    int h; // Heuristic value
};

#endif //KLOTSKI_NODEKLOTSKY_H
