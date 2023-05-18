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

public:

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

    Klotsky* parent;

    const char empty_char = ' ';
    const char _1x1_char = 'A';
    const char _1x2_char = 'B';
    const char _2x1_char = 'C';
    const char _2x2_char = 'O';
    const char target_char = 'X';


    std::bitset<25> getFull () const { return bits_1X1_A | bits_1X1_B | bits_1X1_C | bits_1X1_D | bits_1X2 | bits_2X1_A | bits_2X1_B | bits_2X1_C | bits_2X1_D | bits_2X2;}
    std::bitset<25> getEmpty () const {return getFull().flip() & BOARD_MASK;};

    void addBits(std::bitset<25>bits, Piece pieceToAdd)
    {
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

   std::vector<Klotsky> generateAllLegalMoves()
   {
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
           auto pieceMoves = generatePieceMoves(bitset, piece);
           generatedMoves.insert(generatedMoves.end(), pieceMoves.begin(), pieceMoves.end());
       }

//
//
//       std::vector<Klotsky> generatedMoves;
//
//       auto pieceMoves = generatePieceMoves(bits_1X1_A, Piece::A_1X1);
//       generatedMoves.insert(generatedMoves.end(), pieceMoves.begin(), pieceMoves.end());
//       pieceMoves = generatePieceMoves(bits_1X1_B, Piece::B_1X1);
//       generatedMoves.insert(generatedMoves.end(), pieceMoves.begin(), pieceMoves.end());
//       pieceMoves = generatePieceMoves(bits_1X1_C);
//       generatedMoves.insert(generatedMoves.end(), pieceMoves.begin(), pieceMoves.end());
//       pieceMoves = generatePieceMoves(bits_1X1_D);
//       generatedMoves.insert(generatedMoves.end(), pieceMoves.begin(), pieceMoves.end());
//
//       pieceMoves = generatePieceMoves(bits_1X2);
//       generatedMoves.insert(generatedMoves.end(), pieceMoves.begin(), pieceMoves.end());
//
//       pieceMoves = generatePieceMoves(bits_2X1_A);
//       generatedMoves.insert(generatedMoves.end(), pieceMoves.begin(), pieceMoves.end());
//       pieceMoves = generatePieceMoves(bits_2X1_B);
//       generatedMoves.insert(generatedMoves.end(), pieceMoves.begin(), pieceMoves.end());
//       pieceMoves = generatePieceMoves(bits_2X1_C);
//       generatedMoves.insert(generatedMoves.end(), pieceMoves.begin(), pieceMoves.end());
//       pieceMoves = generatePieceMoves(bits_2X1_D);
//       generatedMoves.insert(generatedMoves.end(), pieceMoves.begin(), pieceMoves.end());
//
//       pieceMoves = generatePieceMoves(bits_2X2);
//       generatedMoves.insert(generatedMoves.end(), pieceMoves.begin(), pieceMoves.end());

       return generatedMoves;
   }


   void removeBitsInAllBitsets(std::bitset<25> bits)
   {
       bits_1X1_A ^= bits;
       bits_1X1_B ^= bits;
       bits_1X1_C ^= bits;
       bits_1X1_D ^= bits;

       bits_1X2 ^= bits;

       bits_2X1_A ^= bits;
       bits_2X1_B ^= bits;
       bits_2X1_C ^= bits;
       bits_2X1_D ^= bits;

       bits_2X2 ^= bits;
   }

   std::vector<Klotsky> generatePieceMoves(std::bitset<25> piece, Piece pieceType)
   {
       //we create a copy to be modified.
       Klotsky boardWithoutPiece = *this;
       //first we remove the piece bits, so it become empty space.
       boardWithoutPiece.removeBitsInAllBitsets(piece);

       std::bitset<25> shiftedPiece = piece;
       std::vector<Klotsky> generatedMoves;
       for (int i = 0; i < 4; ++i) {
           auto direction = static_cast<Direction>(i);
           //now we add moves in the direction until the piece gets out of bounds or there is another piece blocking the move.
           int j= 0;
           while (true)
           {
               shiftedPiece = shiftDirectionUnsafe(shiftedPiece, direction);
               //we check if the shifted piece moves to an empty space.
               if((shiftedPiece & boardWithoutPiece.getEmpty()) == shiftedPiece)
               {
                   std::cout << "looping... "<<  j  << std::endl;
                   Klotsky newMove = boardWithoutPiece;
                   newMove.addBits(shiftedPiece, pieceType);
                   //the move will assign its parent
                   newMove.parent = this;
                   generatedMoves.push_back(newMove);
               }
               else
               {
                   break;
               }
               j++;
           }
       }
       return generatedMoves;
   }


   //the difference in safe shift and unsafe is that the safe one removes the bits that are outside the board.

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


    void printO() const {
        // bitsets are usually printed according to the way in which the byte values are stored in memory
        // therefore to print our visual representation we turn it into a string
        std::string bits_str = getEmpty().to_string();

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

                if(bits_2X2[i] != 0){
                    std::cout << " ";
                    std::cout << _2x2_char;
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


};



#endif //KLOTSKI_KLOTSKY_H
