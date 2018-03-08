#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "lexer.h"

Matrix2x2 * parseMatrix2x2 (token_list *list) {
  if (list->count < 8) {
    fprintf(stderr, "Parser Error: (Matrix2x2) Not enough tokens\n");
    return NULL;
  }

  int i = 0;
  double a, b, c, d;

  if (list->items[i].type != TOKEN_BRACKET_OPEN) {
    fprintf(stderr, "Parser Error: (Matrix2x2) First token not a bracket\n");
    return NULL;
  }
  i++;

  if (list->items[i].type != TOKEN_BRACKET_OPEN) {
    fprintf(stderr, "Parser Error: (Matrix2x2) Second token not a bracket\n");
    return NULL;
  }
  i++;

  // Get a

  if (list->items[i].type == TOKEN_NUMBER) {
    a = list->items[i].val;
    i++;

    if (list->items[i].type == TOKEN_COMMA) {
      i++; // Consume optional comma
    }
  } else if (list->items[i].type == TOKEN_COMMA) {
    a = 0; // First token was comma
    i++;
  } else {
    fprintf(stderr, "Parser Error: (Matrix2x2) Expected number or a comma\n");
    return NULL;
  }

  // Get b

  if (list->items[i].type == TOKEN_NUMBER) {
    b = list->items[i].val;
    i++;
  } else if (list->items[i].type == TOKEN_BRACKET_CLOSE) {
    b = 0; // If we're already at the bracket set b=0
  } else {
    fprintf(stderr, "Parser Error: (Matrix2x2) Expected a number\n");
    return NULL;
  }

  if (list->items[i].type != TOKEN_BRACKET_CLOSE) {
    fprintf(stderr, "Parser Error: (Matrix2x2) Too many tokens\n");
    return NULL;
  }
  i++;

  if (list->items[i].type == TOKEN_COMMA) {
    i++; // Consume optional comma
  }

  if (list->items[i].type != TOKEN_BRACKET_OPEN) {
    fprintf(stderr, "Parser Error: (Matrix2x2) Expected a bracket\n");
    return NULL;
  }
  i++;

  // Get c

  if (list->items[i].type == TOKEN_NUMBER) {
    c = list->items[i].val;
    i++;

    if (list->items[i].type == TOKEN_COMMA) {
      i++; // Consume optional comma
    }
  } else if (list->items[i].type == TOKEN_COMMA) {
    c = 0; // First token was comma
    i++;
  } else {
    fprintf(stderr, "Parser Error: (Matrix2x2) Expected number or a comma\n");
    return NULL;
  }

  // Get d

  if (list->items[i].type == TOKEN_NUMBER) {
    d = list->items[i].val;
    i++;
  } else if (list->items[i].type == TOKEN_BRACKET_CLOSE) {
    d = 0; // If we're already at the bracket set d=0
  } else {
    fprintf(stderr, "Parser Error: (Matrix2x2) Expected a number\n");
    return NULL;
  }

  if (list->items[i].type != TOKEN_BRACKET_CLOSE) {
    fprintf(stderr, "Parser Error: (Matrix2x2) Too many tokens\n");
    return NULL;
  }
  i++;

  if (list->items[i].type != TOKEN_BRACKET_CLOSE) {
    fprintf(stderr, "Parser Error: (Matrix2x2) Too many tokens\n");
    return NULL;
  }

  Matrix2x2 *out = malloc(sizeof(Matrix2x2));
  out->val[0][0] = a;
  out->val[0][1] = b;
  out->val[1][0] = c;
  out->val[1][1] = d;

  return out;
}


Vector2 * parseVector2 (token_list *list) {
  if (list->count < 3) {
    fprintf(stderr, "Parser Error: (Vector2) Not enough tokens\n");
    return NULL;
  }

  int i = 0;
  double x, y;

  if (list->items[i].type != TOKEN_BRACKET_OPEN) {
    fprintf(stderr, "Parser Error: (Vector2) First token not a bracket\n");
    return NULL;
  }

  i++;

  // Get x

  if (list->items[i].type == TOKEN_NUMBER) {
    x = list->items[i].val;
    i++;

    if (list->items[i].type == TOKEN_COMMA) {
      i++; // Consume optional comma
    }
  } else if (list->items[i].type == TOKEN_COMMA) {
    x = 0; // First token was comma
    i++;
  } else {
    fprintf(stderr, "Parser Error: (vector2) Second token not a number or a comma\n");
    return NULL;
  }

  // Get y

  if (list->items[i].type == TOKEN_NUMBER) {
    y = list->items[i].val;
    i++;
  } else if (list->items[i].type == TOKEN_BRACKET_CLOSE) {
    y = 0; // If we're already at the bracket set y=0
  } else {
    fprintf(stderr, "Parser Error: (vector2) Second token not a number\n");
    return NULL;
  }

  if (list->items[i].type != TOKEN_BRACKET_CLOSE) {
    fprintf(stderr, "Parser Error: (vector2) Too many tokens\n");
    return NULL;
  }

  Vector2 *out = malloc(sizeof(Vector2));
  out->val[0] = x;
  out->val[1] = y;

  return out;
}
