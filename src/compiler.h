#pragma once

typedef struct {
    int code;
    int lval;
    const char* text;
} token_t;

/* the current token */
token_t token;

void compile(const char* fname);

void build_expr(token_t token, token_t* args);
void macro(token_t token, token_t* args);
