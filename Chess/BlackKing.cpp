#include "BlackKing.h"

CBlackKing::CBlackKing() :
	CPiece(eColor::Black, "k", INT_MAX) {
	makeMoves();
}

void CBlackKing::makeMoves()
{

	CMove AdjacentSingle{ eMovePattern::Adjacent, eMoveNumber::Once, true };
	m_Moves.push_back(AdjacentSingle);

	CMove DiagonalSingle{ eMovePattern::Diagonal, eMoveNumber::Once, true };
	m_Moves.push_back(DiagonalSingle);

	CMove CastleQueenSide{ eMovePattern::CastleQS, eMoveNumber::Twice, false };
	m_Moves.push_back(CastleQueenSide);

	CMove CastleKingSide{ eMovePattern::CastleKS, eMoveNumber::Twice, false };
	m_Moves.push_back(CastleKingSide);
}