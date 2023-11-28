#ifndef H_PIECE
#define H_PIECE

#include <vector>
#include <string>
#include <iostream>


class CMove;
typedef std::vector<CMove> Moves;
enum class eLetters;
enum class eNumbers;
typedef std::pair<eLetters, eNumbers> Coord;

enum class eLetters {
	OUT_OF_BOUNDS = -1,
	A = 0,
	B,
	C,
	D,
	E,
	F,
	G,
	H,

	Size,
	Captured

};

enum class eNumbers
{
	OUT_OF_BOUNDS = -1,
	One = 0,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,

	Size,
	Captured

};


enum class eColor {
	White = 0,
	Black,

	size
};

enum class eMovePattern {
	Forward = 0,
	Adjacent,
	Diagonal,
	EnPassantQS,
	EnPassantKS,
	LShape,
	CastleQS,
	CastleKS,

};

enum class eMoveNumber {
	Once = 0,
	Twice,
	Continuous,

	size
};

//Constructor
class CMove {

public:
	eMovePattern m_Pattern;
	eMoveNumber m_Number;
	bool m_CanCapture;

//public:
	CMove(eMovePattern pattern, eMoveNumber number, bool canCapture) :
		m_Pattern(pattern),
		m_Number(number),
		m_CanCapture(canCapture)
	{
	
	}

	eMovePattern getMovePattern() {
		return m_Pattern;
	}
	eMoveNumber getMoveNumber() {
		return m_Number;
	}
	bool getCanCapture() {
		return m_CanCapture;
	}
	
};

class CPiece
{

protected:

	Moves		m_Moves;
	bool		m_Captured;
	eColor		m_Color;
	std::string m_Symbol;
	int			m_Points;
	bool		m_HasMoved;
	Coord		m_CurrentCoord;

	std::vector<Coord> m_ValidMoves;

	virtual void makeMoves();

public:

	CPiece();
	CPiece(eColor color, std::string symbol, int point, Coord coord);

	Moves getMoves() {
		return m_Moves;
	}

	void setCaptured(bool captured) {
		m_Captured = captured;
	}
	bool getCaptured() {
		return m_Captured;
	}

	//void setColor(eColor color) {
	//	m_Color = color;
	//}
	eColor getColor() {
		return m_Color;
	}

	std::string getSymbol() {
		return m_Symbol;
	}

	void setHasMoved(bool bMoved) {
		m_HasMoved = bMoved;
	}

	bool getHasMoved() {
		return m_HasMoved;
	}

	std::vector<Coord> getValidMoves() {
		return m_ValidMoves;
	}

	void setValidMoves(std::vector<Coord> coords) {
		m_ValidMoves = coords;
	}

	Coord getCurrentCoord() {
		return m_CurrentCoord;
	}

	void setCurrentCoord(Coord coord) {
		if (coord.first < eLetters::A || coord.first > eLetters::H
			|| coord.second < eNumbers::One || coord.second > eNumbers::Eight)

		{
			std::cout << "Invalid piece position";
			return;
		}
		m_CurrentCoord = coord;
	}

};
#endif
