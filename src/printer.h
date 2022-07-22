/**
 * author Serj Sintsov, <ssivikt@gmail.com>, 2014-2015
 */

 #ifndef __PRINTER_H
 #define __PRINTER_H

#include "util.h"
#include "lexer.h"
#include "parser.h"


char *token_as_str(token_t token);

void print_errors_to_std(const error_t *error, size_t length);

void print_lexems_to_std(const lexem_t *lexem, size_t length);

void print_sets_to_std(const set_link *head_link);


#endif /* __PRINTER_H */
