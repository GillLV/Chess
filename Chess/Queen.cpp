#include "Queen.h"


CQueen::CQueen(eColor color, Coord coord) :
	CPiece(color, "Q", 9, coord)
{
	makeMoves();
}

void CQueen::makeMoves()
{

	CMove AdjacentContinuous{ eMovePattern::Adjacent, eMoveNumber::Continuous, true };
	m_Moves.push_back(AdjacentContinuous);

	CMove DiagonalContinuous{ eMovePattern::Diagonal, eMoveNumber::Continuous, true };
	m_Moves.push_back(DiagonalContinuous);

}