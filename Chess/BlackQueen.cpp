#include "BlackQueen.h"


CBlackQueen::CBlackQueen() :
	CPiece(eColor::Black, "q", 9)
{
	makeMoves();
}

void CBlackQueen::makeMoves()
{

	CMove AdjacentContinuous{ eMovePattern::Adjacent, eMoveNumber::Continuous, true };
	m_Moves.push_back(AdjacentContinuous);

	CMove DiagonalContinuous{ eMovePattern::Diagonal, eMoveNumber::Continuous, true };
	m_Moves.push_back(DiagonalContinuous);

}