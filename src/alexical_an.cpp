#include <string>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <cctype>
#include "alexical_an.hpp"

int AlexicalAnalizer::searchName(std::string name) {
  int i = 0;
  // search in vector token_sec
  for (auto know_id: const_table) {
    if (know_id.type == ID && strcmp(know_id.id_name, name.c_str()) == 0) return i;
    i++;
  }

  // Add id to table
  ConstValue buff;
  buff.type = ID;
  strcpy(buff.id_name, name.c_str());
  const_table.push_back(buff);

  return i;
}
  
int AlexicalAnalizer::getLastToken2(void) { return last_token2; }

AlexicalAnalizer::AlexicalAnalizer(std::string source_code_name) {
  // setup file flag
  end_of_code = false;
  // open file
  source_code.open(source_code_name.c_str());
  // read first char of file
  next_char = readChar();
}

AlexicalAnalizer::~AlexicalAnalizer() {
  // close file
  source_code.close();
}

void AlexicalAnalizer::skipSeparators(void) {
  while (next_char == ' ' || next_char == '\n' ||
         next_char == '\f'|| next_char == '\t' ||
         next_char == '\v'|| next_char == '\r') {
    next_char = readChar();
  }
}

char AlexicalAnalizer::readChar(void) {
  char buff = '@';
  if (!source_code.eof()) {
    buff = source_code.get();
    if (source_code.good()) {
      return buff;
    }
  }
  end_of_code = true;
  return buff;
}

t_token AlexicalAnalizer::searchKeyWord(std::string name) {
  // regular key words
  if(name == "array") return ARRAY;
  if(name == "boolean") return BOOLEAN;
  if(name == "break") return BREAK;
  if(name == "char") return CHAR;
  if(name == "continue") return CONTINUE;
  if(name == "do") return DO;
  if(name == "else") return ELSE;
  if(name == "false") return FALSE;
  if(name == "function") return FUNCTION;
  if(name == "if") return IF;
  if(name == "integer") return INTEGER;
  if(name == "of") return OF;
  if(name == "string") return STRING;
  if(name == "struct") return STRUCT;
  if(name == "true") return TRUE;
  if(name == "type") return TYPE;
  if(name == "var") return VAR;
  if(name == "while") return WHILE;
  if(name == "and") return AND;
  if(name == "or") return OR;
  if(name == "not") return NOT;
  
  return ID;
}

int AlexicalAnalizer::addCharConst(char value) {
  // setup values
  ConstValue buff;
  buff.type = CHARACTER; 
  buff.char_const = value;
  // add to table
  const_table.push_back(buff);
  return const_table.size() - 1;
}

int AlexicalAnalizer::addIntConst(int value) {
  // setup values
  ConstValue buff;
  buff.type = INTEGER; 
  buff.int_const = value;
  // add to table
  const_table.push_back(buff);
  return const_table.size() - 1;
}

int AlexicalAnalizer::addStringConst(std::string value) {
  // setup values
  ConstValue buff;
  buff.type = STRINGVAL; 
  strcpy(buff.string_const, value.c_str());
  // add to table
  const_table.push_back(buff);
  return const_table.size() - 1;
} 

t_token AlexicalAnalizer::nextToken(void) {
  t_token token;
  int token2 = -1;

  // Trata comentários
  skipSeparators();
  // Alfa numerico
  if (isalpha(next_char)) {
    // Palavras Reservadas
    char text[MAX_STRING_SIZE];
    // init text
    for (int i=0; i<MAX_STRING_SIZE ;i++) { text[i] = '\0'; }
    int i = 0;
    do {
      text[i++] = next_char;
      next_char = readChar();
    } while (isalnum(next_char) || next_char == '_');
    // discover alpha type
    token = searchKeyWord(text);
    // if is a id, add to table
    if (token == ID) { token2 = searchName(text); }
  }
  // Numeral
  else if (isdigit(next_char)) {
    int n = 0;
    do {
      n = n * 10 + (next_char - '0');
      next_char = readChar();
    } while (isdigit(next_char));

    // update token variables
    token = NUMERAL;
    token2 = addIntConst(n);
  }
  // Stringval
  else if (next_char == '"') {
    char string[MAX_STRING_SIZE + 1];
    int i = 0;
    // to remove '"' from string
    next_char = readChar();
    // store value of string on variable
    do {
      string[i++] = next_char;
      next_char = readChar();
    } while (next_char != '"');
    next_char = readChar();

    // update token variables
    token = STRINGVAL;
    token2 = addStringConst(string);
  } else {
    switch (next_char) {
    /************
     * SIMBOLOS *
     ************/
    case '.':
      next_char = readChar();
      token = DOT;
      break;
    // COLON
    case ':':
      next_char = readChar();
      token = COLON;
      break;
    // SEMI_COLON
    case ';':
      next_char = readChar();
      token = SEMI_COLON;
      break;
    // COMMA
    case ',':
      next_char = readChar();
      token = COMMA;
      break;
    // 'Squares'
    case '[':
      next_char = readChar();
      token = LEFT_SQUARE;
      break;
    case ']':
      next_char = readChar();
      token = RIGHT_SQUARE;
      break;
    // Braces
    case '{':
      next_char = readChar();
      token = LEFT_BRACES;
      break;
    case '}':
      next_char = readChar();
      token = RIGHT_BRACES;
      break;
    // Parenthesis
    case '(':
      next_char = readChar();
      token = LEFT_PARENTHESIS;
      break;
    case ')':
      next_char = readChar();
      token = RIGHT_PARENTHESIS;
      break;
    // Less_than and Less_or_equal
    case '<':
      next_char = readChar();
      token = LESS_THAN;
      if (next_char == '=') {
        token = LESS_OR_EQUAL;
        next_char = readChar();
      }
      break;
    // Greater_than and Greater_or_equal
    case '>':
      next_char = readChar();
      token = GREATER_THAN;
      if (next_char == '=') {
        token = GREATER_OR_EQUAL;
        next_char = readChar();
      }
      break;
    // Not_equal
    case '!':
      next_char = readChar();
      if (next_char == '=') {
        token = NOT_EQUAL;
        next_char = readChar();
      } else {
        token = NOT;
      }
      break;
    // Equals and equal_equal
    case '=':
      next_char = readChar();
      if (next_char == '=') {
        token = EQUAL_EQUAL;
        next_char = readChar();
      } else {
        token = EQUALS;
      }
      break;
    // Plus and plus_plus
    case '+':
      next_char = readChar();
      if (next_char == '+') {
        token = PLUS_PLUS;
        next_char = readChar();
      } else {
        token = PLUS;
      }
      break;
    // Minus and minus_minus
    case '-':
      next_char = readChar();
      if (next_char == '-') {
        token = MINUS_MINUS;
        next_char = readChar();
      } else {
        token = MINUS;
      }
      break;
    // Times
    case '*':
      next_char = readChar();
      token = TIMES;
      break;
    // Divide
    case '/':
      next_char = readChar();
      token = DIVIDE;
      break;
    /********************
     * Tokens Regulares *
     ********************/
    // Character
    case '\'':
      next_char = readChar();
      // update token variable
      token = CHARACTER;
      token2 = addCharConst(next_char);
      next_char = readChar();
      if ('\'' != next_char)
        token = UNKNOWN;
      next_char = readChar();
      break;
    }
  }
  // Checa se o código já foi lido
  if (end_of_code) { return END_OF_CODE; }

  // setup last token variables
  last_token = token;
  last_token2 = token2;

  return token;
}

