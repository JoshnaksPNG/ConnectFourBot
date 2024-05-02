#include "pch.h"
#include "bot.h"
#include "board.h"

#include<array>
#include<string>

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6

// Board implementations
Board::Board()
{

	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < BOARD_HEIGHT; ++j)
		{
			this->placement[i][j] = Empty;
		}
	}

	pieces = 0;
}

Board::Board(long pBoard, long oBoard)
{
	long mask = 1;

	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < BOARD_HEIGHT; ++j)
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

	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < BOARD_HEIGHT; ++j)
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
	if (rank < 0 || rank >= BOARD_WIDTH)
	{
		return;
	}

	this->placement[rank][file] = piece;
}

void Board::dropPiece(int rank, BoardPiece piece)
{
	if (rank < 0 || rank >= BOARD_WIDTH || piece == Empty)
	{
		return;
	}

	int topOfStack = BOARD_HEIGHT - 1;

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

	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < BOARD_HEIGHT; ++j)
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

	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < BOARD_HEIGHT; ++j)
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

	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < BOARD_HEIGHT; ++j)
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

	//this->parentBot = bot;
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

	//this->parentBot = bot;
}

void BoardTreeNode::generatePossibleChildren()
{
	for (int i = 0; i < BOARD_WIDTH; ++i)
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
		for (int i = 0; i < BOARD_WIDTH; ++i)
		{
			possibleBoards[i] = new BoardTreeNode(this, i);
			generateFutureChildren(depth - 1);
		}
	}

}

std::pair<long, long> BoardTreeNode::getBoardKey()
{
	return std::pair<long, long>(currentBoard->getPBitboard(), currentBoard->getOBitboard());
}

BitBoard::BitBoard()
{
	pBoard = 0;
	oBoard = 0;

	pieces = 0;
}

BitBoard::BitBoard(BoardPiece startingPiece, short rank)
{
	pBoard = 0;
	oBoard = 0;

	pieces = 0;

	dropPiece(startingPiece, rank);
}

// Rank is 0-6
// Height is 0-5
bool BitBoard::dropPiece(BoardPiece piece, short rank)
{
	short height = 0;
	bool empty_spot = false;

	long bitMask = 1;

	bitMask = bitMask << rank;

	while (height < BOARD_HEIGHT && !empty_spot)
	{
		long pTest = pBoard & bitMask;
		long oTest = oBoard & bitMask;

		if (!pTest && !oTest)
		{
			if (piece == Player)
			{
				pBoard = pBoard | bitMask;
			}
			else
			{
				oBoard = oBoard | bitMask;
			}

			++pieces;
			empty_spot = true;
		}
		else
		{
			++height;
			bitMask = bitMask << BOARD_WIDTH;
		}
	}

	return empty_spot;
}
