//
// Created by Javier on 18-05-2023.
//

#include "Klotsky.h"
void Klotsky::print() const {
    // bitsets are usually printed according to the way in which the byte values are stored in memory
    // therefore to print our visual representation we turn it into a string
    std::string bits_str = getFull().to_string();
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

            if(getFull()[i] != 0 && bits_2X2[i] != 0){
                std::cout << _2x2_char;
            }
            else if((getFull()[i] != 0 && bits_1X2[i] != 0)){
                std::cout << _1x2_char;
            }
            else if((getFull()[i] != 0 && bits_1X1_A[i] != 0) || (getFull()[i] != 0 && bits_1X1_B[i] != 0) || (getFull()[i] != 0 && bits_1X1_C[i] != 0) || (getFull()[i] != 0 && bits_1X1_D[i] != 0)){
                std::cout << _1x1_char;
            }
            else if((getFull()[i] != 0 && bits_2X1_A[i] != 0) || (getFull()[i] != 0 && bits_2X1_B[i] != 0) || (getFull()[i] != 0 && bits_2X1_C[i] != 0) || (getFull()[i] != 0 && bits_2X1_D[i] != 0)){
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



void Klotsky::printTarget() const {
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

    return *this;
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

