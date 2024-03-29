#include "../include/token.h"

#include <sstream>


using namespace std;


Token::Token(TokenType type, string lexeme, string literal, int line) {
    this->type = type;
    this->lexeme = lexeme;
    this->literal = literal;
    this->line = line;
};
 
string Token::toString(){
    stringstream ss;


    ss << this->type << " " << this->lexeme << " "; 
    if (this->literal == "") {
        ss << "*null*";
    } else {
        ss << this->literal;
    }

    ss << endl;
    
    return ss.str();
};
