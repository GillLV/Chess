#ifndef H_KNIGHT
#define H_KNIGHT

#include "Piece.h"

class CKnight : public CPiece {

public:
	CKnight(eColor color, Coord coord);


private:

	void makeMoves() override;


};

#endif
