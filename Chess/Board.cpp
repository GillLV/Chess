#include <iostream>
#include "Board.h"
#include "Square.h"
#include "Piece.h"
#include "King.h"
#include "Pawn.h"


CBoard::CBoard( ) 
{
	InitStringPos();
	InitBoardString();
	InitBoardVec();
}

void CBoard::InitBoardVec()
{
	CPieceFactory pieceFactory;

	for (int letter = static_cast<int>(eLetters::A); letter != static_cast<int>(eLetters::Size); letter++)
	{
		std::vector<CSquare> vec;
		m_Board.push_back(vec);

		for (int number = static_cast<int>(eNumbers::One); number != static_cast<int>(eNumbers::Size); number++)
		{
			std::shared_ptr<CPiece> Piece = pieceFactory.CreatePiece({ static_cast<eLetters>(letter), static_cast<eNumbers>(number)});
			int pos = m_StringPosVec[letter][number];

			CSquare Square(Piece, pos);

			m_Board[letter].push_back(Square);
		}
	}

}

void CBoard::InitStringPos() {
 
	m_StringPosVec = {
						{ 577, 503, 429, 355, 281, 217, 143, 79 },
						{ 581, 507, 433, 359, 285, 221, 147, 83 },
						{ 585, 511, 437, 363, 289, 225, 151, 87 },
						{ 589, 515, 441, 367, 293, 229, 155, 81 },
						{ 593, 519, 445, 371, 297, 243, 159, 85 },
						{ 597, 523, 449, 375, 301, 247, 163, 89	},
						{ 601, 527, 453, 379, 305, 251, 167, 93 },
						{ 605, 531, 457, 383, 309, 255, 171, 97 }
					};

}

void CBoard::InitBoardString() {
	 
	m_BoardString =  "     A   B   C   D   E   F   G   H  \n";
	m_BoardString += "     -   -   -   -   -   -   -   -  \n";
	m_BoardString += " 8 | r | n | b | q | k | b | n | r |\n";
	m_BoardString += "     -   -   -   -   -   -   -   -  \n";
	m_BoardString += " 7 | p | p | p | p | p | p | p | p |\n";
	m_BoardString += "     -   -   -   -   -   -   -   -  \n";
	m_BoardString += " 6 |   |   |   |   |   |   |   |   |\n";
	m_BoardString += "     -   -   -   -   -   -   -   -  \n";
	m_BoardString += " 5 |   |   |   |   |   |   |   |   |\n";
	m_BoardString += "     -   -   -   -   -   -   -   -  \n";
	m_BoardString += " 4 |   |   |   |   |   |   |   |   |\n";
	m_BoardString += "     -   -   -   -   -   -   -   -  \n";
	m_BoardString += " 3 |   |   |   |   |   |   |   |   |\n";
	m_BoardString += "     -   -   -   -   -   -   -   -  \n";
	m_BoardString += " 2 | P | P | P | P | P | P | P | P |\n";
	m_BoardString += "     -   -   -   -   -   -   -   -  \n";
	m_BoardString += " 1 | R | N | B | Q | K | B | N | R |\n";
	m_BoardString += "     -   -   -   -   -   -   -   -    ";

}

void CBoard::DrawBoard()
{
	std::cout << m_BoardString;
}

void CBoard::UpdateSquareText(int stringSquarePos, std::string Symbol)
{

	m_BoardString.replace(stringSquarePos, 1, Symbol);

}


