#include <vector>
#include <sstream>
#include <string>
#include <string.h>
#include <fstream>

#include "alexical_an.hpp"
#include "syntactical_an.hpp"

// Stack methods
void Stack::pop(int n) { for (int i = 0; i<n ;i++) _data.pop_back(); }
void Stack::push(int d) { _data.push_back(d); }
int Stack::top(void) { return _data.back(); }
void Stack::print(void) {
  for (int i=0; i<_data.size() ;i++) { printf(" %d", _data.at(i)); }
  printf("\n");
}

// Syntactical Analyser
SyntacticalAn::SyntacticalAn(std::string code, std::string grammar) {
  // setup of variables
  // setup of rules matrix
  int _r[6][2] = {
    1, _P,
    2, _LDE,
    1, _LDE,
    5, _DV,
    1, _T,
    1, _T
  };
  // copy to rules array
  memcpy(rules, _r, 6 * 2 * sizeof(int));
  // load grammar action table
  setup_action_table(grammar);
  // setup of lexical analizer
  lex_an = new AlexicalAnalizer(code);
}

SyntacticalAn::~SyntacticalAn(void) { delete lex_an; }

gram_token SyntacticalAn::convert_token(t_token t) {
  switch (t) {
    case VAR:         return _VAR;
    case ID:          return _ID;
    case COLON:       return _COLON;
    case SEMI_COLON:  return _SEMICOLON;
    case INTEGER:     return _INTEGER;
    case BOOLEAN:     return _BOOLEAN;
    case END_OF_CODE: return _END_OF_CODE;
    default:          return _UNKNOWN;
  }
}

int SyntacticalAn::check_syntax(void) {
  int curr_state, input_token, curr_action, rule;

  curr_state = 0;
  input_token = convert_token( lex_an->nextToken() );
  stack.push(curr_state);

  do {
    // get current action from action table
    curr_action = gram_action_table[curr_state][input_token];
    if ( IS_SHIFT( curr_action ) ) {
      // shift
      //printf(" shift ");
      stack.push(curr_action);
      input_token = convert_token ( lex_an->nextToken() );
      // check token
      if (input_token == _UNKNOWN)  {
        return EXIT_LEXICAL_ERROR;
      }
    } else if ( IS_REDUCTION ( curr_action ) ) {
      // reduction
      rule = RULE( curr_action ) - 2;
      printf(" reduction rule: %d, len: %d, %d", rule, LEN, rules[rule][LEN]);
      stack.pop( rules[rule][LEN] );
      stack.push( gram_action_table [ stack.top() ][ rules[rule][LEFT] ] );
    } else if ( curr_action == 0 ) {
      // syntax problem
      return EXIT_SYNTAX_ERROR;
    }
    printf("action: %d ", curr_action);
    stack.print();
    // update current state
    curr_state = stack.top();
  } while( curr_state != FINAL_STATE);

  return EXIT_SYNTAX_SUCCESS;
}

void SyntacticalAn::setup_action_table(std::string gram_file) {
  // open file
  std::ifstream  data(gram_file);
  std::string line;

  // alias of size_t
  std::string::size_type sz;

  // Reading table
  for (int i = 0; std::getline(data, line) ;i++) {
    std::stringstream  line_stream(line);
    std::string        cell;

    for (int j = 0; std::getline(line_stream, cell, ',') ;j++) {
      gram_action_table[i][j] = std::stoi (cell, &sz);
    }
  }
}
