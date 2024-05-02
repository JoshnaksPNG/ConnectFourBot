#pragma once

#include<array>
#include<string>

#include "pch.h"
#include "bot.h"
#include "board.h"

enum BoardPiece
{
	Empty,
	Player,
	Op,
};

class Board
{
	std::array<std::array<BoardPiece, 6>, 7> placement;

	int pieces;

public:
	Board(long pBitboard, long oBitboard);
	Board();

	void setPiece(int rank, int file, BoardPiece piece);
	void dropPiece(int rank, BoardPiece piece);
	char* getPlacement();

	long getPBitboard();
	long getOBitboard();

	int getPieces();
};

class BoardTreeNode
{
public:
	BoardTreeNode(BoardPiece startingPiece, int rank);
	BoardTreeNode(BoardTreeNode* lastBoard, int rank);

	// Reference Possible Board by Rank(Collumn) of Possible Move
	std::array<BoardTreeNode*, 7> possibleBoards;

	BoardPiece lastMove;
	Board* currentBoard;

	int score;
	int minMaxRound;

	void generatePossibleChildren();
	void generateFutureChildren(int depth);

	std::pair<long, long> getBoardKey();
};

class BitBoard
{
public:
	BitBoard();
	BitBoard(BoardPiece startingPiece, short rank);
	BitBoard(long pBitboard, long oBitboard);

	long pBoard;
	long oBoard;

	short pieces;

	bool dropPiece(BoardPiece piece, short rank);

};

template<> struct std::hash<std::pair<long, long>>
{
	std::size_t operator()(std::pair<long, long> const& obj) const noexcept
	{
		std::size_t h1 = std::hash<long>{}(obj.first);
		std::size_t h2 = std::hash<long>{}(obj.second);

		return h1 ^ h2;
	}
};