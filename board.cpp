#include <iostream>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include "maskgeneration.cpp"
#include "header.h"
#pragma once
using namespace std;

typedef int8_t Square;
typedef uint64_t U64;
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

void printboard(U64 bitboard){
    for (int j=7;j>=0;j--){
        for (int i=0;i<8;i++){
            int square = j*8+i;
            U64 temp = 1ULL<<square;
            if (bitboard & temp) cout<<1;
            else cout<<0;
        }
        cout<<endl;
    }
    cout<<'\n';
}
vector<Move> getLegal(board state){
    const U64 not_a_file = 18374403900871474942ULL;
    const U64 not_h_file = 9187201950435737471ULL;
    const U64 not_hg_file = 4557430888798830399ULL;
    const U64 not_ab_file = 18229723555195321596ULL;
    const U64 second_rank = 65280ULL;
    const U64 seventh_rank = 71776119061217280ULL;
    U64 empty_or_black = ~state.whitepieces();  // Allows moves to empty or enemy-occupied squares

    vector<Move> output;
    if (!state.turn){
        // legal moves for white
        // find legal moves of pawns
        U64 empty = ~state.totboard();
        U64 tuff= ((((second_rank & state.white_pawns)<<8) & empty)<<8) & empty;
        while (tuff){
            Square s= bitscanForward(tuff);
            output.push_back(Move{s-16,s,"", 0});
            tuff=lsbReset(tuff);
        }
        tuff=((state.white_pawns & (~seventh_rank))<<8) & empty;
        while (tuff){
            Square s= bitscanForward(tuff);
            output.push_back(Move{s-8,s,"",0});
            tuff=lsbReset(tuff);
        }
        //for promotions
        tuff=((state.white_pawns & seventh_rank)<<8) & empty;
        while (tuff){
            Square s= bitscanForward(tuff);
            output.push_back(Move{s-8,s,"Q",0});
            output.push_back(Move{s-8, s, "B",0});
            output.push_back(Move{s-8, s, "R",0});
            output.push_back(Move{s-8, s, "N",0});
            tuff=lsbReset(tuff);
        }
        //for attacks
        tuff =((state.white_pawns & not_a_file)<<9) & state.blackpieces();
        while(tuff){
            Square s = bitscanForward(tuff);
            output.push_back(Move{s-9, s, "",0});
            tuff = lsbReset(tuff);
        }
        tuff =((state.white_pawns & not_h_file)<<7) & state.blackpieces();
        while(tuff){
            Square s = bitscanForward(tuff);
            output.push_back(Move{ s-7, s, "",0});
            tuff = lsbReset(tuff);
        }
        //legal moves of knights
        tuff = state.white_knights ;
        while(tuff){
            Square s = bitscanForward(tuff);
            U64 temp = knightAttacks[s] & empty_or_black;
            while(temp){
                Square k = bitscanForward(temp);
                output.push_back(Move{s, k, "", 1});
                temp = lsbReset(temp);
            }
            tuff=lsbReset(tuff);
        }
        //all king moves 
        tuff = state.white_king;
        while(tuff){
            Square s = bitscanForward(tuff);
            U64 temp = kingAttacks[s] & empty_or_black;
            while(temp){
                Square k = bitscanForward(temp);
                output.push_back(Move{s, k, "", 5});
                temp = lsbReset(temp);
            }
            tuff=lsbReset(tuff);
        }

    }
    if (state.turn){
        
    }
    return output;
}
board make_move(board state, Move move2){
    U64 target = 1ULL << (move2.from);
    U64 antitarget = ~target;
    U64 fin = 1ULL << (move2.to);
    state.turn= !state.turn;
    vector<Move> LEGALMOVES = getLegal(state);
    bool a=0;
    for (Move move1:LEGALMOVES){
        if (move1 == move2){
            a=1;
        }
    }
    if (a) cout<<"LEGAL MOVE"<<endl;
    else cout<<"ILLEGAL MOVE"<<endl;
    if (move2.piecetype ==0) {
        state.white_pawns &= antitarget;
        state.white_pawns |= fin;
    }
    if (move2.piecetype ==1) {
        state.white_knights &= antitarget;
        state.white_knights |= fin;
    }
    if (move2.piecetype ==2) {
        state.white_bishops &= antitarget;
        state.white_bishops |= fin;
    }
    if (move2.piecetype ==3) {
        state.white_rooks &= antitarget;
        state.white_rooks |= fin;
    }
    if (move2.piecetype ==4) {
        state.white_queen &= antitarget;
        state.white_queen |= fin;
    }
    if (move2.piecetype ==5) {
        state.white_king &= antitarget;
        state.white_king |= fin;
    }
    if (move2.piecetype ==6) {
        state.black_pawns &= antitarget;
        state.black_pawns |= fin;
    }
    if (move2.piecetype ==7) {
        state.black_knights &= antitarget;
        state.black_knights |= fin;
    }
    if (move2.piecetype ==8) {
        state.black_bishops &= antitarget;
        state.black_bishops |= fin;
    }
    if (move2.piecetype ==9) {
        state.black_rooks &= antitarget;
        state.black_rooks |= fin;
    }
    if (move2.piecetype ==10) {
        state.black_queen &= antitarget;
        state.black_queen |= fin;
    }
    if (move2.piecetype ==11) {
        state.black_king &= antitarget;
        state.black_king |= fin;
    }
    
    return state;
};
void printlegal(vector<Move> MOVESVECT){
    for (int i=0;i<int(MOVESVECT.size());i++){
        cout<<MOVESVECT[i].piecetype<<mintspace[MOVESVECT[i].from]<<mintspace[MOVESVECT[i].to]<<MOVESVECT[i].promotion<<endl;
    }
    cout<<'\n';
}


int main(){
   //nothing for now
}
