//
// Created by Javier on 18-05-2023.
//

#include <queue>
#include <unordered_set>
#include <algorithm>

#include "Klotsky.h"


Klotsky::Klotsky(const std::bitset<25> &bits1X1A, const std::bitset<25> &bits1X1B, const std::bitset<25> &bits1X1C,
                 const std::bitset<25> &bits1X1D, const std::bitset<25> &bits1X2, const std::bitset<25> &bits2X1A,
                 const std::bitset<25> &bits2X1B, const std::bitset<25> &bits2X1C, const std::bitset<25> &bits2X1D,
                 const std::bitset<25> &bits2X2) : bits_1X1_A(bits1X1A), bits_1X1_B(bits1X1B), bits_1X1_C(bits1X1C),
                                                   bits_1X1_D(bits1X1D), bits_1X2(bits1X2), bits_2X1_A(bits2X1A),
                                                   bits_2X1_B(bits2X1B), bits_2X1_C(bits2X1C), bits_2X1_D(bits2X1D),
                                                   bits_2X2(bits2X2) {
    parent = nullptr;
}

Klotsky::Klotsky(const Klotsky& other) {

    bits_1X1_A = other.bits_1X1_A;
    bits_1X1_B = other.bits_1X1_B;
    bits_1X1_C = other.bits_1X1_C;
    bits_1X1_D = other.bits_1X1_D;
    bits_1X2 = other.bits_1X2;
    bits_2X1_A = other.bits_2X1_A;
    bits_2X1_B = other.bits_2X1_B;
    bits_2X1_C = other.bits_2X1_C;
    bits_2X1_D = other.bits_2X1_D;
    bits_2X2 = other.bits_2X2;
    parent = other.parent;
}

Klotsky& Klotsky::operator=(const Klotsky& other) {
    if (this == &other) {
        return *this; // Self-assignment check
    }

    // Perform member-wise assignment
    bits_1X1_A = other.bits_1X1_A;
    bits_1X1_B = other.bits_1X1_B;
    bits_1X1_C = other.bits_1X1_C;
    bits_1X1_D = other.bits_1X1_D;
    bits_1X2 = other.bits_1X2;
    bits_2X1_A = other.bits_2X1_A;
    bits_2X1_B = other.bits_2X1_B;
    bits_2X1_C = other.bits_2X1_C;
    bits_2X1_D = other.bits_2X1_D;
    bits_2X2 = other.bits_2X2;
    parent = other.parent;

    return *this;
}

void Klotsky::print() const {
    std::cout << " Klotsky Board " << std::endl;
    std::cout << "   A B C D " <<std::endl;
    std::cout << "   _ _ _ _ " <<std::endl;
    int row = 1;
    int j = 0;

    // Tablero
    for (int i = 24; i >= 0; --i) {

        if(j==0){
            std::cout<< row << "|";
        }
        if(i%5 != 0){

            std::cout << " ";

            if(bits_2X2[i] != 0){
                std::cout << _2x2_char;
            }
            else if(bits_1X2[i] != 0){
                std::cout << _1x2_char;
            }
            else if(bits_1X1_A[i] != 0 || bits_1X1_B[i] != 0 || bits_1X1_C[i] != 0 || bits_1X1_D[i] != 0){
                std::cout << _1x1_char;
            }
            else if(bits_2X1_A[i] != 0 || bits_2X1_B[i] != 0 || bits_2X1_C[i] != 0 || bits_2X1_D[i] != 0){
                std::cout << _2x1_char;
            }
            else{
                std::cout << empty_char;
            }
        }

        j++;
        if(j==5){
            j = 0;
            row++;
            std::cout<<std::endl;
        }
    }
}
void Klotsky::printO(bool show0, bool showA) const {

    std::cout << " Target Board " << std::endl;
    std::cout << "   A B C D " <<std::endl;
    std::cout << "   _ _ _ _ " <<std::endl;
    int row = 1;
    int j = 0;

    // Tablero Reverso
    for (int i = 24; i >= 0; --i) {

        if(j==0){
            std::cout<< row << "| ";
        }
        if(i%5 != 0){


            if(show0 && bits_2X2[i] != 0){
                std::cout << _2x2_char;
            }else if(showA && bits_1X1_A[i] != 0 || bits_1X1_B[i] != 0 || bits_1X1_C[i] != 0 || bits_1X1_D[i] != 0 ){
                std::cout << _1x1_char;
            }
            else{
                std::cout << " ";
            }

            std::cout << " ";
        }

        j++;
        if(j==5){
            j = 0;
            row++;
            std::cout<<std::endl;
        }

    }
}
void Klotsky::printTarget() const {
    std::cout << " Target Board " << std::endl;
    std::cout << "   A B C D " <<std::endl;
    std::cout << "   _ _ _ _ " <<std::endl;
    int row = 1;
    int j = 0;

    // Tablero Reverso
    for (int i = 24; i >= 0; --i) {

        if(j==0){
            std::cout<< row << "| ";
        }
        if(i%5 != 0){

            if(bits_Target[i] != 0){
                std::cout << " ";
                std::cout << target_char;
            }
            else{
                std::cout << " ";
            }
        }

        j++;
        if(j==5){
            j = 0;
            row++;
            std::cout<<std::endl;
        }

    }
}