void AlexicalAnalizer::print(t_token t) {
  switch(t) {
    // palavras reservadas
    case ARRAY:
      printf("ARRAY\n");
      break;
    case BOOLEAN:
      printf("BOOLEAN\n");
      break;
    case BREAK:
      printf("BREAK\n");
      break;
    case CHAR:
      printf("CHAR\n");
      break;
    case CONTINUE:
      printf("CONTINUE\n");
      break;
    case DO:
      printf("DO\n");
      break;
    case ELSE:
      printf("ELSE\n");
      break;
    case FALSE:
      printf("FALSE\n");
      break;
    case FUNCTION:
      printf("FUNCTION\n");
      break;
    case IF:
      printf("IF\n");
      break;
    case INTEGER:
      printf("INTEGER\n");
      break;
    case OF:
      printf("OF\n");
      break;
    case STRING:
      printf("STRING\n");
      break;
    case STRUCT:
      printf("STRUCT\n");
      break;
    case TRUE:
      printf("TRUE\n");
      break;
    case TYPE:
      printf("TYPE\n");
      break;
    case VAR:
      printf("VAR\n");
      break;
    case WHILE:
      printf("WHILE\n");
      break;
    // simbolos
    case COLON:
      printf("COLON\n");
      break;
    case SEMI_COLON:
      printf("SEMI_COLON\n");
      break;
    case COMMA:
      printf("COMMA\n");
      break;
    case EQUALS:
      printf("EQUALS\n");
      break;
    case LEFT_SQUARE:
      printf("LEFT_SQUARE\n");
      break;
    case RIGHT_SQUARE:
      printf("RIGHT_SQUARE\n");
      break;
    case LEFT_BRACES:
      printf("LEFT_BRACES\n");
      break;
    case RIGHT_BRACES:
      printf("RIGHT_BRACES\n");
      break;
    case LEFT_PARENTHESIS:
      printf("LEFT_PARENTHESIS\n");
      break;
    case RIGHT_PARENTHESIS:
      printf("RIGHT_PARENTHESIS\n");
      break;
    case AND:
      printf("AND\n");
      break;
    case OR:
      printf("OR\n");
      break;
    case LESS_THAN:
      printf("LESS_THAN\n");
      break;
    case GREATER_THAN:
      printf("GREATER_THAN\n");
      break;
    case LESS_OR_EQUAL:
      printf("LESS_OR_EQUAL\n");
      break;
    case GREATER_OR_EQUAL:
      printf("GREATER_OR_EQUAL\n");
      break;
    case NOT_EQUAL:
      printf("NOT_EQUAL\n");
      break;
    case EQUAL_EQUAL:
      printf("EQUAL_EQUAL\n");
      break;
    case PLUS:
      printf("PLUS\n");
      break;
    case PLUS_PLUS:
      printf("PLUS_PLUS\n");
      break;
    case MINUS:
      printf("MINUS\n");
      break;
    case MINUS_MINUS:
      printf("MINUS_MINUS\n");
      break;
    case TIMES:
      printf("TIMES\n");
      break;
    case DIVIDE:
      printf("DIVIDE\n");
      break;
    case DOT:
      printf("DOT\n");
      break;
    case NOT:
      printf("NOT\n");
      break;
    // tokens regulare
    case CHARACTER:
      printf("CHARACTER\n");
      break;
    case NUMERAL:
      printf("NUMERAL\n");
      break;
    case STRINGVAL:
      printf("STRINGVAL\n");
      break;
    case ID:
      printf("ID\n");
      break;
    // grammar token
    case P:
      printf("case\n");
      break;
    case LDE:
      printf("LDE\n");
      break;
    case DV:
      printf("DV\n");
      break;
    case T:
      printf("case\n");
      break;
    // token deconhecido
    case UNKNOWN:
      printf("UNKNOWN\n");
      break;
    case END_OF_CODE:
      printf("END_OF_CODE\n");
      break;
    default:
      printf("O.o\n");
  }
}
