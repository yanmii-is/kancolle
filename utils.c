#include "utils.h"


uint8_t read_u8(char *prompt)
{
  char in[4];
  // We use an u16 as a temporary buffer to detect OOB input
  int16_t ret = -1;

  while (ret < 0)
  {
    printf(prompt);
    fgets(in, sizeof(in), stdin);
    ret = atoi(in);

    // Detect OOB input
    if (ret < 0 || ret > 255)
    {
      printf("Input error, you must input a valid number [0,255]\n");
      ret = -1;
    }
  }

  return (uint8_t) ret;
}