std::bitset<25> Klotsky::shiftUp(std::bitset<25> bitset) const {
    return bitset << 5 & BOARD_MASK;
}

std::bitset<25> Klotsky::shiftDown(std::bitset<25> bitset) const {
    return bitset >> 5 & BOARD_MASK;
}

std::bitset<25> Klotsky::shiftLeft(std::bitset<25> bitset) const {
    return bitset << 1 & BOARD_MASK;
}

std::bitset<25> Klotsky::shiftRight(std::bitset<25> bitset) const {
    return bitset >> 1 & BOARD_MASK;
}

std::bitset<25> Klotsky::shiftDirection(std::bitset<25> bitset, Klotsky::Direction direction) const {
    switch (direction)
    {
        case Direction::LEFT:
            return shiftLeft(bitset);
        case Direction::RIGHT:
            return shiftRight(bitset);
        case Direction::UP:
            return shiftUp(bitset);
        case Direction::DOWN:
            return shiftDown(bitset);
        default:
            std::bitset<25> empty;
            return empty;
    }

}


std::bitset<25> Klotsky::shiftDirectionUnsafe(std::bitset<25> bitset, Klotsky::Direction direction) const {
    switch (direction)
    {
        case Direction::LEFT:
            return shiftLeftUnsafe(bitset);
        case Direction::RIGHT:
            return shiftRightUnsafe(bitset);
        case Direction::UP:
            return shiftUpUnsafe(bitset);
        case Direction::DOWN:
            return shiftDownUnsafe(bitset);
        default:
            std::bitset<25> empty;
            return empty;
    }

}

std::bitset<25> Klotsky::shiftRightUnsafe(std::bitset<25> bitset) const {
    return bitset >> 1;
}

std::bitset<25> Klotsky::shiftLeftUnsafe(std::bitset<25> bitset) const {
    return bitset << 1;
}

std::bitset<25> Klotsky::shiftDownUnsafe(std::bitset<25> bitset) const {
    return bitset >> 5;
}

std::bitset<25> Klotsky::shiftUpUnsafe(std::bitset<25> bitset) const {
    return bitset << 5;
}

std::vector<Klotsky> Klotsky::generatePieceMoves(Klotsky board, std::bitset<25> piece, Klotsky::Piece pieceType) {
    //we create a copy to be modified.
    Klotsky boardWithoutPiece = board;
    //first we remove the piece bits, so it become empty space.
    boardWithoutPiece.removeBits(piece, pieceType);

    //std::bitset<25> shiftedPiece = piece;
    std::vector<Klotsky> generatedMoves;
    for (int i = 0; i < 4; ++i) {
        auto direction = static_cast<Direction>(i);
        std::bitset<25> shiftedPiece = piece;
        //now we add moves in the direction until the piece gets out of bounds or there is another piece blocking the move.
        while (true)
        {
            shiftedPiece = shiftDirectionUnsafe(shiftedPiece, direction);
            //we check if the shifted piece moves to an empty space.
            if((shiftedPiece & boardWithoutPiece.getEmpty()) == shiftedPiece && (shiftedPiece.count() == piece.count()))
            {
                shiftedPiece &= BOARD_MASK;
                Klotsky newMove = boardWithoutPiece;
                newMove.addBits(shiftedPiece, pieceType);
                //the move will assign its parent
                //newMove.parent = this;
                generatedMoves.push_back(newMove);
            }
            else
            {
                break;
            }
        }
    }
    return generatedMoves;
}

std::vector<Klotsky> Klotsky::generateAllLegalMoves(Klotsky board) {
    std::vector<std::pair<std::bitset<25>, Piece>> bitsets = {
            {bits_1X1_A, Piece::A_1X1},
            {bits_1X1_B, Piece::B_1X1},
            {bits_1X1_C, Piece::C_1X1},
            {bits_1X1_D, Piece::D_1X1},
            {bits_1X2, Piece::A_1X2},
            {bits_2X1_A, Piece::A_2X1},
            {bits_2X1_B, Piece::B_2X1},
            {bits_2X1_C, Piece::C_2X1},
            {bits_2X1_D, Piece::D_2X1},
            {bits_2X2, Piece::A_2X2}
    };

    std::vector<Klotsky> generatedMoves;

    for (const auto& [bitset, piece] : bitsets) {
        auto pieceMoves = generatePieceMoves(board,bitset, piece);
        generatedMoves.insert(generatedMoves.end(), pieceMoves.begin(), pieceMoves.end());
    }
    return generatedMoves;
}

