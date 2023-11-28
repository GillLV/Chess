#include "BlackPawn.h"

CBlackPawn::CBlackPawn() :
	CPiece(eColor::Black, "p", 1)
{
	makeMoves();
}

void CBlackPawn::makeMoves() {

	CMove ForwardOne{ eMovePattern::Forward, eMoveNumber::Once, false };
	m_Moves.push_back(ForwardOne);

	CMove ForwardTwice{ eMovePattern::Forward, eMoveNumber::Twice, false };
	m_Moves.push_back(ForwardTwice);

	CMove DiagonalCapture{ eMovePattern::Diagonal, eMoveNumber::Once, true };
	m_Moves.push_back(DiagonalCapture);
};
