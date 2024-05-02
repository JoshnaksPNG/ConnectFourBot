#include "pch.h"
#include "bot.h"
#include "board.h"

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

void Bot::generateNodeChildren(BoardTreeNode* rootNode, int depth)
{
	if (depth)
	{
		for (int i = 0; i < 7; ++i)
		{
			BoardTreeNode* checkedBoard = new BoardTreeNode(rootNode, i);

			std::pair<long, long> checkKey = checkedBoard->getBoardKey();

			// If allPossibleBoards doesn't contain the board mentioned
			if (this->allPossibleBoards.find(checkKey) != this->allPossibleBoards.end())
			{
				rootNode->possibleBoards[i] = checkedBoard;

				generateNodeChildren(checkedBoard, depth - 1);
			}
			else
			{
				rootNode->possibleBoards[i] = allPossibleBoards.at(checkKey);
			}
		}
	}
}


