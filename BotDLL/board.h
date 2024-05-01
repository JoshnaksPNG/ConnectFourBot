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
	BoardTreeNode(BoardPiece startingPiece, int rank);//, Bot* bot);
	BoardTreeNode(BoardTreeNode* lastBoard, int rank);//, Bot* bot);

	// Reference Possible Board by Rank(Collumn) of Possible Move
	std::array<BoardTreeNode*, 7> possibleBoards;

	BoardPiece lastMove;
	Board* currentBoard;

	//Bot* parentBot;
	

	int score;

	void generatePossibleChildren();
	void generateFutureChildren(int depth);
};

template<> struct std::hash<std::pair<long, long>>
{
	std::size_t operator()(std::pair<long, long> const& obj) const noexcept
	{
		std::size_t h1 = std::hash<int>{}(obj.first);
		std::size_t h2 = std::hash<int>{}(obj.second);

		return h1 ^ h2;
	}
};