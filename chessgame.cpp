#include <iostream>

class MAPiece
{
public:
	MAPiece(char cColor) : mcColor(cColor) {}
	~MAPiece() {}
	virtual char GetPiece() = 0;
	char GetColor() {
		return mcColor;
	}
	bool IsLegalMove(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, MAPiece* qpaaBoard[8][8]) {
		MAPiece* qpDest = qpaaBoard[iDestRow][iDestCol];
		if ((qpDest == 0) || (mcColor != qpDest->GetColor())) {
			return AreSquaresLegal(iSrcRow, iSrcCol, iDestRow, iDestCol, qpaaBoard);
		}
		return false;
	}
private:
	virtual bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, MAPiece* qpaaBoard[8][8]) = 0;
	char mcColor;
};

class MPawn : public MAPiece
{
public:
	MPawn(char cColor) : MAPiece(cColor) {}
	~MPawn() {}
private:
	virtual char GetPiece() {
		return 'P';
	}
	bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, MAPiece* qpaaBoard[8][8]) {
		MAPiece* qpDest = qpaaBoard[iDestRow][iDestCol];
		if (qpDest == 0) {
			// Destination square is unoccupied
			if (iSrcCol == iDestCol) {
				if (GetColor() == 'W') {
					if (iDestRow == iSrcRow + 1) {
						return true;
					}
				} else {
					if (iDestRow == iSrcRow - 1) {
						return true;
					}
				}
			}
		} else {
			// Dest holds piece of opposite color
			if ((iSrcCol == iDestCol + 1) || (iSrcCol == iDestCol - 1)) {
				if (GetColor() == 'W') {
					if (iDestRow == iSrcRow + 1) {
						return true;
					}
				} else {
					if (iDestRow == iSrcRow - 1) {
						return true;
					}
				}
			}
		}
		return false;
	}
};

class MKnight : public MAPiece
{
public:
	MKnight(char cColor) : MAPiece(cColor) {}
	~MKnight() {}
private:
	virtual char GetPiece() {
		return 'N';
	}
	bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, MAPiece* qpaaBoard[8][8]) {
		// Destination square is unoccupied or occupied by opposite color
		if ((iSrcCol == iDestCol + 1) || (iSrcCol == iDestCol - 1)) {
			if ((iSrcRow == iDestRow + 2) || (iSrcRow == iDestRow - 2)) {
				return true;
			}
		}
		if ((iSrcCol == iDestCol + 2) || (iSrcCol == iDestCol - 2)) {
			if ((iSrcRow == iDestRow + 1) || (iSrcRow == iDestRow - 1)) {
				return true;
			}
		}
		return false;
	}
};

