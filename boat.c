#include "boat.h"

// Bitmap preset Linear size 1
u8 bitmap_TL1[5][5] = {
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 }
};
// Bitmap preset Linear size 2
u8 bitmap_TL2[5][5] = {
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 }
};
// Bitmap preset Linear size 3
u8 bitmap_TL3[5][5] = {
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0 }
};
// Bitmap preset Linear size 4
u8 bitmap_TL4[5][5] = {
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0 }
};
// Bitmap preset TShape size 5
u8 bitmap_TT5[5][5] = {
	{ 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 1, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0 }
};


Boat* boat_construct(BoatType type, BoatRotation rotation)
{
	Boat* ret;

	ret           = malloc(sizeof(Boat));
	ret->type     = type;
	ret->rotation = rotation;

	switch (type)
	{
		case TYPE_LINEAR_1:
			memcpy(&ret->bitmap, &bitmap_TL1, sizeof(u8) * 5 * 5);
			ret->life = 1;
			break;
		case TYPE_LINEAR_2:
			memcpy(&ret->bitmap, &bitmap_TL2, sizeof(u8) * 5 * 5);
			ret->life = 2;
			break;
		case TYPE_LINEAR_3:
			memcpy(&ret->bitmap, &bitmap_TL3, sizeof(u8) * 5 * 5);
			ret->life = 3;
			break;
		case TYPE_LINEAR_4:
			memcpy(&ret->bitmap, &bitmap_TL4, sizeof(u8) * 5 * 5);
			ret->life = 4;
			break;
		case TYPE_TSHAPE_5:
			memcpy(&ret->bitmap, &bitmap_TT5, sizeof(u8) * 5 * 5);
			ret->life = 5;
			break;
		default:
			_logf(L_FATAL, "Attempted construction boat with invalid or unsupported type %d", type);
			free(ret);
			return NULL;
	}

	_logf(L_INFO, "Boat constructed with type %d and rotation %d", type, rotation);
	return ret;
}

return_code boat_destruct(Boat* boat)
{
	if (boat == NULL)
	{
		return BOAT_INVALID_BOAT;
	}

	_logf(L_INFO, "Boat destructed with type %d and rotation %d", boat->type, boat->rotation);
	free(boat);

	return RETURN_OK;
}

// Print the Boat's bitmap
return_code boat_print(Boat* boat)
{
	if (boat == NULL)
	{
		return BOAT_INVALID_BOAT;
	}

	// Bitmap headers
	printf("   | ");
	for (u8 x = 0; x < 5; x++)
	{
		printf("%02hhu ", x);
	}
	newline();

	printf("---+");
	for (u8 x = 0; x < 5; x++)
	{
		printf("---");
	}
	newline();

	// Bitmap content
	for (u8 x = 0; x < 5; x++)
	{
		printf("%02hhu | ", x);
		for (u8 y = 0; y < 5; y++)
		{
			switch (boat->bitmap[x][y])
			{
				case 0:
					printf("~~ ");
					break;
				case 1:
					printf("BB ");
					break;
				case 2:
					printf("OO ");
					break;
				case 3:
					printf("xx ");
					break;
				default:
					printf("?? ");
			}
		}
		newline();
	}

	return RETURN_OK;
}

// Clockwise rotation (90º)
return_code boat_rotate(Boat* boat)
{
	u8 rotated[5][5];

	if (boat == NULL)
	{
		return BOAT_INVALID_BOAT;
	}

	for (u8 i = 0; i < 5; i++)
	{
		for (u8 j = 0; j < 5; j++)
		{
			rotated[i][j] = boat->bitmap[5-j-1][i];
		}
	}

	// Copy the rotated matrix to the source one
	memcpy(&boat->bitmap, &rotated, sizeof(u8) * 5 * 5);
	// Update Boat's internal rotation
	boat->rotation = (boat->rotation == 0) ? 3 : boat->rotation - 1;

	return RETURN_OK;
}
