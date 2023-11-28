#include "King.h"

CKing::CKing(eColor color, Coord coord) :
	CPiece(color, "K" , INT_MAX, coord),
	m_CanCastleQS(false),
	m_CanCastleKS(false)
{
	makeMoves();
}

void CKing::makeMoves()
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