void CBoard::FindLegalMoves(std::shared_ptr<CPiece> piece, bool &isKingInCheck)
{
	Coord currentCoord = piece->getCurrentCoord();

	std::vector<Coord> coordVec;
	std::vector<CMove> moves = piece->getMoves();
	for (CMove move : moves) {
		switch (move.getMovePattern())
		{
		case eMovePattern::Forward:
			if (move.getMoveNumber() == eMoveNumber::Once)
			{
				getForwardOnceCoord(coordVec, piece, move.getCanCapture(), isKingInCheck);
			}
			else if (move.getMoveNumber() == eMoveNumber::Twice)
			{
				//Can only use this move if piece has not already been moved
				if (piece->getHasMoved() == true) break;
				getForwardTwiceCoord(coordVec, piece, move.getCanCapture(), isKingInCheck);
			}
			break;
		case eMovePattern::Adjacent:
			if (move.getMoveNumber() == eMoveNumber::Once)
			{
				getAdjacentOnceCoord(coordVec,  piece, move.getCanCapture(), isKingInCheck);
			}
			else if (move.getMoveNumber() == eMoveNumber::Continuous)
			{
				getAjacentContinuousCoord(coordVec, piece, move.getCanCapture(), isKingInCheck);
			}
			break;
		case eMovePattern::Diagonal:
			if (move.getMoveNumber() == eMoveNumber::Once)
			{
				getDiagonalOnceCoord(coordVec, piece, move.getCanCapture(), isKingInCheck);
			}
			else if (move.getMoveNumber() == eMoveNumber::Continuous)
			{
				getDiagonalContinuousCoord(coordVec, piece, move.getCanCapture(), isKingInCheck);
			}
			break;
		case eMovePattern::EnPassantQS:
			canEnPassantQS(currentCoord);
			break;
		case eMovePattern::EnPassantKS:
			canEnPassantKS(currentCoord);
			break;
		case eMovePattern::LShape:
			getLShapeCoord(coordVec, piece, move.getCanCapture(), isKingInCheck);
			break;
		case eMovePattern::CastleQS:
			canCastle(currentCoord);
			break;
		case eMovePattern::CastleKS:
			canCastle(currentCoord);
			break;
		default:
			std::cout << "Error : Piece does not have a move pattern!";
			break;
		}
	}
	piece->setValidMoves(coordVec);
}

bool CBoard::hasRookMoved(eLetters letter, eNumbers number)
{
	std::shared_ptr<CPiece> piece = getBoardSquare(letter, number).getPiece();
	return (piece != nullptr && !piece->getHasMoved()) ? false : true;
	
}

bool CBoard::isSpaceValid(Coord moveCoord, std::shared_ptr<CPiece> piece, bool canCapture, bool& isKingInCheck)
{
	if (moveCoord.first >= eLetters::A && moveCoord.first <= eLetters::H &&
		moveCoord.second >= eNumbers::One && moveCoord.second <= eNumbers::Eight)
	{     

		int letter = static_cast<int>(moveCoord.first);
		int number = static_cast<int>(moveCoord.second);

		std::shared_ptr<CPiece> target =  m_Board[letter][number].getPiece();

		bool movingPieceIsPawn = (piece->getSymbol() == "p" || piece->getSymbol() == "P");

		bool canMove = target == nullptr ? movingPieceIsPawn && canCapture ? false : true : (target->getColor() != piece->getColor() && canCapture);

		if (canMove)
		{
			if (target->getSymbol() == "k" || target->getSymbol() == "K")
			{
				std::shared_ptr<CKing> king = std::static_pointer_cast<CKing>(target);
				king->setInCheck(true);
			}

			return true;
		}
		
	}
	return false;
}

void CBoard::getForwardOnceCoord(std::vector<Coord>& coordVec, std::shared_ptr<CPiece> piece, bool canCapture, bool& isKingInCheck)
{
	Coord moveCoord = piece->getCurrentCoord();
	++moveCoord.second;

	if (isSpaceValid(moveCoord, piece, canCapture,isKingInCheck))
		coordVec.push_back(moveCoord);
}

void CBoard::getForwardTwiceCoord(std::vector<Coord>& coordVec, std::shared_ptr<CPiece> piece, bool canCapture, bool& isKingInCheck)
{
	Coord moveCoord = piece->getCurrentCoord();
	++moveCoord.second+=2;

	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);
}

void CBoard::getAdjacentOnceCoord(std::vector<Coord>& coordVec, std::shared_ptr<CPiece> piece, bool canCapture, bool& isKingInCheck)
{
	Coord moveCoord =  piece->getCurrentCoord();

	//Check forward
	++moveCoord.second;
	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);

	//Check backward
	moveCoord =  piece->getCurrentCoord();
	--moveCoord.second;
	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);

	//Check left
	moveCoord = piece->getCurrentCoord();
	--moveCoord.first;
	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);

	//Check right
	moveCoord = piece->getCurrentCoord();
	++moveCoord.first;
	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);
}

