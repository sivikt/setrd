/**
 * author Serj Sintsov, <ssivikt@gmail.com>, 2014-2015
 */

#include <stdlib.h>

#include "util.h"


error_t *create_error(char *message, position_t pos)
{
  error_t *error = (error_t *) malloc(sizeof(error_t));
  error->message = message;
  error->pos.row = pos.row;
  error->pos.col = pos.col;

  return error;
}


error_t *add_error(error_t *new, error_t **prev)
{
  if (*prev == NULL)
  {
    (*prev) = new;
  }
  else
  {
    (*prev)->next = new;
  }

  return new;
}


void free_errors_list(error_t *error)
{
  error_t *next = error;

  while (next != NULL)
  {
    error = next;
    next = error->next;
    free(error->message);
    free(error);
  }
}
