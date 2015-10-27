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
// TODO: update stack for more data types
int Stack::top(void) { return _data.back(); }
int Stack::top(int offset_from_top) {
  if ( offset_from_top + 1 > _data.size() ) return 0;
  return _data.at(_data.size() - 1 - offset_from_top);
}
void Stack::print(void) {
  for (int i=0; i<_data.size() ;i++) { printf(" %d", _data.at(i)); }
  printf("\n");
}

// Syntactical Analyser
SyntacticalAn::SyntacticalAn(std::string code, std::string grammar) {
  // setup of variables
  // setup of rules matrix
  /*
  int _r[GRAM_RULES_NUM][2] = {
    1, _P,
    2, _LDE,
    1, _LDE,
    5, _DV,
    1, _T,
    1, _T
  };
  */
  int _r[GRAM_RULES_NUM][2] = {
    1, _P,
    2, _LDE,
    1, _LDE,
    1, _DE,
    1, _DE,
    5, _DV,
    1, _T,
    1, _T
    8, _DF,
    4, _B,
    2, _LDV,
    1, _LDV,
    7, _S,
    1, _S,
    2, _S,
    2, _S,
    3, _L,
    3, _L,
    3, _L,
    3, _L,
    3, _L,
    3, _L,
    1, _L,
    3, _R,
    3, _R,
    1, _R,
    1, _F,
    3, _F,
    1, _F,
    1, _F,
    1, _F,
    1, _ID,
    1, _IDD,
    1, _IDU,
    1, _TRUE,
    1, _FALSE,
    1, _NUM
  };
  // copy to rules array
  memcpy(rules, _r, GRAM_RULES_NUM * 2 * sizeof(int));
  // load grammar action table
  setup_action_table(grammar);
  // setup of lexical analizer
  lex_an = new AlexicalAnalizer(code);
}

SyntacticalAn::~SyntacticalAn(void) { delete lex_an; }

gram_token SyntacticalAn::convert_token(t_token t) {
  switch (t) {
    case END_OF_CODE:  return _END_OF_CODE;
    case LEFT_PARENTHESIS:  return _LEFT_PARENTHESIS;
    case RIGHT_PARENTHESIS:  return _RIGHT_PARENTHESIS;
    case PLUS:  return _PLUS;
    case MINUS:  return _MINUS;
    case COLON:  return _COLON;
    case SEMICOLON:  return _SEMICOLON;
    case LESS_THAN:  return _LESS_THAN;
    case LESS_OR_EQUAL:  return _LESS_OR_EQUAL;
    case EQUALS:  return _EQUALS;
    case EQUAL_EQUAL:  return _EQUAL_EQUAL;
    case GREATER_THAN:  return _GREATER_THAN;
    case GREATER_OR_EQUAL:  return _GREATER_OR_EQUAL;
    case Id:  return _Id;
    case BOOLEAN:  return _BOOLEAN;
    case BREAK:  return _BREAK;
    case ELSE:  return _ELSE;
    case FALSE:  return _FALSE;
    case FUNCTION:  return _FUNCTION;
    case IF:  return _IF;
    case INTEGER:  return _INTEGER;
    case main:  return _main;
    case n:  return _n;
    case TRUE:  return _TRUE;
    case VAR:  return _VAR;
    case VOID:  return _VOID;
    case LEFT_BRACES:  return _LEFT_BRACES;
    case RIGHT_BRACES:  return _RIGHT_BRACES;
    case ACCEPT:  return _ACCEPT;
    case B:  return _B;
    case DE:  return _DE;
    case DF:  return _DF;
    case DV:  return _DV;
    case F:  return _F;
    case FALSE:  return _FALSE;
    case ID:  return _ID;
    case IDD:  return _IDD;
    case IDU:  return _IDU;
    case L:  return _L;
    case LDE:  return _LDE;
    case LDV:  return _LDV;
    case NUMERAL:  return _NUMERAL;
    case P:  return _P;
    case R:  return _R;
    case S:  return _S;
    case T:  return _T;
    case TRUE:  return _TRUE;
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
#ifdef DEBUG
      printf(" shift ");
#endif
      stack.push(curr_action);
      input_token = convert_token ( lex_an->nextToken() );
      // check token
      if (input_token == _UNKNOWN)  {
        return EXIT_LEXICAL_ERROR;
      }
    } else if ( IS_REDUCTION ( curr_action ) ) {
      // reduction
      //rule = RULE( curr_action ) - 2;
      rule = RULE( curr_action ) - 1;
#ifdef DEBUG
      printf(" reduction rule: %d, len: %d, %d", rule, LEN, rules[rule][LEN]);
#endif
      stack.pop( rules[rule][LEN] );
      stack.push( gram_action_table [ stack.top() ][ rules[rule][LEFT] ] );
      semantics(rule);
    } else if ( curr_action == 0 ) {
      // syntax problem
      return EXIT_SYNTAX_ERROR;
    }
#ifdef DEBUG
    printf("action: %d ", curr_action);
    stack.print();
#endif
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

void SyntacticalAn::semantics(int rule) {
  // TODO
  // initialize buffer attributes
  t_attrib a, b, c;
  switch ( rule ) {
    // one case for each rule
    case 0:
    default:
      a;
  }
}
