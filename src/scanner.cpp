#include "../include/scanner.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "../include/util.h"
#include "../include/token.h"

using namespace std;


const unordered_map<string, TokenType> Scanner::keywords = {
        {"nil", NIL},
        {"define", DEFINE},
        {"set", SET},
};

Scanner::Scanner (string source) {
    this->source = source;
}

vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        // We are at the beginning of the next lexeme.
        start = current;
        scanToken();
    }


    tokens.push_back(Token(END_OF_FILE, "", "", line));

    return tokens;
};

bool Scanner::isAtEnd(){
    return current >= source.length();
}

char Scanner::advance() {
    return source.at(current++);
}

void Scanner::addToken(TokenType type) {
    addToken(type, "");
}

void Scanner::addToken(TokenType type, string literal) {
    string text = source.substr(start, current-start);
    Token t(type, text, literal, line);
    tokens.push_back(t);
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_' || c == '?';
}

bool Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isdigit(c);
}

bool Scanner::match(char expected) {
    if (isAtEnd()) {return false;}
    if (source.at(current) != expected) {return false;}

    current++;
    return true;
}

char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source.at(current);
}

char Scanner::peekNext() {
    if (current + 1 >= source.length()) return '\0';
    return source.at(current + 1);
}

void Scanner::stringFunc() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }

    if (isAtEnd()) {
        Util::error(line, "Unterminated string.");
        return;
    }

    // The closing ".
    advance();

    // don't trim the surrounding quotes.
    string val = source.substr(start, current - start);
    addToken(STRING, val);
}


void Scanner::number(){
    while (isdigit(peek())) {
        advance();
    }

    // Look for a fractional part.
    if (peek() == '.' && isdigit(peekNext())) {
        // Consume the "."
        advance();

        while (isdigit(peek())) advance();
    }

    addToken(
            NUMBER,
            source.substr(start, current-start)
    );
}

void Scanner::identifier(){
    while (isAlphaNumeric(peek())){ advance();}

    string text = source.substr(start, current-start);
    string key;
    for(int i = 0; i < text.size(); ++i){
        key += tolower(text[i]);
    }
    if (keywords.find(key) != keywords.end()){
        addToken(keywords.at(key));
    } else {
        addToken(IDENTIFIER);
    }
}

void Scanner::scanToken(){
    char c = advance();
    switch (c) {
        case '(': 
            if (match(')')){
                addToken(NIL);
            } else {
                addToken(LEFT_PAREN);
            }
            break;
        case ')': addToken(RIGHT_PAREN); break;
        case '-': addToken(MINUS); break;
        case '+': addToken(PLUS); break;
        case '*': addToken(STAR); break;
        case '/': addToken(SLASH); break;
        case '=':
            if (match('=')){
                addToken(EQUAL_EQUAL);
            } else {
                Util::error(line, "Unexpected character.");
            }
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL : GREATER);
            break;
        case ';':
            // A comment goes until the end of the line.
            while (peek() != '\n' && !isAtEnd()){
                advance();
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace.
            break;

        case '\n':
            line++;
            break;
        case '"':
            stringFunc();
            break;
        case '\'':
            addToken(QUOTE);
            break;
        default:
            if (isdigit(c)){
                number();
            } else if (isAlpha(c)){ //TODO: need to add "'" to allowed alpha so we can process literals
                identifier();
            } else {
                Util::error(line, "Unexpected character.");
            }
            break;
    }
}