#include "BlackRook.h"


CBlackRook::CBlackRook() :
	CPiece(eColor::Black, "r", 5)
{
	makeMoves();
}

void CBlackRook::makeMoves()
{

	CMove AdjacentContinuous{ eMovePattern::Adjacent, eMoveNumber::Continuous, true };
	m_Moves.push_back(AdjacentContinuous);

}