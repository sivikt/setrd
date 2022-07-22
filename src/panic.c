/**
 * author Serj Sintsov, <ssivikt@gmail.com>, 2014-2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "panic.h"


static void error(const char *fmt, va_list args)
{
  fputs("Error: ", stderr);
  vfprintf(stderr, fmt, args);
}


void panic(const char *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  error(fmt, args);
  va_end(args);

  exit(EXIT_FAILURE);
}
