/**
 * author Serj Sintsov, <ssivikt@gmail.com>, 2014-2015
 */

 #ifndef __UTIL_H
 #define __UTIL_H

 typedef int bool;
 static const bool TRUE  = 1;
 static const bool FALSE = 0;

 typedef struct position
 {
   int col;
   int row;

 } position_t;

 typedef struct error
 {
   position_t pos;
   char *message;
   struct error *next;

 } error_t;


error_t *create_error(char *message, position_t pos);

error_t *add_error(error_t *new, error_t **prev);

void free_errors_list(error_t *error);


#endif /* __UTIL_H */
