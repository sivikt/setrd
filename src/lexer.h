/**
 * author Serj Sintsov, <ssivikt@gmail.com>, 2014-2015
 */

#ifndef __LEXER_H
#define __LEXER_H

#include "util.h"

/* Possible token types */
typedef enum token
{
  IDENTIFIER,
  LBRACE,
  RBRACE,
  LABRACKET,
  RABRACKET,
  EQUALS,
  COMMA

} token_t;


typedef struct lexem
{
  struct lexem *next;
  position_t pos;
  token_t token;
  size_t length;
  char *symbols;

} lexem_t;


typedef struct lexer_out
{
  lexem_t *lexem;
  error_t *error;
  size_t lex_length;
  size_t err_length;

} lexer_out_t;


/**
 * Reads all lexems at ones.
 */
lexer_out_t *fetch_lemexs(const char *src_path);

void free_lexer_out(lexer_out_t *out);


#endif /* __LEXER_H */
