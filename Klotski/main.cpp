#include <iostream>
#include <chrono>
#include "Klotsky.h"

int main() {
    std::bitset<25> start_bits_1X1_A {"00000"
                                      "00000"
                                      "00000"
                                      "00000"
                                      "10000"};
    std::bitset<25> start_bits_1X1_B{"00000"
                                     "00000"
                                     "00000"
                                     "00000"
                                     "00010"};
    std::bitset<25> start_bits_1X1_C{"00000"
                                     "00000"
                                     "00000"
                                     "01000"
                                     "00000"};
    std::bitset<25> start_bits_1X1_D{"00000"
                                     "00000"
                                     "00000"
                                     "00100"
                                     "00000"};
    std::bitset<25> start_bits_1X2{"00000"
                                   "00000"
                                   "01100"
                                   "00000"
                                   "00000"};
    std::bitset<25> start_bits_2X1_A{"00000"
                                     "00000"
                                     "10000"
                                     "10000"
                                     "00000"};
    std::bitset<25> start_bits_2X1_B{"10000"
                                     "10000"
                                     "00000"
                                     "00000"
                                     "00000"};
    std::bitset<25> start_bits_2X1_C{"00000"
                                     "00000"
                                     "00010"
                                     "00010"
                                     "00000"};
    std::bitset<25> start_bits_2X1_D{"00010"
                                     "00010"
                                     "00000"
                                     "00000"
                                     "00000"};
    std::bitset<25> start_bits_2x2{"01100"
                                   "01100"
                                   "00000"
                                   "00000"
                                   "00000"};


    Klotsky k = Klotsky(start_bits_1X1_A, start_bits_1X1_B, start_bits_1X1_C,start_bits_1X1_D, start_bits_1X2, start_bits_2X1_A,start_bits_2X1_B,start_bits_2X1_C,start_bits_2X1_D,start_bits_2x2);


    //To modify the execution, change the bool variables below.

    //Prints the sequence of all the moves that it takes to find a solution.
    bool printAllMoves = false;

    //Admissible heuristic is slower than the not admissible
    bool admissibleHeuristic = false;
    //Use IDA* with a transposition table?
    bool withTransposition = false;

    //human play
    bool play = true;
    //What algorithms to use to solve the puzzle
    bool doBFS = false;
    bool doAStar = false;
    bool doIDA = false;

    std::cout << "-------------- KLOTSKY C++ --------------" <<std::endl;
    k.print();
    k.printH(admissibleHeuristic);

    // Algorithms
    if (doBFS)
    {
        auto start = std::chrono::high_resolution_clock::now();
        auto solution = Klotsky::solvePuzzleBFS(k);

        if(printAllMoves)
        {
            for (const auto& move : solution) {
                move.print();
            }
        } else
        {
            solution.back().print();
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "BFS Solution time: " << duration << " milliseconds" << std::endl;

    }

    if(doAStar){

        auto start = std::chrono::high_resolution_clock::now();
        auto solutionAStar = Klotsky::solvePuzzleAStar(k,admissibleHeuristic);

        if(printAllMoves)
        {
            for (const auto& move : solutionAStar) {
                move.print();
            }
        } else
        {
            solutionAStar.back().print();

        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "AStar Solution time: " << duration << " milliseconds" << std::endl;
    }

    if(doIDA){

        auto start = std::chrono::high_resolution_clock::now();
        auto solutionIDA = k.solvePuzzleIDAStar(k,admissibleHeuristic,withTransposition);


        if(printAllMoves)
        {
            for (const auto& move : solutionIDA) {
                move.print();
            }
        } else
        {
            solutionIDA.back().print();
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "IDA Solution time: " << duration << " milliseconds" << std::endl;


    }

    // Play Game
    if(play){
        std::cout << "-----------------------" <<std::endl;
        std::cout << "      USER PLAYS" <<std::endl;
        std::cout << "DIRECTIONS:" << std::endl;
        std::cout << "  Left: l" <<   std::endl;
        std::cout << "  Right: r" <<  std::endl;
        std::cout << "  Up: u" <<   std::endl;
        std::cout << "  Down: d" <<   std::endl;
        std::cout << "  Change piece: z" << std::endl;
        std::cout << "OBJECTIVE: The O Piece must reach the target Board" << std::endl;
        k.printTarget();
        std::cout << std::endl;

        std::vector<Klotsky> move;
        std::bitset<25> pieceToMove;
        Klotsky::Piece pieceToMoveType;

        Klotsky::Direction direction;
        Klotsky mask;
        char input;
        bool playing = true;
        bool validDirection = false;

        while(playing)
        {
            k.print();

            bool pieceSet = false;
            bool directionSet = false;
            move.clear();


            // Selection of the piece to move
            while (!pieceSet){
                std::cout << "Enter the piece that you want to move: ";
                std::cin >> input;
                switch (input) {
                    case '1': {
                        pieceToMove = k.bits_1X1_A;
                        pieceToMoveType = Klotsky::Piece::A_1X1;
                        move = k.generatePieceMoves(k, k.bits_1X1_A, Klotsky::Piece::A_1X1);
                        break;
                    }
                    case '2': {
                        pieceToMove = k.bits_1X1_B;
                        pieceToMoveType = Klotsky::Piece::B_1X1;
                        move = k.generatePieceMoves(k, k.bits_1X1_B, Klotsky::Piece::B_1X1);
                        break;
                    }
                    case '3': {
                        pieceToMove = k.bits_1X1_C;
                        pieceToMoveType = Klotsky::Piece::C_1X1;
                        move = k.generatePieceMoves(k, k.bits_1X1_C, Klotsky::Piece::C_1X1);
                        break;
                    }
                    case '4': {
                        pieceToMove = k.bits_1X1_D;
                        pieceToMoveType = Klotsky::Piece::D_1X1;
                        move = k.generatePieceMoves(k, k.bits_1X1_D, Klotsky::Piece::D_1X1);
                        break;
                    }
                    case 'A': {
                        pieceToMove = k.bits_1X2;
                        pieceToMoveType = Klotsky::Piece::A_1X2;
                        move = k.generatePieceMoves(k, k.bits_1X2, Klotsky::Piece::A_1X2);
                        break;
                    }
                    case 'B': {
                        pieceToMove = k.bits_2X1_A;
                        pieceToMoveType = Klotsky::Piece::A_2X1;
                        move = k.generatePieceMoves(k, k.bits_2X1_A, Klotsky::Piece::A_2X1);
                        break;
                    }
                    case 'C': {
                        pieceToMove = k.bits_2X1_B;
                        pieceToMoveType = Klotsky::Piece::B_2X1;
                        move = k.generatePieceMoves(k, k.bits_2X1_B, Klotsky::Piece::B_2X1);
                        break;
                    }
                    case 'D': {
                        pieceToMove = k.bits_2X1_C;
                        pieceToMoveType = Klotsky::Piece::C_2X1;
                        move = k.generatePieceMoves(k, k.bits_2X1_C, Klotsky::Piece::C_2X1);
                        break;
                    }
                    case 'E': {
                        pieceToMove = k.bits_2X1_D;
                        pieceToMoveType = Klotsky::Piece::D_2X1;
                        move = k.generatePieceMoves(k, k.bits_2X1_D, Klotsky::Piece::D_2X1);
                        break;
                    }
                    case 'O': {
                        pieceToMove = k.bits_2X2;
                        pieceToMoveType = Klotsky::Piece::A_2X2;
                        move = k.generatePieceMoves(k, k.bits_2X2, Klotsky::Piece::A_2X2);
                        break;
                    }
                    default:
                        std::cout << "Invalid input entered. ";
                        break;
                }

                std::cin.clear();

                if(!move.empty()){
                    pieceSet = true;
                }
                else{
                    std::cout << "Invalid, that piece cannot move. ";
                }
            }

            // Selection of shift
            while (!directionSet){
                validDirection = false;
                std::cout << "Enter your direction(\"r\", \"l\", \"u\", \"d\"): ";
                std::cin >> input;

                switch(input){
                    case 'l': direction = Klotsky::Direction::LEFT;
                        validDirection = true;
                        break;
                    case 'r': direction = Klotsky::Direction::RIGHT;
                        validDirection = true;
                        break;
                    case 'u': direction = Klotsky::Direction::UP;
                        validDirection = true;
                        break;
                    case 'd': direction = Klotsky::Direction::DOWN;
                        validDirection = true;
                        break;
                    case 'z':
                        move.clear();
                        directionSet = true;
                        break;
                    default:
                        std::cout << "Invalid input entered try one of the available moves: "<<   std::endl;
                        std::cout << "Left: l" <<   std::endl;
                        std::cout << "Right: r" <<  std::endl;
                        std::cout << "Up: u" <<   std::endl;
                        std::cout << "Down: d" <<   std::endl;
                        break;
                }

                std::cin.clear();

                if(validDirection){
                    //Check if the direction allow a legal move
                    Klotsky boardWithoutPiece = k;
                    //first we remove the piece bits, so it become empty space.
                    boardWithoutPiece.removeBits(pieceToMove, pieceToMoveType);
                    std::bitset<25> shiftedPiece = pieceToMove;
                    shiftedPiece = k.shiftDirection(shiftedPiece,direction);
                    Klotsky newMove = boardWithoutPiece;
                    newMove.addBits(shiftedPiece, pieceToMoveType);

                    for (const auto& element : move) {
                        // if the move is legal
                        if(element == newMove){
                            // Make the move
                            k = newMove;
                            k.print();

                            directionSet = true;
                            break;
                        }
                    }
                    if(!directionSet){
                        std::cout << "Invalid move there is a piece on the way!" <<   std::endl;
                    }
                }
                else{
                    std::cout << "Invalid move there is a piece on the way!" <<   std::endl;
                }
            }

            playing = !k.isGoalState();
        }

        std::cout << "Well played you've won!!!" <<   std::endl;
    }

    return 0;
}
