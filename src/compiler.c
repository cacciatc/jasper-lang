#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>

#include "compiler.h"
#include "parser.h"
#include "parser.c"
#include "scanner.h"
#include "symtab.h"
#include "scope.h"

void print_token(token_t token) {
    printf("token: lval = %d, text = %s, code = %d\n", 
        token.lval, token.text, token.code);
}

void instruction(token_t instr, token_t* args, uint8_t argc) {
    print_token(instr);
}

void macro(token_t expr, token_t* args) {
    print_token(expr);
}

void compile(const char* fname) {
    /* open input file */
    yyin = fopen(fname, "r");
    if(!yyin) {
        fprintf(stderr, "Unable to open %s for compilation:\n\t%s", 
            fname, strerror(errno));
        exit(EXIT_FAILURE);
    }

    token_t   token;
    void*     parser;
    scope_t*  scope;

    /* create global scope */
    scope_create(&scope);    
    
    /* init parser */
    parser = ParseAlloc(malloc);

    do {
        /* get next code */
        token.code  = yylex();
        token.text  = strdup(yytext);
        token.lval  = next_token.lval;
        
        /* parse token */
        Parse(parser, token.code, token, scope);
    } while(token.code > 0);
    
    /* free EOF token */
    free(token.text);

    /* TODO: better scanner error output */
    if(token.code == -1) {
        fprintf(stderr, "Scanner encountered a problem.\n");
    }

    /* close input file */
    if(yyin) {
        fclose(yyin);
    }

    /* cleanup parser */
    ParseFree(parser, free);

    /* cleanup global scope */
    scope_free(&scope);
}
