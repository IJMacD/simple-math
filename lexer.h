#ifndef LEXER_H
#define LEXER_H

#define TOKEN_BRACKET_OPEN 1
#define TOKEN_BRACKET_CLOSE 2
#define TOKEN_NUMBER 3
#define TOKEN_COMMA 4

typedef struct token {
  int type;
  double val;
} token;

typedef struct token_list {
  int count;
  token *items;
} token_list;

token_list *parse_tokens (char *);

void free_tokens (token_list *);

void debug_tokens (token_list *);

#endif
