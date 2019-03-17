#ifndef PROJ_H
# define PROJ_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

int     eval_expr(char *expr);
int     parse_number(char **expr);
int     parse_factors(char **expr);
int     parse_sum(char **expr);

#endif
