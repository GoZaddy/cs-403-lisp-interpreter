#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <iostream>
#include "token.h"
#include "expr.cpp"
#include "util.h"
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
            if (check(LEFT_PAREN)){
                return call_expr();
            }
            return primary();
        }

        // Stmtvp declaration(){
        //     try {
        //         if (match({LEFT_PAREN})){
        //             // if (match({DEFINE})) return function_stmt();
        //             // if (match({SET})) return varDeclaration();
        //         }
        //         return expressionStatement();
        //     } catch (string error){
        //         synchronize();
        //         return nullptr;
        //     }
        // }


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

        // Stmtvp varDeclaration(){
        //     Token name = consume(IDENTIFIER, "Expect variable name.");

        //     Exprvp initializer = expression();
            

        //     consume(RIGHT_PAREN, "Expect ')' to end SET call");
        //     return new Setv(name, initializer);
        // }


        // Stmtvp expressionStatement() {
        //     Exprvp expr = expression();
        //     Stmtvp stmt = new Expressionv(expr);
        //     return stmt;
        // }

        // Functionvp function_stmt() {
        //     Token name = consume(IDENTIFIER, "Expect function name.");

        //     consume(LEFT_PAREN, "Expect '(' after function name.");
        //     vector<Token> parameters;

        //     while (!check(RIGHT_PAREN)){
        //         if (parameters.size() >= 255) {
        //             Util::error(peek(), "Can't have more than 255 parameters.");
        //         }

        //         parameters.push_back(
        //             consume(IDENTIFIER, "Expect parameter name.")
        //         );
        //     }
        //     consume(RIGHT_PAREN, "Expect ')' after parameters.");

        //     Exprvp body = expression();
        //     return new Functionv(name, parameters, body);
        // }

        Exprvp call_expr() {
            consume(LEFT_PAREN,  "Expect '(' at beginning of call expressions.");

            if (match({DEFINE})){
                return define_rest();
            }

            if (match({SET})){
                return set_rest();
            }

            Exprvp expr = primary();

            vector<Exprvp> arguments;
            while(!check(RIGHT_PAREN)){
                if (arguments.size() >= 255) {
                    Util::error(peek(), "Can't have more than 255 arguments.");
                }
                arguments.push_back(expression());
            }

            consume(RIGHT_PAREN,  "Expect ')' after arguments.");

            return new Callv(expr, arguments);
        }

        Exprvp define_rest(){
            Token funcName = consume(IDENTIFIER, "Expected identifer after define");
            vector<Token> params;

            if (!match({NIL})){
                consume(LEFT_PAREN, "Expected ( after function name");
            
                while(!check(RIGHT_PAREN)){
                    if (params.size() >= 255) {
                        Util::error(peek(), "Can't have more than 255 arguments.");
                    }
                    params.push_back(consume(IDENTIFIER, "Expected identifier as parameter of function"));
                }

                consume(RIGHT_PAREN,  "Expect ')' after function parameters.");
            }
            

            Exprvp function_body = expression();

            consume(RIGHT_PAREN,  "Expect ')' at end of define call.");

            return new Functionv(funcName, params, function_body);
        }

        Exprvp set_rest(){
            Token varName = consume(IDENTIFIER, "Expected identifer for variable name");

            Exprvp value = expression();

            consume(RIGHT_PAREN,  "Expect ')' at end of set call.");

            return new Setv(varName, value);
        }


        Exprvp primary(){
            if (match({QUOTE})){
                return quote();
            }
            

            if (match({NIL})) {
                return new Litv("()");
            }

            // operators
            if (match({
                PLUS, MINUS, SLASH, STAR, EQUAL_EQUAL,
                GREATER, GREATER_EQUAL, LESS, LESS_EQUAL
            })){
                return new Opv(previous());
            }
            

            if (match({NUMBER, STRING})) {
                return new Litv(previous().literal);
            }

            if (match({IDENTIFIER})){
                return new Variablev(previous());
            }

            throw parseError(peek(), "Expect expression");
            return nullptr;
        }

        Exprvp quote(){
            if (match({QUOTE})){
                Exprvp recur = quote();
                if (recur->getType() != "Literal"){
                    throw parseError(peek(), "Expect expression for quote operation");
                }
                return new Litv("(quote "+((Litvp) recur)->value+")");
            }
            if (match({NIL})) {
                return new Litv("()");
            }

            // operators
            if (match({
                PLUS, MINUS, SLASH, STAR, EQUAL_EQUAL,
                GREATER, GREATER_EQUAL, LESS, LESS_EQUAL
            })){
                return new Litv(previous().lexeme);
            }
            

            if (match({NUMBER, STRING})) {
                return new Litv(previous().literal);
            }

            if (match({IDENTIFIER})){
                return new Litv(previous().lexeme);
            }

            if (match({LEFT_PAREN})){
                string list = "(";
                while(!check(RIGHT_PAREN)){
                    Exprvp elem = quote();

                    if (elem->getType() != "Literal"){
                        throw parseError(peek(), "Expect expression for quote operation");
                    }
                    list += ((Litvp) elem)->value + " ";
                }
                consume(RIGHT_PAREN, "Expect ')' at end of list literal");

                list.pop_back(); // remove trailing space character
                list += ")";

                return new Litv(list);
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

        vector<Exprvp> parse(){
            vector<Exprvp> expr;
            try{
                while (!isAtEnd()){
                    expr.push_back(expression());
                }
            } catch(string error){
                std::cerr << error << endl;
            }
            
            

            return expr;
        }
};


#endif