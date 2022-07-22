/**
 * author Serj Sintsov, <ssivikt@gmail.com>, 2014-2015
 */

#include <stdio.h>
#include <stdlib.h>

#include "eval.h"

int main(int argc, char **argv)
{
  if (argc == 1)
  {
    printf("error: Specify input file!\n");
    return EXIT_FAILURE;
  }

  eval(argv[1]);

  return EXIT_SUCCESS;
}
