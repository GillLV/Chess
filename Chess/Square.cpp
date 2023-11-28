#include<memory>
#include "Square.h"


CSquare::CSquare(std::shared_ptr<CPiece> piece, int stringPos) :
	m_Piece(piece),
	m_StringPos(stringPos)
{
	
}

