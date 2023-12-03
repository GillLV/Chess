#include "Pawn.h"

CPawn::CPawn(eColor color, Coord coord): 
	CPiece(color, "P", 1, coord),
	m_CanTakeEnPassantQS(false),
	m_CanTakeEnPassantKS(false),
	m_CanBeTakenEnPassant(false)
{
	makeMoves();
}

void CPawn::makeMoves( ) {

	CMove ForwardOne{ eMovePattern::Forward, eMoveNumber::Once, false };
	m_Moves.push_back(ForwardOne);

	CMove ForwardTwice{ eMovePattern::Forward, eMoveNumber::Twice, false };
	m_Moves.push_back(ForwardTwice);

	CMove EnPassantQS{ eMovePattern::EnPassantQS, eMoveNumber::Once, true };
	m_Moves.push_back(EnPassantQS);

	CMove EnPassantKS{ eMovePattern::EnPassantKS, eMoveNumber::Once, true };
	m_Moves.push_back(EnPassantKS);
}

bool CPawn::canPromote()
{
	if (m_Color == eColor::White && m_CurrentCoord.second == eNumbers::Eight) return true;
	else if (m_Color == eColor::Black && m_CurrentCoord.second == eNumbers::One) return true;
	else return false;
	return false;
}
;
