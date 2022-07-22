/**
 * author Serj Sintsov, <ssivikt@gmail.com>, 2014-2015
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "panic.h"
#include "lexer.h"


/* read 1024 bytes at a time */
static const size_t SCANNER_BUFFER_SIZE = 1024;

/* suppose that 64 char identifiers a really big rarity */
static const size_t MIN_ID_BUFFER_CAPACITY = 64;


typedef enum lex_err_code
{
  UNEXPECTED_SYMBOL

} lex_err_code_t;


typedef struct scanner_marker
{
  char *buff;
  char symbol;
  size_t buff_size;
  size_t buff_pos;
  position_t src_pos;
  FILE *src;

  struct scanner_identifier
  {
    char *symbols;
    size_t capacity;
    size_t length;

  } id;

} scanner_marker_t;


static inline char *to_error_msg(lex_err_code_t err_code)
{
    switch (err_code)
    {
      case UNEXPECTED_SYMBOL: return strdup("Unexpected symbol!");
      default: return strdup("lexical error");
    }
}


static FILE *open_src(const char *src_path)
{
  if (src_path == NULL)
  {
    panic("Input file path pointer is NULL");
  }

  FILE *src = fopen(src_path, "r");

  if (src == NULL)
  {
    panic("Could't open file '%s'", src_path);
  }

  return src;
}


static inline bool is_eol(char c)
{
  /* accept only LF -- Unix-like newline terminals */
  return (c == '\n') ? TRUE : FALSE;
}


static inline bool is_whitespace(char c)
{
  return (c == ' ' || c == '\t' || is_eol(c)) ? TRUE : FALSE;
}


static inline bool is_comment(char c)
{
  return (c == '#') ? TRUE : FALSE;
}


static inline bool is_regular(char c)
{
  return (isalnum(c) || c == '_') ? TRUE : FALSE;
}


static inline bool is_special(char c)
{
  return (c == '=' || c == '{' || c == '}' || c == '<' || c == '>' || c == ',') ? TRUE : FALSE;
}


static lexem_t *create_lexem(token_t token, position_t pos)
{
  lexem_t *lexem = (lexem_t *) malloc(sizeof(lexem_t));

  lexem->next = NULL;
  lexem->token = token;
  lexem->length = 0;
  lexem->symbols = NULL;
  lexem->pos.row = pos.row;
  lexem->pos.col = pos.col;

  return lexem;
}


static void free_lexem(lexem_t *lexem)
{
  lexem_t *next = lexem;

  while (next != NULL)
  {
    lexem = next;
    next = lexem->next;
    free(lexem->symbols);
    free(lexem);
  }
}


static lexer_out_t *init_lexer_out()
{
  lexer_out_t *out = (lexer_out_t *) malloc(sizeof(lexer_out_t));
  out->lex_length = 0;
  out->err_length = 0;
  out->error = NULL;
  out->lexem = NULL;

  return out;
}


void free_lexer_out(lexer_out_t *out)
{
  free_lexem(out->lexem);
  free_errors_list(out->error);
  free(out);
}


static void push_lexem(lexem_t *new, lexem_t **tail, lexer_out_t *out)
{
  if (out->lexem == NULL)
  {
    out->lexem = new;
    *tail = new;
    out->lex_length = 1;
  }
  else
  {
    (*tail)->next = new;
    *tail = new;
    out->lex_length += 1;
  }
}


static scanner_marker_t *init_scanner(const char *src_path)
{
  FILE* src = open_src(src_path);

  scanner_marker_t *marker = (scanner_marker_t *) malloc(sizeof(scanner_marker_t));
  marker->buff = (char *) malloc(SCANNER_BUFFER_SIZE * sizeof(char));
  marker->buff_size = 0;
  marker->buff_pos  = 0;
  marker->src_pos.row = 1;
  marker->src_pos.col = 0;
  marker->src = src;
  marker->id.length = 0;
  marker->id.symbols = (char *) malloc(MIN_ID_BUFFER_CAPACITY * sizeof(char));
  marker->id.capacity = MIN_ID_BUFFER_CAPACITY;

  return marker;
}


