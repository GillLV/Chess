#include "Bishop.h"


CBishop::CBishop(eColor color, Coord coord) :
	CPiece(color, "B" , 3, coord)
{
	makeMoves();
}

void CBishop::makeMoves()
{

	CMove DiagonalContinuous{ eMovePattern::Diagonal, eMoveNumber::Continuous, true };
	m_Moves.push_back(DiagonalContinuous);
}