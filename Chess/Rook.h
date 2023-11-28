#ifndef H_ROOK
#define H_ROOK

#include "Piece.h"

enum class eSide {
	QS = 0,
	KS,

	Size
};

class CRook : public CPiece {

public:
	CRook(eColor color, Coord coord, eSide side);


private:

	eSide m_Side;

	void makeMoves() override;


};

#endif
