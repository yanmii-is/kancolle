#include "game.h"
#include "utils.h"
#include "config.h"

// TODO
bool can_add(Board* board, uint8_t x, uint8_t y, uint8_t size, Direction direction)
{
  // Out of boundaries
  if (x + size - 1 > board->height || y + size - 1 > board->width)
  {
    return false;
  }
  return true;
}

uint8_t read_boardsize()
{
  uint8_t ret = 0;
  while (ret < 5 || ret > 100)
  {
    ret = read_u8("Choose the board size: ");
    if (ret < 5 || ret > 100)
    {
      printf("Invalid size (%dx%d), a board must be between 5x5 and 100x100\n", ret, ret);
    }
  }
  return ret;
}

uint8_t read_amount(uint8_t size)
{
  char prompt[38];
  sprintf(prompt, "Choose the amount of size %hhu boats: ", size);
  return read_u8(prompt);
}

uint8_t* read_boatamount()
{
  uint8_t* boats = (uint8_t*) malloc((BOAT_MAX_SIZE + 1) * sizeof(uint8_t));
  boats[0] = 0;
  while (boats[0] == 0)
  {
    uint16_t all = 0;
    for (uint8_t i = BOAT_MIN_SIZE; i <= BOAT_MAX_SIZE; i++)
    {
      boats[i] = read_amount(i);
      all += boats[i];
    }
    boats[0] = all;

    if (all == 0)
    {
      printf("You must have at least one boat on your game\n");
    }
    else if (boats[0] != all || boats[0] > MAX_BOATS)
    {
      // Overflow detected (u16 vs u8), user past the 255 limit or above MAX_BOATS limit
      printf("You can't have more than %d boats on your game\n", MAX_BOATS);
      boats[0] = 0;
    }
  }
  return boats;
}

Boat* read_boat(Board* board, uint8_t size, uint8_t remaining, uint8_t total, bool mode)
{
  // Maybe we can use something other than s16?
  int16_t x = -1;
  int16_t y = -1;
  int8_t  d = -1;

  while (x < 0 || y < 0 || x >= board->height || y >= board->width)
  {
    // Manual input
    if (mode)
    {
      printf("Choose the properties for your next size %d boat\n", size);
      x = read_u8("Vertical coordinate: ");
      y = read_u8("Horizontal coordinate: ");
      // Do not ask for direction on size 1 boats
      if (size != 1)
      {
        while (d != HORIZONTAL && d != VERTICAL)
        {
          d = read_u8("What direction do you want to place this boat at (0 = Horizontal, 1 = Vertical): ");
          if (d != HORIZONTAL && d != VERTICAL)
          {
            printf("Invalid direction\n");
          }
        }
      }
      else {
        d = HORIZONTAL;
      }
    }
    // Random input
    else {
      while (x == -1 || y == -1)
      {
        srand(time(0));
        x = rand() % board->height;
        y = rand() % board->width;
        d = rand() % 2;
      }
    }

    if (!can_add(board, x, y, size, d))
    {
      if (mode)
      {
        printf("Not possible to add size %d boat at (%d, %d) with direction %d\n", size, x, y, d);
      }
      x = -1;
      y = -1;
      d = -1;
    }
  }

  return construct_boat(x, y, size, d);
}

void place_boats(Board* board, uint8_t size, uint8_t total, bool mode)
{
  if (total < 1)
  {
    _logf(L_INFO, "No boats of size %d to place", size);
    return;
  }

  for (uint8_t remaining = total; remaining > 0; remaining--)
  {
    Boat* boat = read_boat(board, size, remaining, total, mode);
    if (add_boat(board, boat) == false)
    {
      destruct_boat(boat);
      remaining++;
      continue;
    }
		printf("\n");
    print_board(board);
    printf("\n");
  }
}

int main(int argc, char *argv[])
{
  clear();
  bool config = read_bool("Choose the configuration type (0 = random, 1 = manual): ");
  uint8_t boardsz = read_boardsize();
  uint8_t* boats = read_boatamount();
  Game* game = construct_game(boardsz, boardsz, boats);

  printf("\n");
  printf("Player 1, it's time to set up your board\n");
  printf("\n");
  print_board(game->board_p1);
  printf("\n");

  for (uint8_t i = BOAT_MAX_SIZE; i >= BOAT_MIN_SIZE; i--)
  {
    place_boats(game->board_p1, i, boats[i], config);
  }

  printf("\n");
  printf("Player 2, it's time to set up your board\n");
  printf("\n");
  print_board(game->board_p2);
  printf("\n");

  for (uint8_t i = BOAT_MAX_SIZE; i >= BOAT_MIN_SIZE; i--)
  {
    place_boats(game->board_p2, i, boats[i], config);
  }

  destruct_game(game);
  return 0;
}