void CBoard::getAjacentContinuousCoord(std::vector<Coord>& coordVec, std::shared_ptr<CPiece> piece, bool canCapture, bool& isKingInCheck)
{
	Coord moveCoord = piece->getCurrentCoord();

	//check Forward
	for (int i = static_cast<int>(eNumbers::One); i < static_cast<int>(eNumbers::Size); i++)
	{
		++moveCoord.second;
		if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
			coordVec.push_back(moveCoord);
		else break;
	}

	moveCoord = piece->getCurrentCoord();

	//check Backward
	for (int i = static_cast<int>(eNumbers::Eight); i > static_cast<int>(eNumbers::OUT_OF_BOUNDS); i--)
	{
		--moveCoord.second;
		if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
			coordVec.push_back(moveCoord);
		else break;
	}

	moveCoord = piece->getCurrentCoord();

	//check left
	for (int i = static_cast<int>(eLetters::H); i > static_cast<int>(eNumbers::OUT_OF_BOUNDS); i--)
	{
		++moveCoord.first;
		if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
			coordVec.push_back(moveCoord);
		else break;
	}

	moveCoord = piece->getCurrentCoord();

	//check right
	for (int i = static_cast<int>(eLetters::A); i < static_cast<int>(eNumbers::Size); i++)
	{
		++moveCoord.first;
		if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
			coordVec.push_back(moveCoord);
		else break;
	}
}
//AHHHHH THIS IS WRONG

void CBoard::canEnPassantQS(Coord currentCoord)
{
	std::shared_ptr<CPawn> currentPawn = std::static_pointer_cast<CPawn>(getBoardSquare(currentCoord.first, currentCoord.second).getPiece());
	bool isWhite = currentPawn->getColor() == eColor::White ? true: false;
	if (isWhite)
	{
		if (currentCoord.second  != eNumbers::Five)
			currentPawn->setCanTakeEnPassantQS(false);
			return;
	}
	else
	{
		if(currentCoord.second != eNumbers::Four)
			currentPawn->setCanTakeEnPassantQS(false);
			return;
	}

	Coord sideCoord = currentCoord;
	sideCoord.first--;
	std::shared_ptr<CPiece> sidePiece = getBoardSquare(sideCoord.first, sideCoord.second).getPiece();
	if (sidePiece != nullptr && (sidePiece->getSymbol() == "p" || sidePiece->getSymbol() == "P")
		&& sidePiece->getColor() != currentPawn->getColor() && sidePiece)
	{
		std::shared_ptr<CPawn> sidePawn = std::static_pointer_cast<CPawn>(sidePiece);
		if (sidePawn->getCanBeTakenEnPassant())
			currentPawn->setCanTakeEnPassantQS(true);
		return;
	}
	else
	{
		currentPawn->setCanTakeEnPassantQS(false);
		return;
	}
}

void CBoard::canEnPassantKS(Coord currentCoord)
{
	std::shared_ptr<CPawn> currentPawn = std::static_pointer_cast<CPawn>(getBoardSquare(currentCoord.first, currentCoord.second).getPiece());
	bool isWhite = currentPawn->getColor() == eColor::White ? true : false;
	if (isWhite)
	{
		if (currentCoord.second != eNumbers::Five)
			currentPawn->setCanTakeEnPassantKS(false);
		return;
	}
	else
	{
		if (currentCoord.second != eNumbers::Four)
			currentPawn->setCanTakeEnPassantKS(false);
		return;
	}

	Coord sideCoord = currentCoord;
	sideCoord.first++;
	std::shared_ptr<CPiece> sidePiece = getBoardSquare(sideCoord.first, sideCoord.second).getPiece();
	if (sidePiece != nullptr && (sidePiece->getSymbol() == "p" || sidePiece->getSymbol() == "P")
		&& sidePiece->getColor() != currentPawn->getColor() && sidePiece)
	{
		std::shared_ptr<CPawn> sidePawn = std::static_pointer_cast<CPawn>(sidePiece);
		if (sidePawn->getCanBeTakenEnPassant())
			currentPawn->setCanTakeEnPassantKS(true);
		return;
	}
	else
	{
		currentPawn->setCanTakeEnPassantKS(false);
		return;
	}
}

