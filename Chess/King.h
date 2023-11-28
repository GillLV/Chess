#ifndef H_KING
#define H_KING

#include "Piece.h"

class CKing : public CPiece {

public:
	CKing(eColor color, Coord coord);


private:

	bool m_CanCastleQS;
	bool m_CanCastleKS;
	bool m_InCheck;

	void makeMoves() override;

public:

	bool getCanCastleQS() {
		return m_CanCastleQS;
	}

	void setCanCastleQS(bool canCastleQS) {
		m_CanCastleQS = canCastleQS;
	}

	bool getCanCastleKS() {
		return m_CanCastleKS;
	}

	void setCanCastleKS(bool canCastleKS) {
		m_CanCastleKS = canCastleKS;
	}

	bool getInCheck() {
		return;
	}

	void setInCheck(bool inCheck) {
		m_InCheck = inCheck;
	}

};

#endif