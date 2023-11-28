#ifndef H_BISHOP
#define H_BISHOP

#include "Piece.h"

class CBishop : public CPiece {

public:
	CBishop(eColor color, Coord coord);


private:

	void makeMoves() override;


};

#endif