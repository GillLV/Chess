#include "WhiteKSRook.h"


CWhiteKSRook::CWhiteKSRook() :
	CPiece(eColor::White, "R", 5)
{
	makeMoves();
}

void CWhiteKSRook::makeMoves()
{
	//CASTLING!!!!!!!!!!!!
	CMove AdjacentContinuous{ eMovePattern::Adjacent, eMoveNumber::Continuous, true, false };
	m_Moves.push_back(AdjacentContinuous);

	CMove


}