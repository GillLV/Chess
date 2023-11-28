#ifndef H_ROOK
#define H_ROOK

#include "Piece.h"

class CRook : public CPiece {

public:
	CRook();


private:

	void makeMoves() override;


};

#endif
