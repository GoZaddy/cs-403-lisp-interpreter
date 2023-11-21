#ifndef TOKEN_H
#define TOKEN_H

#include <string>



enum TokenType {
  // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN,
  DOT, MINUS, PLUS, SLASH, STAR,

  // One or two character tokens.
  EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  IDENTIFIER, STRING, NUMBER, 

  // LISP SPECIFIC STUFF
  CELL, NIL,

  // Keywords.
  FALSE, DEFINE, TRUE, COND, SET,

  END_OF_FILE
};


class Token {
    public:
        TokenType type;
        std::string lexeme;
        std::string literal;
        int line;

        Token(TokenType type, std::string lexeme, std::string literal, int line);
        Token() = default;
        std::string toString();
};

#endif