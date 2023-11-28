#include "BlackBishop.h"


CBlackBishop::CBlackBishop() :
	CPiece(eColor::Black, "b", 3)
{
	makeMoves();
}

void CBlackBishop::makeMoves()
{

	CMove DiagonalContinuous{ eMovePattern::Diagonal, eMoveNumber::Continuous, true};
	m_Moves.push_back(DiagonalContinuous);
}