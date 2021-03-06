%{
#include <stdlib.h>

#include "trial-lang.h"
#include "y.tab.h"

struct parser_control {
  tl_state *tl;
  tl_value value;
};

#define YY_DECL int yylex (struct parser_control *p)
%}

%%

"(" return tLPAREN;
")" return tRPAREN;
"." return tDOT;
"'" return tQUOTE;
[1-9][0-9]* { yylval.datum = tl_float_value(atoi(yytext)); return tNUMBER; }
[a-zA-Z+-/*][a-z0-9A-Z+-/*]* { yylval.datum = tl_intern_cstr(p->tl, yytext); return tSYMBOL; }

%%

int yywrap() {
  return 1;
}
