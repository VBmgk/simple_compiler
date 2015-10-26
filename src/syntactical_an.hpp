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
  _P,
  _LDE,
  _DV,
  _T,
  _VAR,
  _ID,
  _COLON,
  _SEMICOLON,
  _INTEGER,
  _BOOLEAN,
  _END_OF_CODE,
  _UNKNOWN
} gram_token;


class Stack {
  std::vector<int> _data;

public:
  void push(int d);
  int top(void);
  void pop(int);
  void print(void);
};

class SyntacticalAn {
  Stack stack;
  AlexicalAnalizer *lex_an;
  int gram_action_table[STATES_NUM][VAR_NUM],
      rules[GRAM_RULES_NUM][2];

public:  
  SyntacticalAn(std::string _code, std::string _grammar);
  ~SyntacticalAn(void);
  gram_token convert_token(t_token);
  int check_syntax(void);
  void setup_action_table(std::string gram_file);
};
