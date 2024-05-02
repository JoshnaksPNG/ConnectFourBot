#pragma once

#include<array>
#include<string>
#include<stdio.h>
#include<unordered_map>
#include "board.h"
#include "bot.h"
#include "pch.h"

class Bot
{
	BoardPiece firstPlayer;

	Board currentBoard;

	std::unordered_map<std::pair<long, long>, BoardTreeNode*> allPossibleBoards;

public:
	Bot();
	int suggestColumn();
	void generateNodeChildren(BoardTreeNode* rootNode, int depth);
};

