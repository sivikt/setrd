/**
 * author Serj Sintsov, <ssivikt@gmail.com>, 2014-2015
 */

#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "lexer.h"
#include "parser.h"
#include "printer.h"


char *token_as_str(token_t token)
{
  switch (token)
  {
    case IDENTIFIER: return "IDENTIFIER";
    case LBRACE: return "LBRACE";
    case RBRACE: return "RBRACE";
    case LABRACKET: return "LABRACKET";
    case RABRACKET: return "RABRACKET";
    case EQUALS: return "EQUALS";
    case COMMA:  return "COMMA";
  }

  return "";
}


void print_errors_to_std(const error_t *error, size_t length)
{

  for (size_t i = 0; i < length && error != NULL; i++)
  {
    printf("Error [%d:%d] - %s", error->pos.row, error->pos.col, error->message);
    printf("\n");
    error = error->next;
  }

  printf("Total errors count %zu\n", length);
}


void print_lexems_to_std(const lexem_t *lexem, size_t length)
{

  for (size_t i = 0; i < length && lexem != NULL; i++)
  {
    printf("%d:%d %s", lexem->pos.row, lexem->pos.col, token_as_str(lexem->token));

    if (lexem->length > 0)
    {
      printf(" '%s'", lexem->symbols);
    }

    printf("\n");

    lexem = lexem->next;
  }

  printf("Total lexems count %zu\n", length);
}


void print_sets_to_std(const set_link *head_link)
{
  printf("(dbg): need to print sets\n");
}
