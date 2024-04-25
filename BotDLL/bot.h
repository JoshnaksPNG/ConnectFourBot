#pragma once

#include<array>
#include<string>
#include<stdio.h>
#include<unordered_map>


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

extern "C" __declspec(dllexport) void* NewBoard()
{
	return (void*) new Board();
}

extern "C" __declspec(dllexport) void BoardSetPiece(Board b, int r, int f, int p)
{
	b.setPiece(r, f, (BoardPiece)p);
}

extern "C" __declspec(dllexport) char* BoardGetPlacement(Board b)
{
	
	return b.getPlacement();
}

class BoardTreeNode
{
public:
	BoardTreeNode(BoardPiece startingPiece, int rank);
	BoardTreeNode(BoardTreeNode* lastBoard, int rank);

	// Reference Possible Board by Rank(Collumn) of Possible Move
	std::unordered_map<int, BoardTreeNode*> possibleBoards;

	BoardPiece lastMove;
	Board* currentBoard;

	int score;

	void generatePossibleChildren();
	void generateFutureChildren(int depth);
};

class Bot
{
	BoardPiece firstPlayer;

	Board currentBoard;

	// Need to find a better way to key this map
	//std::unordered_map<std::pair<long, long>, BoardTreeNode*> allPossibleBoards;
	std::unordered_map<std::string, BoardTreeNode*> allPossibleBoards;

public:
	Bot();
	int suggestColumn();
	
};

extern "C" __declspec(dllexport) void* NewBot()
{
	return (void*) new Bot();
}

extern "C" __declspec(dllexport) int SuggestColumn(Bot bot)
{
	return bot.suggestColumn();
}