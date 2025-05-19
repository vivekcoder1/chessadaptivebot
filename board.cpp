#include <iostream>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <bitset>
using namespace std;
const uint64_t not_a_file = 18374403900871474942ULL;
const uint64_t not_h_file = 9187201950435737471ULL;
const uint64_t not_hg_file = 4557430888798830399ULL;
const uint64_t not_ab_file = 18229723555195321596ULL;
struct board{
    uint64_t white_pawns;
    uint64_t white_knights;
    uint64_t white_bishops; 
    uint64_t white_rooks; 
    uint64_t white_queen; 
    uint64_t white_king;   

    uint64_t black_pawns;  
    uint64_t black_knights;
    uint64_t black_bishops;
    uint64_t black_rooks;
    uint64_t black_queen;
    uint64_t black_king; 
    bool turn;
    //A state of 0 is white's move, a state of 1 is black's move
    uint64_t whitepieces() {
        return white_pawns | white_knights | white_bishops | white_rooks | white_queen | white_king;
    }

    uint64_t blackpieces() {
        return black_pawns | black_knights | black_bishops | black_rooks | black_queen | black_king;
    }

    uint64_t totboard() {
        return whitepieces() | blackpieces();
    }
};
board initstate(){
    board initboard;
    initboard.white_pawns= 0x000000000000FF00ULL;
    initboard.white_knights = 0x0000000000000042ULL;
    initboard.white_bishops = 0x0000000000000024ULL;
    initboard.white_rooks = 0x0000000000000081ULL;
    initboard.white_queen = 0x0000000000000008ULL;
    initboard.white_king = 0x0000000000000010ULL;
    initboard.black_pawns = 0x00FF000000000000ULL;
    initboard.black_knights = 0x4200000000000000ULL;
    initboard.black_bishops =0x2400000000000000ULL;
    initboard.black_rooks = 0x8100000000000000ULL;
    initboard.black_queen =0x0800000000000000ULL;
    initboard.black_king= 0x1000000000000000ULL;
    initboard.turn=0;
    return initboard;
};
vector<tuple<int,int>> getLegal(board state){
    vector<tuple<int,int>> output;
    if (!state.turn){
        // legal moves for white
        // find legal moves of pawns

    }
    if (state.turn){

    }
    return output;
}
unordered_map<int, string> mintspace{
    {0,  "a8"}, {1,  "b8"}, {2,  "c8"}, {3,  "d8"}, {4,  "e8"}, {5,  "f8"}, {6,  "g8"}, {7,  "h8"},
    {8,  "a7"}, {9,  "b7"}, {10, "c7"}, {11, "d7"}, {12, "e7"}, {13, "f7"}, {14, "g7"}, {15, "h7"},
    {16, "a6"}, {17, "b6"}, {18, "c6"}, {19, "d6"}, {20, "e6"}, {21, "f6"}, {22, "g6"}, {23, "h6"},
    {24, "a5"}, {25, "b5"}, {26, "c5"}, {27, "d5"}, {28, "e5"}, {29, "f5"}, {30, "g5"}, {31, "h5"},
    {32, "a4"}, {33, "b4"}, {34, "c4"}, {35, "d4"}, {36, "e4"}, {37, "f4"}, {38, "g4"}, {39, "h4"},
    {40, "a3"}, {41, "b3"}, {42, "c3"}, {43, "d3"}, {44, "e3"}, {45, "f3"}, {46, "g3"}, {47, "h3"},
    {48, "a2"}, {49, "b2"}, {50, "c2"}, {51, "d2"}, {52, "e2"}, {53, "f2"}, {54, "g2"}, {55, "h2"},
    {56, "a1"}, {57, "b1"}, {58, "c1"}, {59, "d1"}, {60, "e1"}, {61, "f1"}, {62, "g1"}, {63, "h1"}
};

unordered_map<string, int> mspaceint{
    {"a8", 0},  {"b8", 1},  {"c8", 2},  {"d8", 3},  {"e8", 4},  {"f8", 5},  {"g8", 6},  {"h8", 7},
    {"a7", 8},  {"b7", 9},  {"c7",10},  {"d7",11},  {"e7",12},  {"f7",13},  {"g7",14},  {"h7",15},
    {"a6",16},  {"b6",17},  {"c6",18},  {"d6",19},  {"e6",20},  {"f6",21},  {"g6",22},  {"h6",23},
    {"a5",24},  {"b5",25},  {"c5",26},  {"d5",27},  {"e5",28},  {"f5",29},  {"g5",30},  {"h5",31},
    {"a4",32},  {"b4",33},  {"c4",34},  {"d4",35},  {"e4",36},  {"f4",37},  {"g4",38},  {"h4",39},
    {"a3",40},  {"b3",41},  {"c3",42},  {"d3",43},  {"e3",44},  {"f3",45},  {"g3",46},  {"h3",47},
    {"a2",48},  {"b2",49},  {"c2",50},  {"d2",51},  {"e2",52},  {"f2",53},  {"g2",54},  {"h2",55},
    {"a1",56},  {"b1",57},  {"c1",58},  {"d1",59},  {"e1",60},  {"f1",61},  {"g1",62},  {"h1",63}
};
uint64_t setbit(uint64_t bitboard, string square){
    return bitboard | (1ULL<<(64-mspaceint[square]));
}
void printboard(uint64_t bitboard){
    for (int j=7;j>=0;j--){
        for (int i=0;i<8;i++){
            int square = j*8+i;
            uint64_t temp = 1ULL<<square;
            if (bitboard & temp) cout<<1;
            else cout<<0;
        }
        cout<<endl;
    }
}

int main(){
    board tuffboard = initstate();
    cout<<hex<<(tuffboard.blackpieces()<<8)<<endl;
    cout<<(242>>1)<<endl;
    printboard(tuffboard.blackpieces());
    cout<<endl;
}
