//
// Created by Javier on 18-05-2023.
//

#ifndef KLOTSKI_KLOTSKY_H
#define KLOTSKI_KLOTSKY_H

#include <vector>
#include <iostream>
#include <bitset>
#include <array>

class Klotsky{

    //The board is a 4X5 board. But the bitset requieres an extra column to generate a correct bitshift.

public:
    Klotsky(const std::bitset<25> &bits1X1A, const std::bitset<25> &bits1X1B, const std::bitset<25> &bits1X1C,
            const std::bitset<25> &bits1X1D, const std::bitset<25> &bits1X2, const std::bitset<25> &bits2X1A,
            const std::bitset<25> &bits2X1B, const std::bitset<25> &bits2X1C, const std::bitset<25> &bits2X1D,
            const std::bitset<25> &bits2X2);

    Klotsky(const Klotsky& other);
    Klotsky& operator=(const Klotsky& other);

    Klotsky* parent;

    enum class Direction {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    enum class Piece {
        A_1X1,
        B_1X1,
        C_1X1,
        D_1X1,
        A_1X2,
        A_2X1,
        B_2X1,
        C_2X1,
        D_2X1,
        A_2X2
    };

    const std::bitset<25> BOARD_MASK {
        "11110"
        "11110"
        "11110"
        "11110"
        "11110"};

    /// Target is a 2x2 block!
    const std::bitset<25> bits_Target{
            "00000"
            "00000"
            "00000"
            "01100"
            "01100"};

    std::bitset<25> bits_1X1_A;
    std::bitset<25> bits_1X1_B;
    std::bitset<25> bits_1X1_C;
    std::bitset<25> bits_1X1_D;
    std::bitset<25> bits_1X2;
    std::bitset<25> bits_2X1_A;
    std::bitset<25> bits_2X1_B;
    std::bitset<25> bits_2X1_C;
    std::bitset<25> bits_2X1_D;
    std::bitset<25> bits_2X2;

    const char empty_char = ' ';
    const char _1x1_char = 'A';
    const char _1x2_char = 'B';
    const char _2x1_char = 'C';
    const char _2x2_char = 'O';
    const char target_char = 'X';




    std::bitset<25> getFull () const { return (bits_1X1_A | bits_1X1_B | bits_1X1_C | bits_1X1_D | bits_1X2 | bits_2X1_A | bits_2X1_B | bits_2X1_C | bits_2X1_D | bits_2X2) & BOARD_MASK;}
    std::bitset<25> getEmpty () const {return getFull().flip() & BOARD_MASK;};

    void addBits(std::bitset<25>bits, Piece pieceToAdd);
    void removeBits(std::bitset<25> bits, Klotsky::Piece pieceToRemove);


    std::vector<Klotsky> generateAllLegalMoves();
    std::vector<Klotsky> generatePieceMoves(std::bitset<25> piece, Piece pieceType);

   //the difference in safe shift and unsafe is that the safe one removes the bits that are outside the board.

    std::string getStringOfType(Piece pieceType);
    std::string directionToString(Direction direction);

    std::bitset<25> shiftUpUnsafe(std::bitset<25> bitset) const;
    std::bitset<25> shiftDownUnsafe(std::bitset<25> bitset) const;
    std::bitset<25> shiftLeftUnsafe(std::bitset<25> bitset) const;
    std::bitset<25> shiftRightUnsafe(std::bitset<25> bitset) const;
    std::bitset<25> shiftDirectionUnsafe(std::bitset<25> bitset, Klotsky::Direction direction) const;


    std::bitset<25> shiftDirection(std::bitset<25> bitset, Direction direction) const;
    std::bitset<25> shiftUp(std::bitset<25> bitset) const;
    std::bitset<25> shiftDown(std::bitset<25> bitset) const;
    std::bitset<25> shiftLeft(std::bitset<25> bitset) const;
    std::bitset<25> shiftRight(std::bitset<25> bitset) const;

    void print() const;
    void printTarget() const;
    void printO(bool show0, bool showA) const;

};



#endif //KLOTSKI_KLOTSKY_H
