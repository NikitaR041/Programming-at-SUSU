#ifndef CHECKERS_ENGINE_H
#define CHECKERS_ENGINE_H

#include <vector>

class CheckersEngine
{
public:
    static const int EMPTY = 0;
    static const int WHITE_PAWN = 1;
    static const int WHITE_KING = 2;
    static const int BLACK_PAWN = 3;
    static const int BLACK_KING = 4;

    CheckersEngine(int size);

    bool inBounds(int x, int y) const;
    bool isEmpty(int x, int y) const;
    bool isDiagonal(int fx, int fy, int tx, int ty) const;

    bool isOpponentPiece(int x, int y, int myPiece) const;
    bool canMoveSimple(int fx, int fy, int tx, int ty) const;
    bool canCaptureMove(int fx, int fy, int tx, int ty) const;
    bool hasCapture(int x, int y) const;

    bool playerHasAnyCapture(int player) const;
    bool playerHasMoves(int player) const;
    bool playerHasPieces(int player) const;

    void performMove(int fx, int fy, int tx, int ty);
    void checkForKing(int x, int y);

    std::vector<std::vector<int>> board;

private:
    int SIZE;
};

#endif

