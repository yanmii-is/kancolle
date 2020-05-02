#include "stdafx.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include "log.h"

u8   read_u8    (char *prompt);
bool read_bool  (char *prompt);
void clear      ();
void newline    ();
