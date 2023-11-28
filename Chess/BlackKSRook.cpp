#include "BlackKSRook.h"


CBlackKSRook::CBlackKSRook() :
	CPiece(eColor::Black, "r", 5)
{
	makeMoves();
}

void CBlackKQSRook::makeMoves()
{

	CMove AdjacentContinuous{ eMovePattern::Adjacent, eMoveNumber::Continuous, true, false };
	m_Moves.push_back(AdjacentContinuous);

}