#include <string>
inline uint64_t bitscanForward(uint64_t bb) {
//    assert(bb != 0);
    return __builtin_ctzll(bb);
}

inline uint64_t lsbReset(uint64_t number) {
    return number & (number - 1);;
}
struct board{
    U64 white_pawns;
    U64 white_knights;
    U64 white_bishops; 
    U64 white_rooks; 
    U64 white_queen; 
    U64 white_king;   

    U64 black_pawns;  
    U64 black_knights;
    U64 black_bishops;
    U64 black_rooks;
    U64 black_queen;
    U64 black_king;
    U64 attacked;
    bool turn;
    bool check;
    //A state of 0 is white's move, a state of 1 is black's move
    // if check==0, no check, there is check if check==1
    U64 whitepieces() {
        return white_pawns | white_knights | white_bishops | white_rooks | white_queen | white_king;
    }

    U64 blackpieces() {
        return black_pawns | black_knights | black_bishops | black_rooks | black_queen | black_king;
    }

    U64 totboard() {
        return whitepieces() | blackpieces();
    }
    U64 white_attacked(){
        U64 temp;
        //filler until I do this
        return temp;
    }
    U64 black_attacked(){
        U64 temp; 
        //filler until I do this
        return temp;
    }
};
struct Move{
    int from;
    int to;
    string promotion;
    int piecetype; 
    //types: for white:: (0 is  pawns), (1 is knights) (2 is bishops) (3 is rooks) (4 is queen) (5 is king)
    //for black:: (6 is pawns) (7 is knights) (8 is bishops) (9 is rooks) (10 is queen ) (11 is king)
    //this is also specifically only for the piece that it is before the board changes
    bool operator==(const Move& other) const {
    return from == other.from && to == other.to && promotion == other.promotion && piecetype == other.piecetype;
}
};
