#ifndef H_SQUARE
#define H_SQUARE
#include <string>
#include "Piece.h"

//No longer in use but kept for reference
//enum class eSquarePos {
//	A1 = 577, A2 = 503, A3 = 429, A4 = 355, A5 = 281, A6 = 217, A7 = 143, A8 = 79,
//	B1 = 581, B2 = 507, B3 = 433, B4 = 359, B5 = 285, B6 = 221, B7 = 147, B8 = 83,
//	C1 = 585, C2 = 511, C3 = 437, C4 = 363, C5 = 289, C6 = 225, C7 = 151, C8 = 87,
//	D1 = 589, D2 = 515, D3 = 441, D4 = 367, D5 = 293, D6 = 229, D7 = 155, D8 = 81,
//	E1 = 593, E2 = 519, E3 = 445, E4 = 371, E5 = 297, E6 = 243, E7 = 159, E8 = 85,
//	F1 = 597, F2 = 523, F3 = 449, F4 = 375, F5 = 301, F6 = 247, F7 = 163, F8 = 89,
//	G1 = 601, G2 = 527, G3 = 453, G4 = 379, G5 = 305, G6 = 251, G7 = 167, G8 = 93,
//	H1 = 605, H2 = 531, H3 = 457, H4 = 383, H5 = 309, H6 = 255, H7 = 171, H8 = 97
//
//};
class CSquare {


private:
	std::shared_ptr<CPiece> m_Piece;
	int m_StringPos;

public:
	CSquare();
	CSquare(std::shared_ptr<CPiece> piece, int stringPos);

	std::shared_ptr<CPiece> getPiece() {
		return m_Piece;
	}
	
	void setPiece(std::shared_ptr<CPiece> piece) {
		m_Piece = piece;
	}

	int getStringPos() {
		return m_StringPos;
	}

	void setStringPos(int pos) {
		m_StringPos = pos;
	}
};

#endif
