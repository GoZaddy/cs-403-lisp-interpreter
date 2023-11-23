#pragma once

#include "include/interpreter.h"
#include "include/lox_callable.h"
#include <string>
#include "include/types.h"
#include <vector>
#include <chrono>

typedef std::chrono::milliseconds milliseconds;

class Clock : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

// class CallableWrapper: public LoxCallable{
//     private:
//         int arityProp;
//         std::string toStringProp;
//     public:
//         CallableWrapper (int arityProp, std::string toStringProp, rv (func*) ){

//         }
//         int arity();

//         rv call(
//             Interpreter* interpreter,
//             std::vector<Exprvp> arguments,
//             Token calleeToken
//         );

//         std::string toString();
// }


class Add : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class Sub : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class Divide : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class Mul : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class Greater : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class GreaterEqual : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class Less : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class LessEqual : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class Equal : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class And : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};

class Or : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class Not : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class Number : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class Symbol : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class Nil : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};



class List : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};



class Cond : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class MakeList : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class Car : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};


class Cdr : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};



class Cons : public LoxCallable{
    public:
        int arity();

        rv call(
            Interpreter* interpreter,
            std::vector<Exprvp> arguments,
            Token calleeToken
        );

        std::string toString();
};