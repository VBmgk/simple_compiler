#include <cstdlib>
#include <cstdio>
#include <fstream>
#include "alexical_an.hpp"
#include "syntactical_an.hpp"

int main(void) {
  //AlexicalAnalizer lex_an("../test_code.lang");
  //t_token buff;

  printf(" Compilador\n");
  /*
  printf(" Análise léxica\n");
  buff = lex_an.nextToken();
  lex_an.print(buff);
  buff = lex_an.nextToken();
  lex_an.print(buff);
  buff = lex_an.nextToken();
  lex_an.print(buff);
  buff = lex_an.nextToken();
  lex_an.print(buff);
  buff = lex_an.nextToken();
  lex_an.print(buff);
  buff = lex_an.nextToken();
  lex_an.print(buff);
  buff = lex_an.nextToken();
  lex_an.print(buff);
  buff = lex_an.nextToken();
  lex_an.print(buff);
  buff = lex_an.nextToken();
  lex_an.print(buff);
  buff = lex_an.nextToken();
  lex_an.print(buff);
  buff = lex_an.nextToken();
  lex_an.print(buff);
  buff = lex_an.nextToken();
  lex_an.print(buff);
  */
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

  return EXIT_SUCCESS;
}
