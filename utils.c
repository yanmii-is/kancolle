#include "utils.h"


// NOTE: We are assuming that the input is always the
//       expected size as the teacher indicated, however
//       it would be best to have this eat unexpected
//       inputs without trouble.
//       Right now if you send more than the bytes it can
//       store on the read buffers it won't flush stdin
//       and the remaining of the input will fall through
//       to the next read functions on the program.

u8 read_u8(char *prompt)
{
	// 3 byte input + 1 byte newline + 1 byte terminator
	char in[5];
	// We use a s16 as a temporary buffer to detect OOB input
	s16  ret = -1;

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

	return (u8) ret;
}

bool read_bool(char *prompt)
{
	// 1 byte input + 1 byte newline + 1 byte terminator
	char in[3];

	while (true)
	{
		printf(prompt);
		fgets(in, sizeof(in), stdin);

		if (in[0] == '0')
		{
			return false;
		}
		else if (in[0] == '1')
		{
			return true;
		}
		else
		{
			printf("Input error (%c %c %c), you must input a valid boolean [0,1]\n", in[0], in[1], in[2]);
		}
	}
}

void clear()
{
	if (!CLEAR_SCREEN)
	{
		return;
	}

	#if defined(_WIN32)
	system("cls");
	#endif
	#if !defined(_WIN32)
	system("clear");
	#endif
}

void newline()
{
	printf("%c", '\n');
}