void CBoard::getDiagonalOnceCoord(std::vector<Coord>& coordVec, std::shared_ptr<CPiece> piece, bool canCapture, bool& isKingInCheck)
{
	Coord moveCoord = piece->getCurrentCoord();
	
	//Check left forward
	--moveCoord.first;
	++moveCoord.second;
	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);

	moveCoord = piece->getCurrentCoord();

	//Check left backward
	--moveCoord.first;
	--moveCoord.second;
	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);

	moveCoord = piece->getCurrentCoord();

	//Check right forward
	++moveCoord.first;
	++moveCoord.second;
	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);

	moveCoord = piece->getCurrentCoord();

	//Check right backward
	++moveCoord.first;
	--moveCoord.second;
	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);

}

void CBoard::getDiagonalContinuousCoord(std::vector<Coord>& coordVec, std::shared_ptr<CPiece> piece, bool canCapture, bool& isKingInCheck)
{
	Coord moveCoord = piece->getCurrentCoord();

	//check left Forward
	for (int i = static_cast<int>(eNumbers::One); i < static_cast<int>(eNumbers::Size); i++)
	{
		--moveCoord.first;
		++moveCoord.second;
		if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
			coordVec.push_back(moveCoord);
		else break;
	}

	moveCoord = piece->getCurrentCoord();

	//check left Backward
	for (int i = static_cast<int>(eNumbers::Eight); i > static_cast<int>(eNumbers::OUT_OF_BOUNDS); i--)
	{
		--moveCoord.first;
		--moveCoord.second;
		if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
			coordVec.push_back(moveCoord);
		else break;
	}

	moveCoord = piece->getCurrentCoord();

	//check right forward
	for (int i = static_cast<int>(eNumbers::One); i < static_cast<int>(eNumbers::Size); i++)
	{
		++moveCoord.first;
		++moveCoord.second;
		if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
			coordVec.push_back(moveCoord);
		else break;
	}

	moveCoord = piece->getCurrentCoord();

	//check right backward
	for (int i = static_cast<int>(eNumbers::Eight); i > static_cast<int>(eNumbers::OUT_OF_BOUNDS); i--)
	{
		++moveCoord.first;
		--moveCoord.second;
		if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
			coordVec.push_back(moveCoord);
		else break;
	}
}

void CBoard::getLShapeCoord(std::vector<Coord>& coordVec, std::shared_ptr<CPiece> piece, bool canCapture, bool& isKingInCheck)
{
	Coord moveCoord = piece->getCurrentCoord();

	//Check forward left
	--moveCoord.first;
	moveCoord.second += 2;
	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);

	moveCoord = piece->getCurrentCoord();

	//Check left forward
	moveCoord.first -= 2;
	++moveCoord.second;
	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);

	moveCoord = piece->getCurrentCoord();

	//Check left backward
	moveCoord.first -= 2;
	--moveCoord.second;
	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);

	moveCoord = piece->getCurrentCoord();

	//Check backward left
	--moveCoord.first;
	moveCoord.second -= 2;
	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);

	moveCoord = piece->getCurrentCoord();

	//Check backward right
	++moveCoord.first;
	moveCoord.second -= 2;
	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);

	moveCoord = piece->getCurrentCoord();

	//Check right backward
	moveCoord.first += 2;
	--moveCoord.second;
	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);

	moveCoord = piece->getCurrentCoord();

	//Check right forward
	moveCoord.first += 2;
	++moveCoord.second;
	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);

	moveCoord = piece->getCurrentCoord();

	//Check right forward
	++moveCoord.first;
	moveCoord.second+=2;
	if (isSpaceValid(moveCoord, piece, canCapture, isKingInCheck))
		coordVec.push_back(moveCoord);

}

