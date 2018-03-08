#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "lexer.h"

#define MAX_TOKENS 50

token_list *parse_tokens (char *in) {
  char *c = in;
  int token_count = 0;

  token *out = malloc(MAX_TOKENS * sizeof(token));

  while(*c != '\0') {
    if (*c == '[') {
      out[token_count].type = TOKEN_BRACKET_OPEN;
      token_count++;
      c++;
    } else if (*c == ']') {
      out[token_count].type = TOKEN_BRACKET_CLOSE;
      token_count++;
      c++;
    } else if (*c == ',') {
      out[token_count].type = TOKEN_COMMA;
      token_count++;
      c++;
    } else if (*c == ' ') {
      c++;
    } else {
      char *endptr;

      errno = 0;
      double d = strtod(c, &endptr);

      if (errno == ERANGE) {
        fprintf(stderr, "Lexer Error: Range Error\n");
        exit(EXIT_FAILURE);
      }

      if (c == endptr) {
        fprintf(stderr, "Unrecognised char: '%c'\n", *c);
        c++;
        continue;
      }

      out[token_count].type = TOKEN_NUMBER;
      out[token_count].val = d;
      token_count++;

      c = endptr;
    }
  }

  token_list *result = malloc(sizeof(token_list));
  result->count = token_count;
  result->items = out;

  return result;
}

void free_tokens (token_list *list) {
  free(list);
}

void debug_tokens (token_list *list) {

  printf ("%d tokens(s)\n", list->count);

  int i;
  for (i = 0; i < list->count; i++) {
    token item = list->items[i];
    switch(item.type) {
      case TOKEN_BRACKET_OPEN:
        printf("OPEN BRACKET\n");
        break;
      case TOKEN_BRACKET_CLOSE:
        printf("CLOSE BRACKET\n");
        break;
      case TOKEN_NUMBER:
        printf("NUMBER: %lf\n", item.val);
        break;
      case TOKEN_COMMA:
        printf("COMMA\n");
        break;
    }
  }

}
