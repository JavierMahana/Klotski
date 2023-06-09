//
// Created by Javier on 18-05-2023.
//

#include <queue>
#include <unordered_set>
#include <algorithm>

#include "Klotsky.h"
#include "NodeKlotsky.h"


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


bool Klotsky::operator==(const Klotsky &other) const {

    if(
    bits_1X1_A == other.bits_1X1_A &&
    bits_1X1_B == other.bits_1X1_B &&
    bits_1X1_C == other.bits_1X1_C &&
    bits_1X1_D == other.bits_1X1_D &&
    bits_1X2 == other.bits_1X2 &&
    bits_2X1_A == other.bits_2X1_A &&
    bits_2X1_C == other.bits_2X1_C &&
    bits_2X1_D == other.bits_2X1_D &&
    bits_2X2 == other.bits_2X2 &&
    parent == other.parent)
        return true;
    else
        return false;
}


void Klotsky::print() const {
    std::cout << "_____________" << std::endl;
    std::cout << "KLOTSKY BOARD" << std::endl;
    int j = 0;

    // Tablero
    for (int i = 24; i >= 0; --i) {

        if(i%5 != 0){

            std::cout << " ";

            if(bits_2X2[i] != 0) std::cout << _2x2_char;
            else if(bits_1X2[i] != 0)  std::cout << _1x2_char;
            else if(bits_1X1_A[i] != 0 ) std::cout << _1x1_Achar;
            else if(bits_1X1_B[i] != 0 ) std::cout << _1x1_Bchar;
            else if(bits_1X1_C[i] != 0 ) std::cout << _1x1_Cchar;
            else if(bits_1X1_D[i] != 0 ) std::cout << _1x1_Dchar;
            else if(bits_2X1_A[i] != 0 )  std::cout << _2x1_Achar;
            else if(bits_2X1_B[i] != 0 )  std::cout << _2x1_Bchar;
            else if(bits_2X1_C[i] != 0 )  std::cout << _2x1_Cchar;
            else if(bits_2X1_D[i] != 0 )  std::cout << _2x1_Dchar;
            else{
                std::cout << empty_char;
            }
        }

        j++;
        if(j==5){
            j = 0;
            std::cout<<std::endl;
        }
    }

}
void Klotsky::printO(bool show0, bool showA) const {

    std::cout << "____________" << std::endl;
    std::cout << "TARGET BOARD" << std::endl;
    int j = 0;

    // Tablero Reverso
    for (int i = 24; i >= 0; --i) {

        if(i%5 != 0){

            if(bits_2X2[i] != 0) std::cout << _2x2_char;
            else if(bits_1X1_A[i] != 0 ) std::cout << _1x1_Achar;
            else if(bits_1X1_B[i] != 0 ) std::cout << _1x1_Bchar;
            else if(bits_1X1_C[i] != 0 ) std::cout << _1x1_Cchar;
            else if(bits_1X1_D[i] != 0 ) std::cout << _1x1_Dchar;
            else{
                std::cout << " ";
            }

            std::cout << " ";
        }

        j++;
        if(j==5){
            j = 0;
            std::cout<<std::endl;
        }

    }

}
void Klotsky::printTarget() const {
    std::cout << "____________" << std::endl;
    std::cout << "TARGET BOARD" << std::endl;
    int j = 0;

    // Tablero Reverso
    for (int i = 24; i >= 0; --i) {

        if(i%5 != 0){

            std::cout << " ";
            if(bits_Target[i] != 0){
                std::cout << target_char;
            }
            else{
                std::cout << empty_char;
            }
        }


        j++;
        if(j==5){
            j = 0;
            std::cout<<std::endl;
        }
    }
}
void Klotsky::printH() const
{
    int dx,dy = 0;
    std::cout << "__________" << std::endl;
    std::cout << "Heuristics:" << std::endl;
    std::cout << " h = "<< calcH() << " |manhattan h = " << calcH_Manhattan(dy, dx) << " |blocking h = " << calcH_BlockingPieces(dy,dx) << " |manhattan2x1 h = " << calcH_Manhattan2x1() << std::endl;
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

std::vector<Klotsky> Klotsky::generatePieceMoves(Klotsky board, std::bitset<25> piece, Klotsky::Piece pieceType) const {
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

std::vector<Klotsky> Klotsky::generateAllLegalMoves(Klotsky board) const {
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

bool Klotsky::isGoalState() const {
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

std::vector<Klotsky> Klotsky::solvePuzzleAStar(const Klotsky &initialState) {
    auto compare = [](const std::shared_ptr<NodeKlotsky>& a, const std::shared_ptr<NodeKlotsky>& b) {
        return (a->getG() + a->getH()) > (b->getG() + b->getH());
    };

    //priority queue to order the open set
    std::priority_queue<std::shared_ptr<NodeKlotsky>, std::vector<std::shared_ptr<NodeKlotsky>>, decltype(compare)> openSet(compare);
    std::unordered_set<Klotsky, Klotsky::KlotskyHash, Klotsky::KlotskyEqual> closedSet;

    std::shared_ptr<NodeKlotsky> initialNode = std::make_shared<NodeKlotsky>();
    initialNode->board = initialState;
    initialNode->setG(0);
    initialNode->setH(initialNode->board.calcH());

    initialNode->print();
    //return std::vector<Klotsky>();

    openSet.push(initialNode);

    while (!openSet.empty()) {
        std::shared_ptr<NodeKlotsky> currentNode = openSet.top();
        openSet.pop();

        const Klotsky& currentBoard = currentNode->board;

        if (currentBoard.isGoalState()) {
            // Reconstruct the path
            std::vector<Klotsky> solution;
            while (currentNode->parent != nullptr) {
                solution.push_back(currentNode->board);
                currentNode = currentNode->parent;
            }
            std::reverse(solution.begin(), solution.end());

            std::cout << " ---solution found---" << std::endl;
            std::cout << "solution size: "<< solution.size() << std::endl;
            std::cout << "visited size: "<< closedSet.size() << std::endl;

            return solution;
        }

        closedSet.insert(currentBoard);

        std::vector<Klotsky> legalMoves = currentBoard.generateAllLegalMoves(currentBoard);
        for (const Klotsky& move : legalMoves) {
            std::shared_ptr<NodeKlotsky> newNode = std::make_shared<NodeKlotsky>();
            newNode->board = move;
            newNode->parent = currentNode;
            newNode->setG(currentNode->getG() + 1);
            newNode->setH(newNode->board.calcH());

            //if the new move is not in the closed set we add it to the open set.
            //falta chequear por duplicados!
            if (closedSet.find(move) == closedSet.end()) {
                openSet.push(newNode);
                closedSet.insert(move);
            }
        }
    }

    // No solution found
    return std::vector<Klotsky>();
}

Klotsky::~Klotsky() = default;

int Klotsky::calcH() const {
    int distY = 0;
    int distX = 0;
    int hM = calcH_Manhattan(distY, distX);
    int hB = calcH_BlockingPieces(distY, distX);

    int manhattan2x1 = calcH_Manhattan2x1();

    return  hB + hM + manhattan2x1;
}

int Klotsky::calcH_Manhattan(int& distY, int& distX) const {
    auto shiftingBits = bits_2X2;
    auto temp = shiftingBits;

    while (temp.count() == 4)
    {
        temp = shiftDown(shiftingBits);

        if(temp.count() >= 4)
        {
            shiftingBits = temp;
            distY ++;
        }
    }

    distX = (shiftingBits == bits_Target) ? 0 : 1;
    return distY + distX;
}

int Klotsky::calcH_BlockingPieces(int distY, int distX) const {
    int blockedSquaresFromGoal = 0;
    auto tempBoard = getFull() xor bits_2X2;
    auto shiftingBits = bits_2X2;

    for (int i = 0; i < distY; ++i)
    {
        shiftingBits = shiftDown(shiftingBits);

        auto blockedBits = tempBoard & shiftingBits;
        blockedSquaresFromGoal += blockedBits.count();
        tempBoard &= ~blockedBits;
    }

    if (distX != 0) {
        std::bitset<25> tempCopy = shiftingBits;
        shiftLeft(tempCopy);
        if (tempCopy == bits_Target) {
            auto blockedBits = tempBoard & tempCopy;
            blockedSquaresFromGoal += blockedBits.count();
        } else {
            shiftRight(shiftingBits);
            auto blockedBits = tempBoard & shiftingBits;
            blockedSquaresFromGoal += blockedBits.count();
        }
    }

    return blockedSquaresFromGoal;
}

//No admisible
int Klotsky::calcH_Manhattan2x1() const
{
    int manhattanDist = 0;
    for (int i = 0; i < 4; ++i) {
        std::bitset<25> shiftingBits;
        if(i == 0)
        {
            shiftingBits = bits_2X1_A;
        }else if(i == 1)
        {
            shiftingBits = bits_2X1_B;
        }else if(i == 2)
        {
            shiftingBits = bits_2X1_C;
        }else
        {
            shiftingBits = bits_2X1_D;
        }

        while (shiftingBits.count() == 2)
        {
            shiftingBits = shiftUp(shiftingBits);

            if(shiftingBits.count() >= 2)
            {
                manhattanDist ++;
            }
        }
    }
    return manhattanDist;
}

std::vector<Klotsky> Klotsky::solvePuzzleIDAStar(const Klotsky &initialState) {


    int visitedSize = 0;

    int depthLimit = initialState.calcH();

    int iterations = 1;

    std::unordered_set<std::pair<int, Klotsky>, PairHash, PairEqual> visited;

    while (true) {
        std::vector<Klotsky> path;

        //Optimization: The visited list works to prevent the repetition of moves. It is not complete now (needs to check fot the g value).

        std::cout << "Iteration : "<< iterations << " | depth search: " << depthLimit <<" | visited size: " << visited.size() << std::endl;
        iterations++;

        auto searchResult = depthLimitedSearch(initialState, visited, path, 0, depthLimit);

        //visitedSize += visited.size();
        //visited.clear();

        if (searchResult == -1)
        {
            std::cout << " ---solution found---" << std::endl;
            std::cout << "solution size: "<< path.size() << std::endl;
            std::cout << "visited size: "<< visitedSize << std::endl;

            return path;
        }
        else
        {
            depthLimit = searchResult;
        }

        if(depthLimit > 99999999)
        {
            std::cout << "IDA NOT FOUND" << std::endl;
            return {};
        }

         // Increase the depth limit if the solution was not found
    }

    // No solution found
    return {};
}


//returns -1 if found
int Klotsky::depthLimitedSearch(const Klotsky &state, std::unordered_set<std::pair<int, Klotsky>, PairHash, PairEqual> &visited, std::vector<Klotsky> &path,
                                 int g, int depthLimit) {

    int f = g + state.calcH();

    visited.emplace(g, state);
    path.push_back(state);

    if (state.isGoalState()) {
        return -1; // Solution found
    }

    if (f > depthLimit) {
        return f; // Reached the g limit without finding the solution
    }

    int min = INT_MAX;

    //bool solutionFound = false;

    std::vector<Klotsky> legalMoves = state.generateAllLegalMoves(state);

    //Optimization. Sort the legal moves, so it checks the most promising first.
    std::sort(legalMoves.begin(), legalMoves.end(), [](const Klotsky& move1, const Klotsky& move2) {
        return move1.calcH() < move2.calcH();
    });

    for (const auto& move : legalMoves)
    {

        auto elementOnVisited =  visited.find({g, move});
        if (elementOnVisited != visited.end())
        {
            if(elementOnVisited->first > g+1)
            {
                //if is greater it means that we should continue expanding and replace the value of the open list.
                //std::remove(visited.begin(), visited.end(),{g, move});
                visited.erase(elementOnVisited++);
            }
            else
            {//otherwise we skip the node
                continue;
            }
        }

        //We expand the search.
        int searchSolution = depthLimitedSearch(move, visited, path, g + 1, depthLimit);
        if (searchSolution == -1) {
            return -1; // Solution found, stop the search
        }
        if(searchSolution < min)
            min = searchSolution;

    }

    // Remove the current state from the path
    path.pop_back();

    return min; // Solution not found at this g level
}

Klotsky::Klotsky() = default;















//this version finds a solution fast. But a very large one: solution size: 38434
//visited size: 5503713
//std::vector<Klotsky> Klotsky::solvePuzzleIDAStar(const Klotsky &initialState) {
//
//
//    int visitedSize = 0;
//
//    int depthLimit = initialState.calcH();
//
//    while (true) {
//        //Optimization: The visited list works to prevent the repetition of moves. It is not complete now (needs to check fot the g value).
//
//        std::unordered_set<std::pair<int, Klotsky>, PairHash, PairEqual> visited;
//        //std::unordered_set<Klotsky, KlotskyHash, KlotskyEqual> visited;
//        std::vector<Klotsky> path;
//
//        auto searchResult = depthLimitedSearch(initialState, visited, path, 0, depthLimit);
//
//        visitedSize += visited.size();
//        visited.clear();
//
//        if (searchResult == -1)
//        {
//            std::cout << " ---solution found---" << std::endl;
//            std::cout << "solution size: "<< path.size() << std::endl;
//            std::cout << "visited size: "<< visitedSize << std::endl;
//
//            return path;
//        }
//        else
//        {
//            depthLimit = searchResult;
//        }
//
//        if(depthLimit > 300)
//        {
//            std::cout << "IDA NOT FOUND" << std::endl;
//            return {};
//        }
//
//        // Increase the depth limit if the solution was not found
//    }
//
//    // No solution found
//    return {};
//}
//
//
////returns -1 if found
//int Klotsky::depthLimitedSearch(const Klotsky &state, std::unordered_set<std::pair<int, Klotsky>, PairHash, PairEqual> &visited, std::vector<Klotsky> &path,
//                                int g, int depthLimit) {
//
//    //std::cout << "iteration" << std::endl;
//    int f = g + state.calcH();
//
//    visited.emplace(g, state);
//    //visited.insert(std::make_pair(g, state));
//    path.push_back(state);
//
//    if (state.isGoalState()) {
//        return -1; // Solution found
//    }
//
//    if (f > depthLimit) {
//        return f; // Reached the g limit without finding the solution
//    }
//
//    int min = INT_MAX;
//
//    //bool solutionFound = false;
//
//    std::vector<Klotsky> legalMoves = state.generateAllLegalMoves(state);
//
//    //Optimization. Sort the legal moves, so it checks the most promising first.
//    std::sort(legalMoves.begin(), legalMoves.end(), [](const Klotsky& move1, const Klotsky& move2) {
//        return move1.calcH() < move2.calcH();
//    });
//
//    for (const auto& move : legalMoves) {
//
//        auto elementOnVisited = visited.find (std::make_pair(g, move));
//
//        if (elementOnVisited == visited.end())
//        {
//            int searchSolution = depthLimitedSearch(move, visited, path, g + 1, depthLimit);
//            if (searchSolution == -1) {
//                return -1; // Solution found, stop the search
//            }
//            if(searchSolution < min)
//                min = searchSolution;
//
//        }
//
//    }
//
//    // Remove the current state from the path
//    path.pop_back();
//
//    return min; // Solution not found at this g level
//}