void Klotsky::removeBits(std::bitset<25> bits, Klotsky::Piece pieceToRemove) {

    switch (pieceToRemove) {
        case Piece::A_1X1:
            bits_1X1_A &= ~bits;
            break;
        case Piece::B_1X1:
            bits_1X1_B &= ~bits;
            break;
        case Piece::C_1X1:
            bits_1X1_C &= ~bits;
            break;
        case Piece::D_1X1:
            bits_1X1_D &= ~bits;
            break;
        case Piece::A_1X2:
            bits_1X2 &= ~bits;
            break;
        case Piece::A_2X1:
            bits_2X1_A &= ~bits;
            break;
        case Piece::B_2X1:
            bits_2X1_B &= ~bits;
            break;
        case Piece::C_2X1:
            bits_2X1_C &= ~bits;
            break;
        case Piece::D_2X1:
            bits_2X1_D &= ~bits;
            break;
        case Piece::A_2X2:
            bits_2X2 &= ~bits;
            break;
    }

}

void Klotsky::addBits(std::bitset<25> bits, Klotsky::Piece pieceToAdd) {
    switch (pieceToAdd) {

        case Piece::A_1X1:
            bits_1X1_A |= bits;
            break;
        case Piece::B_1X1:
            bits_1X1_B |= bits;
            break;
        case Piece::C_1X1:
            bits_1X1_C |= bits;
            break;
        case Piece::D_1X1:
            bits_1X1_D |= bits;
            break;
        case Piece::A_1X2:
            bits_1X2 |= bits;
            break;
        case Piece::A_2X1:
            bits_2X1_A |= bits;
            break;
        case Piece::B_2X1:
            bits_2X1_B |= bits;
            break;
        case Piece::C_2X1:
            bits_2X1_C |= bits;
            break;
        case Piece::D_2X1:
            bits_2X1_D |= bits;
            break;
        case Piece::A_2X2:
            bits_2X2 |= bits;
            break;
    }
}

std::string Klotsky::getStringOfType(Klotsky::Piece pieceType) {
    std::string pieceTypeStr;
    switch (pieceType) {
        case Piece::A_1X1:
            pieceTypeStr = "A_1X1";
            break;
        case Piece::B_1X1:
            pieceTypeStr = "B_1X1";
            break;
        case Piece::C_1X1:
            pieceTypeStr = "C_1X1";
            break;
        case Piece::D_1X1:
            pieceTypeStr = "D_1X1";
            break;
        case Piece::A_1X2:
            pieceTypeStr = "A_1X2";
            break;
        case Piece::A_2X1:
            pieceTypeStr = "A_2X1";
            break;
        case Piece::B_2X1:
            pieceTypeStr = "B_2X1";
            break;
        case Piece::C_2X1:
            pieceTypeStr = "C_2X1";
            break;
        case Piece::D_2X1:
            pieceTypeStr = "D_2X1";
            break;
        case Piece::A_2X2:
            pieceTypeStr = "A_2X2";
            break;
        default:
            pieceTypeStr = "Unknown";
            break;
    }

    return pieceTypeStr;
}

std::string Klotsky::directionToString(Klotsky::Direction direction) {
    switch (direction) {
        case Direction::LEFT:
            return "LEFT";
        case Direction::RIGHT:
            return "RIGHT";
        case Direction::UP:
            return "UP";
        case Direction::DOWN:
            return "DOWN";
        default:
            return "Unknown";
    }
}

bool Klotsky::isGoalState() {
    if(bits_2X2 == bits_Target)
        return true;
    else
        return false;
}


std::vector<Klotsky>  Klotsky::solvePuzzleBFS(const Klotsky& initialState) {
    std::queue<Klotsky> queue;
    std::unordered_set<Klotsky, Klotsky::KlotskyHash, Klotsky::KlotskyEqual> visited;

    queue.push(initialState);
    visited.insert(initialState);

    while (!queue.empty()) {

        Klotsky current = queue.front();
        queue.pop();

        // Check if the current state is the goal state
        if (current.isGoalState()) {
            // Return the sequence of moves to reach the goal state
            std::vector<Klotsky> solution;
            while (current.parent != nullptr) {
                solution.push_back(current);
                current = *(current.parent);
            }
            std::reverse(solution.begin(), solution.end());

            std::cout << " ---solution found---" << std::endl;
            std::cout << "solution size: "<< solution.size() << std::endl;
            std::cout << "visited size: "<< visited.size() << std::endl;

            return solution;
        }

        // Generate all legal moves from the current state
        std::vector<Klotsky> legalMoves = current.generateAllLegalMoves(current);
        for (Klotsky& move : legalMoves) {
            //if the move is not inside the visited list is a new move. We insert it.
            if (visited.find(move) == visited.end()) {
                move.parent = std::make_shared<Klotsky>(current);
                queue.push(move);
                visited.insert(move);
            }
        }
    }

    // No solution found
    return std::vector<Klotsky>();
}

Klotsky::~Klotsky() {
    //delete parent;
}


















