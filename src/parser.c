/**
 * Do syntactic analysis based on input lexems (represented a set definition)
 * and translates the input into C-lang data structures which represent Sets.
 *
 * author Serj Sintsov, <ssivikt@gmail.com>, 2014-2015
 */

#include <stdio.h>
#include <stdlib.h>

#include "panic.h"
#include "lexer.h"
#include "parser.h"

/*static synt_error** push_error(const char* msg, const lexem_link* lexem_link,
                               synt_error** errors)
{
  // TODO impl
  return NULL;
}*/


/*static int match_token(token token, const lexem_link* lexem_link,
                       const char* err_msg, synt_error** errors)
{
  printf("(dbg): match token %s\n", token_as_str(token));

  if (lexem_link != NULL && token == lexem_link->lexem->token)
  {
    return 1;
  }
  else
  {
    //push_error(err_msg, lexem_link, errors_head);
    return 0;
  }
}*/


/*static int match_token_symbol(token token, char c, const lexem_link* lexem_link)
{
  printf("(dbg): match token symbol %s, %c\n", token_as_str(token), c);
  return  (lexem_link->lexem->content_len == 1 && c == lexem_link->lexem->content[0])
            ? 1
            : 0;
}*/


static set_link* parse_sets_list(const lexem_t *lexem, synt_error **errors)
{
  // TODO fix
  /*lexem_link next_lexem_link = lexem_link;
  synt_error* errors_head = errors;
  set_link* sets_head = NULL;
  //set_link* sets_tail = NULL;

  while (lexem_link != NULL)
  {
    match_token(SET_ELEMENT_ID, lexem_link, errors_head,
                "set name identifier expected");

    match_token_symbol(SPECIAL_TOKEN, '=', lexem_link->next_link))
    {
      errors_tail = push_error("'=' assignment expressions expected", lexem_link,
                               errors_tail);
    }

    if (errors_tail != NULL)
    {
      //free_set_link(NULL);
      return NULL;
    }
  }

  return sets_head;*/
  return NULL;
}


set_link *do_syntan(const lexem_t *lexem, synt_error **errors)
{
  if (lexem == NULL)
    return NULL;

  if (errors == NULL)
    panic("Output errors pointer is null");

  return parse_sets_list(lexem, errors);
}


void free_set_link(set_link *head_link)
{
  printf("(dbg): need to free sets list memory!\n");
}


void free_synt_error(synt_error *errors)
{
  printf("(dbg): need to free error list memory!\n");
}
