#ifndef H_QUEEN
#define H_QUEEN

#include "Piece.h"

class CQueen : public CPiece {

public:
	CQueen(eColor color, Coord coord);


private:

	void makeMoves() override;


};

#endif