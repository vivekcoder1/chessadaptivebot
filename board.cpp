#include <iostream>
#include "headers.h"
using namespace std;

typedef int8_t Square;
inline Square bitscanForward(uint64_t bb) {
//    assert(bb != 0);
    return __builtin_ctzll(bb);
}

inline uint64_t lsbReset(uint64_t number) {
    return number & (number - 1);;
}
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
    uint64_t attacked;
    bool turn;
    bool check;
    //A state of 0 is white's move, a state of 1 is black's move
    // if check==0, no check, there is check if check==1
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
struct Move{
    int from;
    int to;
    string promotion;
    bool operator==(const Move& other) const {
    return from == other.from && to == other.to && promotion == other.promotion;
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

unordered_map<int, string> mintspace{
    {0,  "h1"}, {1,  "g1"}, {2,  "f1"}, {3,  "e1"}, {4,  "d1"}, {5,  "c1"}, {6,  "b1"}, {7,  "a1"},
    {8,  "h2"}, {9,  "g2"}, {10, "f2"}, {11, "e2"}, {12, "d2"}, {13, "c2"}, {14, "b2"}, {15, "a2"},
    {16, "h3"}, {17, "g3"}, {18, "f3"}, {19, "e3"}, {20, "d3"}, {21, "c3"}, {22, "b3"}, {23, "a3"},
    {24, "h4"}, {25, "g4"}, {26, "f4"}, {27, "e4"}, {28, "d4"}, {29, "c4"}, {30, "b4"}, {31, "a4"},
    {32, "h5"}, {33, "g5"}, {34, "f5"}, {35, "e5"}, {36, "d5"}, {37, "c5"}, {38, "b5"}, {39, "a5"},
    {40, "h6"}, {41, "g6"}, {42, "f6"}, {43, "e6"}, {44, "d6"}, {45, "c6"}, {46, "b6"}, {47, "a6"},
    {48, "h7"}, {49, "g7"}, {50, "f7"}, {51, "e7"}, {52, "d7"}, {53, "c7"}, {54, "b7"}, {55, "a7"},
    {56, "h8"}, {57, "g8"}, {58, "f8"}, {59, "e8"}, {60, "d8"}, {61, "c8"}, {62, "b8"}, {63, "a8"}
};
unordered_map<string, int> mspaceint{
    {"h1", 0},  {"g1", 1},  {"f1", 2},  {"e1", 3},  {"d1", 4},  {"c1", 5},  {"b1", 6},  {"a1", 7},
    {"h2", 8},  {"g2", 9},  {"f2",10},  {"e2",11},  {"d2",12},  {"c2",13},  {"b2",14},  {"a2",15},
    {"h3",16},  {"g3",17},  {"f3",18},  {"e3",19},  {"d3",20},  {"c3",21},  {"b3",22},  {"a3",23},
    {"h4",24},  {"g4",25},  {"f4",26},  {"e4",27},  {"d4",28},  {"c4",29},  {"b4",30},  {"a4",31},
    {"h5",32},  {"g5",33},  {"f5",34},  {"e5",35},  {"d5",36},  {"c5",37},  {"b5",38},  {"a5",39},
    {"h6",40},  {"g6",41},  {"f6",42},  {"e6",43},  {"d6",44},  {"c6",45},  {"b6",46},  {"a6",47},
    {"h7",48},  {"g7",49},  {"f7",50},  {"e7",51},  {"d7",52},  {"c7",53},  {"b7",54},  {"a7",55},
    {"h8",56},  {"g8",57},  {"f8",58},  {"e8",59},  {"d8",60},  {"c8",61},  {"b8",62},  {"a8",63}
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
vector<Move> getLegal(board state){
    const uint64_t not_a_file = 18374403900871474942ULL;
    const uint64_t not_h_file = 9187201950435737471ULL;
    const uint64_t not_hg_file = 4557430888798830399ULL;
    const uint64_t not_ab_file = 18229723555195321596ULL;
    const uint64_t second_rank = 65280ULL;
    const uint64_t seventh_rank = 71776119061217280ULL;
    vector<Move> output;
    if (!state.turn){
        // legal moves for white
        // find legal moves of pawns
        uint64_t occupied = ~state.totboard();
        uint64_t tuff= ((second_rank & state.white_pawns)<<16) & occupied;
        while (tuff){
            Square s= bitscanForward(tuff);
            output.push_back(Move{s-16,s,""});
            tuff=lsbReset(tuff);
        }
        tuff=((state.white_pawns & (~seventh_rank))<<8) & occupied;
        while (tuff){
            Square s= bitscanForward(tuff);
            output.push_back(Move{s-8,s,""});
            tuff=lsbReset(tuff);
        }
        //for promotions
        tuff=((state.white_pawns & seventh_rank)<<8) & occupied;
        while (tuff){
            Square s= bitscanForward(tuff);
            output.push_back(Move{s-8,s,"Q"});
            output.push_back(Move{s-8, s, "B"});
            output.push_back(Move{s-8, s, "R"});
            output.push_back(Move{s-8, s, "N"});
            tuff=lsbReset(tuff);
        }
        //for attacks
        tuff =((state.white_pawns & not_a_file)<<9) & state.blackpieces();
        while(tuff){
            Square s = bitscanForward(tuff);
            output.push_back(Move{s-9, s, ""});
            tuff = lsbReset(tuff);
        }
        tuff =((state.white_pawns & not_h_file)<<7) & state.blackpieces();
        while(tuff){
            Square s = bitscanForward(tuff);
            output.push_back(Move{ s-7, s, ""});
            tuff = lsbReset(tuff);
        }
        //legal moves of knights
        //up or down moves first
        tuff = ((state.white_knights & not_a_file))&occupied;

    }
    if (state.turn){
        
    }
    return output;
}
board make_move(board state, Move move2){
    uint64_t target = 1ULL << (move2.from);
    uint64_t antitarget = ~target;
    uint64_t fin = 1ULL << (move2.to);
    vector<Move> LEGALMOVES = getLegal(state);
    bool a=0;
    for (Move move1:LEGALMOVES){
        if (move1 == move2){
            a=1;
        }
    }
    if (a) cout<<"LEGAL MOVE"<<endl;
    else cout<<"ILLEGAL MOVE"<<endl;
    if (state.white_pawns & target) {
        state.white_pawns &= antitarget;
        state.white_pawns |= fin;
    }
    if (state.white_knights & target) {
        state.white_knights &= antitarget;
        state.white_knights |= fin;
    }
    if (state.white_bishops & target) {
        state.white_bishops &= antitarget;
        state.white_bishops |= fin;
    }
    if (state.white_rooks & target) {
        state.white_rooks &= antitarget;
        state.white_rooks |= fin;
    }
    if (state.white_queen & target) {
        state.white_queen &= antitarget;
        state.white_queen |= fin;
    }
    if (state.white_king & target) {
        state.white_king &= antitarget;
        state.white_king |= fin;
    }
    if (state.black_pawns & target) {
        state.black_pawns &= antitarget;
        state.black_pawns |= fin;
    }
    if (state.black_knights & target) {
        state.black_knights &= antitarget;
        state.black_knights |= fin;
    }
    if (state.black_bishops & target) {
        state.black_bishops &= antitarget;
        state.black_bishops |= fin;
    }
    if (state.black_rooks & target) {
        state.black_rooks &= antitarget;
        state.black_rooks |= fin;
    }
    if (state.black_queen & target) {
        state.black_queen &= antitarget;
        state.black_queen |= fin;
    }
    if (state.black_king & target) {
        state.black_king &= antitarget;
        state.black_king |= fin;
    }
    
    return state;
};
void printlegal(vector<Move> MOVESVECT){
    for (int i=0;i<int(MOVESVECT.size());i++){
        cout<<mintspace[MOVESVECT[i].from]<<mintspace[MOVESVECT[i].to]<<MOVESVECT[i].promotion<<endl;
    }
}


int main(){
    board tuffboard = initstate();
    printlegal(getLegal(tuffboard));
    cout<<'\n';
    
    printlegal(getLegal(make_move(tuffboard, Move{mspaceint["e2"],mspaceint["e4"],""})));
}
