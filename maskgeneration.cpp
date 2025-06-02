typedef uint64_t U64;
#include <array>
std::array<U64, 64> knightAttacks;
std::array<U64, 64> kingAttacks;

const U64 not_a_file = 18374403900871474942ULL;
const U64 not_h_file = 9187201950435737471ULL;
const U64 not_hg_file = 4557430888798830399ULL;
const U64 not_ab_file = 18229723555195321596ULL;
const U64 second_rank = 65280ULL;
const U64 seventh_rank = 71776119061217280ULL;
U64 maskKnightAttacks(int square) {
    U64 attacks = 0ULL;
    U64 bitboard = 1ULL << square;

    if ((bitboard >> 17) & not_h_file) attacks |= (bitboard >> 17);
    if ((bitboard >> 15) & not_a_file) attacks |= (bitboard >> 15);
    if ((bitboard >> 10) & not_hg_file) attacks |= (bitboard >> 10);
    if ((bitboard >> 6) & not_ab_file) attacks |= (bitboard >> 6);
    if ((bitboard << 17) & not_a_file) attacks |= (bitboard << 17);
    if ((bitboard << 15) & not_h_file) attacks |= (bitboard << 15);
    if ((bitboard << 10) & not_ab_file) attacks |= (bitboard << 10);
    if ((bitboard << 6) & not_hg_file) attacks |= (bitboard << 6);

    return attacks;
}
U64 maskKingAttacks(int square) {
    U64 attacks = 0ULL;
    U64 bitboard = 1ULL << square;
    if ((bitboard >> 8)) attacks |= (bitboard >> 8); 
    if ((bitboard << 8)) attacks |= (bitboard << 8);
    if ((bitboard >> 1) & not_h_file) attacks |= (bitboard >> 1);
    if ((bitboard << 1) & not_a_file) attacks |= (bitboard << 1); 

    if ((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);
    if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
    if ((bitboard << 9) & not_a_file) attacks |= (bitboard << 9);
    if ((bitboard << 7) & not_h_file) attacks |= (bitboard << 7); 
    return attacks;
}
void initAttackMasks() {
    for (int square = 0; square < 64; square++) {
        knightAttacks[square] = maskKnightAttacks(square);
        kingAttacks[square] = maskKingAttacks(square);
    }
}
