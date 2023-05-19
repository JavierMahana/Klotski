#include <iostream>
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
    std::cout << " Welcome to Klotsky: " <<std::endl;
    k.print();
    k.printTarget();

    auto allMoves = k.generateAllLegalMoves();

    for (const auto& move : allMoves) {
        move.print();
        //move.printO(false, true);
    }


    //TODO
    //LA GENERACION DE MOVIDAS ES POR COPIA, QUIZAS ES MEJOR HACER POR REFERENCIA ASI NO SE GASTA TANTA MEMORIA.

    return 0;
}