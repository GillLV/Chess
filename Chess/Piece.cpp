#include "Piece.h"

//CMove::CMove(eMovePattern pattern, eMoveNumber number, bool canCapture) :
//	m_Pattern(pattern), m_Number(number), m_CanCapture(canCapture)
//{
//	
//}

CPiece::CPiece(eColor color, std::string symbol, int points, Coord coord) : 
	m_Color(color),
	m_Symbol(symbol), 
	m_Points(points),
	m_Captured(false),
	m_HasMoved(false),
	m_CurrentCoord(coord)
{


}

void CPiece::makeMoves() {
	return;
}