void CBoard::canCastle(Coord currentCoord)
{
	if (currentCoord.second == eNumbers::One)
	{
		std::shared_ptr<CKing> king = static_pointer_cast<CKing>(getBoardSquare(currentCoord.first, currentCoord.second).getPiece());

		if (king->getHasMoved() || hasRookMoved(eLetters::A, eNumbers::One)) {
			king->setCanCastleQS(false);
			return;
		}
		std::shared_ptr<CPiece> B1Piece = getBoardSquare(eLetters::B, eNumbers::One).getPiece();
		std::shared_ptr<CPiece> C1Piece = getBoardSquare(eLetters::C, eNumbers::One).getPiece();
		std::shared_ptr<CPiece> D1Piece = getBoardSquare(eLetters::D, eNumbers::One).getPiece();

		if (B1Piece != nullptr || C1Piece != nullptr || D1Piece != nullptr) {
			king->setCanCastleQS(false);
			return;
		}
		king->setCanCastleQS(true);

	}

	else if (currentCoord.second == eNumbers::Eight)
	{
		std::shared_ptr<CKing> king = static_pointer_cast<CKing>(getBoardSquare(currentCoord.first, currentCoord.second).getPiece());

		if (king->getHasMoved() || hasRookMoved(eLetters::A, eNumbers::Eight)) {
			king->setCanCastleQS(false);
			return;
		}
		std::shared_ptr<CPiece> B8Piece = getBoardSquare(eLetters::B, eNumbers::Eight).getPiece();
		std::shared_ptr<CPiece> C8Piece = getBoardSquare(eLetters::C, eNumbers::Eight).getPiece();

		if (B8Piece != nullptr || C8Piece != nullptr ) {
			king->setCanCastleQS(false);
			return;
		}
		king->setCanCastleQS(true);

	}


}

bool CBoard::canPromote(std::shared_ptr<CPiece> piece)
{
	bool isPawn = piece->getSymbol() == "p" || piece->getSymbol() == "P";
	if (!isPawn) return;
	
	if (piece->getColor() == eColor::White && piece)


}

eLetters& operator+=(eLetters& lhs, int rhs)
{
	lhs = static_cast<eLetters>(static_cast<int>(lhs) + rhs);
	return lhs;
}

eLetters& operator-=(eLetters& lhs, int rhs)
{
	lhs = static_cast<eLetters>(static_cast<int>(lhs) - rhs);
	return lhs;
}

eNumbers& operator+=(eNumbers& lhs, int rhs)
{
	lhs = static_cast<eNumbers>(static_cast<int>(lhs) + rhs);
	return lhs;
}

eNumbers& operator-=(eNumbers& lhs, int rhs)
{
	lhs = static_cast<eNumbers>(static_cast<int>(lhs) - rhs);
	return lhs;
}

eLetters& operator++(eLetters& letter)
{
	if (letter == eLetters::H || letter == eLetters::OUT_OF_BOUNDS)
	{
		letter = eLetters::OUT_OF_BOUNDS;
		return letter;
	}
	else
	{
		letter = static_cast<eLetters>((static_cast<int>(letter) + 1));
		return letter;
	}
}

eLetters& operator--(eLetters& letter)
{
	if (letter == eLetters::OUT_OF_BOUNDS)
	{
		letter = eLetters::OUT_OF_BOUNDS;
		return letter;
	}
	else
	{
		letter = static_cast<eLetters>((static_cast<int>(letter) - 1));
		return letter;
	}
}

eNumbers& operator++(eNumbers& number)
{
	if (number == eNumbers::Eight || number == eNumbers::OUT_OF_BOUNDS)
	{
		number = eNumbers::OUT_OF_BOUNDS;
		return number;
	}
	else
	{
		number = static_cast<eNumbers>((static_cast<int>(number) + 1));
		return number;
	}
}

eNumbers& operator--(eNumbers& number)
{
	if (number == eNumbers::OUT_OF_BOUNDS)
	{
		number = eNumbers::OUT_OF_BOUNDS;
		return number;
	}
	else
	{
		number = static_cast<eNumbers>((static_cast<int>(number) - 1));
		return number;
	}
}

