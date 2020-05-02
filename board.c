#include "board.h"


Board* board_construct(u8 height, u8 width)
{
	Board* ret;

	if (height == 0 || width == 0)
	{
		_logf(L_FATAL, "Cannot create a board with zero size (%hhu, %hhu)", height, width);
		return NULL;
	}

	ret          = malloc(sizeof(Board));
	ret->height  = height;
	ret->width   = width;
	ret->n_boats = 0;
	ret->matrix  = (Cell*) malloc(width * height * sizeof(Cell));
	ret->boats   = (Boat**) malloc(width * height / 25 * sizeof(Boat*));

	for (u8 x = 0; x < height; x++)
	{
		for (u8 y = 0; y < width; y++)
		{
			ret->matrix[x * height + y].boat = 0x0;
			ret->matrix[x * height + y].shot = 0;
		}
	}

	_logf(L_INFO, "Board created with size %hhux%hhu", height, width);
	return ret;
}

return_code board_destruct(Board* board)
{
	if (board == NULL)
	{
		return BOARD_INVALID_BOARD;
	}

	// Destruct all Boat objects attached to this Board
	for (s16 n = board->n_boats-1; n >= 0; n--)
	{
		boat_destruct(board->boats[n]);
		board->n_boats--;
	}

	// Destruct the Boat pointers array
	free(board->boats);

	// Destruct the Cell matrix
	free(board->matrix);

	_logf(L_INFO, "Board (%hhu, %hhu) destructed", board->height, board->width);
	free(board);

	return RETURN_OK;
}

return_code board_print(Board* board, bool obfuscate)
{
	if (board == NULL)
	{
		return BOARD_INVALID_BOARD;
	}

	// Table headers
	printf("   | ");
	for (u8 x = 0; x < board->height; x++)
	{
		printf("%02hhu ", x);
	}
	printf("\n");

	printf("---+");
	for (u8 x = 0; x < board->height; x++)
	{
		printf("---");
	}
	printf("\n");


	// Table content
	for (u8 x = 0; x < board->height; x++)
	{
		printf("%02hhu | ", x);
		for (u8 y = 0; y < board->width; y++)
		{
			// Sea cell without hit
			if (board->matrix[x * board->height + y].boat == 0x0 && board->matrix[x * board->height + y].shot == 0)
			{
				printf("~~ ");
			}
			// Sea cell with hit
			else if (board->matrix[x * board->height + y].shot == 1)
			{
				printf("xx ");
			}
			// Boat cell with hit, but boat still has life points
			else if (board->matrix[x * board->height + y].shot == 2 && board->matrix[x * board->height + y].boat->life != 0)
			{
				if (SHOW_BOAT_TYPE_ON_HIT)
				{
					printf("%d%d ", board->matrix[x * board->height + y].boat->type, board->matrix[x * board->height + y].boat->type);
				}
				else
				{
					printf("00 ");
				}
			}
			// Boat cell with hit, and boat no longer has life points
			else if (board->matrix[x * board->height + y].shot == 2)
			{
				printf("±± ");
			}
			// Every case below this one is obfuscated when this flag is true
			else if (obfuscate)
			{
				printf("~~ ");
			}
			// Boat cell without hit
			else if (board->matrix[x * board->height + y].boat != 0x0 && board->matrix[x * board->height + y].shot == 0)
			{
				printf("%d%d ", board->matrix[x * board->height + y].boat->type, board->matrix[x * board->height + y].boat->type);
			}
		}
		printf("\n");
	}

	return RETURN_OK;
}

return_code board_add(Board* board, Boat* boat, s16 x, s16 y)
{
	if (board == NULL)
	{
		return BOARD_INVALID_BOARD;
	}

	if (boat == NULL)
	{
		return BOARD_INVALID_BOAT;
	}

	if (x >= board->height || y >= board->width)
	{
		return BOARD_INVALID_COORDINATES;
	}

	if (board->n_boats >= board->height * board->width / 25)
	{
		return BOARD_CAPACITY_FULL;
	}

	// Verify if Boat won't overlap any used Board coordinates
	for (s16 i = x; i < x+5; i++)
	{
		for (s16 j = y; j < y+5; j++)
		{
			// Ignore unused Boat bitmap coordinates
			if (boat->bitmap[i-x][j-y] == 0)
			{
				continue;
			}

			// Trying to add boat out of bounds
			if (boat->bitmap[i-x][j-y] != 0 && (i >= board->height || j >= board->width || i < 0 || j < 0))
			{
				return BOARD_ADD_OUT_OF_BOUNDS;
			}

			// Boat overlap detected, pointer to Boat already exists
			if (board->matrix[i * board->height + j].boat != 0x0)
			{
				return BOARD_ADD_OVERLAP;
			}
		}
	}

	// Update Board's Cell matrix
	for (s16 i = x; i < x+5; i++)
	{
		for (s16 j = y; j < y+5; j++)
		{
			if (boat->bitmap[i-x][j-y] == 1)
			{
				board->matrix[i * board->height + j].boat = boat;
			}
		}
	}

	board->boats[board->n_boats] = boat;
	board->n_boats++;

	_logf(L_INFO, "Added boat with type %hhu to board", boat->type);

	return RETURN_OK;
}
