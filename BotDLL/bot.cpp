#include "pch.h"
#include "bot.h"
#include "board.h"

#include<array>
#include<string>

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6

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
				boardHasConnect(checkedBoard);
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

	// Check Horizontal (1)
	for (int y = 0; y < BOARD_HEIGHT; ++y)
	{
		for (int x = 0; x < BOARD_WIDTH - 3; ++x)
		{
			hasConnect = matchWindow(checkedBoard, x, y, 1);

			if (hasConnect)
			{
				node->hasConnection = true;
				return true;
			}
		}
	}

	// Check Vertical (7)
	for (int y = 0; y < BOARD_HEIGHT - 2; ++y)
	{
		for (int x = 0; x < BOARD_WIDTH; ++x)
		{
			hasConnect = matchWindow(checkedBoard, x, y, 7);

			if (hasConnect)
			{
				node->hasConnection = true;
				return true;
			}
		}
	}

	// Check Diagonal (6)
	for (int y = 0; y < BOARD_HEIGHT - 2; ++y)
	{
		for (int x = 3; x < BOARD_WIDTH; ++x)
		{
			hasConnect = matchWindow(checkedBoard, x, y, 6);

			if (hasConnect)
			{
				node->hasConnection = true;
				return true;
			}
		}
	}


	// Check Diagonal (8)
	for (int y = 0; y < BOARD_HEIGHT - 2; ++y)
	{
		for (int x = 0; x < BOARD_WIDTH - 3; ++x)
		{
			hasConnect = matchWindow(checkedBoard, x, y, 8);

			if (hasConnect)
			{
				node->hasConnection = true;
				return true;
			}
		}
	}

	return false;
}
