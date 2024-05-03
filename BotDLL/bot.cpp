#include "pch.h"
#include "bot.h"
#include "board.h"

#include<array>
#include<string>

// Bot Implementations
Bot::Bot()
{
	this->minMaxRound = 0;
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

int Bot::minimax(BoardTreeNode* rootNode, int depth, int alpha, int beta)
{
	int value;

	if (rootNode->minMaxRound == this->minMaxRound)
	{
		return rootNode->score;
	}

	if (depth <= 0 /*Or is End Node*/)
	{
		value = determineBoardVal(rootNode);
	}
	else
	{
		// Maximizing
		if (rootNode->lastMove == Player)
		{
			value = INT_MIN;

			for each (BoardTreeNode * node in rootNode->possibleBoards)
			{
				if (node != NULL)
				{
					value = max(value, minimax(node, depth - 1, alpha, beta));

					alpha = max(alpha, value);

					if (alpha >= beta)
					{
						break;
					}
				}
			}
		}
		else // Minimizing
		{
			value = INT_MAX;

			for each (BoardTreeNode * node in rootNode->possibleBoards)
			{
				if (node != NULL)
				{
					value = min(value, minimax(node, depth - 1, alpha, beta));

					beta = min(alpha, value);

					if (alpha >= beta)
					{
						break;
					}
				}
			}
		}
	}

	rootNode->minMaxRound = this->minMaxRound;
	rootNode->score = value;

	return value;
}

int Bot::determineBoardVal(BoardTreeNode* node)
{
	return -1;
}

/******************
horizontal      : 1
vertical        : 7
diagonal(right) : 6
diagonal(left)  : 8
******************/
bool Bot::matchWindow(long board, short x, short y, short distance)
{
	long mask = 1;
	mask = mask << x;
	mask = mask << (y * 7);

	bool isMatch = true;

	for (int i = 0; i < 4; ++i)
	{
		isMatch == isMatch && (board & mask);

		mask = mask << distance;

		if (!isMatch)
		{
			break;
		}
	}

	return isMatch;
}

bool Bot::boardHasConnect(BoardTreeNode* node)
{
	long checkedBoard = node->lastMove == Player ? 
		node->currentBoard->pBoard :
		node->currentBoard->oBoard;

	bool hasConnect = false;

	// Check Horizontal


	// Check Vertical


	// Check Diagonal (6)


	// Check Diagonal (8)

	return false;
}
