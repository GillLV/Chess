#ifndef H_PAWN
#define H_PAWN

#include "Piece.h"

class CPawn : public CPiece {

public:
	CPawn(eColor color, Coord coord);


private:

	bool m_CanTakeEnPassantQS;
	bool m_CanTakeEnPassantKS;
	bool m_CanBeTakenEnPassant;

	void makeMoves() override;

public:

	bool getCanTakeEnPassantQS() {
		return m_CanTakeEnPassantQS;
	}

	void setCanTakeEnPassantQS(bool canEnpassant) {
		m_CanTakeEnPassantQS = canEnpassant;
	}

	bool getCanTakeEnPassantKS() {
		return m_CanTakeEnPassantKS;
	}

	void setCanTakeEnPassantKS(bool canEnpassant) {
		m_CanTakeEnPassantKS = canEnpassant;
	}

	bool getCanBeTakenEnPassant() {
		return m_CanBeTakenEnPassant;
	}

	void setCanBeTakenEnPassant(bool canBeTakenEnpassant) {
		m_CanBeTakenEnPassant = canBeTakenEnpassant;
	}
};


#endif