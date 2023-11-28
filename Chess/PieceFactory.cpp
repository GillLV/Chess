#include <memory>
#include "PieceFactory.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

std::shared_ptr<CPiece> CPieceFactory::CreatePiece(Coord pair) {
	eLetters first = pair.first;
	eNumbers second = pair.second;


	//FALTHROUGH????
	switch (second)
	{
	case eNumbers::One:
	case eNumbers::Eight:
		if (first == eLetters::A )
			return (second == eNumbers::One ? 
					static_cast<std::shared_ptr<CPiece>>(std::make_shared<CRook>(eColor::White, pair, eSide::QS))
					: static_cast<std::shared_ptr<CPiece>>(std::make_shared<CRook>(eColor::Black, pair, eSide::QS)));
		else if (first == eLetters::H)
			return (second == eNumbers::One ?
				static_cast<std::shared_ptr<CPiece>>(std::make_shared<CRook>(eColor::White, pair, eSide::KS))
				: static_cast<std::shared_ptr<CPiece>>(std::make_shared<CRook>(eColor::Black, pair, eSide::KS)));
		else if (first == eLetters::B || first == eLetters::G)
			return (second == eNumbers::One ?
				static_cast<std::shared_ptr<CPiece>>(std::make_shared<CKnight>(eColor::White, pair))
				: static_cast<std::shared_ptr<CPiece>>(std::make_shared<CKnight>(eColor::Black, pair)));
		else if (first == eLetters::C || first == eLetters::F)
			return (second == eNumbers::One ?
				static_cast<std::shared_ptr<CPiece>>(std::make_shared<CBishop>(eColor::White, pair))
				: static_cast<std::shared_ptr<CPiece>>(std::make_shared<CBishop>(eColor::Black, pair)));
		else if (first == eLetters::D)
			return (second == eNumbers::One ?
				static_cast<std::shared_ptr<CPiece>>(std::make_shared<CQueen>(eColor::White, pair))
				: static_cast<std::shared_ptr<CPiece>>(std::make_shared<CQueen>(eColor::Black, pair)));
		else if (first == eLetters::E)
				return (second == eNumbers::One ?
					static_cast<std::shared_ptr<CPiece>>(std::make_shared<CKing>(eColor::White, pair))
					: static_cast<std::shared_ptr<CPiece>>(std::make_shared<CKing>(eColor::Black, pair)));
		else
			return nullptr;
		break;
	case eNumbers::Two:
	case eNumbers::Seven:
		if (first >= eLetters::A && first <= eLetters::H)
			return (second == eNumbers::Two ?
				static_cast<std::shared_ptr<CPiece>>(std::make_shared<CPawn>(eColor::White, pair))
				: static_cast<std::shared_ptr<CPiece>>(std::make_shared<CPawn>(eColor::Black, pair)));
		else
			return nullptr;
		break;
	default:
		return nullptr;
		break;
	}
	
}