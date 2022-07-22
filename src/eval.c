/**
 * Translator entry point. Semantic part. It links lexer and parser together.
 *
 * author Serj Sintsov, <ssivikt@gmail.com>, 2014-2015
 */

#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "eval.h"
#include "lexer.h"
#include "parser.h"
#include "printer.h"


static void print_lexer_results(const lexer_out_t *lexout)
{
  if (lexout->err_length == 0)
  {
    print_lexems_to_std(lexout->lexem, lexout->lex_length);
  }
  else
  {
    print_errors_to_std(lexout->error, lexout->err_length);
  }

  printf("\n");
}


static void process_ast(const set_link *set_list_head, const synt_error *errors)
{
  if (errors != NULL)
  {
    //print_errors_to_std(errors);
  }
  else
  {
    print_sets_to_std(set_list_head);
  }
}


void eval(const char *src_path)
{
  lexer_out_t *lexout = fetch_lemexs(src_path);
  print_lexer_results(lexout);

  // do syntax analysis if no lexical errors
  if (lexout->err_length == 0)
  {
    synt_error *errors;
    set_link *set_list_head = do_syntan(lexout->lexem, &errors);
    process_ast(set_list_head, errors);

    free_synt_error(errors);
    free_set_link(set_list_head);
  }

  free_lexer_out(lexout);
}