class MBishop : public MAPiece
{
public:
	MBishop(char cColor) : MAPiece(cColor) {}
	~MBishop() {}
private:
	virtual char GetPiece() {
		return 'B';
	}
	bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, MAPiece* qpaaBoard[8][8]) {
		if ((iDestCol - iSrcCol == iDestRow - iSrcRow) || (iDestCol - iSrcCol == iSrcRow - iDestRow)) {
			// Make sure that all invervening squares are empty
			int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
			int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
			int iCheckRow;
			int iCheckCol;
			for (iCheckRow = iSrcRow + iRowOffset, iCheckCol = iSrcCol + iColOffset;
				iCheckRow !=  iDestRow;
				iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
			{
				if (qpaaBoard[iCheckRow][iCheckCol] != 0) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
};

class MRook : public MAPiece
{
public:
	MRook(char cColor) : MAPiece(cColor) {}
	~MRook() {}
private:
	virtual char GetPiece() {
		return 'R';
	}
	bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, MAPiece* qpaaBoard[8][8]) {
		if (iSrcRow == iDestRow) {
			// Make sure that all invervening squares are empty
			int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
			for (int iCheckCol = iSrcCol + iColOffset; iCheckCol !=  iDestCol; iCheckCol = iCheckCol + iColOffset) {
				if (qpaaBoard[iSrcRow][iCheckCol] != 0) {
					return false;
				}
			}
			return true;
		} else if (iDestCol == iSrcCol) {
			// Make sure that all invervening squares are empty
			int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
			for (int iCheckRow = iSrcRow + iRowOffset; iCheckRow !=  iDestRow; iCheckRow = iCheckRow + iRowOffset) {
				if (qpaaBoard[iCheckRow][iSrcCol] != 0) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
};

class MQueen : public MAPiece
{
public:
	MQueen(char cColor) : MAPiece(cColor) {}
	~MQueen() {}
private:
	virtual char GetPiece() {
		return 'Q';
	}
	bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, MAPiece* qpaaBoard[8][8]) {
		if (iSrcRow == iDestRow) {
			// Make sure that all invervening squares are empty
			int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
			for (int iCheckCol = iSrcCol + iColOffset; iCheckCol !=  iDestCol; iCheckCol = iCheckCol + iColOffset) {
				if (qpaaBoard[iSrcRow][iCheckCol] != 0) {
					return false;
				}
			}
			return true;
		} else if (iDestCol == iSrcCol) {
			// Make sure that all invervening squares are empty
			int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
			for (int iCheckRow = iSrcRow + iRowOffset; iCheckRow !=  iDestRow; iCheckRow = iCheckRow + iRowOffset) {
				if (qpaaBoard[iCheckRow][iSrcCol] != 0) {
					return false;
				}
			}
			return true;
		} else if ((iDestCol - iSrcCol == iDestRow - iSrcRow) || (iDestCol - iSrcCol == iSrcRow - iDestRow)) {
			// Make sure that all invervening squares are empty
			int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
			int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
			int iCheckRow;
			int iCheckCol;
			for (iCheckRow = iSrcRow + iRowOffset, iCheckCol = iSrcCol + iColOffset;
				iCheckRow !=  iDestRow;
				iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
			{
				if (qpaaBoard[iCheckRow][iCheckCol] != 0) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
};

class MKing : public MAPiece
{
public:
	MKing(char cColor) : MAPiece(cColor) {}
	~MKing() {}
private:
	virtual char GetPiece() {
		return 'K';
	}
	bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, MAPiece* qpaaBoard[8][8]) {
		int iRowDelta = iDestRow - iSrcRow;
		int iColDelta = iDestCol - iSrcCol;
		if (((iRowDelta >= -1) && (iRowDelta <= 1)) &&
			((iColDelta >= -1) && (iColDelta <= 1)))
		{
			return true;
		}
		return false;
	}
};

class MBoard
{
public:
	MBoard() {
		for (int iRow = 0; iRow < 8; ++iRow) {
			for (int iCol = 0; iCol < 8; ++iCol) {
				mqpaaBoard[iRow][iCol] = 0;
			}
		}
		// Allocate and place black pieces
		for (int iCol = 0; iCol < 8; ++iCol) {
			mqpaaBoard[6][iCol] = new MPawn('B');
		}
		mqpaaBoard[7][0] = new MRook('B');
		mqpaaBoard[7][1] = new MKnight('B');
		mqpaaBoard[7][2] = new MBishop('B');
		mqpaaBoard[7][3] = new MKing('B');
		mqpaaBoard[7][4] = new MQueen('B');
		mqpaaBoard[7][5] = new MBishop('B');
		mqpaaBoard[7][6] = new MKnight('B');
		mqpaaBoard[7][7] = new MRook('B');
		// Allocate and place white pieces
		for (int iCol = 0; iCol < 8; ++iCol) {
			mqpaaBoard[1][iCol] = new MPawn('W');
		}
		mqpaaBoard[0][0] = new MRook('W');
		mqpaaBoard[0][1] = new MKnight('W');
		mqpaaBoard[0][2] = new MBishop('W');
		mqpaaBoard[0][3] = new MKing('W');
		mqpaaBoard[0][4] = new MQueen('W');
		mqpaaBoard[0][5] = new MBishop('W');
		mqpaaBoard[0][6] = new MKnight('W');
		mqpaaBoard[0][7] = new MRook('W');
	}
	~MBoard() {
		for (int iRow = 0; iRow < 8; ++iRow) {
			for (int iCol = 0; iCol < 8; ++iCol) {
				delete mqpaaBoard[iRow][iCol];
				mqpaaBoard[iRow][iCol] = 0;
			}
		}
	}

	void Print() {
		using namespace std;
		const int kiSquareWidth = 4;
		const int kiSquareHeight = 3;
		for (int iRow = 0; iRow < 8*kiSquareHeight; ++iRow) {
			int iSquareRow = iRow/kiSquareHeight;
			// Print side border with numbering
			if (iRow % 3 == 1) {
				cout << '-' << (char)('1' + 7 - iSquareRow) << '-';
			} else {
				cout << "---";
			}
			// Print the chess board
			for (int iCol = 0; iCol < 8*kiSquareWidth; ++iCol) {
				int iSquareCol = iCol/kiSquareWidth;
				if (((iRow % 3) == 1) && ((iCol % 4) == 1 || (iCol % 4) == 2) && mqpaaBoard[7-iSquareRow][iSquareCol] != 0) {
					if ((iCol % 4) == 1) {
						cout << mqpaaBoard[7-iSquareRow][iSquareCol]->GetColor();
					} else {
						cout << mqpaaBoard[7-iSquareRow][iSquareCol]->GetPiece();
					}
				} else {
					if ((iSquareRow + iSquareCol) % 2 == 1) {
						cout << '*';
					} else {
						cout << ' ';
					}
				}
			}
			cout << endl;
		}
		// Print the bottom border with numbers
		for (int iRow = 0; iRow < kiSquareHeight; ++iRow) {
			if (iRow % 3 == 1) {
				cout << "---";
				for (int iCol = 0; iCol < 8*kiSquareWidth; ++iCol) {
					int iSquareCol = iCol/kiSquareWidth;
					if ((iCol % 4) == 1) {
						cout << (iSquareCol + 1);
					} else {
						cout << '-';
					}
				}
				cout << endl;
			} else {
				for (int iCol = 1; iCol < 9*kiSquareWidth; ++iCol) {
					cout << '-';
				}
				cout << endl;
			}
		}
	}

	bool IsInCheck(char cColor) {
		// Find the king
		int iKingRow;
		int iKingCol;
		for (int iRow = 0; iRow < 8; ++iRow) {
			for (int iCol = 0; iCol < 8; ++iCol) {
				if (mqpaaBoard[iRow][iCol] != 0) {
					if (mqpaaBoard[iRow][iCol]->GetColor() == cColor) {
						if (mqpaaBoard[iRow][iCol]->GetPiece() == 'K') {
							iKingRow = iRow;
							iKingCol = iCol;
						}
					}
				}
			}
		}
		// Run through the opponent's pieces and see if any can take the king
		for (int iRow = 0; iRow < 8; ++iRow) {
			for (int iCol = 0; iCol < 8; ++iCol) {
				if (mqpaaBoard[iRow][iCol] != 0) {
					if (mqpaaBoard[iRow][iCol]->GetColor() != cColor) {
						if (mqpaaBoard[iRow][iCol]->IsLegalMove(iRow, iCol, iKingRow, iKingCol, mqpaaBoard)) {
							return true;
						}
					}
				}
			}
		}

		return false;
	}

	bool CanMove(char cColor) {
		// Run through all pieces
		for (int iRow = 0; iRow < 8; ++iRow) {
			for (int iCol = 0; iCol < 8; ++iCol) {
				if (mqpaaBoard[iRow][iCol] != 0) {
					// If it is a piece of the current player, see if it has a legal move
					if (mqpaaBoard[iRow][iCol]->GetColor() == cColor) {
						for (int iMoveRow = 0; iMoveRow < 8; ++iMoveRow) {
							for (int iMoveCol = 0; iMoveCol < 8; ++iMoveCol) {
								if (mqpaaBoard[iRow][iCol]->IsLegalMove(iRow, iCol, iMoveRow, iMoveCol, mqpaaBoard)) {
									// Make move and check whether king is in check
									MAPiece* qpTemp					= mqpaaBoard[iMoveRow][iMoveCol];
									mqpaaBoard[iMoveRow][iMoveCol]	= mqpaaBoard[iRow][iCol];
									mqpaaBoard[iRow][iCol]			= 0;
									bool bCanMove = !IsInCheck(cColor);
									// Undo the move
									mqpaaBoard[iRow][iCol]			= mqpaaBoard[iMoveRow][iMoveCol];
									mqpaaBoard[iMoveRow][iMoveCol]	= qpTemp;
									if (bCanMove) {
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
		return false;
	}

	MAPiece* mqpaaBoard[8][8];
};

class MChess
{
public:
	MChess() : mcPlayerTurn('W') {}
	~MChess() {}

	void Start() {
		do {
			GetNextMove(mqGameBoard.mqpaaBoard);
			AlternateTurn();
		} while (!IsGameOver());
		mqGameBoard.Print();
	}

	void GetNextMove(MAPiece* qpaaBoard[8][8]) {
		using namespace std;
		bool bValidMove		= false;
		do {
			mqGameBoard.Print();

			// Get input and convert to coordinates
			cout << mcPlayerTurn << "'s Move: ";
			int iStartMove;
			cin >> iStartMove;
			int iStartRow = (iStartMove / 10) - 1;
			int iStartCol = (iStartMove % 10) - 1;

			cout << "To: ";
			int iEndMove;
			cin >> iEndMove;
			int iEndRow = (iEndMove / 10) - 1;
			int iEndCol = (iEndMove % 10) - 1;

			// Check that the indices are in range
			// and that the source and destination are different
			if ((iStartRow >= 0 && iStartRow <= 7) &&
				(iStartCol >= 0 && iStartCol <= 7) &&
				(iEndRow >= 0 && iEndRow <= 7) &&
				(iEndCol >= 0 && iEndCol <= 7)) {
				// Additional checks in here
				MAPiece* qpCurrPiece = qpaaBoard[iStartRow][iStartCol];
				// Check that the piece is the correct color
				if ((qpCurrPiece != 0) && (qpCurrPiece->GetColor() == mcPlayerTurn)) {
					// Check that the destination is a valid destination
					if (qpCurrPiece->IsLegalMove(iStartRow, iStartCol, iEndRow, iEndCol, qpaaBoard)) {
						// Make the move
						MAPiece* qpTemp					= qpaaBoard[iEndRow][iEndCol];
						qpaaBoard[iEndRow][iEndCol]		= qpaaBoard[iStartRow][iStartCol];
						qpaaBoard[iStartRow][iStartCol]	= 0;
						// Make sure that the current player is not in check
						if (!mqGameBoard.IsInCheck(mcPlayerTurn)) {
							delete qpTemp;
							bValidMove = true;
						} else { // Undo the last move
							qpaaBoard[iStartRow][iStartCol] = qpaaBoard[iEndRow][iEndCol];
							qpaaBoard[iEndRow][iEndCol]		= qpTemp;
						}
					}
				}
			}
			if (!bValidMove) {
				cout << "Invalid Move!" << endl;
			}
		} while (!bValidMove);
	}

	void AlternateTurn() {
		mcPlayerTurn = (mcPlayerTurn == 'W') ? 'B' : 'W';
	}

	bool IsGameOver() {
		// Check that the current player can move
		// If not, we have a stalemate or checkmate
		bool bCanMove(false);
		bCanMove = mqGameBoard.CanMove(mcPlayerTurn);
		if (!bCanMove) {
			if (mqGameBoard.IsInCheck(mcPlayerTurn)) {
				AlternateTurn();
				std::cout << "Checkmate, " << mcPlayerTurn << " Wins!" << std::endl;
			} else {
				std::cout << "Stalemate!" << std::endl;
			}
		}
		return !bCanMove;
	}
private:
	MBoard mqGameBoard;
	char mcPlayerTurn;
};

int main() {
	MChess qGame;
	qGame.Start();
	return 0;
}
