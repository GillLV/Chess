#ifndef H_BOARD
#define H_BOARD
 
#include "Square.h"
#include "Piece.h"
#include "PieceFactory.h"
#include "Rook.h"

typedef std::vector<std::vector<CSquare>> BoardVec;
typedef std::vector<std::vector<int>> PosVec;

static eLetters& operator+=(eLetters& lhs, int rhs);


static eLetters& operator-=(eLetters& lhs, int rhs);

static eNumbers& operator+=(eNumbers& lhs, int rhs);

static eNumbers& operator-=(eNumbers& lhs, int rhs);

static eLetters& operator++(eLetters& letter);

static eLetters& operator--(eLetters& letter);

static eNumbers& operator++(eNumbers& number);

static eNumbers& operator--(eNumbers& number);


class CValidSquare {
	Coord moveCoord;
	bool canCapture;
	eColor currentColor;
	BoardVec boardVec;

public:
	CValidSquare(BoardVec boardvec);
	bool isSquareInBounds();
	std::shared_ptr<CPiece> getTarget();
	bool isKing();
	bool isPawn();
};


class CBoard
{

private:
	BoardVec m_Board;
	std::string m_BoardString;
	PosVec m_StringPosVec;


	void UpdateSquareText(int stringSquare, std::string Symbol);
	void InitBoardVec();
	void InitStringPos();
	void InitBoardString();


	//Find legal Moves
	bool isSpaceValid(CValidSquare ValidSquare, bool& isKingInCheck);
	void getForwardOnceCoord(std::vector<Coord>& coordVec, Coord currentCoord, bool canCapture, eColor currentColor, bool& isKingInCheck);
	void getForwardTwiceCoord(std::vector<Coord>& coordVec, Coord currentCoord, bool canCapture,eColor currentColor, bool& isKingInCheck);
	void getAdjacentOnceCoord(std::vector<Coord>& coordVec, Coord currentCoord, bool canCapture, eColor currentColor, bool& isKingInCheck);
	void getAjacentContinuousCoord(std::vector<Coord>& coordVec, Coord currentCoord, bool canCapture, eColor currentColor, bool& isKingInCheck);
	void canEnPassantQS(Coord currentCoord );
	void canEnPassantKS(Coord currentCoord );
	void getDiagonalOnceCoord(std::vector<Coord>& coordVec, Coord currentCoord, bool canCapture, eColor currentColor, bool& isKingInCheck);
	void getDiagonalContinuousCoord(std::vector<Coord>& coordVec, Coord currentCoord, bool canCapture, eColor currentColor, bool& isKingInCheck);
	void getLShapeCoord(std::vector<Coord>& coordVec, Coord currentCoord, bool canCapture, eColor currentColor, bool& isKingInCheck);
	void canCastle(Coord currentCoord);

	bool canPromote(std::shared_ptr<CPiece> piece);


public:
	CBoard();
	void DrawBoard();

	void FindLegalMoves(std::shared_ptr<CPiece> piece, bool &isKingInCheck);

	BoardVec &getBoard() {
		return m_Board;
	}

	BoardVec getBoardCopy() {
		return m_Board;
	}

	CSquare &getBoardSquare(eLetters letter, eNumbers number) {
		if (letter < eLetters::A || number > eNumbers::Eight)
		{
			std::cout << "Invalid square";
			return;
		}
		return m_Board[static_cast<int>(letter)][static_cast<int>(number)];
	}

	int getStringPos(eLetters letter, eNumbers number) { 
		if (letter < eLetters::A || number > eNumbers::Eight)
		{
			std::cout << "Invalid square";
			return;
		}
		return m_Board[int(letter)][int(number)].getStringPos();
	}
	//Promote?

	bool hasRookMoved(eLetters letter, eNumbers number);
};

#endif
