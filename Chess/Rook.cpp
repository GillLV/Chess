#include "Rook.h"


CRook::CRook(eColor color, Coord coord, eSide side) :
	CPiece(color, "R", 5, coord),
	m_Side(side)
{
	makeMoves();
}

void CRook::makeMoves()
{
	
	CMove AdjacentContinuous{ eMovePattern::Adjacent, eMoveNumber::Continuous, true };
	m_Moves.push_back(AdjacentContinuous);

}