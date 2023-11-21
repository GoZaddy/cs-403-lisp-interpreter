#ifndef INTERPRETER_H
#define INTERPRETER_H


#include <iostream>
#include "util.h"
#include <cstdlib>
#include "types.h"
#include <vector>
#include "environment.h"
#include "native_funcs.h"
#include "lox_callable.h"
#include "lox_function.h"

class Interpreter : public ExprVisv{
    private:
        Environment* environment; // TODO: I wonder if this causes issues

        std::unordered_map<Exprvp, int> locals;

        rv evaluate(Exprvp expr);
        bool isTruthy(rv object);

        bool isStringLiteral(string literal);

        bool isNumberLiteral(string literal);

        bool isCallable(string expr);

        bool isEqual(rv a, rv b);

        void checkNumberOperand(Token operatorToken, rv operand);

        void checkNumberOperands(Token operatorToken, rv left, rv right);

        string stripTrailingZeroes(rv text);

        rv lookUpVariable(Token name, Exprvp expr);

        
    public:
        Environment* globals;
        

        Interpreter();
        void interpret(std::vector<Exprvp> statements);

        rv executeBlock(
            Exprvp statements,
            Environment* environment
        );


        rv visit(Litv* expr);

        rv visit(Groupv* expr);

        rv visit(Callvp expr);

        rv visit(Variablevp expr);

        rv visit(Setvp stmt);

        rv visit(Functionvp stmt);

        rv visit(Opvp expr);

        void resolve(Exprvp expr, int depth);

        friend class Add;

        // friend class Sub;

        // friend class Mul;

        // friend class Divide;

        // friend class Equal;

        // friend class GreaterEqual;

        // friend class Greater;

        // friend class LessEqual;

        // friend class Less;

};


#endif