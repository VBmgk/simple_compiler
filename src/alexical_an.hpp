#ifndef ALEXICAL_AN
#define ALEXICAL_AN
#include <vector>
#define MAX_STRING_SIZE 100

typedef enum {
  // palavras reservadas
  ARRAY,
  BOOLEAN,
  BREAK,
  CHAR,
  CONTINUE,
  DO,
  ELSE,
  FALSE,
  FUNCTION,
  IF,
  INTEGER,
  OF,
  STRING,
  STRUCT,
  TRUE,
  TYPE,
  VAR,
  WHILE,
  // simbolos
  COLON,
  SEMI_COLON,
  COMMA,
  EQUALS,
  LEFT_SQUARE,
  RIGHT_SQUARE,
  LEFT_BRACES,
  RIGHT_BRACES,
  LEFT_PARENTHESIS,
  RIGHT_PARENTHESIS,
  AND,
  OR,
  LESS_THAN,
  GREATER_THAN,
  LESS_OR_EQUAL,
  GREATER_OR_EQUAL,
  NOT_EQUAL,
  EQUAL_EQUAL,
  PLUS,
  PLUS_PLUS,
  MINUS,
  MINUS_MINUS,
  TIMES,
  DIVIDE,
  DOT,
  NOT,
  // tokens regulares
  CHARACTER,
  NUMERAL,
  STRINGVAL,
  ID,
  // grammar tokens
  P,
  LDE,
  DV,
  T,
  // token deconhecido
  UNKNOWN,
  // end of code flag
  // the 'dollar' flag
  END_OF_CODE
} t_token;

typedef struct {
  t_token type;
  union {
    char char_const;
    char string_const[MAX_STRING_SIZE];
    char id_name[MAX_STRING_SIZE];
    int int_const;
  };
} ConstValue;

class AlexicalAnalizer {
  std::ifstream source_code;
  t_token last_token;
  int last_token2;
  char next_char;
  std::vector<ConstValue> const_table;
  bool end_of_code;

public:
  AlexicalAnalizer(std::string);
  ~AlexicalAnalizer(void);
  void skipSeparators(void);
  char readChar(void);
  int addCharConst(char);
  int addIntConst(int);
  int addStringConst(std::string);
  t_token nextToken(void);
  int getLastToken2(void);
  t_token searchKeyWord(std::string);
  int searchName(std::string);
  void print(t_token);
};
#endif