static void close_scanner(scanner_marker_t *marker)
{
  fclose(marker->src);
  free(marker->id.symbols);
  free(marker->buff);
  free(marker);
}


inline static void update_marker_src_pos(scanner_marker_t *marker)
{
  if (is_eol(marker->symbol))
  {
    marker->src_pos.row += 1;
    marker->src_pos.col = 0;
  }
  else
  {
    marker->src_pos.col += 1;
  }
}


static bool scan(scanner_marker_t *marker)
{
  if (marker->buff_pos < marker->buff_size)
  {
    marker->symbol = marker->buff[marker->buff_pos];
    marker->buff_pos += 1;
    update_marker_src_pos(marker);

    return TRUE;
  }

  if (feof(marker->src))
  {
    return FALSE;
  }

  marker->buff_size = fread(marker->buff, sizeof(char), SCANNER_BUFFER_SIZE, marker->src);
  if (ferror(marker->src))
  {
    panic("while reading source file");
  }

  marker->buff_pos = 0;
  marker->symbol = marker->buff[marker->buff_pos];
  update_marker_src_pos(marker);

  return TRUE;
}


static void skip_comments(scanner_marker_t *marker)
{
  while (scan(marker) && !is_eol(marker->symbol));
}


static void accumulate_identifier(scanner_marker_t *marker)
{
  marker->id.symbols[marker->id.length] = marker->symbol;
  marker->id.length += 1;
}


static lexem_t *create_identifier(scanner_marker_t *marker)
{

  lexem_t *lexem = create_lexem(IDENTIFIER, marker->src_pos);
  marker->id.length = 0;

  accumulate_identifier(marker);
  while (scan(marker) && is_regular(marker->symbol))
  {
    accumulate_identifier(marker);
  }

  lexem->symbols = strndup(marker->id.symbols, marker->id.length);
  lexem->length = marker->id.length;
  lexem->pos.col = lexem->pos.col - marker->id.length + 1;

  return lexem;
}


static lexem_t *create_special_lexem(const scanner_marker_t *marker)
{
  switch (marker->symbol)
  {
    case '=': return create_lexem(EQUALS, marker->src_pos);
    case '{': return create_lexem(LBRACE, marker->src_pos);
    case '}': return create_lexem(RBRACE, marker->src_pos);
    case '<': return create_lexem(LABRACKET, marker->src_pos);
    case '>': return create_lexem(RABRACKET, marker->src_pos);
    case ',': return create_lexem(COMMA, marker->src_pos);
    default:  return NULL;
  }
}


static error_t *meet_lexical_error(lex_err_code_t err_code, lexer_out_t *out,
                                   const scanner_marker_t *marker)
{
  error_t *err = create_error(to_error_msg(err_code), marker->src_pos);
  add_error(err, &out->error);
  out->err_length += 1;
  return err;
}


lexer_out_t *fetch_lemexs(const char *src_path)
{
  scanner_marker_t *marker = init_scanner(src_path);
  lexer_out_t *out = init_lexer_out();
  lexem_t *tail = NULL;

  while (scan(marker))
  {
    check_current_marker:

    if (is_whitespace(marker->symbol))
    {
      continue;
    }

    if (is_comment(marker->symbol))
    {
      skip_comments(marker);
      continue;
    }

    if (is_regular(marker->symbol))
    {
      push_lexem(create_identifier(marker), &tail, out);
      goto check_current_marker;
    }

    if (is_special(marker->symbol))
    {
      push_lexem(create_special_lexem(marker), &tail, out);
    }
    else
    {
      meet_lexical_error(UNEXPECTED_SYMBOL, out, marker);
      close_scanner(marker);
      return out;
    }
  }

  close_scanner(marker);

  return out;
}
