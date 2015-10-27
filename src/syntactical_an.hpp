#define IS_SHIFT(p)     ((p) > 0)
#define IS_REDUCTION(p) ((p) < 0)
#define RULE(p)         (-(p))

#define EXIT_SYNTAX_ERROR -1
#define EXIT_SYNTAX_SUCCESS 0
#define EXIT_LEXICAL_ERROR 1
#define FINAL_STATE 5
#define GRAM_RULES_NUM 6
#define VAR_NUM 11
#define STATES_NUM 13

enum {
  LEN,
  LEFT
};

// auxiliar grammar symbols
// must mach action table order

typedef enum {
/*
 * _P,
 * _LDE,
 * _DV,
 * _T,
 * _VAR,
 * _ID,
 * _COLON,
 * _SEMICOLON,
 * _INTEGER,
 * _BOOLEAN,
 * _END_OF_CODE,
 * _UNKNOWN 
 */
  _END_OF_CODE,
  _LEFT_PARENTHESIS,
  _RIGHT_PARENTHESIS,
  _PLUS,
  _MINUS,
  _COLON,
  _SEMICOLON,
  _LESS_THAN,
  _LESS_OR_EQUAL,
  _EQUALS,
  _EQUAL_EQUAL,
  _GREATER_THAN,
  _GREATER_OR_EQUAL,
  _Id,
  _BOOLEAN,
  _BREAK,
  _ELSE,
  _FALSE,
  _FUNCTION,
  _IF,
  _INTEGER,
  _main,
  _n,
  _TRUE,
  _VAR,
  _VOID,
  _LEFT_BRACES,
  _RIGHT_BRACES,
  _ACCEPT,
  _B,
  _DE,
  _DF,
  _DV,
  _F,
  _FALSE,
  _ID,
  _IDD,
  _IDU,
  _L,
  _LDE,
  _LDV,
  _NUMERAL,
  _P,
  _R,
  _S,
  _T,
  _TRUE,
  _UNKNOWN
} gram_token;

// TODO
typedef enum { N_, L_, B_ } t_nonterminal;

// TODO
typedef struct {
  t_nonterminal nont;
  union {
    struct {
      int v;
    } N;
    struct {
      int v, c;
    } L;
    struct {
      int v;
    } B;
  }_;
} t_attrib;


class Stack {
  std::vector<int> _data;

public:
  void push(int d);
  int top(void);
  int top(int);
  void pop(int);
  void print(void);
};

class SyntacticalAn {
  Stack stack, sem_stack;
  AlexicalAnalizer *lex_an;
  int gram_action_table[STATES_NUM][VAR_NUM],
      rules[GRAM_RULES_NUM][2];

public:  
  SyntacticalAn(std::string _code, std::string _grammar);
  ~SyntacticalAn(void);
  gram_token convert_token(t_token);
  int check_syntax(void);
  void setup_action_table(std::string gram_file);
  void semantics(int);
};
