#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <iostream>
#include "token.h"
#include "expr.cpp"
#include "util.h"
#include "stmt.cpp"
#include "types.h"


class Parser {
    private:
        std::vector<Token> tokens;
        int current = 0;


        bool isAtEnd(){
            return peek().type == END_OF_FILE;
        }

        Token peek(){
            return tokens[current];
        }

        Token previous(){
            if (current == 0) {cout << "invalid call to previous() because current is 0" << endl;}
            return tokens[current-1];
        }

        bool check(TokenType type){
            if (isAtEnd()) return false;
            return peek().type == type;
        }

        Token advance(){
            if (!isAtEnd()) current++;
            return previous();
        }

        bool match(initializer_list<TokenType> types){
            for (auto type : types){
                if (check(type)){
                    advance();
                    return true;
                }
            }

            return false;
        }

        string parseError(Token token, string message){
            Util::error(token, message);
            return "Parse Error occurred!";
        }

        Exprvp expression(){
            if (match({LEFT_PAREN})){
                return expression();
            }
            return call_expr();
        }

        Stmtvp declaration(){
            try {
                if (match({LEFT_PAREN})){
                    if (match({DEFINE})) return function_stmt();
                    if (match({SET})) return varDeclaration();
                }
                return expressionStatement();
            } catch (string error){
                synchronize();
                return nullptr;
            }
        }


        // Stmtvp ifStatement() {
        //     consume(LEFT_PAREN, "Expect '(' after 'if'.");
        //     Exprvp condition = expression();
        //     consume(RIGHT_PAREN, "Expect ')' after if condition."); 

        //     Stmtvp thenBranch = statement();
        //     Stmtvp elseBranch = nullptr;
        //     if (match({ELSE})) {
        //         elseBranch = statement();
        //     }

        //     return new Ifv(condition, thenBranch, elseBranch);
        // }

        Stmtvp varDeclaration(){
            Token name = consume(IDENTIFIER, "Expect variable name.");

            Exprvp initializer = expression();
            

            consume(RIGHT_PAREN, "Expect ')' to end SET call");
            return new Setv(name, initializer);
        }


        Stmtvp expressionStatement() {
            Exprvp expr = expression();
            Stmtvp stmt = new Expressionv(expr);
            return stmt;
        }

        Functionvp function_stmt() {
            Token name = consume(IDENTIFIER, "Expect function name.");

            consume(LEFT_PAREN, "Expect '(' after function name.");
            vector<Token> parameters;

            while (!check(RIGHT_PAREN)){
                if (parameters.size() >= 255) {
                    Util::error(peek(), "Can't have more than 255 parameters.");
                }

                parameters.push_back(
                    consume(IDENTIFIER, "Expect parameter name.")
                );
            }
            consume(RIGHT_PAREN, "Expect ')' after parameters.");

            Exprvp body = expression();
            return new Functionv(name, parameters, body);
        }

        Exprvp call_expr() {
            Exprvp expr = primary();

            vector<Exprvp> arguments;
            while(!check(RIGHT_PAREN)){
                if (arguments.size() >= 255) {
                    Util::error(peek(), "Can't have more than 255 arguments.");
                }
                arguments.push_back(expression());
            }

            cout << "exit out" << endl;

            Token paren = consume(RIGHT_PAREN,  "Expect ')' after arguments.");

            return new Callv(expr, paren, arguments);
        }

        Exprvp primary(){
            if (match({FALSE})) {
                return new Litv("'f");
            }

            if (match({TRUE})) {
                return new Litv("'t");
            }

            if (match({NIL})) {
                return new Litv("()");
            }

            // operators
            if (match({PLUS, MINUS, SLASH, STAR, EQUAL_EQUAL})){
                cout << "match op: " << previous().lexeme << endl;
                return new Opv(previous());
            }
            

            if (match({NUMBER, STRING})) {
                cout << "match number or string" << endl;
                return new Litv(previous().literal);
            }

            if (match({IDENTIFIER})){
                return new Variablev(previous());
            }

            throw parseError(peek(), "Expect expression");
            return nullptr;
        }

        Token consume(TokenType type, string message){
            if (check(type)) return advance();

            throw parseError(peek(), message);
        }

        void synchronize(){
            // advance();

            // while (!isAtEnd()){
            //     if (previous().type == SEMICOLON) return;

            //     switch (peek().type){
            //         case CLASS:
            //         case FUN:
            //         case VAR:
            //         case FOR:
            //         case IF:
            //         case WHILE:
            //         case PRINT:
            //         case RETURN:
            //             return;
            //     }

            //     advance();
            // }
        }

    public:
        Parser(std::vector<Token> tokens){
            this->tokens = tokens;
        }

        vector<Stmtvp> parse(){
            vector<Stmtvp> expr;
            try{
                while (!isAtEnd()){
                    expr.push_back(declaration());
                }
            } catch(string error){
                std::cerr << error << endl;
            }
            
            

            return expr;
        }
};


#endif