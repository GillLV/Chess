#ifndef H_PIECE_FACTORY
#define H_PIECE_FACTORY

#include<utility>
#include "Piece.h"

class CPieceFactory { 

public:
	std::shared_ptr<CPiece> CreatePiece(Coord pair);

};




#endif
