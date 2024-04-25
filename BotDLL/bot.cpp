#include "pch.h"
#include "bot.h"

#include<array>
#include<string>

// Bot Implementations
Bot::Bot()
{
	
}

int Bot::suggestColumn()
{
	return -1;
}


// Board implementations
Board::Board()
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			this->placement[i][j] = Empty;
		}
	}

	pieces = 0;
}

Board::Board(long pBoard, long oBoard)
{
	long mask = 1;

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			// this->placement[i][j] = Empty;
			if (pBoard & mask)
			{
				this->placement[i][j] = Player;
			}

			mask = mask << 1;
		}
	}

	mask = 1;

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			// this->placement[i][j] = Empty;
			if (oBoard & mask)
			{
				this->placement[i][j] = Op;
			}

			mask = mask << 1;
		}
	}
}

void Board::setPiece(int rank, int file, BoardPiece piece)
{
	if (rank < 0 || rank > 6)
	{
		return;
	}

	this->placement[rank][file] = piece;
}

void Board::dropPiece(int rank, BoardPiece piece)
{
	if (rank < 0 || rank > 6 || piece == Empty)
	{
		return;
	}

	int topOfStack = 5;

	if (this->placement[rank][topOfStack] != Empty)
	{
		return;
	}

	while (topOfStack != -1 && this->placement[rank][topOfStack] == Empty)
	{
		--topOfStack;
	}

	this->placement[rank][topOfStack + 1] = piece;

	return;
}

char* Board::getPlacement()
{
	std::string board_str = "";

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			BoardPiece piece = this->placement[i][j];
			
			switch (piece)
			{
			case Player:
				board_str += '1';
				break;

			case Op:
				board_str += '2';
				break;

			default:
			case Empty:
				board_str += '0';
				break;
			}
		}

		board_str += '\n';
	}
	const char* ret_str = board_str.c_str();

	return (char*)ret_str;
}

long Board::getPBitboard()
{
	long pBoard = 0;
	long pMask = 1;

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			// this->placement[i][j] = Empty;
			if (this->placement[i][j] == Player)
			{
				pBoard |= pMask;
			}

			pMask = pMask << 1;
		}
	}

	return pBoard;
}

long Board::getOBitboard()
{
	long oBoard = 0;
	long oMask = 1;

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			if (this->placement[i][j] == Player)
			{
				oBoard |= oMask;
			}

			oMask = oMask << 1;
		}
	}

	return oBoard;
}

int Board::getPieces()
{
	return this->pieces;
}

// BoardTreeNode Implementations
BoardTreeNode::BoardTreeNode(BoardPiece startingPiece, int rank)
{
	this->currentBoard = new Board();
	this->currentBoard->dropPiece(rank, startingPiece);

	this->lastMove = startingPiece;

	this->score = 0;
}

BoardTreeNode::BoardTreeNode(BoardTreeNode* lastBoard, int rank)
{
	long pBoard = lastBoard->currentBoard->getPBitboard();
	long oBoard = lastBoard->currentBoard->getOBitboard();

	BoardPiece currentPiece;

	if (lastBoard->lastMove == Player)
	{
		currentPiece = Op;
	}
	else
	{
		currentPiece = Player;
	}


	this->currentBoard = new Board(pBoard, oBoard);
	this->currentBoard->dropPiece(rank, currentPiece);

	this->lastMove = currentPiece;

	this->score = 0;
}

void BoardTreeNode::generatePossibleChildren()
{
	for (int i = 0; i < 7; ++i)
	{
		possibleBoards[i] = new BoardTreeNode(this, i);
	}
}

void BoardTreeNode::generateFutureChildren(int depth)
{
	if (depth == 1)
	{
		this->generatePossibleChildren();
	}
	else
	{
		for (int i = 0; i < 7; ++i)
		{
			possibleBoards[i] = new BoardTreeNode(this, i);
			generateFutureChildren(depth - 1);
		}
	}

}