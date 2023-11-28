#include "Knight.h"


CKnight::CKnight(eColor color, Coord coord) :
	CPiece(color, "N", 3, coord)
{
	makeMoves();
}

void CKnight::makeMoves()
{

	CMove LShapeOnce{ eMovePattern::LShape, eMoveNumber::Once, true };
	m_Moves.push_back(LShapeOnce);

}