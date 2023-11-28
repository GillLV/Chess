#include "BlackKnight.h"


CBlackKnight::CBlackKnight() :
	CPiece(eColor::Black, "n", 3)
{
	makeMoves();
}

void CBlackKnight::makeMoves()
{

	CMove LShapeOnce{ eMovePattern::LShape, eMoveNumber::Once, true };
	m_Moves.push_back(LShapeOnce);

}