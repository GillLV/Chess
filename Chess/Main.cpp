#include<iostream>
#include "Board.h"
#include "King.h"
//#include "Square.h"

int main()
{

	CBoard board;
	
	std::shared_ptr<CKing> King = static_pointer_cast<CKing>(board.getBoardSquare(eLetters::E,eNumbers::One).getPiece());

	Coord currentCoord({ eLetters::E , eNumbers::One });

	board.getBoardSquare(eLetters::D, eNumbers::One).setPiece(nullptr);
	board.getBoardSquare(eLetters::C, eNumbers::One).setPiece(nullptr);
	board.getBoardSquare(eLetters::B, eNumbers::One).setPiece(nullptr);

	board.FindLegalMoves(currentCoord, King);
	bool canCastleQS = King->getCanCastleQS();

	return 1;
}

