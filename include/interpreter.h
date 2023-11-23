#pragma once


#include <iostream>
#include "include/util.h"
#include <cstdlib>
#include "include/types.h"
#include <vector>
#include "include/environment.h"
#include "include/native_funcs.h"
#include "include/lox_callable.h"
#include "include/lox_function.h"
#include <sstream>

class Interpreter : public ExprVisv{
    private:
        Environment* environment; // TODO: I wonder if this causes issues

        std::unordered_map<Exprvp, int> locals;

        rv evaluate(Exprvp expr);
        bool isTruthy(rv object);

        bool isStringLiteral(string literal);

        bool isNumberLiteral(string literal);

        bool isCallable(string expr);

        bool isList(string expr);

        bool isConsCell(rv expr);

        bool isEqual(rv a, rv b);

        bool isSymbol(string expr);

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

        rv visit(Printvp expr);

        void resolve(Exprvp expr, int depth);

        friend class Add;

        friend class Sub;

        friend class Mul;

        friend class Divide;

        friend class Equal;

        friend class GreaterEqual;

        friend class Greater;

        friend class LessEqual;

        friend class Less;

        friend class And;

        friend class Or;

        friend class Not;

        friend class Number;

        friend class Symbol;

        friend class Nil;

        friend class List;

        friend class LoxFunction;

        friend class Cond;

        friend class MakeList;

        friend class Car;

        friend class Cdr;

        friend class Cons;

};