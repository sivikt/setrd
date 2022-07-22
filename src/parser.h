/**
 * author Serj Sintsov, <ssivikt@gmail.com>, 2014-2015
 */

#ifndef __PARSER_H
#define __PARSER_H

#include "util.h"
#include "lexer.h"


typedef struct set
{
  char* id;

} set_t;


typedef struct parser_result
{
  set* set;
  size_t err_length;
  error_t *error;

} parser_result_t;


parser_result_t* build_ast(const lexem_t *lexem);

void free_parser_result(parser_result_t *result);

#endif /* __PARSER_H */
