#include <cstdlib>
#include <cstdio>
#include <fstream>
#include "alexical_an.hpp"
#include "syntactical_an.hpp"

int main(void) {
  AlexicalAnalizer lex_an("../test_codes/test_code_3.lang");
  int token_2 = -1;
  t_token buff = VAR;

  printf(" Compilador\n");
  
  printf(" Análise léxica\n");
  for (int i=0; buff != END_OF_CODE ;i++) {
    buff = lex_an.nextToken();
    token_2 = lex_an.getLastToken2();
    lex_an.print(buff);
    if (token_2 >= 0) lex_an.print_const(token_2);
  }

  /*
  SyntacticalAn syn_an("../test_codes/test_code.lang","../compilada.csv");
  switch(syn_an.check_syntax()) {
    case EXIT_LEXICAL_ERROR:
      printf("lexical_error\n");
      break;
    case EXIT_SYNTAX_ERROR:
      printf("syntax_error\n");
      break;
    case EXIT_SYNTAX_SUCCESS:
      printf("syntax correct!!!\n");
      break;
  }
  */

  return EXIT_SUCCESS;
}
