//
// Created by Javier on 18-05-2023.
//

#ifndef KLOTSKI_KLOTSKY_H
#define KLOTSKI_KLOTSKY_H

#include <queue>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <bitset>
#include <array>
#include <memory>

class Klotsky {

    //The board is a 4X5 board. But the bitset requieres an extra column to generate a correct bitshift.

public:
    Klotsky(const std::bitset<25> &bits1X1A, const std::bitset<25> &bits1X1B, const std::bitset<25> &bits1X1C,
            const std::bitset<25> &bits1X1D, const std::bitset<25> &bits1X2, const std::bitset<25> &bits2X1A,
            const std::bitset<25> &bits2X1B, const std::bitset<25> &bits2X1C, const std::bitset<25> &bits2X1D,
            const std::bitset<25> &bits2X2);
    Klotsky();

    Klotsky(const Klotsky &other);

    Klotsky &operator=(const Klotsky &other);

    bool operator==(const Klotsky& other) const;

    ~Klotsky();

    //to enable the use of unordered sets.
    //It doesn't use the parent for these operations.
    struct KlotskyHash {
        std::size_t operator()(const Klotsky &klotsky) const {
            std::size_t hash = 0;
            hash_combine(hash, klotsky.bits_1X1_A);
            hash_combine(hash, klotsky.bits_1X1_B);
            hash_combine(hash, klotsky.bits_1X1_C);
            hash_combine(hash, klotsky.bits_1X1_D);
            hash_combine(hash, klotsky.bits_1X2);
            hash_combine(hash, klotsky.bits_2X1_A);
            hash_combine(hash, klotsky.bits_2X1_B);
            hash_combine(hash, klotsky.bits_2X1_C);
            hash_combine(hash, klotsky.bits_2X1_D);
            hash_combine(hash, klotsky.bits_2X2);
            return hash;
        }

    ~KlotskyHash() = default;
        //transform to string to generate the hash.
    private:
        void hash_combine(std::size_t& seed, const std::bitset<25>& bits) const {
            std::string bitsString = bits.to_string();
            seed ^= std::hash<std::string>{}(bitsString) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
    };
public:
    struct KlotskyEqual {
        bool operator()(const Klotsky &lhs, const Klotsky &rhs) const {
            return lhs.bits_1X1_A == rhs.bits_1X1_A &&
                   lhs.bits_1X1_B == rhs.bits_1X1_B &&
                   lhs.bits_1X1_C == rhs.bits_1X1_C &&
                   lhs.bits_1X1_D == rhs.bits_1X1_D &&
                   lhs.bits_1X2 == rhs.bits_1X2 &&
                   lhs.bits_2X1_A == rhs.bits_2X1_A &&
                   lhs.bits_2X1_B == rhs.bits_2X1_B &&
                   lhs.bits_2X1_C == rhs.bits_2X1_C &&
                   lhs.bits_2X1_D == rhs.bits_2X1_D &&
                   lhs.bits_2X2 == rhs.bits_2X2;
        }
    };

    //hash only the second element
    struct PairHash {
        template <typename T1, typename T2>
        std::size_t operator()(const std::pair<T1, T2>& pair) const {
            //std::size_t h1 = std::hash<T1>{}(pair.first);
            std::size_t h2 = std::hash<T2>{}(pair.second);
            return h2;
        }
    };

    //only the second element too
    struct PairEqual {
        template <typename T1, typename T2>
        bool operator()(const std::pair<T1, T2>& pair1, const std::pair<T1, T2>& pair2) const {
            return pair1.second == pair2.second;
        }
    };


public:
    std::shared_ptr<Klotsky> parent;

    //Klotsky* parent;

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

    const std::bitset<25> BOARD_MASK{
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


    const char empty_char = '.';
    const char _1x1_Achar = '1';
    const char _1x1_Bchar = '2';
    const char _1x1_Cchar = '3';
    const char _1x1_Dchar = '4';
    const char _1x2_char = 'A';
    const char _2x1_Achar = 'B';
    const char _2x1_Bchar = 'C';
    const char _2x1_Cchar = 'D';
    const char _2x1_Dchar = 'E';
    const char _2x2_char = 'O';
    const char target_char = 'X';


    std::bitset<25> getFull() const { return
                (bits_1X1_A | bits_1X1_B | bits_1X1_C | bits_1X1_D | bits_1X2 | bits_2X1_A | bits_2X1_B | bits_2X1_C |
                 bits_2X1_D | bits_2X2) & BOARD_MASK;
    }

    std::bitset<25> getEmpty() const { return getFull().flip() & BOARD_MASK; };

    void addBits(std::bitset<25> bits, Piece pieceToAdd);

    void removeBits(std::bitset<25> bits, Klotsky::Piece pieceToRemove);

    bool isGoalState() const;

    int calcH(bool admissible) const;
    int calcH_Manhattan2x1() const;

    int calcH_Manhattan(int& distY, int& distX) const;
    int calcH_BlockingPieces(int distY, int distX) const;

    std::vector<Klotsky> generateAllLegalMoves(const Klotsky& board) const;
    std::vector<Klotsky> generatePieceMoves(const Klotsky& board, std::bitset<25> piece, Klotsky::Piece pieceType) const;

    static std::vector<Klotsky> solvePuzzleBFS(const Klotsky& initialState);
    // A* algorithm implementation

    static std::vector<Klotsky> solvePuzzleAStar(const Klotsky& initialState, bool admissible);

    std::vector<Klotsky> solvePuzzleIDAStar(const Klotsky& initialState, bool admissible, bool withTransposition);

    int depthLimitedSearch(const Klotsky& state, std::unordered_set<std::pair<int, Klotsky>, PairHash, PairEqual>& visited,
                            std::vector<Klotsky>& path, int g, int depthLimit,  bool admissible, bool withTransposition);

    //the difference in safe shift and unsafe is that the safe one removes the bits that are outside the board.

    static std::string getStringOfType(Piece pieceType);
    static std::string directionToString(Direction direction);

    static std::bitset<25> shiftUpUnsafe(std::bitset<25> bitset) ;
    static std::bitset<25> shiftDownUnsafe(std::bitset<25> bitset) ;
    static std::bitset<25> shiftLeftUnsafe(std::bitset<25> bitset) ;
    static std::bitset<25> shiftRightUnsafe(std::bitset<25> bitset) ;
    static std::bitset<25> shiftDirectionUnsafe(std::bitset<25> bitset, Klotsky::Direction direction) ;


    std::bitset<25> shiftDirection(std::bitset<25> bitset, Direction direction) const;
    std::bitset<25> shiftUp(std::bitset<25> bitset) const;
    std::bitset<25> shiftDown(std::bitset<25> bitset) const;
    std::bitset<25> shiftLeft(std::bitset<25> bitset) const;
    std::bitset<25> shiftRight(std::bitset<25> bitset) const;

    void print() const;
    void printTarget() const;
    void printH(bool admissible) const;

};

// Specialization of std::hash for Klotsky
namespace std {
    template<>
    struct hash<Klotsky> {
        std::size_t operator()(const Klotsky& klotsky) const {
            Klotsky::KlotskyHash hasher;
            return hasher(klotsky);
        }
    };
}
#endif //KLOTSKI_KLOTSKY_H
